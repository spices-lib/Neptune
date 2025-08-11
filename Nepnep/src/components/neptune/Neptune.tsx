import { useEffect } from 'react'

const initModule = async() => {
    window.Module = {
        preRun: [],
        postRun: [],
        print: (function () {
            return function (text: string) {
                text = Array.prototype.slice.call(arguments).join(' ')
                console.log(text)
            }
        })(),

        printErr: function (text: string) {
            text = Array.prototype.slice.call(arguments).join(' ')
            console.error(text)
        },

        canvas: (function () {
            const canvas = document.getElementById('Nepnep')
            //canvas.addEventListener("webglcontextlost", function(e) { alert('FIXME: WebGL context lost, please reload the page'); e.preventDefault(); }, false)
            return canvas
        })(),

        setStatus: function (text: string) {
            console.log("status: " + text)
        },

        monitorRunDependencies: function () {
            // no run dependencies to log
        }
    };

    window.onerror = function () {
        console.log("onerror: " + event)
    };

    // Initialize the graphics adapter
    {
        if (!navigator.gpu) {
            throw Error("WebGPU not supported.")
        }

        const adapter = await navigator.gpu?.requestAdapter()
        const device = await adapter?.requestDevice()
        window.Module.preinitializedWebGPUDevice = device
    }

    {
        const js = document.createElement('script')
        js.async = true
        js.src = '././wasm/SandBox.js'
        document.body.appendChild(js)
    }
}

export function Neptune () {

    useEffect(()=>{ initModule().then() }, [])

    return(
        <>
            <canvas
                className='absolute top-0 left-0 m-0 border-0 w-full h-full overflow-hidden block image-rendering-pixelated'
                id="Nepnep"
            >
            </canvas>
        </>
    )
}