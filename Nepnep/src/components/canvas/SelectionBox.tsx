import { useSelf, useStorage } from '@liveblocks/react'
import { LayerType, Side } from '../../types/types.d'
import { LiveMap, LiveObject } from '@liveblocks/client/dist/index'
import { useEffect, useRef, useState } from 'react'

const handleWidth = 8

export default function SelectionBox({
    onResizeHandlePointerDown
} : {
    onResizeHandlePointerDown: (corner: Side, initialBounds: XYWH) => void
}) {
    const soleLayerId = useSelf((me) => {
        const selection = me.presence.selection as string[]
        return selection?.length === 1 ? selection[0] : null
    })
    
    const isShowingHandles = useStorage((root) => 
        soleLayerId && ((root.layers as LiveMap<string, LiveObject<Layer>> | undefined)?.get(soleLayerId) as Layer | undefined)?.type !== LayerType.Path
    )

    const textRef = useRef<SVGTextElement>(null)
    const [ textWidth, setTextWidth ] = useState(0)
    const padding = 16
    
    const layers = useStorage((root) => root.layers) as LiveMap<string, LiveObject<Layer>> | undefined
    const layer = soleLayerId ? layers?.get(soleLayerId) as Layer | undefined : null

    useEffect(() => {
        if (textRef.current) {
            const bbox = textRef.current.getBBox()
            setTextWidth(bbox.width)
        }
    }, [layer])
    
    if (!layer) return null
    
    return (
        <g>
            <rect
                style={{transform: `translate(${layer.x}px, ${layer.y}px)`}}
                className='pointer-events-none fill-transparent stroke-[#0b99ff] stroke-[1px]'
                width={ layer.width }
                height={ layer.height }
            >
            </rect>
            <rect
                className='fill-[#0b99ff]'
                x={ layer.x + layer.width / 2 - (textWidth + padding) / 2 }
                y={ layer.y + layer.height + 10 }
                width={ textWidth + padding }
                height={ 20 }
                rx={ 4 }
            >
            </rect>
            <text
                ref={ textRef }
                style={{transform: `translate(${layer.x + layer.width / 2}px, ${layer?.y + layer.height + 25}px)`}}
                textAnchor='middle'
                className='pointer-events-none fill-white text-[11px]'
            >
                { Math.round(layer.width) } x { Math.round(layer.height) }
            </text>
            { isShowingHandles && (
                <g>
                    <rect
                        style={{
                            cursor: 'nwse-resize',
                            width: `${handleWidth}px`, 
                            height: `${handleWidth}px`, 
                            transform: `translate(${layer.x - handleWidth / 2}px, ${layer.y - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Top + Side.Left, layer)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'ns-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${layer.x + layer.width / 2 - handleWidth / 2}px, ${layer.y - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Top, layer)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'nesw-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${layer.x + layer.width - handleWidth / 2}px, ${layer.y - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Top + Side.Right, layer)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'ew-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${layer.x - handleWidth / 2}px, ${layer.y + layer.height / 2 - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Left, layer)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'nesw-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${layer.x - handleWidth / 2}px, ${layer.y + layer.height - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Bottom + Side.Left, layer)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'ew-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${layer.x  + layer.width - handleWidth / 2}px, ${layer.y + layer.height / 2 - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Right, layer)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'nwse-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${layer.x + layer.width - handleWidth / 2}px, ${layer.y + layer.height - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Bottom + Side.Right, layer)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'ns-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${layer.x + layer.width / 2 - handleWidth / 2}px, ${layer.y + layer.height - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Bottom, layer)
                        }}
                    >
                    </rect>
                </g>
            )}
        </g>
    )
}