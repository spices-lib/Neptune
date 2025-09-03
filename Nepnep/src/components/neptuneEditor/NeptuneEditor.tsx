'use client'

import MainMenu from './mainMenu/MainMenu'
import InfoBar from './infoBar/InfoBar'
import Property from './propertyPanel/Property'
import Console from './propertyPanel/Console'
import COLORS from '../../types/colors'
import OperatorPanel from './operatorPanel/OperatorPanel'
import Viewport from './viewport/Viewport'
import {
    ResizableHandle,
    ResizablePanel,
    ResizablePanelGroup,
} from '@/components/ui/resizable'
import { useEffect, useState, useCallback } from 'react'
import useWindowSize from '../../hooks/useWindowSize'

export default function NeptuneEditor() {

    const windowSize = useWindowSize()

    const [section0, setSection0] = useState({
        top: 22,
        middle: 1000,
        bottom: 30
    })

    const [section1, setSection1] = useState({
        left: 1100,
        right: 300
    })

    const [section2, setSection2] = useState({
        top: 500,
        bottom: 150
    })

    const [section3, setSection3] = useState({
        left: 50,
        right: 1200
    })

    const calculateSectionSizes = useCallback(() => {
        if (!windowSize)
            return {}
        
        const section0Middle = Math.min(Math.max(windowSize.height - section0.top - section0.bottom, 0), 100)
        const section1Left = Math.min(Math.max(windowSize.width - section1.right, 0), 100)
        const section2Top = Math.min(Math.max(section0Middle - section2.bottom, 0), 100)
        const rightWidth = Math.min(Math.max(section1Left - section3.left, 0), 100)

        setSection0({top: section0.top, middle: section0Middle, bottom: section0.bottom});
        setSection1({left: section1Left, right: section1.right});
        setSection2({top: section2Top, bottom: section2.bottom});
        setSection3({left: section3.left, right: rightWidth});
        
    }, [section0, section1, section2, section3, windowSize])

    const saveLayout = () => {
        localStorage.setItem('neptune-editor-section0', JSON.stringify(section0))
        localStorage.setItem('neptune-editor-section1', JSON.stringify(section1))
        localStorage.setItem('neptune-editor-section2', JSON.stringify(section2))
        localStorage.setItem('neptune-editor-section3', JSON.stringify(section3))
    }

    const loadLayout = useCallback(() => {

        const savedSection0 = localStorage.getItem('neptune-editor-section0')
        const savedSection1 = localStorage.getItem('neptune-editor-section1')
        const savedSection2 = localStorage.getItem('neptune-editor-section2')
        const savedSection3 = localStorage.getItem('neptune-editor-section3')
        
        if (!savedSection0 || !savedSection1 || !savedSection2 || !savedSection3) {
            calculateSectionSizes()
            return
        }
        
        setSection0(JSON.parse(savedSection0))
        setSection1(JSON.parse(savedSection1))
        setSection2(JSON.parse(savedSection2))
        setSection3(JSON.parse(savedSection3))
        
    }, [calculateSectionSizes])

    useEffect(() => {
        loadLayout()
    }, [])

    const handleSection0Change = (sizes: number[]) => {
        if (!windowSize)
            return
        
        const height = windowSize.height

        setSection0({
            top: Math.round(sizes[0] * height / 100),
            middle: Math.round(sizes[1] * height / 100),
            bottom: Math.round(sizes[2] * height / 100)
        })
    }

    const handleSection1Change = (sizes: number[]) => {
        if (!windowSize)
            return
        
        const width = windowSize.width

        setSection1({
            left: Math.round(sizes[0] * width / 100),
            right: Math.round(sizes[1] * width / 100)
        })
    }

    const handleSection2Change = (sizes: number[]) => {
        const height = section0.middle

        setSection2({
            top: Math.round(sizes[0] * height / 100),
            bottom: Math.round(sizes[1] * height / 100)
        })
    }

    const handleSection3Change = (sizes: number[]) => {
        const width = section1.left
        
        setSection3({
            left: Math.round(sizes[0] * width / 100),
            right: Math.round(sizes[1] * width / 100)
        })
    }
    
    if (!windowSize)
        return null
    
    return (
        <div className={`flex h-screen w-screen ${COLORS.bg_black}`}>
            <div className='fixed top-[24px] bottom-[0px] w-screen flex'>
                <ResizablePanelGroup
                    direction='vertical'
                    onLayout={ handleSection0Change }
                >
                    <ResizablePanel 
                        defaultSize={ section0.middle / windowSize.height * 100 }
                    >
                        <ResizablePanelGroup
                            direction='horizontal'
                            onLayout={ handleSection1Change }
                        >
                            <ResizablePanel 
                                defaultSize={ section1.left / windowSize.width * 100 }
                            >
                                <ResizablePanelGroup
                                    direction="vertical"
                                    onLayout={ handleSection2Change }
                                >
                                    <ResizablePanel 
                                        defaultSize={ section2.top / section0.middle * 100 }
                                    >
                                        <ResizablePanelGroup
                                            direction="horizontal"
                                            onLayout={ handleSection3Change }
                                        >
                                            <ResizablePanel 
                                                defaultSize={ section3.left / section1.left * 100 }
                                            >
                                                <OperatorPanel/>
                                            </ResizablePanel>
                                            <ResizableHandle className= {`data-[panel-group-direction=horizontal]:w-[2px] ${COLORS.bg_black}`}/>
                                            <ResizablePanel 
                                                defaultSize={ section3.right / section1.left * 100 }
                                            >
                                                <Viewport/>
                                            </ResizablePanel>
                                        </ResizablePanelGroup>
                                    </ResizablePanel>
                                    <ResizableHandle className= {`data-[panel-group-direction=vertical]:h-[2px] ${COLORS.bg_black}`}/>
                                    <ResizablePanel 
                                        defaultSize={ section2.bottom / section0.middle * 100 }
                                    >
                                        <Console/>
                                    </ResizablePanel>
                                </ResizablePanelGroup>
                            </ResizablePanel>
                            <ResizableHandle className= {`data-[panel-group-direction=horizontal]:w-[2px] ${COLORS.bg_black}`}/>
                            <ResizablePanel 
                                defaultSize={ section1.right / windowSize.width * 100 }
                            >
                                <Property/>
                            </ResizablePanel>
                        </ResizablePanelGroup>
                    </ResizablePanel>
                    <ResizableHandle className= {`data-[panel-group-direction=vertical]:h-[2px] ${COLORS.bg_black}`}/>
                    <ResizablePanel 
                        defaultSize={ section0.bottom / windowSize.height * 100 }
                    >
                        <InfoBar/>
                    </ResizablePanel>
                </ResizablePanelGroup>
            </div>
            <div className='fixed h-[22px] top-0 w-screen'>
                <MainMenu/>
            </div>
        </div>
    )
}