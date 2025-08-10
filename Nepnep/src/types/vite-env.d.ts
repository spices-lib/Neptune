/// <reference types="vite/client" />

interface ImportMetaEnv {
    readonly VITE_LIVEBLOCKS_PUBLIC_KEY: string
    readonly VITE_LIVEBLOCKS_SECRET_KEY: string
    readonly VITE_LIVEBLOCKS_ROOM_ID: string
    readonly VITE_DATABASE_URL: string
}

interface ImportMeta {
    readonly env: ImportMetaEnv
}