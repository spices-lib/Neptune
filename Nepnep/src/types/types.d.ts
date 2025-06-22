declare module '*.css' {
    const content: { [className: string]: string }
    export default content
}

interface EmscriptenModule {
    preRun: any[],
    postRun: any[],
    print: (text: string) => void,
    printErr: (text: string) => void,
    canvas: HTMLElement | null,
    setStatus: (text: string) => void,
    monitorRunDependencies: () => void,
    preinitializedWebGPUDevice?: GPUDevice
}

declare global {
    interface Window {
        Module: EmscriptenModule
    }
}