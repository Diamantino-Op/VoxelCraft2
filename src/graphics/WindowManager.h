#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Wrapper for GLFW windows
class WindowManager
{
public:
	// Singleton pattern
	static WindowManager &Instance()
	{
		static WindowManager instance;
		return instance;
	}

	WindowManager();
	void Update(float dt) const;

	void Init(int width, int height);

	// Getters
	[[nodiscard]] GLFWwindow *GetWindow() const;
	[[nodiscard]] glm::ivec2 GetResolution() const;
	[[nodiscard]] glm::vec3 GetClearColor() const;

	// Setters
	void SetClearColor(glm::vec3 color);

	// Maximize this window
	void Maximize() const;

	// Set rendering target to window
	void SetFramebuffer() const;

	~WindowManager();

private:
	GLFWwindow *window_;
	glm::ivec2 resolution_;
	glm::vec3 clearColor_{};

	static int windowWidth;
	static int windowHeight;

	static void ResizeCallback(GLFWwindow *window, int width, int height); // window resize callback

public: // Remove functions for singleton
	WindowManager(WindowManager const &) = delete;
	void operator=(WindowManager const &) = delete;
};