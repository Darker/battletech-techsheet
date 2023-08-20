import ComponentRef from "./ComponentRef.js";
import WeaponRef from "./WeaponRef.js";
import { wrapVectorResult } from "./cppWrapUtil.js";
import { TYPES, cwrap } from "./wasmWrap.js";

class TechsheetAPI {
    constructor(asmModule) {
        this.Module = asmModule;
        this.initStructureInternal = cwrap(asmModule, "initStructureInternal", TYPES.int, TYPES.string, TYPES.int);
        this.getStructureInternal = cwrap(asmModule, "getStructureInternal", TYPES.int, TYPES.string);
        this.initStructureArmor = cwrap(asmModule, "initStructureArmor", TYPES.int, TYPES.string, TYPES.int);
        this.getStructureArmor = cwrap(asmModule, "getStructureArmor", TYPES.int, TYPES.string);
        this.getInternalNames = wrapVectorResult(asmModule, "getInternalNames", TYPES.string);
        this.getArmorNames = wrapVectorResult(asmModule, "getArmorNames", TYPES.string);
        this.receiveDamage = cwrap(asmModule, "receiveDamage", TYPES.bool, TYPES.string, TYPES.int, TYPES.bool);
        this.unstageDamage = cwrap(asmModule, "unstageDamage", TYPES.void_t);
        this.getTotalJumpPower = cwrap(asmModule, "getTotalJumpPower", TYPES.int);
        this._parseMech = cwrap(asmModule, "parseMech", TYPES.bool, TYPES.string);
        this.getComponentIds = wrapVectorResult(asmModule, "getComponents", TYPES.int);
        this.getWeaponIds = wrapVectorResult(asmModule, "getWeapons", TYPES.int);
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