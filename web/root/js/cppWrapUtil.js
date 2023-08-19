import {CType} from "./wasmWrap.js"

function* iterStdVector(vector) {
    const size = vector.size();
    for(let i=0; i<size; ++i) {
        yield vector.get(i);
    }
}

/**
 * @template TRet
 * @template T1
 * @template T2
 * @template T3
 * @template T4
 * @template T5
 * @template T6
 * 
 * @param {any} Module wasm main module container
 * @param {string} functionName 
 * @param {CType<TRet>} returnVal vector type
 * @param {CType<T1>} arg1 
 * @param {CType<T2>} arg2 
 * @param {CType<T3>} arg3 
 * @param {CType<T4>} arg4 
 * @param {CType<T5>} arg5 
 * @param {CType<T6>} arg6 
 * 
 * @returns {(arg1: T1, arg2: T2, arg3: T3, arg4: T4, arg5: T5) => TRet[]}
 */
export function wrapVectorResult(module, name, returnVal, arg1, arg2, arg3, arg4, arg5, arg6) {
    return function() {
        const vector = module[name](...arguments);
        /** @type {TRet[]} **/
        const resAr = [...iterStdVector(vector)];
        vector.delete();
        return resAr;
    };
}