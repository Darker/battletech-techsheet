/**
 * @typedef {import("./TechsheetAPI.js").default} TechsheetAPI
 **/

class ComponentRef {
    /**
     * 
     * @param {TechsheetAPI} techsheetAPI 
     * @param {number} id
     */
    constructor(techsheetAPI, id) {
        this.techsheet = techsheetAPI;
        this.id = id;

        this.invalid = false;
    }
    get _ref() {
        const data = this.techsheet.Module.getComponent(this.id);
        if(data.has_value()) {
            return data;
        }
        else {
            data.delete();
            return null;
        }
    }
    readComponent(callback) {
        const ref = this._ref;
        if(ref) {
            const res = callback(ref.value());
            ref.delete();
            return res;
        }
        else {
            throw new Error("invalid component id "+this.id);
        }
    }
    get name() {
        return this.readComponent(x=>x.name);
    }
    get position() {
        return this.readComponent(x=>x.position);
    }
    /** @type {string} **/
    get description() {
        return this.readComponent(x=>x.description);
    }
    isWeapon() {
        return this.readComponent(x=>x.isWeapon());
    }
    isValid() {
        return this.readComponent(x=>x.isValid());
    }
};

export default ComponentRef;