import COLORS from '../../../types/colors'
import MainMenuItem from './MainMenuItem'
import Menu from './Menu'
import MenuItem from './MenuItem'
import Separator from './Separator'
import Session from './Session'
import { FaFile, FaFolderOpen, FaRegSave, FaPencilAlt, FaSquare } from 'react-icons/fa'
import { IoOpenOutline } from 'react-icons/io5'
import { HiOutlineDocumentDuplicate } from 'react-icons/hi'
import { MdVisibility, MdLightMode } from 'react-icons/md'
import { TbForbid2 } from 'react-icons/tb'
import { RiDeleteBin5Fill, RiSettings3Fill, RiJavascriptFill } from 'react-icons/ri'
import { BiSolidCube } from 'react-icons/bi'
import { PiFileAudio } from 'react-icons/pi'
import { IoMdFolder } from 'react-icons/io'
import { BsCameraReelsFill } from 'react-icons/bs'
import { LuAxis3D } from 'react-icons/lu'
import { LiaBezierCurveSolid } from 'react-icons/lia'
import { AiTwotonePicture } from 'react-icons/ai'
import { SiMaterialdesignicons } from 'react-icons/si'

export default function MainMenu() {
    
    return (
        <div className={`relative flex w-full h-full items-center justify-between ${COLORS.bg_gray}`}>
            <div className='flex justify-center px-2'>
                <MainMenuItem name='File'>
                    <MenuItem name='New' shortcut='Ctrl + N' icon={ <FaFile className='w-3 h-3'/> }/>
                    <MenuItem name='Open' shortcut='Ctrl + O' icon={ <FaFolderOpen className='w-3 h-3'/> }/>
                    <MenuItem name='Open Recent'>
                        <Menu isLeft={true}/>
                    </MenuItem>
                    <MenuItem name='New From Stage Template' icon={ <FaFile className='w-3 h-3'/> }>
                        <Menu isLeft={true}>
                            <MenuItem name='Default Stage'/>
                            <MenuItem name='Empty'/>
                            <MenuItem name='Sunlight'/>
                            <MenuItem name='Autoshop'/>
                            <MenuItem name='Baybridge'/>
                            <MenuItem name='Desert Road'/>
                            <MenuItem name='Grassfield Day'/>
                            <MenuItem name='La Vista'/>
                            <MenuItem name='Northern Valley'/>
                            <MenuItem name='Nyc Day'/>
                            <MenuItem name='Pacific Highway'/>
                            <MenuItem name='Salt Flats'/>
                            <MenuItem name='Socal Track'/>
                            <MenuItem name='Urban Alley'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Import'/>
                    <Separator/>
                    <MenuItem name='Re-open with New Edit Layer' icon={ <IoOpenOutline className='w-3 h-3'/> }/>
                    <Separator/>
                    <MenuItem name='Save' shortcut='Ctrl + S' icon={ <FaRegSave className='w-3 h-3'/> }/>
                    <MenuItem name='Save With Options' shortcut='Ctrl + Alt + S' icon={ <FaRegSave className='w-3 h-3'/> }/>
                    <MenuItem name='Save As...' shortcut='Shift + Alt + S'/>
                    <MenuItem name='Save Flattened As...'/>
                    <MenuItem name='Export'/>
                    <MenuItem name='Collct As...'/>
                    <Separator/>
                    <MenuItem name='Add Reference'/>
                    <MenuItem name='Add Payload'/>
                    <Separator/>
                    <MenuItem name='Exit'/>
                </MainMenuItem>
                <MainMenuItem name='Edit'>
                    <MenuItem name='Undo' shortcut='Ctrl + Z'/>
                    <MenuItem name='Redo' shortcut='Ctrl + Y'/>
                    <MenuItem name='Repeat' shortcut='Ctrl + R'/>
                    <MenuItem name='Select'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Select Recent'/>
                            <MenuItem name='Select All' shortcut='Ctrl + A'/>
                            <MenuItem name='Select None' shortcut='Escape'/>
                            <MenuItem name='Select Invert' shortcut='Ctrl + I'/>
                            <MenuItem name='Select Parent' shortcut='Up'/>
                            <MenuItem name='Select Leaf'/>
                            <MenuItem name='Select Hierarchy'/>
                            <MenuItem name='Select Similar'/>
                            <Separator/>
                            <MenuItem name='Create Selection Set'/>
                            <MenuItem name='Select Set'/>
                            <Separator/>
                            <MenuItem name='Select by Kind'/>
                        </Menu>
                    </MenuItem>
                    <Separator></Separator>
                    <MenuItem name='Instance' shortcut='Shift + Ctrl + I'/>
                    <MenuItem name='Duplicate' shortcut='Ctrl + D' icon={ <HiOutlineDocumentDuplicate className='w-3 h-3'/> }/>
                    <MenuItem name='Duplicate - All Layers' icon={ <HiOutlineDocumentDuplicate className='w-3 h-3'/> }/>
                    <MenuItem name='Duplicate - Collapsed' icon={ <HiOutlineDocumentDuplicate className='w-3 h-3'/> }/>
                    <MenuItem name='Parent' shortcut='P' icon={ <HiOutlineDocumentDuplicate className='w-3 h-3'/> }/>
                    <MenuItem name='Unparent' shortcut='Shift + P' icon={ <HiOutlineDocumentDuplicate className='w-3 h-3'/> }/>
                    <MenuItem name='Group' shortcut='Ctrl + G'/>
                    <MenuItem name='Ungroup'/>
                    <MenuItem name='Toggle Visibility' shortcut='H' icon={ <MdVisibility className='w-3 h-3'/> }/>
                    <Separator/>
                    <MenuItem name='Deactivate' shortcut='Shift + Del' icon={ <TbForbid2 className='w-3 h-3'/> }/>
                    <MenuItem name='Delete' shortcut='Del' icon={ <RiDeleteBin5Fill className='w-3 h-3'/> }/>
                    <MenuItem name='Delete - All Layers' icon={ <RiDeleteBin5Fill className='w-3 h-3'/> }/>
                    <MenuItem name='Rename' shortcut='F2' icon={ <FaPencilAlt className='w-3 h-3'/> }/>
                    <Separator/>
                    <MenuItem name='Hidde Unselected'/>
                    <MenuItem name='Unhide All'/>
                    <Separator/>
                    <MenuItem name='Focus' shortcut='F'/>
                    <MenuItem name='Toggle Visualization Mode'/>
                    <MenuItem name='Capture Screenshot' shortcut='F10'/>
                    <Separator/>
                    <MenuItem name='Preferences' icon={ <RiSettings3Fill className='w-3 h-3'/> }/>
                </MainMenuItem>
                <MainMenuItem name='Create'>
                    <MenuItem name='Mesh' icon={ <BiSolidCube className='w-3 h-3'/> }>
                        <Menu
                            isLeft={true}
                        > 
                            <MenuItem name='Cone'/>
                            <MenuItem name='Cube'/>
                            <MenuItem name='Cylinder'/>
                            <MenuItem name='Disk'/>
                            <MenuItem name='Plane'/>
                            <MenuItem name='Sphere'/>
                            <MenuItem name='Torus'/>
                            <Separator/>
                            <MenuItem name='Setting'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Shape' icon={ <BiSolidCube className='w-3 h-3'/> }>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Capsule'/>
                            <MenuItem name='Cone'/>
                            <MenuItem name='Cube'/>
                            <MenuItem name='Cylinder'/>
                            <MenuItem name='Sphere'/>
                            <Separator/>
                            <MenuItem name='High Quality'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Light' icon={ <MdLightMode className='w-3 h-3 text-[#B5B06A]'/> }>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Cylinder Light'/>
                            <MenuItem name='Disk Light'/>
                            <MenuItem name='Distant Light'/>
                            <MenuItem name='Dome Light'/>
                            <MenuItem name='Rect Light'/>
                            <MenuItem name='Sphere Light'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Audio' icon={ <PiFileAudio className='w-3 h-3'/> }>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Spatial Sound'/>
                            <MenuItem name='Non-Spatial Sound'/>
                            <MenuItem name='Listener'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Camera' icon={ <BsCameraReelsFill className='w-3 h-3'/> }/>
                    <MenuItem name='Scope' icon={ <IoMdFolder className='w-3 h-3'/> }/>
                    <MenuItem name='Xform' icon={ <LuAxis3D className='w-3 h-3'/> }/>
                    <MenuItem name='Material' icon={ <SiMaterialdesignicons className='w-3 h-3'/> }>
                        <Menu
                            isLeft={true}
                        >
                            <Separator text='Base'/>
                            <MenuItem name='Emissive'/>
                            <MenuItem name='Glass'/>
                            <MenuItem name='PBR'/>
                            <MenuItem name='PBR ClearCoat'/>
                            <Separator text='Materials'/>
                            <MenuItem name='PBRBase'/>
                            <Separator text='USD Materials'/>
                            <MenuItem name='PBR Preview Surface'/>
                            <MenuItem name='PBR Preview Surface Texture'/>
                            <Separator text='Custom Materials'/>
                            <MenuItem name='Add MDL Files'/>
                            <MenuItem name='Create MDL Graph'/>
                            
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Visual Scripting' icon={ <RiJavascriptFill className='w-3 h-3'/> }>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Action Graph'/>
                            <MenuItem name='Push Graph'/>
                            <MenuItem name='Lazy Graph'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='BasisCurves' icon={ <LiaBezierCurveSolid className='w-3 h-3'/> }>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Create Curve Deformer'/>
                            <MenuItem name='Graph'/>
                            <MenuItem name='New Curve'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='AOV' icon={ <AiTwotonePicture className='w-3 h-3'/> }/>
                    <MenuItem name='UI' icon={ <FaSquare className='w-3 h-3'/> }>
                        <Menu
                            isLeft={true}
                        >
                            <Separator text='Containers'/>
                            <MenuItem name='Frame'/>
                            <MenuItem name='ScrollingFrame'/>
                            <MenuItem name='CollapsableFrame'/>
                            <MenuItem name='HStack'/>
                            <MenuItem name='VStack'/>
                            <MenuItem name='ZStack'/>
                            <MenuItem name='Placer'/>
                            <Separator text='Widgets'/>
                            <MenuItem name='Button'/>
                            <MenuItem name='Image'/>
                            <MenuItem name='Rectangle'/>
                            <MenuItem name='Spacer'/>
                            <MenuItem name='Label'/>
                            <MenuItem name='Line'/>
                            <MenuItem name='Circle'/>
                            <MenuItem name='Triangle'/>
                            <Separator text='Style'/>
                            <MenuItem name='StyleContainer'/>
                            <MenuItem name='Style'/>
                            <Separator text='Viewport'/>
                            <MenuItem name='ViewportButton'/>
                            <MenuItem name='ViewportCircle'/>
                            <Separator text='Window'/>
                            <MenuItem name='Viewport Frame'/>
                            <MenuItem name='Window Frame'/>
                        </Menu>
                    </MenuItem>
                </MainMenuItem>
                <MainMenuItem name='Window'>
                    <MenuItem name='Animation'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Curve Editor'/>
                            <MenuItem name='Timeline'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Browsers'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Configurator Samples'/>
                            <MenuItem name='Context'/>
                            <MenuItem name='Environment'/>
                            <MenuItem name='Materials'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Collection'/>
                    <MenuItem name='Hotkeys'/>
                    <MenuItem name='Layer'/>
                    <MenuItem name='Main ToolBar'/>
                    <MenuItem name='Property'/>
                    <MenuItem name='Rendering'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='MDL Material Graph'/>
                            <MenuItem name='Movie Capture'/>
                            <MenuItem name='Render Settings'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Stage'/>
                    <MenuItem name='Utilities'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Actions'/>
                            <MenuItem name='Activity Progress'/>
                            <MenuItem name='Asset Validator'/>
                            <MenuItem name='Console'/>
                            <MenuItem name='Scene Optimizer'/>
                            <MenuItem name='Statistics'/>
                            <MenuItem name='USD Paths'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Viewport'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Viewport 1'/>
                            <MenuItem name='Viewport 2'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Visual Scripting'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Action Graph'/>
                            <MenuItem name='Generic Graph'/>
                        </Menu>
                    </MenuItem>
                </MainMenuItem>
                <MainMenuItem name='Tools'>
                    <MenuItem name='Animation'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Curve Processing'/>
                            <MenuItem name='Convert'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Product Configurator'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Configurator Publisher'/>
                        </Menu>
                    </MenuItem>
                    <MenuItem name='Variants'>
                        <Menu
                            isLeft={true}
                        >
                            <MenuItem name='Variant Editor'/>
                            <MenuItem name='Variant Presenter'/>
                        </Menu>
                    </MenuItem>
                </MainMenuItem>
                <MainMenuItem name='Developer'>
                    <MenuItem name='Extensions'/>
                    <MenuItem name='Command'/>
                    <MenuItem name='Script Editor'/>
                    <MenuItem name='VS Code Link'/>
                    <MenuItem name='Debug Settings'/>
                </MainMenuItem>
                <MainMenuItem name='Layout'>
                    <MenuItem name='Default' shortcut='Ctrl + 1'/>
                    <Separator/>
                    <MenuItem name='UI Toggle Visibility' shortcut='F7'/>
                    <MenuItem name='Fullscreen Mode' shortcut='F11'/>
                    <Separator/>
                    <MenuItem name='Save Layout'/>
                    <MenuItem name='Load Layout'/>
                    <Separator/>
                    <MenuItem name='Quick Save' shortcut='Ctrl + 7'/>
                    <MenuItem name='Quick Load' shortcut='Ctrl + 8'/>
                </MainMenuItem>
                <MainMenuItem name='Help'>
                    <MenuItem name='Documentation'/>
                    <MenuItem name='About'/>
                    <MenuItem name='USD Reference Guide' shortcut='F1'/>
                    <MenuItem name='Discover Kit SDK'/>
                    <MenuItem name='Developers Manual'/>
                </MainMenuItem>
            </div>
            <div className='flex justify-center'>
                <Session></Session>
            </div>
        </div>
    )
}