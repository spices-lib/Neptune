import { Liveblocks } from '@liveblocks/node'
import { auth } from '../../auth'
import { db } from '../../DataBase'

const liveblocks = new Liveblocks({
    secret: import.meta.env.VITE_LIVEBLOCKS_PUBLIC_KEY
})

export async function POST(req: Request) {
    const userSession = await auth()
    
    const user = await db.user.findUniqueOrThrow({
        where: { id: userSession?.user.id }
    })
    
    const session = liveblocks.prepareSession(user.id, {
        userInfo: {
            name: user.email ?? 'Anonymous'
        }
    })
    
    session.allow(`room:${'test'}`, session.FULL_ACCESS)
    
    const { status, body } = await session.authorize()
    
    return new Response(body, { status })
}