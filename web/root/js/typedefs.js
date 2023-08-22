

/**
 * @typedef {Object} HealthPOD
 * @prop {number} max
 * @prop {number} current
 * @prop {number} staging
 */

/**
 * @typedef {{internal:{[segment:string]:HealthPOD}, armor:{[segment:string]:HealthPOD}}} AllHealthPOD
 */

/**
 * @typedef {Object} DamageResult
 * @property {boolean} criticalHit
 * @property {string} criticalSegment
 * @property {boolean} mechDestroyed
 * @property {boolean} partDestroyed
 * @property {boolean} psrRequired
 * @ method mergeIn
 * @ param {DamageResult} other
 */