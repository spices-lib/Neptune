/// <reference types="vite/client" />

interface ImportMetaEnv {
    readonly VITE_LIVEBLOCKS_PUBLIC_KEY: string
    readonly VITE_LIVEBLOCKS_ROOM_ID: string
}

interface ImportMeta {
    readonly env: ImportMetaEnv
}