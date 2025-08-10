import { RectangleLayer } from '../../types/types'
import {colorToCss} from "../../utils";

export default function Rectangle({ id, layer } : { id: string, layer: RectangleLayer }) {
    const { x, y, width, height, fill, stroke, opacity, connerRadius } = layer
    
    return (
        <g>
            <rect
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