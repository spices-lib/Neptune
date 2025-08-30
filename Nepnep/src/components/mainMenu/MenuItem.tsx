'use client'

import { ReactNode, useRef, useState} from 'react'
import COLORS from '../../types/colors'

export default function MenuItem({
    name,
    shortcut,
    icon,
}:{
    name: string
    shortcut?: string
    icon?: ReactNode
}) {
    const [isSubmenuOpen, setIsSubmenuOpen] = useState(false)
    const itemRef = useRef<HTMLDivElement>(null)
    
    return (
        <div
            className='relative'
            ref={ itemRef }
        >
            <button className={`flex items-center w-full text-left px-2 gap-2 py-1 text-xs hover:bg-[${COLORS.hover}] text-[${COLORS.text}]`}>
                <div className='flex items-center'>
                    { icon ?? <div className='w-[14px] h-[14px]'></div> }
                </div>
                <div className='flex items-center'>
                    { name }
                </div>
                { shortcut &&
                    <div className={`absolute items-center translate-x-[200px] text-[${COLORS.shortcut}]`}>
                        { shortcut }
                    </div>
                }
            </button>
        </div>
    )
}