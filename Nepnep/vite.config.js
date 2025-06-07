import mkcert from "vite-plugin-mkcert";
import crossOriginIsolation from "vite-plugin-cross-origin-isolation";

const isCodeSandbox = !!process.env.SANDBOX_URL

export default {
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
        sourcemap: true
    },
    plugins: [
        mkcert(),               // Enable https
        crossOriginIsolation()  // Enable shared buffer
    ]
}