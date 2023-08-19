/**
 * @typedef {import("./TechsheetAPI.js").default} TechsheetAPI
 **/

import MechDots from "./rendering/MechDots.js";

/**
 * @typedef {{[segment: string]:MechDots[]}} HealthView
 */

/**
 * @param {SVGRectElement} rect
 * @param {HealthView} target
 */
function populateHealthRenderer(rect, target) {
    const name = rect.id.replace(/^(ARMOR_|INTERNAL_)/, "");
    if(typeof target[name] != "object") {
        target[name] = [];
    }
    const res = new MechDots(name, rect);
    target[name].push(res);
    return res;
}



class MechRenderer {
    /**
     * @param {TechsheetAPI} cppApi
     * @param {HTMLObjectElement[]} mechViews 
     */
    constructor(cppApi, mechViews) {
        this.views = mechViews;
        this.techsheet = cppApi;
        this.currentDamageTarget = "";

        /** @type {HealthView} **/
        this.internal = {};
        /** @type {HealthView} **/
        this.armor = {};

        this.stagedDamage = {};
    }
    init() {
        for(const v of this.views) {
            /** @type {Document} **/
            const svg = v.contentDocument;
            const dotSizeConfig = v.getAttribute("data-dotsize");

            for(const rect of svg.querySelectorAll("rect")) {
                let dots = null;
                if(rect.id.startsWith("ARMOR_")) {
                    dots = populateHealthRenderer(rect, this.armor); 
                }
                else if(rect.id.startsWith("INTERNAL_")) {
                    dots = populateHealthRenderer(rect, this.internal);                    
                }
                if(dots) {
                    if(dotSizeConfig) {
                        dots.dotRadius = Number.parseFloat(dotSizeConfig);
                    }
                    dots.populate();
                }
            }
            // listen on clicks on all rects and filter out damage selection
            svg.firstElementChild.addEventListener("click", (e) => {
                const tgt = e.target;
                console.log(tgt);
                if(tgt.id && tgt.id.startsWith("ARMOR_")) {
                    this.setDamageTarget(tgt.id.replace("ARMOR_", ""));
                }
            });
        }
    }
    setDamageTarget(name) {
        this.currentDamageTarget = name;
        console.log("Targeting "+name);
    }
    /**
     * Stages damage provided a damage target location has been set
     * @param {number} amount 
     */
    stageDamage(amount) {
        if(this.currentDamageTarget.length > 0) {
            const res = this.techsheet.receiveDamage(this.currentDamageTarget, amount, true);
            console.log(`Stage ${amount} into ${this.currentDamageTarget} -> ${res}`);
            if(!res) {
                throw new Error("Failed to stage damage (unknown reason, probably bad component name.");
            }
            else {
                if(typeof this.stagedDamage[this.currentDamageTarget] != "number") {
                    this.stagedDamage[this.currentDamageTarget] = 0;
                }
                this.stagedDamage[this.currentDamageTarget] += amount;
                this.updateAllHealth();
            }
        }
        else {
            throw new Error("Damage target not set.");
        }
    }
    confirmDamage() {
        let changed = false;
        for(const name of Object.keys(this.stagedDamage)) {
            if(this.stagedDamage[name] > 0) {
                const dmg = this.stagedDamage[name];
                const ok = this.techsheet.receiveDamage(name, this.stagedDamage[name], false);
                if(!ok) {
                    console.error(`Failed to commit damage ${dmg} to ${name}`);
                }
                else {
                    this.stagedDamage[name] = 0;
                    changed = true;
                }
            }
        }

        if(changed) {
            this.updateAllHealth();
        }
    }
    updateAllHealth() {
        this.setAllHealth(this.techsheet.allHealth());
    }
    /**
     * 
     * @param {AllHealthPOD} data 
     */
    setAllHealth(data) {
        for(const [name, value] of Object.entries(data.internal)) {
            if(this.internal[name]) {
                for(const dots of this.internal[name]) {
                    dots.setHealth(value);
                }
            }
        }

        for(const [name, value] of Object.entries(data.armor)) {
            if(this.armor[name]) {
                for(const dots of this.armor[name]) {
                    dots.setHealth(value);
                }
            }
        }
    }

    setInternal(data) {

    }

};

export default MechRenderer;