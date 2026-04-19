/**
* @file TransformComponent.h.
* @brief The TransformComponent Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "Core/Math/Transform.h"
#include "Core/Container/BitSet.hpp"

namespace Neptune {

    /**
    * @brief TransformComponent Class.
    * This class defines the specific behaves of TransformComponent.
    */
    class TransformComponent : public Component<Transform>
    {
    public:

        enum TransformComponentBits : uint8_t
        {
            Clean = 0,
            NeedUpdateTLAS,
            
            Count
        };

    public:

        /**
        * @brief Constructor Function.
        */
        TransformComponent();

        /**
        * @brief Destructor Function.
        */
        ~TransformComponent() override = default;

        /**
        * @brief Set the position this component handled.
        * Call CalMatrix() during this API.
        * 
        * @param[in] position The entity's world position.
        */
        void SetPosition(const glm::vec3& position) { m_Model.position = position; CalMatrix(); }

        /**
        * @brief Set the rotation this component handled.
        * Call CalMatrix() during this API.
        * 
        * @param[in] rotation The entity's world rotation.
        */
        void SetRotation(const glm::vec3& rotation) { m_Model.rotation = rotation; CalMatrix(); }

        /**
        * @brief Set the scale this component handled.
        * Call CalMatrix() during this API.
        * 
        * @param[in] scale The entity's world scale.
        */
        void SetScale(const glm::vec3& scale) { m_Model.scale = scale; CalMatrix(); }

        /**
        * @brief Add the position to this component handled.
        * Call CalMatrix() during this API.
        * 
        * @param[in] position The entity's world position.
        */
        void AddPosition(const glm::vec3& position) { m_Model.position += position; CalMatrix(); }

        /**
        * @brief Add the rotation to this component handled.
        * Call CalMatrix() during this API.
        * 
        * @param[in] rotation The entity's world rotation.
        */
        void AddRotation(const glm::vec3& rotation) { m_Model.rotation += rotation; CalMatrix(); }

        /**
        * @brief Add the scale to this component handled.
        * Call CalMatrix() during this API.
        * 
        * @param[in] scale The entity's world scale.
        */
        void AddScale(const glm::vec3& scale) { m_Model.scale += scale; CalMatrix(); }

        /**
        * @brief Get the modelMatrix variable.
        * 
        * @return Returns the modelMatrix variable.
        */
        const glm::mat4& GetModelMatrix() { CalMatrix(); return m_ModelMatrix; }

        /**
        * @brief Get Rotate Matrix.
        * 
        * @return Returns the Rotate Matrix.
        */
        glm::mat4 GetRotateMatrix() const;

        /**
        * @brief Get the position variable.
        * 
        * @return Returns the position variable.
        */
        const glm::vec3& GetPosition() const { return m_Model.position; }

        /**
        * @brief Get the rotation variable.
        * 
        * @return Returns the rotation variable.
        */
        const glm::vec3& GetRotation() const { return m_Model.rotation; }

        /**
        * @brief Get the scale variable.
        * 
        * @return Returns the scale variable.
        */
        const glm::vec3& GetScale() const { return m_Model.scale; }

        /**
        * @brief Get WorldMarkFlags this frame.
        * 
        * @return Returns the TransformComponentFlags.
        */
        const Container::BitSet<TransformComponentBits>& GetMarker() const { return m_Marker; }

        /**
        * @brief Mark TransformComponentFlags with flags.
        * 
        * @param[in] flags In flags.
        */
        void Mark(const Container::BitSet<TransformComponentBits>& flags) { m_Marker |= flags; }

        /**
        * @brief Mark TransformComponentFlags with flags.
        * 
        * @param[in] bit In flags.
        */
        void Mark(const TransformComponentBits& bit) { m_Marker.Set(bit, true); }

        /**
        * @brief Clear TransformComponentFlags with flags.
        * 
        * @param[in] flags In flags.
        */
        void ClearMarkerWithBits(const Container::BitSet<TransformComponentBits>& flags) { m_Marker ^= flags; }

    private:

        /**
        * @brief Calculate Model Matrix.
        */
        void CalMatrix();

    private:

        glm::mat4 m_ModelMatrix = glm::mat4(1.0f);   // @brief The modelMatrix this component handled.

        Container::BitSet<TransformComponentBits> m_Marker = Clean;  // @brief World State this frame.
    };
}