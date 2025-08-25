'use client'

import { ReactNode } from 'react'
import {
    LiveblocksProvider,
    RoomProvider,
    ClientSideSuspense,
} from '@liveblocks/react/suspense'
import '@liveblocks/react-ui/styles.css'
import { LiveList, LiveMap, LiveObject } from '@liveblocks/node'
import { Layer } from '../../types/types'

export function Room({ 
    children, 
    roomId 
}: {
    children: ReactNode
    roomId: string
}) {
    return (
        <LiveblocksProvider
            authEndpoint='/api/liveblocks-auth'
        >
            <RoomProvider 
                id={ roomId }
                initialPresence={{
                    selection: [],
                    cursor: null,
                    penColor: null,
                    pencilDraft: []
                }}
                initialStorage={{
                    roomColor: { r: 30, g: 30, b: 30 },
                    layers: new LiveMap<string, LiveObject<Layer>>(),
                    layerIds: new LiveList([])
                }}
            >
                <ClientSideSuspense 
                    fallback={
                    <div className='flex h-screen items-center justify-center flex-col gap-2'>
                        <img
                            src='/xx.svg'
                            alt='Loading...'
                            className='h-[50px] w-[50px] animate-bounce'
                        >
                        </img>
                        <h1 className='text-sm font-normal'>
                            Loading...
                        </h1>
                    </div>
                }
                >
                    { children }
                </ClientSideSuspense>
            </RoomProvider>
        </LiveblocksProvider>
    )
}