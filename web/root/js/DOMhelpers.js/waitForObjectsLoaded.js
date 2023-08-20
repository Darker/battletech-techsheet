

function waitForObjectsLoad(cssSelector) {
    /** @type {HTMLObjectElement[]} **/
    const objects = [...document.querySelectorAll(cssSelector)];

    if (objects.every(object => object.contentDocument && object.contentDocument.readyState === 'complete')) {
        return Promise.resolve(objects);
    }

    return new Promise(resolve => {
        const checkObjectsLoaded = () => {
            if (objects.every(object => object.contentDocument && object.contentDocument.readyState === 'complete')) {
                resolve(objects); // All objects are loaded
            }
        };

        for(const obj of objects) {
            obj.addEventListener("load", checkObjectsLoaded, {once: true});
        }

        // Check initially in case some objects are already loaded
        checkObjectsLoaded();
    });
}

export default waitForObjectsLoad;