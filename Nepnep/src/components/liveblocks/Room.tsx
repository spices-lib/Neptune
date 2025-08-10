import { ReactNode } from 'react'
import {
    LiveblocksProvider,
    RoomProvider,
    ClientSideSuspense,
} from '@liveblocks/react/suspense'
import '@liveblocks/react-ui/styles.css'
import { Layer } from '../../types/types'
import { LiveList, LiveMap, LiveObject } from '@liveblocks/node'

interface RoomProps {
    children: ReactNode
    roomId: string
}

export function Room({ children, roomId }: RoomProps) {

    return (
        <LiveblocksProvider
            /*authEndpoint='/api/liveblocks-auth'*/
            publicApiKey={ import.meta.env.VITE_LIVEBLOCKS_PUBLIC_KEY! }
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