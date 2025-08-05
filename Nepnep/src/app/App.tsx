import { Neptune } from '../components/neptune/Neptune'
import { Room } from '../components/liveblocks/Room'

//import { Inter } from 'next/font/google'
import { StrictMode } from 'react'
import { AppRoutes } from './routes/AppRoutes'

/*const inter = Inter({
    subsets: ['latin'],
    display: 'swap'
})*/

export function App() {
    return (
        /*<Room>
            <Neptune></Neptune>
        </Room>*/

            <StrictMode>
                <AppRoutes></AppRoutes>
            </StrictMode>
    )
}