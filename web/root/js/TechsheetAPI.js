import ComponentRef from "./ComponentRef.js";
import WeaponRef from "./WeaponRef.js";
import { wrapVectorResult } from "./cppWrapUtil.js";
import { TYPES, cwrap, CType } from "./wasmWrap.js";

/**
 * @typedef {Object} CritOption
 * @prop {number} component
 * @prop {{min:number, max: number}} range
 * @prop {boolean} alreadyDestroyed
 */
/** @type {CritOption} **/
const _CritOption = null;
const T_CritOption = new CType("CritOption", _CritOption);

class TechsheetAPI {
    constructor(asmModule) {
        this.Module = asmModule;
        this.initStructureInternal = cwrap(asmModule, "initStructureInternal", TYPES.int, TYPES.string, TYPES.int);
        this.getStructureInternal = cwrap(asmModule, "getStructureInternal", TYPES.int, TYPES.string);
        this.initStructureArmor = cwrap(asmModule, "initStructureArmor", TYPES.int, TYPES.string, TYPES.int);
        this.getStructureArmor = cwrap(asmModule, "getStructureArmor", TYPES.int, TYPES.string);
        this.getInternalNames = wrapVectorResult(asmModule, "getInternalNames", TYPES.string);
        this.getArmorNames = wrapVectorResult(asmModule, "getArmorNames", TYPES.string);
        this.unstageDamage = cwrap(asmModule, "unstageDamage", TYPES.void_t);
        this.getTotalJumpPower = cwrap(asmModule, "getTotalJumpPower", TYPES.int);
        this._parseMech = cwrap(asmModule, "parseMech", TYPES.bool, TYPES.string);
        this.getComponentIds = wrapVectorResult(asmModule, "getComponents", TYPES.int);
        this.getWeaponIds = wrapVectorResult(asmModule, "getWeapons", TYPES.int);
        this.endTurn = cwrap(asmModule, "endTurn", TYPES.void_t);
        this._getCritOptions = wrapVectorResult(asmModule, "getCritOptions", T_CritOption, TYPES.string);
    }

    /**
     * 
     * @param {string} partName 
     * @returns {HealthPOD}
     */
    getHealthInternal(partName) {
        const hp = this.Module.getHealthInternal(partName);
        const res = {current: hp.current.value, max: hp.max.value, staging: hp.staging.value};
        hp.delete();
        return res;
    }

    receiveCrit(partName, diceRoll, execute = true) {
        const res = this.Module.receiveCrit(partName, diceRoll, execute);
        const resObj = {component: res.component, invalid: !!res.invalid, rollAgain: !!res.rollAgain};
        res.delete();
        return resObj;
    }

    /**
     * 
     * @param {string} partName 
     * @param {boolean} fromCritical if caused by a critical hit
     * @returns 
     */
    destroyAppendage(partName, fromCritical) {
        const res = this.Module.destroyAppendage(partName, fromCritical);
        const resObj = {success: res.first, damage: res.second.value};
        res.delete();
        if(!resObj.success) {
            console.warn(`Invalid limb destruction at ${partName}`)
        }
        return resObj;
    }
    /**
     * 
     * @param {string} partName 
     * @returns {CritOption[]}
     */
    getCritOptions(partName) {
        console.log("Loading crit options: ", partName);
        const opts = this._getCritOptions(partName);
        return opts.map(x=>({component: x.component.value, range: {min: x.range.min, max: x.range.max}, alreadyDestroyed:x.alreadyDestroyed}));
    }
    /**
     * 
     * @param {string} part 
     * @param {number} amount 
     * @param {boolean} staging 
     * @returns {DamageResult}
     */
    receiveDamage(part, amount, staging = false) {
        const res = this.Module.receiveDamage(part, amount, staging);
        const resStatus = {
            criticalHit: res.criticalHit,
            criticalSegment: res.criticalSegment,
            mechDestroyed: res.mechDestroyed,
            partDestroyed: res.partDestroyed,
            psrRequired: res.psrRequired
        };
        res.delete();
        return resStatus;
    }

    *getComponents() {
        const ids = this.getComponentIds();
        for(const id of ids) {
            yield new ComponentRef(this, id);
        }
    }

    *getWeapons() {
        const ids = this.getWeaponIds();
        for(const id of ids) {
            yield new WeaponRef(this, id);
        }
    }

    /**
     * 
     * @param {string} partName 
     * @returns {HealthPOD}
     */
    getHealthArmor(partName) {
        const hp = this.Module.getHealthArmor(partName);
        const res = {current: hp.current.value, max: hp.max.value, staging: hp.staging.value};
        hp.delete();
        return res;
    }

    *allStructureCurrent() {
        const names = this.getInternalNames();
        for(const name of names) {
            yield {name, currentHealth: this.getStructureInternal(name)};
        }
    }

    *allInternal() {
        const names = this.getInternalNames();
        for(const name of names) {
            yield {name, health: this.getHealthInternal(name)};
        }
    }
    *allArmor() {
        const names = this.getArmorNames();
        for(const name of names) {
            yield {name, health: this.getHealthArmor(name)};
        }
    }

    /**
     * 
     * @param {string} fileText 
     */
    parseMech(fileText) {
        const res = this._parseMech(fileText);
        return res;
    }
    /**
     * 
     * @returns {{internal:{[segment:string]:HealthPOD}, armor:{[segment:string]:HealthPOD}}}
     */
    allHealth() {
        const res = {armor:{}, internal:{}};
        for(const v of this.allArmor()) {
            res.armor[v.name] = v.health;
        }
        for(const v of this.allInternal()) {
            res.internal[v.name] = v.health;
        }
        return res;
    }
};

export default TechsheetAPI;