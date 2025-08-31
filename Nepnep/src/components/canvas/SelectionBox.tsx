import { useSelf, useStorage } from '@liveblocks/react'
import { LiveMap, LiveObject } from '@liveblocks/client/dist/index'
import { memo, useEffect, useRef, useState} from 'react'
import useSelectionBounds from '../../hooks/useSelectionBounds'
import { Side, XYWH, Layer, LayerType,  } from '@/types/types'

const handleWidth = 8

const SelectionBox = memo(({
    onResizeHandlePointerDown
} : {
    onResizeHandlePointerDown: (corner: Side, initialBounds: XYWH) => void
}) => {
    const soleLayerId = useSelf((me) => {
        const selection = me.presence.selection as string[]
        return selection?.length === 1 ? selection[0] : null
    })
    
    const isShowingHandles = useStorage((root) => 
        soleLayerId && ((root.layers as LiveMap<string, LiveObject<Layer>> | undefined)?.get(soleLayerId) as Layer | undefined)?.type !== LayerType.Path
    )

    const bounds = useSelectionBounds()
    const textRef = useRef<SVGTextElement>(null)
    const [ textWidth, setTextWidth ] = useState(0)
    const padding = 16

    
    useEffect(() => {
        if (textRef.current) {
            const bbox = textRef.current.getBBox()
            setTextWidth(bbox.width)
        }
    }, [bounds])
    
    if (!bounds) return null
    
    return (
        <g>
            <rect
                style={{transform: `translate(${bounds.x}px, ${bounds.y}px)`}}
                className='pointer-events-none fill-transparent stroke-[#0b99ff] stroke-[1px]'
                width={ bounds.width }
                height={ bounds.height }
            >
            </rect>
            <rect
                className='fill-[#0b99ff]'
                x={ bounds.x + bounds.width / 2 - (textWidth + padding) / 2 }
                y={ bounds.y + bounds.height + 10 }
                width={ textWidth + padding }
                height={ 20 }
                rx={ 4 }
            >
            </rect>
            <text
                ref={ textRef }
                style={{transform: `translate(${bounds.x + bounds.width / 2}px, ${bounds.y + bounds.height + 25}px)`}}
                textAnchor='middle'
                className='pointer-events-none select-none fill-white text-[11px]'
            >
                { Math.round(bounds.width) } x { Math.round(bounds.height) }
            </text>
            { isShowingHandles && (
                <g>
                    <rect
                        style={{
                            cursor: 'nwse-resize',
                            width: `${handleWidth}px`, 
                            height: `${handleWidth}px`, 
                            transform: `translate(${bounds.x - handleWidth / 2}px, ${bounds.y - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Top + Side.Left, bounds)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'ns-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${bounds.x + bounds.width / 2 - handleWidth / 2}px, ${bounds.y - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Top, bounds)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'nesw-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${bounds.x + bounds.width - handleWidth / 2}px, ${bounds.y - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Top + Side.Right, bounds)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'ew-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${bounds.x - handleWidth / 2}px, ${bounds.y + bounds.height / 2 - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Left, bounds)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'nesw-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${bounds.x - handleWidth / 2}px, ${bounds.y + bounds.height - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Bottom + Side.Left, bounds)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'ew-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${bounds.x  + bounds.width - handleWidth / 2}px, ${bounds.y + bounds.height / 2 - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Right, bounds)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'nwse-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${bounds.x + bounds.width - handleWidth / 2}px, ${bounds.y + bounds.height - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Bottom + Side.Right, bounds)
                        }}
                    >
                    </rect>
                    <rect
                        style={{
                            cursor: 'ns-resize',
                            width: `${handleWidth}px`,
                            height: `${handleWidth}px`,
                            transform: `translate(${bounds.x + bounds.width / 2 - handleWidth / 2}px, ${bounds.y + bounds.height - handleWidth / 2}px)`
                        }}
                        className='fill-white stroke-[#0b99ff] stroke-[1px]'
                        onPointerDown={(e) => {
                            e.stopPropagation()
                            onResizeHandlePointerDown(Side.Bottom, bounds)
                        }}
                    >
                    </rect>
                </g>
            )}
        </g>
    )
})

SelectionBox.displayName = 'SelectionBox'

export default SelectionBox