import { ReactNode, useEffect, useRef, useState } from 'react'
import COLORS from '@/types/colors'
import { RiArrowLeftDoubleLine, RiArrowRightDoubleLine } from 'react-icons/ri'

export default function SideBar({
    children
}: {
    children?: ReactNode
}){
    const [isOpen, setIsOpen] = useState(false)
    const menuRef = useRef<HTMLDivElement>(null)

    useEffect(() => {
        const handleClickOutside = (event: MouseEvent) => {
            if (menuRef.current && !menuRef.current.contains(event.target as Node)) {
                setIsOpen(false)
            }
        }

        document.addEventListener('mousedown', handleClickOutside)

        return () => document.removeEventListener('mousedown', handleClickOutside)
    }, [])
    
    return (
        <div 
            className='relative flex items-center justify-start'
            ref={menuRef}
        >
            { !isOpen &&
                <div className='w-full h-full flex items-center justify-start'>
                    <button 
                        className={`relative h-[25px] rounded-[4px] flex items-center justify-center border-2 hover:border-2 ${COLORS.border_black} ${COLORS.text} ${COLORS.hover_blue} ${COLORS.hover_border_blue} ${COLORS.separator_bg_black}`}
                        onClick={() => setIsOpen(true)}
                    >
                        <div className='w-[15px] h-full flex items-center justify-center'>
                            <RiArrowRightDoubleLine></RiArrowRightDoubleLine>
                        </div>
                    </button>
                </div>
            }
            { isOpen &&
                { children } &&
                <div className='w-full h-full flex items-center justify-start'>
                    <button
                        className={`relative h-[25px] rounded-[4px] flex items-center justify-center border-2 hover:border-2 ${COLORS.border_black} ${COLORS.text} ${COLORS.hover_blue} ${COLORS.hover_border_blue} ${COLORS.separator_bg_black}`}
                        onClick={() => setIsOpen(false)}
                    >
                        <div className='w-[15px] h-full flex items-center justify-center'>
                            <RiArrowLeftDoubleLine></RiArrowLeftDoubleLine>
                        </div>
                    </button>
                </div>
            }
        </div>
    )
}