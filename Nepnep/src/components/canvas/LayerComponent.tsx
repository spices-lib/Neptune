import React, { memo } from 'react'
import { useStorage } from '@liveblocks/react'
import Rectangle from './Rectangle'
import Ellipse from './Ellipse'
import { LiveMap, LiveObject } from "@liveblocks/client/dist/index";
import { LayerType } from '../../types/types.d'
import Path from './Path'
import Text from './Text'
import { colorToCss } from '../../utils'

const LayerComponent = memo(({ 
    id,
    onLayerPointerDown
}: { 
    id: string,
    onLayerPointerDown: (e: React.PointerEvent, layerId: string) => void
}) => {
    const layer = useStorage((root) => (root.layers as LiveMap<string, LiveObject<Layer>> | undefined)?.get(id)) as Layer | undefined
    if(!layer) {
        return null
    }
    
    switch (layer.type) {
        case LayerType.Path:
            return (
                <Path
                    onPointerDown={(e) => onLayerPointerDown(e, id)}
                    points={ layer.points } 
                    x={ layer.x } 
                    y={ layer.y }
                    fill={ layer.fill ? colorToCss(layer.fill) : '#CCC' }
                    stroke={ layer.stroke ? colorToCss(layer.stroke) : '#CCC' }
                    opacity={ layer.opacity }
                >
                </Path>
            )
        case LayerType.Rectangle:
            return (
                <Rectangle
                    onPointerDown={ onLayerPointerDown }
                    id={ id } 
                    layer={ layer }
                >
                </Rectangle>
            )
        case LayerType.Ellipse:
            return (
                <Ellipse
                    onPointerDown={ onLayerPointerDown }
                    id={ id } 
                    layer={ layer }
                >
                </Ellipse>
            )
        case LayerType.Text:
            return (
                <Text
                    onPointerDown={ onLayerPointerDown }
                    id={ id }
                    layer={ layer }
                >
                </Text>
            )
        default:
            return null
    }
})

LayerComponent.displayName = 'LayerComponent'

export default LayerComponent