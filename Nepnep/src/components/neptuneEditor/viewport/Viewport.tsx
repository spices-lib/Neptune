import COLORS from '@/types/colors'
import Canvas from './Canvas'
import ToolsBar from './ToolsBar'

export default function Viewport() {
    
    return (
        <div className={`relative flex items-center justify-center w-full h-full p-[4px] ${COLORS.bg_gray}`}>
            <Canvas></Canvas>
            <ToolsBar></ToolsBar>
        </div>
    )
}