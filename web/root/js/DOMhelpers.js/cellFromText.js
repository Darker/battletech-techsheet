export default function cellFromText(text) {
    const td = document.createElement("td");
    td.appendChild(new Text(text));
    return td;
}