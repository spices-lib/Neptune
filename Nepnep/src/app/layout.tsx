import '../styles/style.css'

import { Inter } from 'next/font/google'
import { type Metadata } from 'next'
import React from 'react'

export const metadata: Metadata = {
    title: 'nepnep',
    description: 'nepnep',
    icons: [{ rel: 'icon', url: '/favicon/favicon-64.ico' }],
}

const inter = Inter({
    subsets: ["latin"],
    display: "swap",
})

export default function RootLayout({
    children,
}: { 
    children: React.ReactNode 
}) {
    return (
        <html 
            lang='en' 
            className={`${inter.className}`}
        >
            <body
                className='overflow-hidden overscroll-none'
            >
            { children }
            </body>
        </html>
    );
}
