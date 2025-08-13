import React from 'react'
import { LayerType } from '../types/types.d'
import {Color} from "../types/types";

export function colorToCss(color: Color) {
    return `#
        ${color.r.toString(16).padStart(2, '0')}
        ${color.g.toString(16).padStart(2, '0')}
        ${color.b.toString(16).padStart(2, '0')}
    `
}

export const pointerEventToCanvasPoint = (
    e: React.PointerEvent,
    camera: Camera
): Point => {
    return {
        x: Math.round(e.clientX) - camera.x,
        y: Math.round(e.clientY) - camera.y,
    }
}

export function penPointsToPathLayer(
    points: number[][],
    color: Color,
) : PathLayer {
    let left = Number.POSITIVE_INFINITY
    let top = Number.POSITIVE_INFINITY
    let right = Number.NEGATIVE_INFINITY
    let bottom = Number.NEGATIVE_INFINITY
    
    for (const point of points) {
        const [ x, y ] = point
        if (x === undefined || y === undefined) continue
        
        if (left > x) left = x
        if (top > y) top = y
        if (right < x) right = x
        if (bottom < y) bottom = y
    }
    
    return {
        type: LayerType.Path,
        x: left,
        y: top,
        height: bottom - top,
        width: right - left,
        fill: color,
        stroke: color,
        opacity: 100,
        points: points
            .filter((point): point is [number, number, number] => 
                point[0] !== undefined && 
                point[1] !== undefined && 
                point[2] !== undefined
            ).map(([x, y, pressure]) => [x - left, y - top, pressure])
    }
}