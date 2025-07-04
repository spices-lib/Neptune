import { defineConfig } from 'vite'
import mkcert from 'vite-plugin-mkcert'
// @ts-ignore
import crossOriginIsolation from 'vite-plugin-cross-origin-isolation'
import react from '@vitejs/plugin-react'

const isCodeSandbox = !!process.env.SANDBOX_URL
export default defineConfig(({ mode }) => {

    return {
        root : 'src/',
        envDir: '../',
        publicDir: '../static/',
        base: './',
        server:
        {
            host: true,
            open: !isCodeSandbox,
        },
        build:
        {
            outDir: '../dist',
            emptyOutDir: true,
            sourcemap: true,
            target: 'es2022'
        },
        preview: {
            // vite build do not use the plugin: crossOriginIsolation, add headers here.
            headers: {
                'Cross-Origin-Opener-Policy': 'same-origin',
                'Cross-Origin-Embedder-Policy': 'require-corp',
                'Cross-Origin-Resource-Policy': 'same-origin'
            }
        },
        plugins: [
            mkcert(),               // Enable https
            crossOriginIsolation(), // Enable shared buffer
            react()                 // Use React
        ]
    }
})