﻿import { useSelf, useStorage } from '@liveblocks/react'
import { LiveMap} from '@liveblocks/client/dist/index'
import { LiveObject, shallow } from '@liveblocks/client'

function boundingBox(layers: Layer[]): XYWH | null {
    const first = layers[0]
    if (!first) return null
    
    let left = first.x
    let right = first.x + first.width
    let top = first.y
    let bottom = first.y + first.height
    
    for (let i = 1; i < layers.length; i++) {
        const { x, y, width, height } = layers[i]!
        
        if (left > x) left = x
        if (right < x + width) right = x + width
        if (top > y) top = y
        if (bottom < y + height) bottom = y + height
    }

    return {
        x: left,
        y: top,
        width: right - left,
        height: bottom - top
    }
}

export default function useSelectionBounds() {
    const selection = useSelf((me) => me.presence.selection) as string[]
    
    return useStorage((root) => {
        const layers = root.layers as LiveMap<string, Layer> | undefined
        
        const selectedLayers = selection
            ?.map((layerId) => layers?.get(layerId)!)
            .filter(Boolean)
        
        return boundingBox(selectedLayers)
    }, shallow)
}