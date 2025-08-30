import { Point, Color, Layer } from './src/types/types'
import { LiveList, LiveMap, LiveObject } from '@liveblocks/client'

declare global {
    interface Liveblocks {
        Presence: {
            selection: string[]
            cursor: Point | null
            penColor: Color | null
            pencilDraft: [x: number, y: number, pressure: number][] | null
        }
        Storage: {
            roomColor: Color | null
            layers: LiveMap<string, LiveObject<Layer>>
            layerIds: LiveList<string>
        }
        UserMeta: {
            id: string
            info: {
                name: string
            }
        }
        RoomEvent: {}
        ThreadMetadata: {}
        RoomInfo: {}
    }
}

export {}