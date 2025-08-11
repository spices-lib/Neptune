import { useMutation, useStorage } from '@liveblocks/react'
import { colorToCss, pointerEventToCanvasPoint } from '../../utils'
import LayerComponent from './LayerComponent'
import ToolsBar from '../toolsbar/ToolsBar'
import { nanoid } from 'nanoid'
import { LiveObject } from '@liveblocks/client'
import { useEffect, useState } from 'react'
import { LiveList, LiveMap } from '@liveblocks/client/dist/index'
import { CanvasMode, LayerType } from '../../types/types.d'

const MAX_LAYERS = 100

export function Canvas() {
    const roomColor = useStorage((root) => ( root.roomColor)) as Color | undefined
    const layerIds = useStorage((root) => root.layerIds) as string[] | undefined
    const [ canvasState, setState ] = useState<CanvasState>({ mode: CanvasMode.None })
    const [ camera, setCamera ] = useState<Camera>({ x: 0, y: 0, zoom:1 })
    
    const insertLayer = useMutation(
        (
            { storage, setMyPresence }, 
            layerType: LayerType,
            position: Point
        ) => {
            if (!storage) {
                return
            }
            
            const liveLayers = storage.get('layers') as LiveMap<string, LiveObject<Layer>> | undefined
            if(!liveLayers || liveLayers.size >= MAX_LAYERS) {
                return
            }
            
            const liveLayerIds = storage.get('layerIds') as LiveList<string> | undefined
            if (!liveLayerIds) {
                return
            }
            
            const layerId = nanoid()
            let layer: LiveObject<Layer> | null = null
            
            if (layerType === LayerType.Rectangle) {
                layer = new LiveObject<RectangleLayer>({
                    type: layerType,
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
            else if (layerType === LayerType.Ellipse) {
                layer = new LiveObject<EllipseLayer>({
                    type: layerType,
                    x: position.x,
                    y: position.y,
                    height: 100,
                    width: 100,
                    fill: { r: 217, g: 217, b: 217 },
                    stroke: { r: 217, g: 217, b: 217 },
                    opacity: 100,
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

    const storageLoaded = useStorage((root) => root.layers !== undefined)
    
    useEffect(()=>{
        if (!storageLoaded)
            return
        
        insertLayer(LayerType.Rectangle, { x: 100, y: 100 })
    }, [insertLayer])
    
    const onPointerUp = useMutation(({}, e: PointerEvent) => {
        if (!storageLoaded)
            return
        
        const point = pointerEventToCanvasPoint(e, camera)
        
        insertLayer(LayerType.Ellipse, point)
    }, [insertLayer])
    
    return (
        <div className='flex h-screen w-full'>
            <main className='overflow-y-auto fixed left-0 right-0 h-screen'>
                <div
                    style={{
                        backgroundColor: roomColor ? colorToCss(roomColor) : '#1e1e1e'
                    }}
                    className='h-full w-full touch-none'
                >
                    <svg
                        onPointerUp={ onPointerUp }
                        className='w-full h-full'
                    >
                        <g>
                            { layerIds && layerIds.map((layerId) => (
                                <LayerComponent
                                    key={ layerId }
                                    id={ layerId }
                                >
                                </LayerComponent>
                            )) }
                        </g>
                    </svg>
                </div>
            </main>
            <ToolsBar
                canvasState={ canvasState }
                setCanvasState={ (newState) => setState(newState) }
            >
            </ToolsBar>
        </div>
    )
}