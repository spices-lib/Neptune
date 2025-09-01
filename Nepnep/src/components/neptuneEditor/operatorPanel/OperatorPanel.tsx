import COLORS from '../../../types/colors'
import Separator from '@/components/neptuneEditor/mainMenu/Separator'
import OperatorItem from './OperatorItem'
import { IoMdPlay } from 'react-icons/io'
import { LuImageUpscale } from 'react-icons/lu'
import { FaMousePointer } from 'react-icons/fa'
import { TiArrowMove } from 'react-icons/ti'
import { FaRotate } from 'react-icons/fa6'
import { BiSolidMagnet } from 'react-icons/bi'
import { PiCubeFocusFill } from 'react-icons/pi'
import { GrPauseFill } from 'react-icons/gr'
import { IoStopSharp } from 'react-icons/io5'

export default function OperatorPanel() {
    return (
        <div className={`relative flex flex-col items-center justify-start w-full h-full py-2 gap-[2.5px] ${COLORS.bg_gray}`}>
            <div className='flex flex-col items-start justify-start w-full h-[20px] gap-0.5'>
                <Separator color='bg-[#343434]' height='h-[3px]'></Separator>
                <Separator color='bg-[#343434]' height='h-[3px]'></Separator>
                <Separator color='bg-[#343434]' height='h-[3px]'></Separator>
            </div>
            <OperatorItem>
                <PiCubeFocusFill className='h-10 w-10'></PiCubeFocusFill>
            </OperatorItem>
            <OperatorItem>
                <FaMousePointer className='h-6 w-6'></FaMousePointer>
            </OperatorItem>
            <OperatorItem>
                <TiArrowMove className='h-8 w-8'></TiArrowMove>
            </OperatorItem>
            <OperatorItem>
                <FaRotate className='h-6 w-6'></FaRotate>
            </OperatorItem>
            <OperatorItem>
                <LuImageUpscale className='h-6 w-6'></LuImageUpscale>
            </OperatorItem>
            <Separator color='bg-[#555555]'></Separator>
            <OperatorItem>
                <BiSolidMagnet className='h-6 w-6'></BiSolidMagnet>
            </OperatorItem>
            <Separator color='bg-[#555555]'></Separator>
            <OperatorItem>
                <IoMdPlay className='h-6 w-6'></IoMdPlay>
            </OperatorItem>
            <OperatorItem>
                <GrPauseFill className='h-6 w-6'></GrPauseFill>
            </OperatorItem>
            <OperatorItem>
                <IoStopSharp className='h-7 w-7'></IoStopSharp>
            </OperatorItem>
        </div>
    )
}