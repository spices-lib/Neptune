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
    
    reactStrictMode: true,
    devIndicators: false,
    poweredByHeader: false,
    trailingSlash: false,
}

export default nextConfig
