import MainMenu from './mainMenu/MainMenu'
import InfoBar from './infoBar/InfoBar'
import Property from './propertyPanel/Property'
import Console from './propertyPanel/Console'
import COLORS from '../../types/colors'
import OperatorPanel from './operatorPanel/OperatorPanel'
import Viewport from './viewport/Viewport'

export default function NeptuneEditor() {
    return (
        <div className={`flex h-screen w-screen ${COLORS.bg_black}`}>
            <div className='fixed h-[22px] top-0 w-screen'>
                <MainMenu/>
            </div>
            <div className='fixed w-[500px] top-[22px] bottom-[30px] right-[0px]'>
                <Property/>
            </div>
            <div className='fixed top-[720px] bottom-[30px] left-[0px] right-[500px]'>
                <Console/>
            </div>
            <div className='fixed w-[50px] top-[22px] bottom-[320px] left-[0px]'>
                <OperatorPanel/>
            </div>
            <div className='fixed w-[50px] top-[22px] bottom-[320px] left-[0px]'>
                <Viewport/>
            </div>
            <div className='fixed h-[30px] bottom-[0px] w-screen'>
                <InfoBar/>
            </div>
        </div>
    )
}