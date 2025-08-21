import { useMutation, useSelf } from '@liveblocks/react'
import { LiveList, LiveMap, LiveObject } from '@liveblocks/client'

export default function useDeleteLayers() {
    const selection = useSelf((me) => me.presence.selection) as string[]
    
    return useMutation(({storage, setMyPresence}) => {
        const liveLayers = storage.get('layers') as LiveMap<string, LiveObject<Layer>>
        const liveLayerIds = storage.get('layerIds') as LiveList<string>
        
        for (const id of selection) {
            liveLayers.delete(id)
            
            const index = liveLayerIds.indexOf(id)
            if (index !== -1) {
                liveLayerIds.delete(index)
            }
        }
        
        setMyPresence({ selection: [] }, { addToHistory: true })
    }, [selection])
}