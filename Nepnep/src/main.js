import { WASI } from '@wasmer/wasi'

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

loadWasmStreaming('wasm/SandBox.wasm')
    .then(obj => {
        console.log(obj)
    })
