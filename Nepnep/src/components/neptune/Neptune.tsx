import Canvas from './Canvas'

import MainMenu from "../mainMenu/MainMenu";

export default function Neptune() {
    return (
        <div className='flex h-screen w-full'>
            <main className='overflow-y-auto fixed left-0 right-0 h-screen'>
                <div
                    style={{
                        backgroundColor: '#1e1e1e'
                    }}
                    className='h-full w-full touch-none'
                >
                </div>
            </main>
            <MainMenu

            >
            </MainMenu>
        </div>
    )
}