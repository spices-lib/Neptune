'use client'

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
            const canvas = document.getElementById('nepnep')
            //canvas.addEventListener("webglcontextlost", function(e) { alert('FIXME: WebGL context lost, please reload the page'); e.preventDefault(); }, false)
            return canvas
        })(),

        setStatus: function (text: string) {
            console.log("status: " + text)
        },

        monitorRunDependencies: function () {
            // no run dependencies to log
        }
    }

    window.onerror = function () {
        console.log("onerror: " + event)
    }

    {
        const js = document.createElement('script')
        js.async = true
        js.src = '/wasm/Debug/NeptuneRuntime.js'
        document.body.appendChild(js)
    }
}

export default function NeptuneCanvas () {

    useEffect(()=>{ initModule().then() }, [])

    return(
        <div 
            className={`relative flex items-center justify-center w-full h-full`}
            id="nepnep-div"
        >
            <canvas
                className={`w-full h-full`}
                id='nepnep'
            >
            </canvas>
        </div>
    )
}