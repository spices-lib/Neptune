import { useOther } from '@liveblocks/react'
import { memo } from 'react'
import { connectionIdToColor } from '../../utils'
import { Point } from '../../types/types'

function Cursor({
    connectionId
}: {
    connectionId: number
}) {
    const cursor = useOther(connectionId, (user) => user.presence.cursor as Point | undefined)
    if (!cursor)
        return null
    
    const { x, y } = cursor

    return (
        <path
            style={{transform: `translateX(${x}px) translateY(${y}px)`}}
            fill={ connectionIdToColor(connectionId) }
            d='M5.65376 12.3673H5.46026L5.31717 12.4976L0.500002 16.8829L0.500002 1.19841L11.7841 12.3673H5.65376Z'
        >
        </path>
    )
}

export default memo(Cursor)