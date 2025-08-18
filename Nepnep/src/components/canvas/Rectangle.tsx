import { colorToCss } from '../../utils'
import React from "react";

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
        <g>
            <rect
                onPointerDown={ (e) => onPointerDown(e, id) }
                style={{transform: `translate(${x}px, ${y}px)`}}
                x={x}
                y={y}
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