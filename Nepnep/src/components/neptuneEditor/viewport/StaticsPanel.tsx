import COLORS from '@/types/colors'

export default function StaticsPanel(){
    return (
        <div className={`relative rounded-[4px] flex flex-col items-end justify-center ${COLORS.text} text-[11px] p-2 ${COLORS.separator_bg_black}`}>
            <span>FPS: 0.00, Frame time: 0.00 ms</span>
            <span>Process Memory: 1.8 GiB used, 34.8 GiB available</span>
            <span>2560*1440</span>
        </div>
    )
}