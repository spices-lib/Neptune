﻿'use client'

import { Room } from '@prisma/client'
import React, { useEffect, useMemo, useRef, useState } from 'react'
import ConfirmationModal from './ConfirmationModal'
import { updateRoomTitle, deleteRoom } from '../../app/actions/rooms'

const PASTEL_COLORS = [
    'rgb(255, 182, 193)', // pink
    'rgb(176, 224, 230)', // powder blue
    'rgb(221, 160, 221)', // plum
    'rgb(188, 143, 143)', // rosy brown
    'rgb(152, 251, 152)', // pale green
    'rgb(238, 232, 170)', // pale goldenrod
    'rgb(230, 230, 250)', // lavender
    'rgb(255, 218, 185)', // peach
]

function ViewModeButton({
    onSelect, 
    active, 
    text
}: {
    onSelect: () => void
    active: boolean
    text: string
}) {
    return (
        <button 
            onClick={ onSelect }
            className={`select-none rounded-md p-1 px-2 text-[11px] hover:bg-gray-200 ${active ? 'bg-gray-100' : ''}`}
        >
            { text }
        </button>
    )
}

function SingleRoom({ 
    id, 
    title,
    description,
    color, 
    selected,
    select, 
    navigateTo,
    canEdit
}: {
    id: string
    title: string
    description: string
    color: string
    selected: boolean
    select: () => void
    navigateTo: () => void
    canEdit: boolean
}) {
    const [isEditing, setIsEditing] = useState(false)
    const [editedTitle, setEditedTitle] = useState(title)
    const [showConfirmationModal, setShowConfirmationModal] = useState(false)
    
    const handleKeyPress = async (event: React.KeyboardEvent<HTMLInputElement>) => {
        if (event.key === 'Enter') {
            event.preventDefault()
            setIsEditing(false)
            await updateRoomTitle(editedTitle, id)
        }
    }
    
    const handleBlur = async () => {
        setIsEditing(false)
        await updateRoomTitle(editedTitle, id)
    }
    
    const confirmDelete = async () => {
        await deleteRoom(id)
        setShowConfirmationModal(false)
    }
    
    useEffect(() => {
        const handleKeyDown = (e: KeyboardEvent) => {
            if (e.key === 'Backspace' && selected && !isEditing) {
                e.preventDefault()
                setShowConfirmationModal(true)
            }
        }
        
        document.addEventListener('keydown', handleKeyDown)
        
        return () => document.removeEventListener('keydown', handleKeyDown)
    }, [selected, id, isEditing])
    
    return (
        <div className='flex flex-col gap-0.5'>
            <div 
                onDoubleClick={ navigateTo }
                onClick={ select }
                style={{backgroundColor: color}}
                className={`flex h-56 w-96 cursor-pointer items-center justify-center rounded-md ${selected ? 'border-2 border-blue-500' : 'border border-[#e8e8e8]'}`}
            >
                <p
                    className='text-md select-none font-medium'
                > 
                    { title }
                </p>
            </div>
            { isEditing && canEdit ? 
                <input
                    type='text'
                    value={ editedTitle }
                    onChange={(e) => setEditedTitle(e.target.value)}
                    onBlur={ handleBlur }
                    onKeyDown={ handleKeyPress }
                    autoFocus
                    className='w-full'
                >
                </input>
                :
                <p
                    onClick={ () => setIsEditing(true) }
                    className='mt-2 select-none text-[13px] font-medium'
                >
                    { title }
                </p>
            }
            <p
                className='select-none text-[10px] text-gray-400'
            >
                { description }
            </p>
            <ConfirmationModal
                isOpen={ showConfirmationModal }
                onClose={ ()=> setShowConfirmationModal(false) }
                onConfirm={ confirmDelete }
                message='Are you sure delete this room'
            >
            </ConfirmationModal>
        </div>
    )
}

export default function RoomsView({
    ownedRooms, 
    roomInvites
}: {
    ownedRooms: Room[]
    roomInvites: Room[]
}) {
    const [viewMode, setViewMode] = useState('owns')
    const [selected, setSelected] = useState<string | null>(null)
    const outerDivRef = useRef<HTMLDivElement>(null)
    
    const filteredRooms = useMemo(() => {
        if (viewMode === 'owns') {
            return ownedRooms
        }
        else if (viewMode === 'shared') {
            return roomInvites
        }
        return []
    }, [viewMode, ownedRooms, roomInvites])
    
    const roomColors = useMemo(() => {
        return filteredRooms.map((room, index) => ({
            id: room.id,
            color: PASTEL_COLORS[index % PASTEL_COLORS.length]
        }))
    }, [filteredRooms])
    
    useEffect(() => {
        const handleClickOutside = (e: MouseEvent) => {
            if (outerDivRef.current && !outerDivRef.current.contains(e.target as Node)) {
                setSelected(null)
            }
        }
        
        document.addEventListener('mousedown', handleClickOutside)
        
        return () => document.removeEventListener('mousedown', handleClickOutside)
    }, [])
    
    return (
        <div 
            ref={ outerDivRef }
            className='flex flex-col gap-5'
        >
            <div className='flex gap-1'>
                <ViewModeButton
                    onSelect={ () => setViewMode('owns') }
                    active={ viewMode === 'owns' }
                    text= 'My project'
                ></ViewModeButton>
                <ViewModeButton
                    onSelect={ () => setViewMode('shared') }
                    active={ viewMode === 'shared' }
                    text= 'Shared files'
                ></ViewModeButton>
            </div>
            <div className='flex flex-wrap gap-4'>
                { filteredRooms.map((room) => {
                    const roomColor = roomColors.find((rc) => rc.id === room.id)?.color ?? PASTEL_COLORS[0]!

                    return (
                        <React.Fragment
                            key={ room.id }
                        >
                            <SingleRoom
                                id = { room.id }
                                title={ room.title }
                                description={`Created ${room.createdAt.toDateString()}`}
                                color={ roomColor }
                                selected={ selected === room.id }
                                select={ () => setSelected(room.id) }
                                navigateTo={ () => {} }
                                canEdit={ viewMode === 'owns' }
                            >
                            </SingleRoom>
                        </React.Fragment>
                    )
                }) }
            </div>
        </div>
    )
}