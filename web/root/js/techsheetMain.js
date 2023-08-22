import MechRenderer from "./MechRenderer.js";
import TechsheetAPI from "./TechsheetAPI.js";
import techsheet from "../techsheet_cli.js";
import waitForObjectsLoad from "./DOMhelpers.js/waitForObjectsLoaded.js";

function waitForDOMContentLoad() {
    if (document.readyState === 'complete') {
        return Promise.resolve(); // DOM content is already loaded
    }

    return new Promise(resolve => {
        document.addEventListener('DOMContentLoaded', () => {
            resolve(); // DOM content has been loaded
        });
    });
}

const modulePromise = techsheet();
async function main() {
    console.log("Main starting");
    const module = await modulePromise;
    const techsheetAPI = new TechsheetAPI(module);
    const objs = await waitForObjectsLoad("object.mech_hp");
    const renderer = new MechRenderer(techsheetAPI, objs);
    renderer.init();

    window.techsheetAPI = techsheetAPI;
    window.mechRenderer = renderer;
    window.addEventListener("techsheet-parse", function(e) {
        techsheetAPI.parseMech(e.detail);
        renderer.setAllHealth(techsheetAPI.allHealth());
        renderer.updateMovement();
        renderer.updateWeapons();
    });
    window.addEventListener("techsheet-dmg-stage", function(e) {
        renderer.stageDamage(e.detail);
    });
    window.addEventListener("techsheet-dmg-unstage", function(e) {
        techsheetAPI.unstageDamage();
        renderer.updateAllHealth();
    });
    window.addEventListener("techsheet-dmg-commit", function(e) {
        renderer.confirmDamage();
    });
}

main();