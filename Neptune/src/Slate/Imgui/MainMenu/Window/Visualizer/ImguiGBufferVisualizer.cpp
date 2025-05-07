/**
* @file ImguiGBufferVisualizer.cpp.
* @brief The ImguiGizmos Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "ImguiGBufferVisualizer.h"

#include "Render/Vulkan/VulkanRenderBackend.h"

namespace Neptune {

    ImguiGBufferVisualizer::ImguiGBufferVisualizer(
        const std::string& panelName , 
        FrameInfo&         frameInfo
    )
        : ImguiSlate(panelName, frameInfo)
    {
        NEPTUNE_PROFILE_ZONE;

        QueryGBufferID();
    }

    void ImguiGBufferVisualizer::OnRender()
    {
        NEPTUNE_PROFILE_ZONE;

        if (!m_IsSlateOn) return;

        /**
        * @brief Begin render GBuffer Visualizer.
        */
        Begin(m_PanelName.c_str());

        ImVec2 size = { m_Width , m_Height };

        /**
        * @brief Render SceneColor.
        */
        {
            NEPTUNE_PROFILE_ZONEN("Render SceneColor");

            ImGui::Text("SceneColor");
            ImGui::Image(m_GBufferID.SceneColorID, size);
            ImGui::Separator();
        }

        /**
        * @brief Render Albedo.
        */
        {
            NEPTUNE_PROFILE_ZONEN("Render Albedo");

            ImGui::Text("Albedo");
            ImGui::Image(m_GBufferID.AlbedoID, size);
            ImGui::Separator();
        }

        /**
        * @brief Render Normal.
        */
        {
            NEPTUNE_PROFILE_ZONEN("Render Normal");

            ImGui::Text("Normal");
            ImGui::Image(m_GBufferID.NormalID, size);
            ImGui::Separator();
        }

        /**
        * @brief Render Roughness.
        */
        {
            NEPTUNE_PROFILE_ZONEN("Render Roughness");

            ImGui::Text("Roughness");
            ImGui::Image(m_GBufferID.RoughnessID, size);
            ImGui::Separator();
        }

        /**
        * @brief Render Metallic.
        */
        {
            NEPTUNE_PROFILE_ZONEN("Render Metallic");

            ImGui::Text("Metallic");
            ImGui::Image(m_GBufferID.MetallicID, size);
            ImGui::Separator();
        }

        /**
        * @brief Render Position.
        */
        {
            NEPTUNE_PROFILE_ZONEN("Render Position");

            ImGui::Text("Position");
            ImGui::Image(m_GBufferID.PositionID, size);
            ImGui::Separator();
        }

        /**
        * @brief End render GBuffer Visualizer.
        */
        End();

    }

    void ImguiGBufferVisualizer::OnEvent(Event& event)
    {
        NEPTUNE_PROFILE_ZONE;

        /**
        * @brief Instance a EventDispatcher.
        */
        EventDispatcher dispatcher(event);

        /**
        * @brief Dispatch SlateResizeEvent to ImguiGBufferVisualizer::OnSlateResized.
        */
        dispatcher.Dispatch<SlateResizeEvent>(BIND_EVENT_FN(ImguiGBufferVisualizer::OnSlateResized));
    }

    bool ImguiGBufferVisualizer::OnSlateResized(SlateResizeEvent& event)
    {
        NEPTUNE_PROFILE_ZONE;

        /**
        * @brief Free old DescriptorSet.
        */
        m_GBufferID.Free();

        m_Width = 500;
        m_Height = m_Width * event.GetHeight() / static_cast<float>(event.GetWidth());

        /**
        * @rief Re Query GBufferID.
        */
        QueryGBufferID();

        /**
        * @brief Do not block the event.
        */
        return false;
    }

    void ImguiGBufferVisualizer::QueryGBufferID()
    {
        NEPTUNE_PROFILE_ZONE;

        const VkDescriptorImageInfo* sceneColorInfo = VulkanRenderBackend::GetRendererResourcePool()->AccessResource({ "SceneColor" });
        const VkDescriptorImageInfo* albedoInfo     = VulkanRenderBackend::GetRendererResourcePool()->AccessResource({ "Albedo"     });
        const VkDescriptorImageInfo* normalInfo     = VulkanRenderBackend::GetRendererResourcePool()->AccessResource({ "Normal"     });
        const VkDescriptorImageInfo* roughnessInfo  = VulkanRenderBackend::GetRendererResourcePool()->AccessResource({ "Roughness"  });
        const VkDescriptorImageInfo* metallicInfo   = VulkanRenderBackend::GetRendererResourcePool()->AccessResource({ "Metallic"   });
        const VkDescriptorImageInfo* positionInfo   = VulkanRenderBackend::GetRendererResourcePool()->AccessResource({ "Position"   });

        m_GBufferID.SceneColorID  = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(sceneColorInfo->sampler , sceneColorInfo->imageView , sceneColorInfo->imageLayout  ));
        m_GBufferID.AlbedoID      = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(albedoInfo->sampler     , albedoInfo->imageView     , albedoInfo->imageLayout      ));
        m_GBufferID.NormalID      = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(normalInfo->sampler     , normalInfo->imageView     , normalInfo->imageLayout      ));
        m_GBufferID.RoughnessID   = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(roughnessInfo->sampler  , roughnessInfo->imageView  , roughnessInfo->imageLayout   ));
        m_GBufferID.MetallicID    = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(metallicInfo->sampler   , metallicInfo->imageView   , metallicInfo->imageLayout    ));
        m_GBufferID.PositionID    = reinterpret_cast<ImTextureID>(ImGui_ImplVulkan_AddTexture(positionInfo->sampler   , positionInfo->imageView   , positionInfo->imageLayout    ));
    }
}