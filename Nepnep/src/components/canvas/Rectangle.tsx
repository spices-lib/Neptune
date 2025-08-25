import { colorToCss } from '../../utils'
import React from 'react'
import { RectangleLayer } from '../../types/types'

export default function Rectangle({ 
    id, 
    layer, 
    onPointerDown
} : { 
    id: string,
    layer: RectangleLayer,
    onPointerDown: (e: React.PointerEvent, layerId: string) => void
}) {
    const { x, y, width, height, fill, stroke, opacity, connerRadius } = layer
    
    return (
        <g
            className='group'
        >
            <rect
                style={{transform: `translate(${x}px, ${y}px)`}}
                width={ width }
                height={ height }
                fill='none'
                stroke='#0b99ff'
                strokeWidth={ 4 }
                className='pointer-events-none opacity-0 group-hover:opacity-100'
            >
            </rect>
            <rect
                onPointerDown={ (e) => onPointerDown(e, id) }
                style={{transform: `translate(${x}px, ${y}px)`}}
                width={width}
                height={height}
                fill={fill ? colorToCss(fill) : '#CCC'}
                strokeWidth={1}
                stroke={stroke ? colorToCss(stroke) : '#CCC'}
                opacity={opacity}
                rx={connerRadius ?? 0}
                ry={connerRadius ?? 0}
            >
            </rect>
        </g>
    )
}