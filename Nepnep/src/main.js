import { WASI } from '@wasmer/wasi';

const wasi = {
    fd_write: () => {},
    fd_read: () => {},
    fd_close: () => {},
    fd_seek: () => {},
    environ_get: () => {},
    environ_sizes_get: () => {},
    proc_exit: () => {},
}

const imports = {
    wasi_snapshot_preview1: wasi
}

async function loadWasmStreaming(url) {
    try {
        // 直接流式编译和实例化
        const { instance } = await WebAssembly.instantiateStreaming(fetch(url), imports);
        return instance;
    } catch (err) {
        console.error('Failed to load wasm:', err);
        throw err;
    }
}

loadWasmStreaming('WebCPP.wasm')
    .then(obj => {

        console.log(obj.exports)

        const exports = obj.exports

        const functionNames = Object.keys(exports).filter(
            key => typeof exports[key] == 'function'
        )
        console.log(functionNames)

        const add = exports._Z3addii
        const wasmMain = exports._Z8wasmMainv
        const main = exports.__original_main

        console.log(add)
        console.log(wasmMain())
        console.log(main())
    })
