import mkcert from "vite-plugin-mkcert";

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
    plugins: [mkcert()]
}