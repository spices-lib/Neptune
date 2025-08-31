'use client'

import COLORS from '../../../types/colors'
import { FaSearch } from 'react-icons/fa'
import { ReactNode } from 'react'
import { MdFilterAlt } from 'react-icons/md'
import { PiListBold } from 'react-icons/pi'

export default function SearchBar({
    searchString,
    filterItem,
    OptionItem,
}: {
    searchString: string
    filterItem?: ReactNode
    OptionItem?: ReactNode
}) {
    const setSearchString = (str: string) => {
        searchString = str
    }
    
    return (
        <div className={`relative flex items-center justify-center w-full h-full ${COLORS.bg_gray} text-[11px] ${COLORS.text} p-1 gap-1`}>
            <div className={`flex items-center justify-start w-full h-full ${COLORS.bg_black} ${COLORS.shortcut_gray}`}>
                { searchString === '' &&
                    <div className='fixed flex items-center justify-center px-2 gap-2'>
                        <FaSearch className='w-3 h-3'></FaSearch>
                        <span> Search </span>
                    </div> 
                }
                <input
                    className='w-full h-full border-gray-300 focus:border-black pl-2'
                    type='text'
                    value={ searchString }
                    onChange={ (e) => setSearchString(e.target.value) }
                >
                </input>
            </div>
            <button className={`flex items-center justify-center ${COLORS.hover}`}>
                <MdFilterAlt className={`h-4 w-4 text-[#A0A0A0]`}></MdFilterAlt>
            </button>
            <button className={`flex items-center justify-center ${COLORS.hover}`}>
                <PiListBold className={`h-4 w-4 text-[#A0A0A0]`}></PiListBold>
            </button>
        </div>
    )
}