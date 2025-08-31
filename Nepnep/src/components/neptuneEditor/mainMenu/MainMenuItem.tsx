'use client'

import COLORS from '../../../types/colors'
import { ReactNode, useEffect, useRef, useState } from 'react'
import Menu from './Menu'

export default function MainMenuItem({
    name,
    children
}: {
    name: string
    children?: ReactNode
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
        
        return () => document.removeEventListener('mousedown', handleClickOutside)
    }, [])
    
    return (
        <div 
            className='relative flex'
            ref={ menuRef }
        >
            <button
                className={`px-1 py-0 ${COLORS.hover} ${COLORS.text} flex items-center text-[12px]`}
                onClick={ () => setIsOpen(!isOpen) }
            >
                { name }
            </button>
            { isOpen && <Menu> { children } </Menu> }
        </div>
    )
}