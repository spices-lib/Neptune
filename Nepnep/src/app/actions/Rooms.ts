import { auth } from '../../server/auth'
import { db } from '../../server/DataBase'
import { redirect } from 'react-router-dom'
import { ROUTE_PATHS } from '../routes/RoutePaths'

export async function createRoom() {
    const session = await auth()
    
    if (!session?.user.id) {
        throw new Error('No user id found.')
    }
    
    const room = await db.room.create({
        data: {
            owner: {
                connect: {
                    id: session.user.id
                }
            }
        },
        select: {
            id: true
        }
    })
    
    redirect(ROUTE_PATHS.USER_DASHBOARD)
}