/**
 * @typedef {import("./TechsheetAPI.js").default} TechsheetAPI
 **/

import cellFromText from "./DOMhelpers.js/cellFromText.js";
import setTextContent from "./DOMhelpers.js/setTextContent.js";
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
        setTextContent(".damage-target-name", name);
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
    updateMovement() {
        setTextContent(".movement-jump-power", this.techsheet.getTotalJumpPower());
    }

    updateWeapons() {
        const list = document.querySelector("#weapon-list");
        while(list.firstChild) {
            list.removeChild(list.firstChild);
        }
        for(const w of this.techsheet.getWeapons()) {
            const row = document.createElement("tr");
            row.appendChild(cellFromText(w.weaponName));
            row.appendChild(cellFromText(w.position));
            row.appendChild(cellFromText(w.readWeapon(x=>x.heatCaused)+""));
            row.appendChild(cellFromText(w.readWeapon(x=>x.totalDamage().value)));
            row.appendChild(cellFromText(w.readWeapon(x=>x.ranges.min().value)));
            row.appendChild(cellFromText(w.readWeapon(x=>x.ranges.sht().value)));
            row.appendChild(cellFromText(w.readWeapon(x=>x.ranges.med().value)));
            row.appendChild(cellFromText(w.readWeapon(x=>x.ranges.lng().value)));
            row.appendChild(cellFromText("-"));
            row.appendChild(cellFromText("-"));
            const fireButton = document.createElement("input");
            //fireButton.addEventListener("click", ())
            fireButton.value = "FIRE";
            const td = document.createElement("td");
            td.appendChild(fireButton);
            row.appendChild(td);
            list.appendChild(row);
        }
    }

    setInternal(data) {

    }

};

export default MechRenderer;