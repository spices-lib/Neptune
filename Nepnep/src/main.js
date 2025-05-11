var Module;

const main = async () => {

    Module = {
        preRun: [],
        postRun: [],
        print: (function () {
            return function (text) {
                text = Array.prototype.slice.call(arguments).join(' ');
                console.log(text);
            };
        })(),

        printErr: function (text) {
            text = Array.prototype.slice.call(arguments).join(' ');
            console.error(text);
        },

        canvas: (function () {
            var canvas = document.getElementById('canvas');
            //canvas.addEventListener("webglcontextlost", function(e) { alert('FIXME: WebGL context lost, please reload the page'); e.preventDefault(); }, false);
            return canvas;
        })(),

        setStatus: function (text) {
            console.log("status: " + text);
        },

        monitorRunDependencies: function (left) {
            // no run dependencies to log
        }
    };

    window.onerror = function () {
        console.log("onerror: " + event);
    };

    // Initialize the graphics adapter
    {
        if (!navigator.gpu) {
            throw Error("WebGPU not supported.");
        }

        const adapter = await navigator.gpu.requestAdapter();
        const device = await adapter.requestDevice();
        Module.preinitializedWebGPUDevice = device;
    }

    {
        const js = document.createElement('script');
        js.async = true;
        js.src = "http://127.0.0.1:8000/SandBox.js";
        document.body.appendChild(js);
    }
}

main()