import ComponentRef from "./ComponentRef.js";


class WeaponRef extends ComponentRef {
    constructor(api, id) {
        super(api, id);
    }

    readWeapon(callback) {
        const weaponOpt = this.techsheet.Module.getWeapon(this.id);
        if(weaponOpt.has_value()) {
            const res = callback(weaponOpt.value());
            weaponOpt.delete();
            return res;
        }
        else {
            weaponOpt.delete();
            throw new Error("Invalid weapon ID "+this.id);
        }
    }

    get totalDamage() {
        return this.readWeapon(x=>x.totalDamage());
    }
    get weaponName() {
        return this.readWeapon(x=>x.name);
    }
};

export default WeaponRef;