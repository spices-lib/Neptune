/**
* @file EntryPoint.h.
* @brief EntryPoint Definitions.
* @author Spices.
*/
#pragma once

#include <emscripten.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/html5_webgpu.h>

#include <GLFW/glfw3.h>
#include <GLFW/emscripten_glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_wgpu.h>

#include <webgpu/webgpu.h>
#include <webgpu/webgpu_cpp.h>

static WGPUInstance      wgpu_instance = nullptr;
static WGPUDevice        wgpu_device = nullptr;
static WGPUSurface       wgpu_surface = nullptr;
static WGPUTextureFormat wgpu_preferred_fmt = WGPUTextureFormat_RGBA8Unorm;
static WGPUSwapChain     wgpu_swap_chain = nullptr;
static int               wgpu_swap_chain_width = 1280;
static int               wgpu_swap_chain_height = 720;

// Our state
bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

/**
 * The purpose of this example is to demonstrate how to make the canvas resizable and occupy the full window. */

//! Display error message in the Console
void consoleErrorHandler(int iErrorCode, char const *iErrorMessage)
{
    printf("glfwError: %d | %s\n", iErrorCode, iErrorMessage);
}

static void wgpu_error_callback(WGPUErrorType error_type, const char* message, void*)
{
    const char* error_type_lbl = "";
    switch (error_type)
    {
        case WGPUErrorType_Validation:  error_type_lbl = "Validation"; break;
        case WGPUErrorType_OutOfMemory: error_type_lbl = "Out of memory"; break;
        case WGPUErrorType_Unknown:     error_type_lbl = "Unknown"; break;
        case WGPUErrorType_DeviceLost:  error_type_lbl = "Device lost"; break;
        default:                        error_type_lbl = "Unknown";
    }
    printf("%s error: %s\n", error_type_lbl, message);
}

static bool InitWGPU(GLFWwindow* window)
{
    wgpu::Instance instance = wgpuCreateInstance(nullptr);

    wgpu_device = emscripten_webgpu_get_device();
    if (!wgpu_device)
        return false;

    wgpu::SurfaceDescriptorFromCanvasHTMLSelector html_surface_desc = {};
    html_surface_desc.selector = "#Nepnep";
    wgpu::SurfaceDescriptor surface_desc = {};
    surface_desc.nextInChain = &html_surface_desc;
    wgpu::Surface surface = instance.CreateSurface(&surface_desc);

    wgpu::Adapter adapter = {};
    wgpu_preferred_fmt = (WGPUTextureFormat)surface.GetPreferredFormat(adapter);


    wgpu_instance = instance.MoveToCHandle();
    wgpu_surface = surface.MoveToCHandle();

    wgpuDeviceSetUncapturedErrorCallback(wgpu_device, wgpu_error_callback, nullptr);

    return true;
}

static void CreateSwapChain(int width, int height)
{
    if (wgpu_swap_chain)
        wgpuSwapChainRelease(wgpu_swap_chain);
    wgpu_swap_chain_width = width;
    wgpu_swap_chain_height = height;
    WGPUSwapChainDescriptor swap_chain_desc = {};
    swap_chain_desc.usage = WGPUTextureUsage_RenderAttachment;
    swap_chain_desc.format = wgpu_preferred_fmt;
    swap_chain_desc.width = width;
    swap_chain_desc.height = height;
    swap_chain_desc.presentMode = WGPUPresentMode_Fifo;
    wgpu_swap_chain = wgpuDeviceCreateSwapChain(wgpu_device, wgpu_surface, &swap_chain_desc);
}


//! Called for each frame
void renderFrame(GLFWwindow *iWindow)
{
    static int frameCount = 0;

    // poll events
    glfwPollEvents();

    int w,h;
    glfwGetWindowSize(iWindow, &w, &h);

    int fw,fh;
    glfwGetFramebufferSize(iWindow, &fw, &fh);

    double mx,my;
    glfwGetCursorPos(iWindow, &mx, &my);

    if (fw != wgpu_swap_chain_width || fh != wgpu_swap_chain_height)
    {
        ImGui_ImplWGPU_InvalidateDeviceObjects();
        CreateSwapChain(fw, fh);
        ImGui_ImplWGPU_CreateDeviceObjects();
    }

    // Start the Dear ImGui frame
    ImGui_ImplWGPU_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                                // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");                     // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);            // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);                  // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color);       // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                                  // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);         // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }

    // Rendering
    ImGui::Render();


    WGPURenderPassColorAttachment color_attachments = {};
    color_attachments.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    color_attachments.loadOp = WGPULoadOp_Clear;
    color_attachments.storeOp = WGPUStoreOp_Store;
    color_attachments.clearValue = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    color_attachments.view = wgpuSwapChainGetCurrentTextureView(wgpu_swap_chain);

    WGPURenderPassDescriptor render_pass_desc = {};
    render_pass_desc.colorAttachmentCount = 1;
    render_pass_desc.colorAttachments = &color_attachments;
    render_pass_desc.depthStencilAttachment = nullptr;

    WGPUCommandEncoderDescriptor enc_desc = {};
    WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(wgpu_device, &enc_desc);

    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(encoder, &render_pass_desc);
    ImGui_ImplWGPU_RenderDrawData(ImGui::GetDrawData(), pass);
    wgpuRenderPassEncoderEnd(pass);

    WGPUCommandBufferDescriptor cmd_buffer_desc = {};
    WGPUCommandBuffer cmd_buffer = wgpuCommandEncoderFinish(encoder, &cmd_buffer_desc);
    WGPUQueue queue = wgpuDeviceGetQueue(wgpu_device);
    wgpuQueueSubmit(queue, 1, &cmd_buffer);

    wgpuTextureViewRelease(color_attachments.view);
    wgpuRenderPassEncoderRelease(pass);
    wgpuCommandEncoderRelease(encoder);
    wgpuCommandBufferRelease(cmd_buffer);
}

//! The main loop (called by emscripten for each frame)
void main_loop(void *iUserData)
{
    if(auto window = reinterpret_cast<GLFWwindow *>(iUserData); !glfwWindowShouldClose(window))
    {
        // not done => renderFrame
        renderFrame(window);
    }
    else
    {
        // Cleanup
        ImGui_ImplWGPU_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);

        // done => terminating
        glfwTerminate();
        emscripten_cancel_main_loop();
    }
}

//! Handle key events => on CTRL+Q sets "window should close" flag, CTRL+F for fullscreen
void onKeyChange(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS && (mods & GLFW_MOD_CONTROL)) {
        switch(key) {
            case GLFW_KEY_Q: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
            case GLFW_KEY_F: emscripten_glfw_request_fullscreen(window, false, true); break; // ok from a keyboard event
            default: break;
        }
    }
}

//! main
int main()
{
    // set a callback for errors otherwise if there is a problem, we won't know
    glfwSetErrorCallback(consoleErrorHandler);

    // print the version on the console
    printf("%s\n", glfwGetVersionString());

    // initialize the library
    if(!glfwInit())
        return -1;

    // no OpenGL (use canvas2D)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // make it not Hi DPI Aware (simplify rendering code a bit)
    glfwWindowHint(GLFW_SCALE_FRAMEBUFFER, GLFW_FALSE);

    // setting the association window <-> canvas
    emscripten_glfw_set_next_window_canvas_selector("#Nepnep");

    // create the only window
    auto window = glfwCreateWindow(wgpu_swap_chain_width, wgpu_swap_chain_height, "Resizable Full Window | emscripten-glfw", nullptr, nullptr);
    if(!window)
        return -1;

    // makes the canvas resizable and match the full window size
    emscripten_glfw_make_canvas_resizable(window, "window", nullptr);

    // set callback for exit (CTRL+Q) and fullscreen (CTRL+F)
    glfwSetKeyCallback(window, onKeyChange);

    // Initialize the WebGPU environment
    if (!InitWGPU(window))
    {
        if (window)
            glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    CreateSwapChain(wgpu_swap_chain_width, wgpu_swap_chain_height);
    //glfwShowWindow(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOther(window, true);
#ifdef __EMSCRIPTEN__
    //ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#Nepnep");
#endif
    ImGui_ImplWGPU_InitInfo init_info;
    init_info.Device = wgpu_device;
    init_info.NumFramesInFlight = 3;
    init_info.RenderTargetFormat = wgpu_preferred_fmt;
    init_info.DepthStencilFormat = WGPUTextureFormat_Undefined;
    ImGui_ImplWGPU_Init(&init_info);



    // tell emscripten to use "main_loop" as the main loop (window is user data)
    emscripten_set_main_loop_arg(main_loop, window, 0, GLFW_FALSE);
}