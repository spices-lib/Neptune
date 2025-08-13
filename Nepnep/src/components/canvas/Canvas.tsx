import { useMutation, useSelf, useStorage } from '@liveblocks/react'
import { colorToCss, penPointsToPathLayer, pointerEventToCanvasPoint } from '../../utils'
import LayerComponent from './LayerComponent'
import ToolsBar from '../toolsbar/ToolsBar'
import { nanoid } from 'nanoid'
import { LiveObject} from '@liveblocks/client'
import React, { useCallback, useEffect, useState } from 'react'
import { LiveList, LiveMap } from '@liveblocks/client/dist/index'
import { CanvasMode, LayerType } from '../../types/types.d'

const MAX_LAYERS = 100

export function Canvas() {
    const roomColor = useStorage((root) => ( root.roomColor)) as Color | undefined
    const layerIds = useStorage((root) => root.layerIds) as string[] | undefined
    const pencilDraft = useSelf((me) => me.presence.pencilDraft) as number[][]
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

    const startDrawing = useMutation(({ setMyPresence }, point: Point, pressure: number) => {
        setMyPresence({
            pencilDraft: [[point.x, point.y, pressure]],
            penColor: { r: 217, g: 217, b: 217 }
        })
    }, [])

    const continueDrawing = useMutation(({ self, setMyPresence }, point: Point, e: React.PointerEvent) => {
        const { pencilDraft } = self.presence
        
        if(canvasState.mode !== CanvasMode.Pencil || e.buttons !== 1 || pencilDraft === null) {
            return
        }
        
        setMyPresence({
            pencilDraft: [...pencilDraft, [point.x, point.y, e]],
            penColor: { r: 217, g: 217, b: 217 }
        })
    }, [canvasState.mode])
    
    const insertPath = useMutation(({ storage, self, setMyPresence }) => {
        const liveLayers = storage.get('layers') as LiveMap<string, LiveObject<Layer>> | undefined
        const liveLayerIds = storage.get('layerIds') as LiveList<string> | undefined
        const { pencilDraft } = self.presence as { pencilDraft: number[][] }
        
        if (pencilDraft === null || pencilDraft.length < 2 || liveLayers === undefined || liveLayers.size >= MAX_LAYERS || liveLayerIds === undefined) {
            setMyPresence({ pencilDraft: null })
            return
        }
        
        const id = nanoid()
        liveLayers.set(id, new LiveObject(penPointsToPathLayer(pencilDraft, { r: 217, g: 217, b: 217 })))
        liveLayerIds.push(id)

        setMyPresence({ pencilDraft: null })
        setState({ mode: CanvasMode.Pencil })
    },[])
    
    const storageLoaded = useStorage((root) => root.layers !== undefined)
    
    useEffect(()=>{
        if (!storageLoaded)
            return
        
        insertLayer(LayerType.Rectangle, { x: 100, y: 100 })
    }, [insertLayer])
    
    const onWheel = useCallback((e: React.WheelEvent) => {
        setCamera((camera) => ({
            x: camera.x - e.deltaX,
            y: camera.y - e.deltaY,
            zoom: camera.zoom
        }))
    }, [])
    
    const onPointerDown = useMutation(({}, e: React.PointerEvent) => {
        if (!storageLoaded)
            return

        const point = pointerEventToCanvasPoint(e, camera)
        
        if (canvasState.mode === CanvasMode.Dragging) {
            setState({ mode: CanvasMode.Dragging, origin: point })
            return
        }
        
        if (canvasState.mode === CanvasMode.Pencil) {
           startDrawing(point, e.pressure)
            return
        }

    }, [camera, canvasState, setState, startDrawing])

    const onPointerMove = useMutation(({}, e: React.PointerEvent) => {
        if (!storageLoaded)
            return

        const point = pointerEventToCanvasPoint(e, camera)

        if (canvasState.mode === CanvasMode.Dragging && canvasState.origin !== null) {
            const deltaX = e.movementX
            const deltaY = e.movementY
            
            setCamera((camera) => ({
                x: camera.x - deltaX,
                y: camera.y - deltaY,
                zoom: camera.zoom
            }))
        }
        else if (canvasState.mode === CanvasMode.Pencil) {
            continueDrawing(point, e)
        }

    }, [canvasState, setCamera, continueDrawing])
    
    const onPointerUp = useMutation(({}, e: React.PointerEvent) => {
        if (!storageLoaded)
            return
        
        const point = pointerEventToCanvasPoint(e, camera)
        
        if (canvasState.mode === CanvasMode.None) {
            setState({ mode: CanvasMode.None })
        }
        else if (canvasState.mode === CanvasMode.Inserting) {
            insertLayer(canvasState.layerType, point)
        }
        else if (canvasState.mode === CanvasMode.Dragging) {
            setState({ mode: CanvasMode.Dragging, origin: null })
        }
        else if (canvasState.mode === CanvasMode.Pencil) {
            insertPath()
        }
        
    }, [camera, canvasState, setState, insertLayer, insertPath])
    
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
                        onWheel={ onWheel }
                        onPointerUp={ onPointerUp }
                        onPointerDown={ onPointerDown }
                        onPointerMove={ onPointerMove }
                        className='w-full h-full'
                    >
                        <g
                            style={{transform: `translate(${camera.x}px, ${camera.y}px) scale(${camera.zoom})`}}
                        >
                            { layerIds && layerIds.map((layerId) => (
                                <LayerComponent
                                    key={ layerId }
                                    id={ layerId }
                                >
                                </LayerComponent>
                            )) }
                        </g>
                        { pencilDraft !== null && pencilDraft.length > 0 }
                    </svg>
                </div>
            </main>
            <ToolsBar
                canvasState={ canvasState }
                setCanvasState={ (newState) => setState(newState) }
                zoomIn={ () => {
                    setCamera((camera) => ({ ...camera, zoom: camera.zoom + 0.1 }))
                } }
                zoomOut={ () => {
                    setCamera((camera) => ({ ...camera, zoom: camera.zoom - 0.1 }))
                } }
                canZoomIn={ camera.zoom < 2 }
                canZoomOut={ camera.zoom > 0.5 }
            >
            </ToolsBar>
        </div>
    )
}