import COLORS from '@/types/colors'
import Canvas from './Canvas'

export default function Viewport() {
    
    return (
        <div className={`relative flex items-center justify-center w-full h-full p-[4px] ${COLORS.bg_gray}`}>
            <Canvas></Canvas>
        </div>
    )
}