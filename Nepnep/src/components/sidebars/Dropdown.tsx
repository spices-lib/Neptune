﻿import { ChangeEvent, useEffect, useState } from 'react'

export default function Dropdown({
    value, 
    onChange,
    options, 
    className
}: {
    value: string
    onChange: (value: string) => void
    options: string[]
    className?: string
}) {
    const [selectValue, setSelectValue] = useState(value)
    
    useEffect(() => {
        setSelectValue(value)
    }, [value])
    
    const handleChange = (e: ChangeEvent<HTMLSelectElement>) => {
        const newValue = e.target.value
        setSelectValue(newValue)
        onChange(newValue)
    }
    
    return (
        <div className={`relative ${className ?? ''}`}>
            <select
                value={ selectValue }
                onChange={ handleChange }
                className='w-full rounded-lg border border-[#e8e8e8] bg-[#f5f5f5] px-2 py-1 text-xs hover:bg-[#e8e8e8]'
            >
                { options.map((option) => (
                    <option 
                        key={ option } 
                        value={ option }
                    >
                        { option }
                    </option>
                ))}
            </select>
        </div>
    )
}