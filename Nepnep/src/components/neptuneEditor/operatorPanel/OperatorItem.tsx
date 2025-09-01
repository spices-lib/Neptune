import { ReactNode } from 'react'
import COLORS from '@/types/colors'

export default function OperatorItem({
    children
}: {
    children: ReactNode
}){
    return (
        <button className={`relative w-[35px] h-[35px] rounded-[4px] flex items-center justify-center ${COLORS.bg_gray} ${COLORS.hover} ${COLORS.text_operator}`}>
            { children }
        </button>
    )
}