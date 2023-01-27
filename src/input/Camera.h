#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Handles camera data and matrix generation
class Camera
{
public:
	Camera(glm::vec3 position, float fov = 75.0f);

	// Camera getters
	[[nodiscard]] glm::vec3 GetPosition() const;
	[[nodiscard]] float GetFov() const;
	[[nodiscard]] float GetPitch() const;
	[[nodiscard]] float GetYaw() const;
	[[nodiscard]] float GetNearPlane() const;
	[[nodiscard]] float GetFarPlane() const;
	[[nodiscard]] float GetAspect() const;

	// Matrix getters
	[[nodiscard]] glm::mat4 GetViewMatrix() const;
	[[nodiscard]] glm::mat4 GetProjectionMatrix() const;
	[[nodiscard]] glm::mat4 GetMatrix() const;

	// Vector getters
	[[nodiscard]] glm::vec3 GetForward() const;
	[[nodiscard]] glm::vec3 GetRight() const;
	[[nodiscard]] glm::vec3 GetUp() const;
	[[nodiscard]] glm::vec3 GetForwardAligned() const;
	[[nodiscard]] static glm::vec3 GetUpAligned();

	// Movement setters
	void MoveForward(float amount);
	void MoveRight(float amount);
	void MoveUp(float amount);

	// Camera setters
	void SetPosition(glm::vec3 pos);
	void SetFov(float fov);
	void SetPitch(float pitch);
	void SetYaw(float yaw);
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);
	void SetAspect(float aspect);

private:
	glm::vec3 pos_{};
	float fov_{};
	float pitch_ = 0;
	float yaw_ = 0;
	float nearPlane_ = 0.1f;
	float farPlane_ = 2000.0f;
	float aspect_ = 16.0f / 9.0f;
};