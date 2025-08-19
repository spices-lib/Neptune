declare module '*.css' {
    const content: { [className: string]: string }
    export default content
}

export enum LayerType {
    Rectangle,
    Ellipse,
    Path,
    Text
}

export enum CanvasMode {
    None,
    Dragging,
    Inserting,
    Pencil,
    Resizing
}

export enum Side { 
    Top= 1,
    Bottom = 2,
    Left = 4,
    Right = 8
}

declare global {

    interface EmscriptenModule {
        preRun: any[]
        postRun: any[]
        print: (text: string) => void
        printErr: (text: string) => void
        canvas: HTMLElement | null
        setStatus: (text: string) => void
        monitorRunDependencies: () => void
        preinitializedWebGPUDevice?: GPUDevice
    }

    interface Window {
        Module?: EmscriptenModule
    }

    interface GPUDevice{}

    interface Navigator {
        gpu?: any
    }
    
    type Color = {
        r: number
        g: number
        b: number
    }

    type Camera = {
        x: number
        y: number
        zoom: number
    }

    type RectangleLayer = {
        type: LayerType.Rectangle
        x: number
        y: number
        height: number
        width: number
        fill: Color
        stroke: Color
        opacity: number
        connerRadius: number
    }

    type EllipseLayer = {
        type: LayerType.Ellipse
        x: number
        y: number
        height: number
        width: number
        fill: Color
        stroke: Color
        opacity: number
    }

    type PathLayer = {
        type: LayerType.Path
        x: number
        y: number
        height: number
        width: number
        fill: Color
        stroke: Color
        opacity: number
        points: number[][]
    }

    type TextLayer = {
        type: LayerType.Text
        x: number
        y: number
        height: number
        width: number
        fill: Color
        stroke: Color
        opacity: number
        text: string
        fontSize: number
        fontWidth: number
        fontFamily: string
    }

    type Layer = RectangleLayer | EllipseLayer | PathLayer | TextLayer

    type Point = {
        x: number
        y: number
    }
    
    type XYWH = {
        x: number
        y: number
        width: number
        height: number
    }
    
    type CanvasState = {
        mode: CanvasMode.None
    } | {
        mode: CanvasMode.Dragging
        origin: Point | null
    } | {
        mode: CanvasMode.Inserting
        layerType: LayerType.Rectangle | LayerType.Ellipse | LayerType.Text
    } | {
        mode: CanvasMode.Pencil
    } | {
        mode: CanvasMode.Resizing
        initialBounds: XYWH
        corner: Side
    }
}

export {}