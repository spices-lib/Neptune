'use client'

import { ReactNode, useRef, useState} from 'react'
import COLORS from '../../types/colors'

export default function MenuItem({
    name,
    shortcut,
    icon,
    children
}:{
    name: string
    shortcut?: string
    icon?: ReactNode
    children?: ReactNode
}) {
    const [isSubmenuOpen, setIsSubmenuOpen] = useState(false)
    const itemRef = useRef<HTMLDivElement>(null)
    
    return (
        <div
            className='relative py-0.25'
            ref={ itemRef }
        >
            <button
                className={`flex items-center w-full text-left px-2 gap-2 py-1 text-xs ${COLORS.hover} ${COLORS.text} `}
                onClick={ () => setIsSubmenuOpen(!isSubmenuOpen) }
            >
                <div className='flex items-center'>
                    { icon ?? <div className='w-[14px] h-[14px]'></div> }
                </div>
                <div className='flex items-center text-[11px]'>
                    { name }
                </div>
                { shortcut &&
                    <div className={`items-center ${COLORS.shortcut_gray} text-[11px] ml-auto`}>
                        { shortcut }
                    </div>
                }
                { children && isSubmenuOpen &&
                    <div className={`items-center ${COLORS.shortcut_gray} text-[11px] ml-auto`}>
                        { children }
                    </div>
                }
            </button>
        </div>
    )
}