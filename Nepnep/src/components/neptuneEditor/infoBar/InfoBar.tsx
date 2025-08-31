import COLORS from '../../../types/colors'
import { PiWarningFill } from 'react-icons/pi'

export default function InfoBar() {
    const info = {
        warning: 'This is a ssssssssssssssssssssswarning!',
        string: 'https://thumbs/256*25',
        progress: 28
    }
    
    return (
        <div className={`relative flex p-2 items-center justify-between w-full h-full ${COLORS.bg_gray}`}>
            <div className={`flex items-center justify-center ${COLORS.text_warn} text-[11px] gap-1 whitespace-nowrap`}>
                <div className='w-[20px] h-[14px]'>
                    <PiWarningFill className='h-4 w-4'></PiWarningFill>
                </div>
                <span>
                    WARNING!
                </span>
                <span>
                    { info.warning }
                </span>
            </div>
            <div className={`flex items-center justify-center ${COLORS.text} text-[11px] gap-1`}>
                <div>
                    <span>
                        { info.string }
                    </span>
                </div>
                <div className={`w-[200px] h-full flex items-center justify-start ${COLORS.bg_black}`}>
                    <div className={`w-[56px] h-full left-0 ${COLORS.progress_blue}`}/>
                    <div className='px-2'>
                        <span> { info.progress } </span>
                    </div>
                </div>
            </div>
        </div>
    )
}