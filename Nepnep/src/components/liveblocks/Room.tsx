'use client'

import { ReactNode } from 'react'
import {
    LiveblocksProvider,
    RoomProvider,
    ClientSideSuspense,
} from '@liveblocks/react/suspense'
import '@liveblocks/react-ui/styles.css'

export function Room({ children }: { children: ReactNode }) {

    console.log(import.meta.env)

    return (
        <LiveblocksProvider publicApiKey={ import.meta.env.VITE_LIVEBLOCKS_PUBLIC_KEY! }>
            <RoomProvider id="my-room">
                <ClientSideSuspense fallback={<div>Loading…</div>}>
                    {children}
                </ClientSideSuspense>
            </RoomProvider>
        </LiveblocksProvider>
    );
}