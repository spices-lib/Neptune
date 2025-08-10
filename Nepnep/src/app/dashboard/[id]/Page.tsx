import { auth } from '../../../server/auth'
import { Room } from '../../../components/liveblocks/Room'
import { Canvas } from '../../../components/canvas/Canvas'
import { useParams } from 'react-router-dom'

export default function Page(){
    const { id } = useParams<{ id: string }>()

    //const session = auth()

    return (
        <Room
            roomId={ `room:${id}` }
        >
            <Canvas></Canvas>
        </Room>
    )
}