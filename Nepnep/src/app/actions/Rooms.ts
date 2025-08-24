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

export async function updateRoomTitle(title: string, id: string) {
    const session = await auth()

    if (!session?.user.id) {
        throw new Error('No user id found.')
    }
    
    await db.room.findUniqueOrThrow({
        where: {
            id: id,
            ownerId: session.user.id
        }
    })
    
    await db.room.update({
        where: {
            id: id
        },
        data: {
            title: title
        }
    })

    redirect(ROUTE_PATHS.DASHBOARD)
}

export async function deleteRoom(id: string) {
    const session = await auth()

    if (!session?.user.id) {
        throw new Error('No user id found.')
    }

    await db.room.findUniqueOrThrow({
        where: {
            id: id,
            ownerId: session.user.id
        }
    })
    
    await db.room.delete({
        where: {
            id: id
        }
    })

    redirect(ROUTE_PATHS.DASHBOARD)
}

export async function shareRoom(id: string, inviteEmail: string) {
    const session = await auth()

    if (!session?.user.id) {
        throw new Error('No user id found.')
    }

    await db.room.findUniqueOrThrow({
        where: {
            id: id,
            ownerId: session.user.id
        }
    })
    
    const inviteUser = await db.user.findUniqueOrThrow({
        where: {
            email: inviteEmail
        },
        select: {
            id: true
        }
    })
    
    await db.roomInvite.create({
        data: {
            roomId: id,
            userId: inviteUser.id
        }
    })

    redirect(ROUTE_PATHS.DASHBOARD)
}

export async function deleteInvitation(id: string, inviteEmail: string) {
    const session = await auth()

    if (!session?.user.id) {
        throw new Error('No user id found.')
    }

    await db.room.findUniqueOrThrow({
        where: {
            id: id,
            ownerId: session.user.id
        }
    })

    await db.roomInvite.deleteMany({
        where: {
            roomId: id,
            user: {
                email: inviteEmail
            }
        }
    })

    redirect(ROUTE_PATHS.DASHBOARD)
}