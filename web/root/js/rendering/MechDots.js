
/**
 * 
 * @param {SVGRectElement} rectangle
 * @param {number} count
 */
function fillDots(rectangle, count, dotRadius = 1.1) {
    const cr = dotRadius;
    const cd = cr * 2;
    // from edge
    const padding = 0.3 + cd/2;
    const YextraPadding = 0.2;
    // between dots
    const margin = 0.5;
    const width = rectangle.getAttribute("width")*1;
    const availWidth = width - padding*2;

    const maxPerLine = Math.floor((availWidth)/(cd+margin));
    const lineWidth = maxPerLine*cd + (maxPerLine-1)*margin;
    const leftPad = (width - lineWidth)/2;

    const cX = rectangle.getAttribute("x")*1;
    const leftEdgeX = cX;
    const startX = leftEdgeX + leftPad;
    const stepX = margin+cd;

    const cY = rectangle.getAttribute("y")*1;
    const startY = cY + padding + YextraPadding;
    const stepY = margin + cd;

    // If count is not set, fill as much as possible
    if(count < 0) {
        const height = rectangle.getAttribute("height")*1;
        const availHeight = height - padding*2;
        count = Math.floor((availHeight)/(cd+margin)) * maxPerLine;
    }
    const circles = [];
    const lines = Math.ceil(count/maxPerLine);
    let dots = 0;
    for(let row = 0; row<lines; ++row) {
        for(let dot = 0; dot<maxPerLine; ++dot) {
            if(dots >= count) {
                break;
            }
            dots++;

            const circle = rectangle.ownerDocument.createElementNS("http://www.w3.org/2000/svg", "circle");
            circle.setAttribute("r", cr+"");
            circle.setAttribute("cx", (dot*stepX + startX)+"");
            circle.setAttribute("cy", (row*stepY + startY)+"");
            circle.style.stroke = "black";
            circle.style.fill = "red";
            circle.style.strokeWidth = "0.1";
            rectangle.parentElement.appendChild(circle);
            circles.push(circle);
        }
    }
    return circles;
}

/**
 * Controls health of a specific component. Expects a SVG rect
 * which represents the component frame, then covers that rect with dots representing health.
 * 
 */
class MechDots {
    /**
     * 
     * @param {string} componentName 
     * @param {SVGRectElement} svgRect 
     */
    constructor(componentName, svgRect) {
        this.name = componentName;
        this.rect = svgRect;
        this.dotRadius = 1.1;
        /** @type {SVGCircleElement[]} **/
        this.dots = [];
        this.health = {max:0, current: 0, staging: 0};
    }
    populate() {
        this.dots = fillDots(this.rect, -1, this.dotRadius);
        this.setStyle("#444", "#AAA");
    }
    /**
     * 
     * @param {{max:number, current:number, staging:number}} health 
     */
    setHealth(health) {
        this.health = health;
        this.setStyle("#000", "#0C0", 0, this.health.current);
        this.setStyle("#000", "#C00", this.health.current, this.health.max);
        if(this.health.current != this.health.staging)
            this.setStyle("#000", "#CC0", this.health.staging, this.health.current);
        this.setStyle("#444", "#AAA", this.health.max);
    }
    setStyle(border, fill, start, end) {
        if(typeof start != 'number') {
            start = 0;
        }
        if(typeof end != 'number') {
            end = this.dots.length;
        }

        end = end < this.dots.length ? end : this.dots.length;

        if(start == end || start > end) {
            return;
        }

        for(; start<end; ++start) {
            const style = this.dots[start].style;
            style.stroke = border;
            style.fill = fill;
        }
    }
};

export default MechDots;