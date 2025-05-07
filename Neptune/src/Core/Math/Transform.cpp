/**
* @file Transform.h.
* @brief The Transform Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Neptune {

	glm::mat4 Transform::ToMatrix()
	{
		NEPTUNE_PROFILE_ZONE;

		return std::move(
			glm::translate(glm::mat4(1.0f), position) * 
			GetRoatationMatrix(rotation) *
			glm::scale(glm::mat4(1.0f), scale)
		);
	}

	glm::mat4 Transform::GetRoatationMatrix(const glm::vec3& rotation)
	{
		NEPTUNE_PROFILE_ZONE;

		return 
			std::move(
			glm::toMat4(
			glm::quat({
				glm::radians(rotation.x),
				glm::radians(rotation.y),
				glm::radians(rotation.z)
			})
		));
	}

	glm::mat4 Transform::ToMatrix(const Transform& transform)
	{
		NEPTUNE_PROFILE_ZONE;

		return std::move(
			glm::translate(glm::mat4(1.0f), transform.position) * 
			GetRoatationMatrix(transform.rotation) *
			glm::scale(glm::mat4(1.0f), transform.scale)
		);
	}
}