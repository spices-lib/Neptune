import { defineConfig } from 'vite'
import mkcert from "vite-plugin-mkcert";
import crossOriginIsolation from "vite-plugin-cross-origin-isolation";

const isCodeSandbox = !!process.env.SANDBOX_URL

export default defineConfig({
    root : 'src/',
    publicDir: '../static/',
    base: './',
    server:
    {
        host: true,
        open: !isCodeSandbox,
        https: true
    },
    build:
    {
        outDir: '../dist',
        emptyOutDir: true,
        sourcemap: true,
        target: 'es2022'
    },
    preview: {
        https: true,
        // vite build do not use the plugin: crossOriginIsolation, add headers here.
        headers: {
            'Cross-Origin-Opener-Policy': 'same-origin',
            'Cross-Origin-Embedder-Policy': 'require-corp',
            'Cross-Origin-Resource-Policy': 'same-origin'
        }
    },
    plugins: [
        mkcert(),               // Enable https
        crossOriginIsolation()  // Enable shared buffer
    ]
})