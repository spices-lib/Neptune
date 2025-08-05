import { Neptune } from '../components/neptune/Neptune'
import { Room } from '../components/liveblocks/Room'

//import { Inter } from 'next/font/google'
import { StrictMode } from 'react'
import Page from './signin/Page'

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
                <Page></Page>
        </StrictMode>
    )
}