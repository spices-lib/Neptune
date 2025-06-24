'use client'

import React from 'react'
import {
    LiveblocksProvider,
    RoomProvider,
    ClientSideSuspense,
} from '@liveblocks/react/suspense'
import '@liveblocks/react-ui/styles.css'

interface RoomProps {
    children: React.JSX.Element;
}

export function Room({ children }: RoomProps) {

    return (
        <LiveblocksProvider publicApiKey={ import.meta.env.VITE_LIVEBLOCKS_PUBLIC_KEY! }>
            <RoomProvider id="nepnep-room">
                <ClientSideSuspense fallback={<div>Loading…</div>}>
                    {children}
                </ClientSideSuspense>
            </RoomProvider>
        </LiveblocksProvider>
    );
}