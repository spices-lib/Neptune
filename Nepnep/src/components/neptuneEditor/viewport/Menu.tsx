import COLORS from '../../../types/colors'
import Separator from '../mainMenu/Separator'
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
            className={`absolute flex flex-col ${ isLeft ? 'left-full top-[-17px]' : 'top-full left-0' } border ${COLORS.border_gray} mt-1 whitespace-nowrap ${COLORS.menu_bg_gray}`}
            style={{
                borderBottomLeftRadius: '6px',
                borderBottomRightRadius: '6px',
            }}
        >
            <div className={`flex w-full ${COLORS.separator_bg_black} p-1.25`}>
                <Separator color={COLORS.separator_bg_gray}></Separator>
            </div>
            { children ?
                <div className='py-0.25'>
                    { children }
                </div>
                :
                <div className='py-0.25'>
                    <div className={`flex w-full px-2 py-1 ${COLORS.shortcut_gray} text-[11px] ml-auto`}>
                        None
                    </div>
                </div>
            }
        </div>
    )
}