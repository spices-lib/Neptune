import { memo } from 'react'
import { useStorage } from '@liveblocks/react'
import Rectangle from './Rectangle'
import Ellipse from './Ellipse'
import { LiveMap, LiveObject } from "@liveblocks/client/dist/index";
import { LayerType } from '../../types/types.d'


const LayerComponent = memo(({ id }: { id: string}) => {
    const layer = useStorage((root) => (root.layers as LiveMap<string, LiveObject<Layer>> | undefined)?.get(id)) as Layer | undefined
    if(!layer) {
        return null
    }
    
    switch (layer.type) {
        case LayerType.Rectangle:
            return <Rectangle id={id} layer={layer}></Rectangle>
        case LayerType.Ellipse:
            return <Ellipse id={id} layer={layer}></Ellipse>
        default:
            return null
    }
})

LayerComponent.displayName = 'LayerComponent'

export default LayerComponent