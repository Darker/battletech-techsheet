

/**
 * @typedef {Object} HealthPOD
 * @prop {number} max
 * @prop {number} current
 * @prop {number} staging
 */

/**
 * @typedef {{internal:{[segment:string]:HealthPOD}, armor:{[segment:string]:HealthPOD}}} AllHealthPOD
 */