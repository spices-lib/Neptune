import { signout } from '../actions/Auth'
import { auth } from '../../server/auth'
import { db } from '../../server/DataBase'
import UserMenu from '../../components/dashboard/UserMenu'
import CreateRoom from '../../components/dashboard/CreateRoom'
import RoomsView from '../../components/dashboard/RoomsView'

export default function Page() {
    /*const session = await auth()
    
    const user = await db.user.findUniqueOrThrow({
        where: {
            id: session?.user.id
        },
        include: {
            ownedRooms: true,
            roomInvites: {
                include: {
                    room: true
                }
            }
        }
    })*/

    const user = {
        email: 'spiecs@outlook.com',
        ownedRooms: [
            {
                id: 'id',
                title: 'title',
                ownerId: 'ownerId',
                createdAt: new Date()
            }
        ],
        roomInvites: [
            {
                room: {
                    id: 'id',
                    title: 'title',
                    ownerId: 'ownerId',
                    createdAt: new Date()
                }
            }
        ]
    }
    
    return (
        <div className='flex h-screen w-full'>
            <div className='flex h-screen min-w-[264px] flex-col border-r border-gray-200 bg-white p-2'>
                <UserMenu
                    email={ user.email }
                >
                </UserMenu>
            </div>
            <div className='flex h-screen w-full flex-col'>
                <div className='flex min-h-[50px] items-center border-b border-gray-200 bg-white pl-8'>
                    <h2 className='text-[13px]'>Recents</h2>
                </div>
                <div className='flex h-full flex-col gap-10 p-8'>
                    <CreateRoom></CreateRoom>
                    <RoomsView
                        ownedRooms={ user.ownedRooms }
                        roomInvites={ user.roomInvites.map((x) => x.room) }
                    ></RoomsView>
                </div>
            </div>
        </div>
    )
}