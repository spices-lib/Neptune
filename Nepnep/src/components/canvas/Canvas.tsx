import {
    useCanRedo, 
    useCanUndo, 
    useHistory, 
    useMutation, 
    useMyPresence, 
    useSelf, 
    useStorage
} from '@liveblocks/react'
import {
    colorToCss,
    findIntersectionLayersWithRectangle,
    penPointsToPathLayer,
    pointerEventToCanvasPoint,
    resizeBounds
} from '../../utils'
import LayerComponent from './LayerComponent'
import ToolsBar from '../toolsbar/ToolsBar'
import { nanoid } from 'nanoid'
import { LiveObject } from '@liveblocks/client'
import React, { useCallback, useEffect, useState } from 'react'
import { LiveList, LiveMap } from '@liveblocks/client/dist/index'
import { CanvasMode, LayerType, Side } from '../../types/types.d'
import Path from './Path'
import SelectionBox from './SelectionBox'
import useDeleteLayers from '../../hooks/useDeleteLayers'
import SelectionTools from './SelectionTools'
import Sidebars from '../sidebars/Sidebars'
import MultiplayerGuides from './MultiplayerGuides'

const MAX_LAYERS = 100

export function Canvas() {
    const [leftIsMinimized, setLeftIsMinimized] = useState(false)
    const roomColor = useStorage((root) => ( root.roomColor)) as Color | undefined
    const layerIds = useStorage((root) => root.layerIds) as string[] | undefined
    const pencilDraft = useSelf((me) => me.presence.pencilDraft) as number[][]
    const deleteLayers = useDeleteLayers()
    const presence = useMyPresence()
    const [ canvasState, setState ] = useState<CanvasState>({ mode: CanvasMode.None })
    const [ camera, setCamera ] = useState<Camera>({ x: 0, y: 0, zoom:1 })
    const history = useHistory()
    const canUndo = useCanUndo()
    const canRedo = useCanRedo()
    
    const selectAllLayers = useMutation(({setMyPresence}) => {
        if (layerIds) {
            setMyPresence({ selection: [...layerIds]}, { addToHistory: true })
        }
    }, [layerIds])
    
    useEffect(() => {
        function onKeyDown (e: KeyboardEvent) {
            const activeElement = document.activeElement
            const isInputField = activeElement && (activeElement.tagName === 'INPUT' || activeElement.tagName === 'TEXTAREA')
            
            if (isInputField) return
            
            switch (e.key) {
                case 'Backspace':
                    deleteLayers()
                    break
                case 'z':
                    if (e.ctrlKey || e.metaKey) {
                        if (e.shiftKey) {
                            history.redo()
                        } else {
                            history.undo()
                        }
                    }
                    break
                case 'a':
                    if (e.ctrlKey || e.metaKey) {
                        selectAllLayers()
                    }
                    break
            }
        }
        
        document.addEventListener('keydown', onKeyDown)
        
        return () => {
            document.removeEventListener('keydown', onKeyDown)
        }
    }, [deleteLayers, selectAllLayers])
    
    const onLayerPointerDown = useMutation(({ self, setMyPresence }, e: React.PointerEvent, layerId: string) => {
        if (canvasState.mode === CanvasMode.Pencil || canvasState.mode === CanvasMode.Inserting) return 
        
        history.pause()
        
        e.stopPropagation()
        
        if (!(self.presence.selection as string[]).includes(layerId)) {
            setMyPresence({
                selection: [layerId]
            }, { addToHistory: true })
        } 
        
        if (e.nativeEvent.button === 2) {
            setState({ mode: CanvasMode.RightClick })
        } else {
            const point = pointerEventToCanvasPoint(e, camera)
            setState({mode: CanvasMode.Translating, current: point})
        }
    }, [ canvasState.mode, camera, history ])

    const onResizeHandlePointerDown = useCallback((corner: Side, initialBounds: XYWH) => {
        history.pause()
        
        setState({
            mode: CanvasMode.Resizing,
            initialBounds,
            corner
        })
    }, [history])
    
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
            else if (layerType === LayerType.Text) {
                layer = new LiveObject<TextLayer>({
                    type: layerType,
                    x: position.x,
                    y: position.y,
                    height: 100,
                    width: 100,
                    fontSize: 16,
                    text: 'Text',
                    fontWeight: 400,
                    fontFamily: 'Inter',
                    stroke: { r: 217, g: 217, b: 217 },
                    fill: { r: 217, g: 217, b: 217 },
                    opacity: 100
                })
            }
            
            if (layer) {
                liveLayerIds.push(layerId)
                liveLayers.set(layerId, layer)
                
                setMyPresence({ selection: [layerId] }, { addToHistory: true })
                setState({ mode: CanvasMode.None })
            }
        },
        []
    )

    const startDrawing = useMutation(({ setMyPresence }, point: Point, pressure: number) => {
        setMyPresence({
            pencilDraft: [[point.x, point.y, pressure]],
            penColor: { r: 217, g: 217, b: 217 }
        }, { addToHistory: true })
    }, [])

    const continueDrawing = useMutation(({ self, setMyPresence }, point: Point, e: React.PointerEvent) => {
        const { pencilDraft } = self.presence as { pencilDraft: number[][] }
        
        if(canvasState.mode !== CanvasMode.Pencil || e.buttons !== 1 || pencilDraft === null) {
            return
        }
        
        setMyPresence({
            cursor: point,
            pencilDraft: [...pencilDraft, [point.x, point.y, e.pressure]],
            penColor: { r: 217, g: 217, b: 217 }
        }, { addToHistory: true })
    }, [canvasState.mode])
    
    const translateSelectedLayers = useMutation(({storage, self}, point: Point) => {
        if (canvasState.mode !== CanvasMode.Translating) {
            return
        }
        
        const offset = {
            x: point.x - canvasState.current.x,
            y: point.y - canvasState.current.y
        }
        
        const liveLayers = storage.get('layers') as LiveMap<string, LiveObject<Layer>> | undefined
        for (const id of self.presence.selection as string[]) {
            const layer = liveLayers?.get(id)
            if (layer) {
                layer.update({
                    x: layer.get('x') + offset.x,
                    y: layer.get('y') + offset.y,
                })
            }
        }
        
        setState({ mode: CanvasMode.Translating, current: point })
    }, [canvasState])
    
    const resizeSelectedLayer = useMutation(({storage, self}, point: Point) => {
        if (canvasState.mode !== CanvasMode.Resizing) {
            return
        }
        
        const bounds = resizeBounds(canvasState.initialBounds, canvasState.corner, point)
            
        const liveLayers = storage.get('layers') as LiveMap<string, LiveObject<Layer>> | undefined
        const selection = self.presence.selection as string[] | undefined
        
        if (selection!.length > 0) {
            const layer = liveLayers?.get(selection![0]!)
            layer?.update(bounds)
        }
        
    }, [canvasState])
    
    const unselectLayers = useMutation(({ self, setMyPresence }) => {
        const selection = self.presence.selection as string[]
        
        if (selection.length > 0) {
            setMyPresence({ selection: [] }, { addToHistory: true })
        }
    }, [])
    
    const insertPath = useMutation(({ storage, self, setMyPresence }) => {
        const liveLayers = storage.get('layers') as LiveMap<string, LiveObject<Layer>> | undefined
        const liveLayerIds = storage.get('layerIds') as LiveList<string> | undefined
        const { pencilDraft } = self.presence as { pencilDraft: number[][] }
        
        if (pencilDraft === null || pencilDraft.length < 2 || liveLayers === undefined || liveLayers.size >= MAX_LAYERS || liveLayerIds === undefined) {
            setMyPresence({ pencilDraft: null }, { addToHistory: true })
            return
        }
        
        const id = nanoid()
        liveLayers.set(id, new LiveObject(penPointsToPathLayer(pencilDraft, { r: 217, g: 217, b: 217 })))
        liveLayerIds.push(id)

        setMyPresence({ pencilDraft: null }, { addToHistory: true })
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
        
        if (canvasState.mode === CanvasMode.Inserting) {
            return
        }
        
        if (canvasState.mode === CanvasMode.Pencil) {
           startDrawing(point, e.pressure)
            return
        }
        
        setState({ mode: CanvasMode.Pressing, origin: point })

    }, [camera, canvasState, setState, startDrawing])

    const startMultiSelection = useCallback((current: Point, origin: Point) => {
        if (Math.abs(current.x - origin.x) + Math.abs(current.y - origin.y) > 5) {
            setState({ mode: CanvasMode.SelectionNet, origin, current })
        }
    }, [])
    
    const updateSelectionNet = useMutation(({storage, setMyPresence}, current: Point, origin: Point) => {
        if (layerIds) {
            const layers = (storage.get('layers') as LiveMap<string, LiveObject<Layer>>).toImmutable()
            setState({ mode: CanvasMode.SelectionNet, origin, current })
            
            const ids = findIntersectionLayersWithRectangle(layerIds, layers, origin, current)
            setMyPresence({ selection: ids }, { addToHistory: true })
        }
    }, [layerIds])
    
    const onPointerMove = useMutation(({setMyPresence}, e: React.PointerEvent) => {
        if (!storageLoaded)
            return

        const point = pointerEventToCanvasPoint(e, camera)

        if (canvasState.mode === CanvasMode.Pressing) {
            startMultiSelection(point, canvasState.origin)
        }
        else if (canvasState.mode === CanvasMode.SelectionNet) {
            updateSelectionNet(point, canvasState.origin)
        }
        else if (canvasState.mode === CanvasMode.Dragging && canvasState.origin !== null) {
            const deltaX = e.movementX
            const deltaY = e.movementY
            
            setCamera((camera) => ({
                x: camera.x - deltaX,
                y: camera.y - deltaY,
                zoom: camera.zoom
            }))
        }
        else if (canvasState.mode === CanvasMode.Translating) {
            translateSelectedLayers(point)
        }
        else if (canvasState.mode === CanvasMode.Pencil) {
            continueDrawing(point, e)
        }
        else if (canvasState.mode === CanvasMode.Resizing) {
            resizeSelectedLayer(point)
        }

        setMyPresence({cursor: point})
        
    }, [canvasState, camera, setCamera, continueDrawing, translateSelectedLayers, resizeSelectedLayer, updateSelectionNet, startMultiSelection])
    
    const onPointerLeave = useMutation(({setMyPresence}) => {
        setMyPresence({cursor: null})
    }, [])
    
    const onPointerUp = useMutation(({}, e: React.PointerEvent) => {
        if (!storageLoaded)
            return

        if (canvasState.mode === CanvasMode.RightClick) {
            return
        }
        
        const point = pointerEventToCanvasPoint(e, camera)
        
        if (canvasState.mode === CanvasMode.None || canvasState.mode === CanvasMode.Pressing) {
            unselectLayers()
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
        else {
            setState({ mode: CanvasMode.None })
        }
        
        history.resume()
        
    }, [camera, canvasState, setState, insertLayer, insertPath, unselectLayers, history])
    
    return (
        <div className='flex h-screen w-full'>
            <main className='overflow-y-auto fixed left-0 right-0 h-screen'>
                <div
                    style={{
                        backgroundColor: roomColor ? colorToCss(roomColor) : '#1e1e1e'
                    }}
                    className='h-full w-full touch-none'
                >
                    <SelectionTools
                        camera={ camera }
                        canvasMode={ canvasState.mode }
                    >
                    </SelectionTools>
                    <svg
                        onWheel={ onWheel }
                        onPointerUp={ onPointerUp }
                        onPointerDown={ onPointerDown }
                        onPointerMove={ onPointerMove }
                        onPointerLeave={ onPointerLeave }
                        className='w-full h-full'
                        onContextMenu={ (e) => e.preventDefault() }
                    >
                        <g
                            style={{transform: `translate(${camera.x}px, ${camera.y}px) scale(${camera.zoom})`}}
                        >
                        </g>
                        { layerIds && layerIds.map((layerId) => (
                            <LayerComponent
                                key={ layerId }
                                id={ layerId }
                                onLayerPointerDown={ onLayerPointerDown }
                            >
                            </LayerComponent>
                        )) }
                        <SelectionBox
                            onResizeHandlePointerDown={ onResizeHandlePointerDown }
                        >
                        </SelectionBox>
                        { canvasState.mode === CanvasMode.SelectionNet && canvasState.current !== null && 
                            <rect
                                className='fill-blue-600/5 stroke-blue-600 stroke-[0.5]'
                                x={ Math.min(canvasState.origin.x, canvasState.current.x) }
                                y={ Math.min(canvasState.origin.y, canvasState.current.y) }
                                width={ Math.abs(canvasState.origin.x - canvasState.current.x) }
                                height={ Math.abs(canvasState.origin.y - canvasState.current.y) }
                            >
                            </rect>  
                        }
                        <MultiplayerGuides/>
                        { pencilDraft !== null && pencilDraft.length > 0 && 
                            <Path
                                x={ 0 }
                                y={ 0 }
                                stroke={ colorToCss({r: 217, g: 217, b: 217 })}
                                fill={ colorToCss({r: 217, g: 217, b: 217 })}
                                opacity={ 100 }
                                points={ pencilDraft }
                            >
                            </Path> 
                        }
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
                undo={ () => history.undo() }
                redo={ () => history.redo() }
                canUndo={ canUndo }
                canRedo={ canRedo }
            >
            </ToolsBar>
            <Sidebars
                leftIsMinimized={ leftIsMinimized }
                setLeftIsMinimized={ setLeftIsMinimized }
            >
            </Sidebars>
        </div>
    )
}