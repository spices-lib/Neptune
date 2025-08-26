import type { NextConfig } from 'next'

const nextConfig: NextConfig = {

    async redirects() {
        return [
            {
                source: "/",
                destination: "/dashboard",
                permanent: true,
            },
        ];
    },

    async headers() {
        return [
            {
                source: '/(.*)',
                headers: [
                    {
                        key: 'Cross-Origin-Opener-Policy',
                        value: 'same-origin',
                    },
                    {
                        key: 'Cross-Origin-Embedder-Policy',
                        value: 'require-corp',
                    },
                    {
                        key: 'Cross-Origin-Resource-Policy',
                        value: 'cross-origin',
                    },
                ],
            },
        ]
    },
    
    reactStrictMode: true,
    devIndicators: false,
    poweredByHeader: false,
    trailingSlash: false,
}

export default nextConfig
