import COLORS from '../../types/colors'

export default function Separator({
    text,
    color,
    height
}: {
    text?: string
    color?: string
    height?: string
}) {
    return (
        <div className='flex w-full items-center'>
            { text && <div className={`text-[11px] left-0 px-2 ${COLORS.separator_text_white}`}> { text } </div> }
            <div className={`flex w-full ${height ?? 'h-[1px]'} mx-1.5 ${color ?? COLORS.separator_bg_white}`}/>
        </div>
    )
}