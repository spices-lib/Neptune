import PropertyPanel from './PropertyPanel'
import Separator from '@/components/neptuneEditor/mainMenu/Separator'
import { FiDelete } from 'react-icons/fi'
import COLORS from '@/types/colors'
import { SlNote } from 'react-icons/sl'
import { FaFolderOpen } from 'react-icons/fa'
import { GoCommandPalette } from 'react-icons/go'
import { MdFilterAlt } from 'react-icons/md'
import { LuSnowflake } from 'react-icons/lu'
import { FaInfoCircle } from 'react-icons/fa'
import { IoWarningSharp } from 'react-icons/io5'
import { GoXCircleFill } from 'react-icons/go'

export default function Console() {
    return (
        <PropertyPanel
            name='Console'
        >
            <div className='flex w-full h-[30px] flex items-center justify-between'>
                <div className='h-full flex items-center justify-start px-[4px]'>
                    <button className={`${COLORS.text} ${COLORS.hover}`}>
                        <div className='h-[22px] w-[22px] flex items-center justify-center'>
                            <FiDelete></FiDelete>
                        </div>
                    </button>
                    <button className={`${COLORS.text} ${COLORS.hover}`}>
                        <div className='h-[22px] w-[22px] flex items-center justify-center'>
                            <SlNote></SlNote>
                        </div>
                    </button>
                    <button className={`${COLORS.text} ${COLORS.hover}`}>
                        <div className='h-[22px] w-[22px] flex items-center justify-center'>
                            <FaFolderOpen></FaFolderOpen>
                        </div>
                    </button>
                    <button className={`${COLORS.text} ${COLORS.hover}`}>
                        <div className='h-[22px] w-[22px] flex items-center justify-center'>
                            <GoCommandPalette></GoCommandPalette>
                        </div>
                    </button>
                </div>
                <div className='h-full flex items-center justify-start'>
                    <button className={`${COLORS.text} ${COLORS.hover}`}>
                        <div className='h-[22px] w-[22px] flex items-center justify-center'>
                            <MdFilterAlt className='w-[20px] h-[20px]'></MdFilterAlt>
                        </div>
                    </button>
                    <button className={`${COLORS.text} ${COLORS.hover}`}>
                        <div className='h-[22px] w-[22px] flex items-center justify-center'>
                            <LuSnowflake></LuSnowflake>
                        </div>
                    </button>
                    <button className={`${COLORS.text} ${COLORS.hover}`}>
                        <div className='h-[22px] w-[22px] flex items-center justify-center'>
                            <FaInfoCircle></FaInfoCircle>
                        </div>
                    </button>
                    <button className={`${COLORS.text} ${COLORS.hover}`}>
                        <div className={`h-[22px] w-[34px] flex items-center justify-center gap-[2px] ${COLORS.text_warn}`}>
                            <IoWarningSharp></IoWarningSharp>
                            <div className='w-[12px] h-full flex items-center justify-center'>
                                <span className='text-[12px]'> 16 </span>
                            </div>
                        </div>
                    </button>
                    <button className={`${COLORS.text} ${COLORS.hover} px-[2px]`}>
                        <div className={`h-[22px] w-[34px] flex items-center justify-center gap-[4px] ${COLORS.text_error}`}>
                            <GoXCircleFill></GoXCircleFill>
                            <div className='w-[12px] h-full flex items-center justify-center'>
                                <span className='text-[12px]'> 16 </span>
                            </div>
                        </div>
                    </button>
                    <div className='w-[180px] h-full flex items-center justify-start p-[4px]'>
                        <div className={`fixed flex items-center justify-center px-2 gap-2 text-[11px] ${COLORS.shortcut_gray}`}>
                            <span> Search </span>
                        </div>
                        <input
                            className={`w-full h-full ${COLORS.bg_black}`}
                            type='text'
                        >
                        </input>
                    </div>
                </div>
            </div>
            <Separator color={`${COLORS.bg_black}`}></Separator>
            <div className='w-full h-full flex items-center justify-center p-[4px]'>
                <div className={`w-full h-full ${COLORS.bg_black}`}></div>
            </div>
        </PropertyPanel>
    )
}