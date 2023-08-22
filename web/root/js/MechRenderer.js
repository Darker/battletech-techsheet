/**
 * @typedef {import("./TechsheetAPI.js").default} TechsheetAPI
 **/

import ComponentRef from "./ComponentRef.js";
import cellFromElm from "./DOMhelpers.js/cellFromElm.js";
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
        /** @type {{[component:number]:number}} number of crits taken in that component **/
        this.thisRoundCrit = {};
        this.pendingCritical = null;
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

        document.getElementById("crit-location-table").addEventListener("click", (e)=>{
            /** @type {HTMLElement} **/
            const tgt = e.target;
            if(tgt.hasAttribute("data-crit-roll")) {
                this.dealCritical(
                    tgt.getAttribute("data-crit-part"),
                    tgt.getAttribute("data-crit-roll")*1,
                    tgt.getAttribute("data-crit-component")*1
                );
            }
            else if(tgt.hasAttribute("data-crit-skip")) {
                this.endCritical();
            }
            else if(tgt.getAttribute("data-destroy-limb") == "crit") {
                this.destroyLimbCritical();
            }
        });
        document.getElementById("weapon-list").addEventListener("click", (e)=>{
            /** @type {HTMLElement} **/
            const tgt = e.target;
            if(tgt.hasAttribute("data-ammo-weapon")) {
                this.selectWeaponAmmo(1 * tgt.getAttribute("data-ammo-weapon"));
            }
        });
        document.getElementById("next-turn").addEventListener("click", ()=>{
            this.endTurn();
        });
    }
    setDamageTarget(name) {
        this.currentDamageTarget = name;
        this.techsheet.unstageDamage();
        this.updateAllHealth();
        setTextContent(".damage-target-name", name);
        console.log("Targeting "+name);
    }
    /**
     * Stages damage provided a damage target location has been set
     * @param {number} amount 
     */
    stageDamage(amount) {
        if(this.pendingCritical) {
            throw new Error("Cannot stage damage until a crit is handled.");
        }

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
        if(this.pendingCritical) {
            throw new Error("Cannot deal damage until a crit is handled.");
        }

        let changed = false;
        for(const name of Object.keys(this.stagedDamage)) {
            if(this.stagedDamage[name] > 0) {
                const dmg = this.stagedDamage[name];
                const result = this.techsheet.receiveDamage(name, dmg, false);
                console.log(`Dealt ${dmg} into ${name} ->`, result);

                this.stagedDamage[name] = 0;
                changed = true;
                
                if(result.criticalHit) {
                    this.pendingCritical = result.criticalSegment;
                    break;
                }
            }
        }

        if(changed) {
            this.updateAll();
        }
    }
    /**
     * 
     * @param {string} segment 
     * @param {number} critLoc 
     * @param {number} componentId 
     */
    dealCritical(segment, critLoc, componentId) {
        const res = this.techsheet.receiveCrit(segment, critLoc);
        if(res.invalid) {
            console.error("Invalid roll ",segment, critLoc)
        }
        else {
            if(typeof this.thisRoundCrit[componentId] != "number") {
                this.thisRoundCrit[componentId] = 0;
            }
            this.thisRoundCrit[componentId]++;
            this.updateAll();
        }
    }
    destroyLimbCritical() {
        this.techsheet.destroyAppendage(this.pendingCritical, true);
        this.endCritical();
    }
    /**
     * End the phase of resolving a critical hit
     */
    endCritical() {
        document.body.classList.remove("pending-crit-"+this.pendingCritical);
        this.pendingCritical = null;
        this.updateAll();
    }
    selectWeaponAmmo(weaponId) {
        throw new Error("Ammo selection not implemented yet.");
    }
    fireWeapon(weaponId) {
        throw new Error("Weapon firing not implemented yet.");
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
            const rowCls = ["status-"+w.readComponent(x=>x.status), "weapon"];
            if(w.readWeapon(x=>x.fired))
                rowCls.push("fired");
            row.classList.add(...rowCls);

            row.appendChild(cellFromText(w.weaponName, "name"));
            row.appendChild(cellFromText(w.position));
            row.appendChild(cellFromText(w.readWeapon(x=>x.heatCaused)+""));
            row.appendChild(cellFromText(w.readWeapon(x=>x.totalDamage().value)));
            row.appendChild(cellFromText(w.readWeapon(x=>x.ranges.min().value)));
            row.appendChild(cellFromText(w.readWeapon(x=>x.ranges.sht().value)));
            row.appendChild(cellFromText(w.readWeapon(x=>x.ranges.med().value)));
            row.appendChild(cellFromText(w.readWeapon(x=>x.ranges.lng().value)));

            
            if(w.readWeapon(x=>x.usesAmmo)) {
                let ammoCell = null;
                const ammoComponent = w.readWeapon(x=>x.ammoBin).value;
                let ammoCount = -1;
                if(ammoComponent != 0) {
                    const c = new ComponentRef(this.techsheet, ammoComponent);
                    if(!c.isDestroyed()) {
                        ammoCount = c.readComponent(x=>x.ammo.value);
                    }
                }
                if(ammoCount >= 0) {
                    ammoCell = cellFromText(ammoCount+"");
                }
                else {
                    ammoCell = cellFromText("?");
                }
                ammoCell.classList.add("ammo-control");
                ammoCell.setAttribute("data-ammo-id", ammoComponent);
                ammoCell.setAttribute("data-ammo-weapon", w.id);
            }
            else {
                row.appendChild(cellFromText("-"));
            }

            row.appendChild(cellFromText("-"));
            const fireButton = document.createElement("input");
            //fireButton.addEventListener("click", ())
            fireButton.value = "FIRE";
            fireButton.type = "button";
            fireButton.className = "fire";
            fireButton.disabled = w.readComponent(x=>x.isDestroyed());
            fireButton.setAttribute("data-weapon-id", w.id);
            const td = document.createElement("td");
            td.appendChild(fireButton);
            row.appendChild(td);
            list.appendChild(row);
        }
    }
    updateCritical() {
        const list = document.querySelector("#crit-locations");
        while(list.firstChild) {
            list.removeChild(list.firstChild);
        }
        list.classList.remove("is-limb");

        if(this.pendingCritical) {
            
            // populate table
            const opts = this.techsheet.getCritOptions(this.pendingCritical);
            if(opts.length == 0) {
                document.body.classList.remove("pending-crit", "pending-crit-"+this.pendingCritical);
                this.pendingCritical = null;
            }
            else {
                document.body.classList.add("pending-crit", "pending-crit-"+this.pendingCritical);

                if(this.pendingCritical == "HEAD" || this.pendingCritical.endsWith("L") || this.pendingCritical.endsWith("A")) {
                    list.classList.add("is-limb");
                }

                for(const opt of opts) {
                    const row = document.createElement("tr");
                    row.classList.add("row-critical", "option");
                    const component = new ComponentRef(this.techsheet, opt.component);
                    const pos = component.position;
                    const cls = ["crit-name"];
                    if(opt.alreadyDestroyed) {
                        cls.push("destroyed");
                    }
                    row.appendChild(cellFromText(component.description, cls));
                    row.appendChild(cellFromText(pos));
                    row.appendChild(cellFromText(`${opt.range.min} - ${opt.range.max}`));
                    const critButton = document.createElement("input");
                    //fireButton.addEventListener("click", ())
                    critButton.value = "Crit";
                    if(typeof this.thisRoundCrit[opt.component] == "number") {
                        critButton.value += " ("+this.thisRoundCrit[opt.component]+")";
                    }
                    critButton.type = "button";
                    critButton.setAttribute("data-crit-part", pos);
                    critButton.setAttribute("data-crit-roll", opt.range.min);
                    critButton.setAttribute("data-crit-component", opt.component);
                    row.appendChild(cellFromElm(critButton));
                    list.append(row);
                }
                const finalRow = document.createElement("tr");
                
                // end dealing crits
                {
                    
                    const skipButton = document.createElement("input");
                    //fireButton.addEventListener("click", ())
                    skipButton.value = "Done";
                    skipButton.type = "button";
                    skipButton.setAttribute("data-crit-skip", "skip");
                    const cell = cellFromElm(skipButton)
                    cell.colSpan = 3;
                    cell.classList.add("skip-crit");
                    finalRow.appendChild(cell);
                }
                // limb destruction
                {
                    const limbButton = document.createElement("input");
                    //fireButton.addEventListener("click", ())
                    limbButton.value = "DESTROY ALL";
                    limbButton.type = "button";
                    limbButton.setAttribute("data-destroy-limb", "crit");
                    const cell = cellFromElm(limbButton)
                    cell.classList.add("destroy-limb");
                    finalRow.appendChild(cell);
                }
                list.append(finalRow);
            }
        }
        else {
            document.body.classList.remove("pending-crit");
        }
    }
    endTurn() {
        this.thisRoundCrit = {};
        this.techsheet.endTurn();
        this.updateAll();
    }
    updateAll() {
        this.updateAllHealth();
        this.updateMovement();
        this.updateWeapons();
        this.updateCritical();
    }

};

export default MechRenderer;