import COLORS from '@/types/colors'
import NeptuneCanvas from './NeptuneCanvas'
import ToolsBar from './ToolsBar'

export default function Viewport() {
    
    return (
        <div className={`relative flex items-center justify-center w-full h-full p-[4px] ${COLORS.bg_gray}`}>
            <div className='absolute w-full h-full flex p-[4px]'>
                <NeptuneCanvas></NeptuneCanvas>
            </div>
            <div className='absolute w-full h-full flex p-[8px]'>
                <ToolsBar></ToolsBar>
            </div>
        </div>
    )
}