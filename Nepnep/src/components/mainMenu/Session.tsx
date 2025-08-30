'use client'

import { BsFillLightningFill } from 'react-icons/bs'
import { FaAngleDown } from 'react-icons/fa'
import { useEffect, useRef, useState } from 'react'
import COLORS from '../../types/colors'

export default function Session() {
    const [isOpen, setIsOpen] = useState(false)
    const buttonRef = useRef<HTMLButtonElement>(null)
    
    useEffect(() => {
        const handleClickOutside = (event: MouseEvent) => {
            if (buttonRef.current && !buttonRef.current.contains(event.target as Node)) {
                setIsOpen(false)
            }
        }

        document.addEventListener('mousedown', handleClickOutside)

        return () => document.removeEventListener('mousedown', handleClickOutside)
    })
    
    return (
        <div className='relative flex gap-0.5 px-0.75  hover:bg-[#333333]'>
            <button
                className={`px-1 py-0 flex items-center rounded-[2px] text-[12px] bg-[#808080] hover:bg-[#9E9E9E] text-[#F0F0F0] font-500`}
                onClick={ () => setIsOpen(!isOpen) }
            >
                <div className='w-[17px] h-[14px] items-center justify-center'>
                    <BsFillLightningFill className='h-3.5 w-3.5 text-[#E6E63A]'></BsFillLightningFill>
                </div>
                LIVE
            </button>
            <button
                className={`px-1 py-0 flex items-center rounded-[2px] text-[12px] bg-[#808080] hover:bg-[#9E9E9E] text-[#F0F0F0]`}
                onClick={ () => setIsOpen(!isOpen) }
            >
            <FaAngleDown className='h-3 w-3 text-[#C0C0C0]'></FaAngleDown>
            </button>
            { isOpen && 
                <button 
                    className={`absolute top-full right-0 whitespace-nowrap p-2 ${COLORS.menu_bg_gray} ${COLORS.text} text-xs rounded-md`}
                    ref={ buttonRef }
                >
                    Join With Session Link
                </button>
            }
        </div>
    )
}