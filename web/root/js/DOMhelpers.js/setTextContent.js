
/**
 * Writes given content to all matching nodes. Will reuse existing text nodes
 * or create new ones and append at the end
 * @param {string} selector 
 * @param {string} content 
 */
export default function setTextContent(selector, content) {
    const elements = document.querySelectorAll(selector);
  
    for (const element of elements) {
      let textNode = null;
  
      // Find the first text node within the element
      for (const childNode of element.childNodes) {
        if (childNode.nodeType === Node.TEXT_NODE) {
          textNode = childNode;
          break;
        }
      }
  
      if (textNode) {
        // If a text node exists, update its content
        textNode.nodeValue = content;
      } else {
        // If no text node exists, create a new one
        const newTextNode = document.createTextNode(content);
        element.appendChild(newTextNode);
      }
    }
  }