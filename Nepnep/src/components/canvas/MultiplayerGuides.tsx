import { memo } from 'react'
import Cursor from './Cursor'
import { useOthersConnectionIds, useOthersMapped } from '@liveblocks/react'
import { shallow } from '@liveblocks/client'
import Path from './Path'
import { colorToCss } from '../../utils'
import { Color } from '../../types/types'

function Cursors() {
    const ids = useOthersConnectionIds()
    
    return (
        <>
            { ids.map((connectionId) => (
                <Cursor
                    key={ connectionId }
                    connectionId={ connectionId }
                >
                </Cursor>
            )) }
        </>
    )
}

function Drafts() {
    const others = useOthersMapped((other) => (
        { pencilDraft: other.presence.pencilDraft, penColor: other.presence.penColor }
    ), shallow)
    
    return (
        <>
            { others.map(([key, other]) => {
                if (!other.pencilDraft) {
                    return null
                }
                
                return (
                    <Path
                        key={ key }
                        x={ 0 }
                        y={ 0 }
                        points={ other.pencilDraft as number[][] }
                        fill={ other.penColor ? colorToCss(other.penColor as Color) : '#CCC' }
                        opacity={ 100 }
                    >
                    </Path>
                )
            }) }
        </>
    )
}

function MultiplayerGuides() { 
    return (
        <>
            <Cursors></Cursors>
            <Drafts></Drafts>
        </>
    )
}

export default memo(MultiplayerGuides)