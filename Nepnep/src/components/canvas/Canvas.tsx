import { useMutation, useStorage } from '@liveblocks/react'
import { colorToCss } from '../../utils'
import LayerComponent from './LayerComponent'
import { Layer, LayerType, Point, RectangleLayer } from '../../types/types'
import { nanoid } from 'nanoid'
import { LiveObject } from '@liveblocks/client'
import {useEffect} from "react";

const MAX_LAYERS = 100

export function Canvas() {
    const roomColor = useStorage((root) => root.roomColor)
    const layerIds = useStorage((root) => root.layerIds)

    const insertLayer = useMutation(
        (
            { storage, setMyPresence }, 
            layerType: LayerType.Ellipse | LayerType.Path | LayerType.Rectangle | LayerType.Text,
            position: Point
        ) => {
            const liveLayers = storage.get('layers')
            if(liveLayers.size >= MAX_LAYERS) {
                return
            }
            
            const liveLayerIds = storage.get('layerIds')
            const layerId = nanoid()
            let layer: LiveObject<Layer> | null = null
            
            if (layerType === LayerType.Rectangle) {
                layer = new LiveObject<RectangleLayer>({
                    type: LayerType.Rectangle,
                    x: position.x,
                    y: position.y,
                    height: 100,
                    width: 100,
                    fill: { r: 217, g: 217, b: 217 },
                    stroke: { r: 217, g: 217, b: 217 },
                    opacity: 100,
                    connerRadius: 0
                })
            }
            
            if (layer) {
                liveLayerIds.push(layerId)
                liveLayers.set(layerId, layer)
                
                setMyPresence({ selection: [layerId] }, { addToHistory: true })
            }
        },
        []
    )
    
    useEffect(()=>{
        insertLayer(LayerType.Rectangle, { x: 100, y: 100 })
    })
    
    return (
        <div className='flex h-screen w-full'>
            <main className='overflow-y-auto fixed left-0 right-0 h-screen'>
                <div
                    style={{
                        backgroundColor: roomColor ? colorToCss(roomColor) : '#1e1e1e'
                    }}
                    className='h-full w-full touch-none'
                >
                    <svg className='w-full height-full'>
                        <g>
                            { layerIds.map((layerId) => { 
                                <LayerComponent
                                    key={ layerId }
                                    id={ layerId }
                                >
                                </LayerComponent>
                            }) }
                        </g>
                    </svg>
                </div>
            </main>
        </div>
    )
}