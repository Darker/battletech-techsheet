/**
 * 
 * @param {HTMLElement} node node to append
 * @param {string|string[]} className class or class names to assign
 * @returns {HTMLTableCellElement}
 */
export default function cellFromElm(node, className = "") {
    const td = document.createElement("td");
    td.appendChild(node);
    if(typeof className == "string") {
        td.className = className;
    }
    else if(className instanceof Array) {
        td.classList.add(...className);
    }
    return td;
}