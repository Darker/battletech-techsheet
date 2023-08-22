import cellFromElm from "./cellFromElm.js";

export default function cellFromText(text, className = "") {
    return cellFromElm(new Text(text), className);
}