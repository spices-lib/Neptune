import { ReactNode } from 'react'
import COLORS from '../../../types/colors'

export default function PropertyPanel({
    name,
    children
}: {
    name: string,
    children?: ReactNode
}) {
    return (
        <div className={`relative flex flex-col items-start justify-center w-full h-full ${COLORS.bg_black}`}>
            <button
                className={`relative w-[80px] h-[22px] flex items-center justify-start p-2 ${COLORS.bg_gray} text-[11px] ${COLORS.text}`}
                style={{
                    borderTopLeftRadius: '6px',
                    borderTopRightRadius: '6px',
                }}
            >
                <span> { name } </span>
            </button>
            <div className={`relative w-full h-full flex flex-col items-center justify-start ${COLORS.bg_gray}`}>
                { children }
            </div>
        </div>
    )
}