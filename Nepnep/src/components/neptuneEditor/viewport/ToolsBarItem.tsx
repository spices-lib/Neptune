import { ReactNode, useEffect, useRef, useState } from 'react'
import COLORS from '@/types/colors'
import Menu from './Menu'

export default function ToolsBarItem({
    icon,
    children
}: {
    icon: ReactNode
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
            className='relative flex'
            ref={menuRef}
        >
            <button 
                className={`relative h-[25px] rounded-[4px] flex items-center justify-center border-2 ${COLORS.border_black} hover:border-2 ${COLORS.text} ${COLORS.hover_blue} ${COLORS.hover_border_blue} ${COLORS.separator_bg_black}`}
                onClick={() => setIsOpen(!isOpen)}
            >
                { icon }
            </button>
            { isOpen && children && <Menu> { children } </Menu> }
        </div>
    )
}