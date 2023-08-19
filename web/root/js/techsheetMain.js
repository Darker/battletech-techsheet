import MechRenderer from "./MechRenderer.js";
import TechsheetAPI from "./TechsheetAPI.js";

window.addEventListener("techsheet-ready", function(e) {
    main();
});

function main() {
    console.log("Main starting");
    const techsheet = new TechsheetAPI(Module);
    const renderer = new MechRenderer(techsheet, document.querySelectorAll("object.mech_hp"));
    renderer.init();
    console.log([...techsheet.allStructureCurrent()]);
    window.techsheetAPI = techsheet;
    window.mechRenderer = renderer;
    window.addEventListener("techsheet-parse", function(e) {
        techsheet.parseMech(e.detail);
        renderer.setAllHealth(techsheet.allHealth());
    });
    window.addEventListener("techsheet-dmg-stage", function(e) {
        renderer.stageDamage(e.detail);
    });
    window.addEventListener("techsheet-dmg-unstage", function(e) {
        techsheet.unstageDamage();
        renderer.updateAllHealth();
    });
    window.addEventListener("techsheet-dmg-commit", function(e) {
        renderer.confirmDamage();
    });
}

confirmLoad("main");