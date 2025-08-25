import { auth } from '../../../server/auth'
import { Room } from '../../../components/liveblocks/Room'
import { Canvas } from '../../../components/canvas/Canvas'
import { redirect, useParams } from 'react-router-dom'
import { db } from '../../../server/DataBase'

export default function Page(){
    const { id } = useParams<{ id: string }>()

    /*const session = await auth()
    
    const room = await db.room.findUnique({
        where: {
            id: id
        },
        select: {
            title: true,
            ownerId: true,
            roomInvites: {
                select: {
                    user: true
                }
            }
        }
    })

    if (!room) {
        redirect('/404')
        return null
    }
    
    const inviteUserIds = room.roomInvites.map((invite) => invite.user,id)
    if (!inviteUserIds.includes(session?.user.id ?? '') && session?.user.id !== room.ownerId) {
        redirect('/404')
        return null
    }*/
    
    const room = {
        title: 'title',
        roomInvites: [
            {
                room: {
                    id: 'id',
                    title: 'title',
                    ownerId: 'ownerId',
                    createdAt: new Date(),
                },
            }
        ]
    }
    
    return (
        <Room
            roomId={ `room:${id!}` }
        >
            <Canvas
                roomName={ room.title }
                roomId={ id! }
               /* otherWithAccessToRoom={ room.roomInvites.map((x) => x.user) }*/
                otherWithAccessToRoom={ [] }
            >
            </Canvas>
        </Room>
    )
}