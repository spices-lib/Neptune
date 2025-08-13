import IconButton from './IconButton'
import { AiOutlineZoomOut } from 'react-icons/ai'

export default function ZoomOutButton({
    onClick,
    disabled
}: {
    onClick: () => void
    disabled: boolean
}) {
    return (
        <IconButton
            onClick={ onClick }
            isActive = { true }
            disabled={ disabled }
        >
            <AiOutlineZoomOut
                size = { 22 }
                color='#888888'
            >
            </AiOutlineZoomOut>
        </IconButton>
    )
}