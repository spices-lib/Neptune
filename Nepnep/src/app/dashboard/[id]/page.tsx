import { auth } from '../../../server/auth'
import { Room } from '../../../components/liveblocks/Room'
import { Canvas } from '../../../components/canvas/Canvas'
import NeptuneEditor from '../../../components/neptuneEditor/NeptuneEditor'
import { redirect } from 'next/navigation'
import { db } from '../../../server/db'

export default async function Page({ 
    params 
}: { 
    params: Promise<{ id: string }> 
}){
    const { id } = await params

    const session = await auth()
    
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
    
    const inviteUserIds = room.roomInvites.map((invite) => invite.user.id)
    if (!inviteUserIds.includes(session?.user.id ?? '') && session?.user.id !== room.ownerId) {
        redirect('/404')
        return null
    }
    
    return (
        <Room
            roomId={ `room:${id!}` }
        >
            {/*<Canvas
                roomName={ room.title }
                roomId={ id! }
                othersWithAccessToRoom={ room.roomInvites.map((x) => x.user) }
            >
            </Canvas>*/}
            <NeptuneEditor></NeptuneEditor>
        </Room>
    )
}