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
import { useEffect, useState } from 'react'

export default function NeptuneEditor() {

    const [mainLayout, setMainLayout] = useState<number[]>([30, 70])
    const [leftLayout, setLeftLayout] = useState<number[]>([70, 30])
    const [verticalLayout, setVerticalLayout] = useState<number[]>([80, 20])
    const [horizontalLayout, setHorizontalLayout] = useState<number[]>([20, 80])

    // 组件挂载时从 localStorage 加载保存的布局
    useEffect(() => {
        const savedMainLayout = localStorage.getItem('neptune-main-layout')
        const savedLeftLayout = localStorage.getItem('neptune-left-layout')
        const savedVerticalLayout = localStorage.getItem('neptune-vertical-layout')
        const savedHorizontalLayout = localStorage.getItem('neptune-horizontal-layout')

        if (savedMainLayout) setMainLayout(JSON.parse(savedMainLayout))
        if (savedLeftLayout) setLeftLayout(JSON.parse(savedLeftLayout))
        if (savedVerticalLayout) setVerticalLayout(JSON.parse(savedVerticalLayout))
        if (savedHorizontalLayout) setHorizontalLayout(JSON.parse(savedHorizontalLayout))
    }, [])

    const saveLayout = () => {
        localStorage.setItem('neptune-main-layout', JSON.stringify(mainLayout))
        localStorage.setItem('neptune-left-layout', JSON.stringify(leftLayout))
        localStorage.setItem('neptune-vertical-layout', JSON.stringify(verticalLayout))
        localStorage.setItem('neptune-horizontal-layout', JSON.stringify(horizontalLayout))
    }

    const resetLayout = () => {
        const defaultMainLayout = [30, 70]
        const defaultLeftLayout = [70, 30]
        const defaultVerticalLayout = [80, 20]
        const defaultHorizontalLayout = [20, 80]

        setMainLayout([...defaultMainLayout])
        setLeftLayout([...defaultLeftLayout])
        setVerticalLayout([...defaultVerticalLayout])
        setHorizontalLayout([...defaultHorizontalLayout])

        // 保存默认布局
        localStorage.setItem('neptune-main-layout', JSON.stringify(defaultMainLayout))
        localStorage.setItem('neptune-left-layout', JSON.stringify(defaultLeftLayout))
        localStorage.setItem('neptune-vertical-layout', JSON.stringify(defaultVerticalLayout))
        localStorage.setItem('neptune-horizontal-layout', JSON.stringify(defaultHorizontalLayout))
    }

    return (
        <div className={`flex h-screen w-screen ${COLORS.bg_black}`}>
            <ResizablePanelGroup
                direction='vertical'
                onLayout={(sizes) => setMainLayout(sizes)}
            >
                <ResizablePanel defaultSize={mainLayout[0] || 30}><MainMenu/></ResizablePanel>
                <ResizableHandle />
                <ResizablePanel defaultSize={mainLayout[1] || 70}>
                    <ResizablePanelGroup
                        direction='horizontal'
                        onLayout={(sizes) => setLeftLayout(sizes)}
                    >
                        <ResizablePanel defaultSize={leftLayout[0] || 70}>
                            <ResizablePanelGroup
                                direction="vertical"
                                onLayout={(sizes) => setVerticalLayout(sizes)}
                            >
                                <ResizablePanel defaultSize={verticalLayout[0] || 80}>
                                    <ResizablePanelGroup
                                        direction="horizontal"
                                        onLayout={(sizes) => setHorizontalLayout(sizes)}
                                    >
                                        <ResizablePanel defaultSize={horizontalLayout[0] || 20}><OperatorPanel/></ResizablePanel>
                                        <ResizableHandle />
                                        <ResizablePanel defaultSize={horizontalLayout[1] || 80}><Viewport/></ResizablePanel>
                                    </ResizablePanelGroup>
                                </ResizablePanel>
                                <ResizableHandle />
                                <ResizablePanel defaultSize={verticalLayout[1] || 20}><Console/></ResizablePanel>
                            </ResizablePanelGroup>
                        </ResizablePanel>
                        <ResizableHandle />
                        <ResizablePanel defaultSize={leftLayout[1] || 30}>
                            <ResizablePanelGroup
                                direction="vertical"
                                onLayout={(sizes) => setHorizontalLayout(sizes)}
                            >
                                <ResizablePanel defaultSize={horizontalLayout[0] || 70}><Property/></ResizablePanel>
                                <ResizableHandle />
                                <ResizablePanel defaultSize={horizontalLayout[1] || 30}>
                                    <div className="flex items-center justify-center p-2">
                                        <button
                                            onClick={saveLayout}
                                            className="mr-2 px-3 py-1 bg-blue-500 text-white rounded hover:bg-blue-600"
                                        >
                                            保存布局
                                        </button>
                                        <button
                                            onClick={resetLayout}
                                            className="px-3 py-1 bg-gray-500 text-white rounded hover:bg-gray-600"
                                        >
                                            重置布局
                                        </button>
                                    </div>
                                </ResizablePanel>
                            </ResizablePanelGroup>
                        </ResizablePanel>
                    </ResizablePanelGroup>
                </ResizablePanel>
                <ResizableHandle />
                <ResizablePanel defaultSize={mainLayout[2] || 10}><InfoBar/></ResizablePanel>
            </ResizablePanelGroup>
        </div>
    )
}