import COLORS from '../../types/colors'
import Separator from './Separator'
import { ReactNode } from 'react'

export default function Menu({
    isLeft,
    children
}: {
    isLeft?: boolean
    children?: ReactNode
}) {
    return (
        <div
            className={`absolute ${ isLeft ? 'left-full top-[-17px]' : 'top-full left-0' } border rounded-md ${COLORS.border_gray} mt-1 whitespace-nowrap ${COLORS.menu_bg_gray}`}
        >
            <div className={`flex w-full flex-col ${COLORS.separator_bg_black} p-1.25`}>
                <Separator color={COLORS.separator_bg_gray}></Separator>
            </div>
            { children ?
                <div className='py-0.25'>
                    { children }
                </div>
                :
                <div className='py-0.25'>
                    <div className={`flex items-center justify-center w-full px-2 gap-2 py-1 ${COLORS.shortcut_gray} text-[11px] ml-auto`}>
                        None
                    </div>
                </div>
            }
        </div>
    )
}