'use client'

import COLORS from '../../types/colors'
import { ReactNode, useEffect, useRef, useState } from 'react'
import MenuItem from './MenuItem'
import Separator from './Separator'

export default function Menu({
    name,
    children
}: {
    name: string
    children: ReactNode[]
}) {
    const [isOpen, setIsOpen] = useState(false)
    const menuRef = useRef<HTMLDivElement>(null)
    
    useEffect(() => {
        const handleClickOutside = (event: MouseEvent) => {
            if (menuRef.current && !menuRef.current.contains(event.target as Node)) {
                setIsOpen(false)
            }
        }

        document.addEventListener('mousedown', handleClickOutside)
        
        return document.removeEventListener('mousedown', handleClickOutside)
    }, [])
    
    return (
        <div 
            className='relative flex'
            ref={ menuRef }
        >
            <button
                className={`px-1 py-0 text-xs h-full hover:bg-[${COLORS.hover}] text-[${COLORS.text}] flex items-center`}
                onClick={ () => setIsOpen(!isOpen) }
            >
                { name }
            </button>
            { isOpen && 
                <div
                    className={`absolute top-full left-0 mt-1 min-w-[310px] bg-[${COLORS.menuBgColor}]`}
                >
                    <div className={`flex w-full flex-col bg-[${COLORS.separatorBg}] p-1.25`}>
                        <Separator color={COLORS.separatorText_gray}></Separator>
                    </div>
                    { children && 
                        <div className='py-0.25'>
                            {
                                children.map((child) => child)
                            }
                        </div>
                    }
                </div>
            }
        </div>
    )
}