import COLORS from '@/types/colors'
import ToolsBarItem from '@/components/neptuneEditor/viewport/ToolsBarItem'
import { FaList } from 'react-icons/fa'
import MenuItem from '@/components/neptuneEditor/viewport/MenuItem'
import Separator from '@/components/neptuneEditor/mainMenu/Separator'
import { FaRegLightbulb } from 'react-icons/fa6'
import { ImEye } from 'react-icons/im'
import { BsCameraReelsFill } from 'react-icons/bs'
import SideBar from '@/components/neptuneEditor/viewport/SideBar'
import { LiaWaveSquareSolid } from 'react-icons/lia'
import { MdLightMode } from 'react-icons/md'
import StaticsPanel from '@/components/neptuneEditor/viewport/StaticsPanel'

export default function ToolsBar(){
    return (
        <div className='w-full h-full flex flex-col items-center justify-between'>
            <div className='w-full flex flex-col items-center justify-start gap-[6px]'>
                <div className='w-full flex items-center justify-between'>
                    <div className='flex items-center justify-start gap-[4px]'>
                        <div className='flex items-center justify-start gap-[12px]'>
                            <ToolsBarItem
                                icon={
                                    <div className='w-[25px] h-full flex items-center justify-center'>
                                        <FaList></FaList>
                                    </div>
                                }
                            >
                                <MenuItem name='Navigation'></MenuItem>
                                <MenuItem name='Selection'></MenuItem>
                                <MenuItem name='Grid'></MenuItem>
                                <MenuItem name='Grizmos'></MenuItem>
                                <MenuItem name='Viewport'></MenuItem>
                                <MenuItem name='Viewport UI'></MenuItem>
                                <MenuItem name='Manipulator Transform'></MenuItem>
                                <Separator></Separator>
                                <MenuItem name='Reset To Defaults'></MenuItem>
                                <Separator></Separator>
                                <MenuItem name='Preferences'></MenuItem>
                            </ToolsBarItem>
                            <ToolsBarItem
                                icon={
                                    <div className='h-full flex items-center justify-center px-2'>
                                        <div className='w-[25px] h-full flex items-center justify-between'>
                                            <FaRegLightbulb></FaRegLightbulb>
                                        </div>
                                        <div className='text-[12px]'>
                                            <span> RTX - Real-Time</span>
                                        </div>
                                    </div>
                                }
                            >
                                <MenuItem name='RTX-Interactive(Path Tracing)'></MenuItem>
                                <MenuItem name='RTX-Real-Time 2.0'></MenuItem>
                                <Separator text='Rendering Settings'></Separator>
                                <MenuItem name='Load from Preset'></MenuItem>
                                <MenuItem name='Save Current as Preset'></MenuItem>
                                <MenuItem name='Reset to Default'></MenuItem>
                                <Separator text='Rendering Mode'></Separator>
                                <MenuItem name='Default'></MenuItem>
                                <MenuItem name='Wireframe' shortcut='Shift + W'></MenuItem>
                                <MenuItem name='Debug View'></MenuItem>
                                <Separator></Separator>
                                <MenuItem name='Camera Light'></MenuItem>
                                <MenuItem name='Disable Materials(White Mode)'></MenuItem>
                                <Separator></Separator>
                                <MenuItem name='Preferences'></MenuItem>
                            </ToolsBarItem>
                            <ToolsBarItem
                                icon={
                                    <div className='w-[25px] h-full flex items-center justify-center'>
                                        <ImEye></ImEye>
                                    </div>
                                }
                            >
                                <MenuItem name='Heads Up Display'></MenuItem>
                                <MenuItem name='Show By Type'></MenuItem>
                                <MenuItem name='Show By Purpose'></MenuItem>
                                <Separator></Separator>
                                <MenuItem name='Selection Outline'></MenuItem>
                                <MenuItem name='Axis'></MenuItem>
                                <MenuItem name='Grid' shortcut='G'></MenuItem>
                                <MenuItem name='Bounding Box'></MenuItem>
                            </ToolsBarItem>
                            <ToolsBarItem
                                icon={
                                    <div className='h-full flex items-center justify-center px-2'>
                                        <div className='w-[25px] h-full flex items-center justify-between'>
                                            <BsCameraReelsFill></BsCameraReelsFill>
                                        </div>
                                        <div className='text-[12px]'>
                                            <span> Perspective</span>
                                        </div>
                                    </div>
                                }
                            >
                                <MenuItem name='Camera'></MenuItem>
                                <MenuItem name='Perspective'></MenuItem>
                                <MenuItem name='Top'></MenuItem>
                                <MenuItem name='Front'></MenuItem>
                                <MenuItem name='Right'></MenuItem>
                                <Separator></Separator>
                                <MenuItem name='Sequencer Camera Sync'></MenuItem>
                                <Separator></Separator>
                                <MenuItem name='Create from View'></MenuItem>
                            </ToolsBarItem>
                        </div>
                        <SideBar>
                        </SideBar>
                    </div>
                    <div className='flex items-center justify-start gap-[12px]'>
                        <ToolsBarItem
                            icon={
                                <div className='h-full flex items-center justify-center px-2'>
                                    <div className='w-[25px] h-full flex items-center justify-between'>
                                        <LiaWaveSquareSolid></LiaWaveSquareSolid>
                                    </div>
                                    <div className='text-[12px]'>
                                        <span>No Pacing</span>
                                    </div>
                                </div>
                            }
                        >
                            <Separator text='Pacing Speed'></Separator>
                            <MenuItem name='No Pacing'></MenuItem>
                            <MenuItem name='60'></MenuItem>
                        </ToolsBarItem>
                        <ToolsBarItem
                            icon={
                                <div className='h-full flex items-center justify-center px-2'>
                                    <div className='w-[25px] h-full flex items-center justify-between'>
                                        <MdLightMode></MdLightMode>
                                    </div>
                                    <div className='text-[12px]'>
                                        <span>Stage Lights</span>
                                    </div>
                                </div>
                            }
                        >
                            <MenuItem name='Lights Off'></MenuItem>
                            <MenuItem name='Camera Light'></MenuItem>
                            <MenuItem name='Stage Lights'></MenuItem>
                            <Separator text='Light Rigs'></Separator>
                            <MenuItem name='Blue Sky'></MenuItem>
                            <MenuItem name='Colored Lights'></MenuItem>
                            <MenuItem name='Default'></MenuItem>
                            <MenuItem name='Grey Sky'></MenuItem>
                            <MenuItem name='Grey Studio'></MenuItem>
                            <MenuItem name='High Contrast'></MenuItem>
                            <MenuItem name='Neutral Lighting'></MenuItem>
                            <MenuItem name='Sunny Sky'></MenuItem>
                            <Separator></Separator>
                            <MenuItem name='Use auto light rig on startup'></MenuItem>
                            <Separator></Separator>
                            <MenuItem name='Add Current Light Rig to Stage'></MenuItem>
                        </ToolsBarItem>
                    </div>
                </div>
                <div className='w-full flex items-center justify-end'>
                    <StaticsPanel></StaticsPanel>
                </div>
            </div>
            <div className='w-full flex flex-col items-start justify-center'>
                <ToolsBarItem
                    icon={
                        <div className='h-full flex items-center justify-center px-2'>
                            <div className='text-[12px]'>
                                <span>cm</span>
                            </div>
                        </div>
                    }
                >
                </ToolsBarItem>
            </div>
        </div>
    )
}