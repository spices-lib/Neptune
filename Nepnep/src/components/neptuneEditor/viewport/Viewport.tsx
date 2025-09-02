import COLORS from '@/types/colors'
import NeptuneCanvas from './NeptuneCanvas'
import ToolsBar from './ToolsBar'
import { FaList } from 'react-icons/fa'
import { FaRegLightbulb } from 'react-icons/fa6'
import ToolsBarItem from './ToolsBarItem'
import { ImEye } from 'react-icons/im'
import { BsCameraReelsFill } from 'react-icons/bs'
import MenuItem from './MenuItem'
import SideBar from './SideBar'
import Separator from '@/components/neptuneEditor/mainMenu/Separator'
import { CgCamera } from 'react-icons/cg'

export default function Viewport() {
    
    return (
        <div className={`relative flex items-center justify-center w-full h-full p-[4px] ${COLORS.bg_gray}`}>
            <div className='w-full h-full flex flex-col items-center justify-between'>
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
                            <div className='flex items-center justify-start h-full'>
                                <ToolsBarItem
                                    icon={
                                        <div className='h-full flex items-center justify-center px-2'>
                                            <div className='w-[25px] h-full flex items-center justify-between'>
                                                <CgCamera></CgCamera>
                                            </div>
                                            <div className='text-[12px]'>
                                                <span> 17 - 35 mm</span>
                                            </div>
                                        </div>
                                    }
                                >
                                </ToolsBarItem>
                                
                            </div>
                        </SideBar>
                    </div>
                    <div className='flex items-center justify-start'>
                        
                    </div>
                </div>
                <div className='w-full flex items-center justify-start'>
                    
                </div>
            </div>
            
            {/*<ToolsBar></ToolsBar>*/}
        </div>
    )
}