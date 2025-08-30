import Canvas from './Canvas'

import MainMenu from '../mainMenu/MainMenu'
import InfoBar from '../infoBar/InfoBar'

export default function Neptune() {
    return (
        <div className='flex h-screen w-full'>
            <main className='overflow-y-auto fixed left-0 right-0 h-screen'>
                <div
                    className='h-full w-full touch-none bg-[#1e1e1e]'
                >
                </div>
            </main>
            <MainMenu/>
            <InfoBar/>
        </div>
    )
}