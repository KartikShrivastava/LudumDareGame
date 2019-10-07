#include <iostream>
#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "Game.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint width = 800;
const GLuint height = 600;

Game AnAvocado(width, height);

int main(int argc, char** argv) {
	if(!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(width, height, "An Avocado", nullptr, nullptr);
	if (!window) {
		std::cout << "Unable to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Unable to intialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	AnAvocado.Init();

	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	AnAvocado.state = GAME_ACTIVE;

	using namespace std::literals::chrono_literals;

	while (!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		AnAvocado.ProcessInput(deltaTime);

		AnAvocado.Update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		AnAvocado.Render();

		glfwSwapBuffers(window);

		std::this_thread::sleep_for(0.001s);
	}

	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			AnAvocado.keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			AnAvocado.keys[key] = GL_FALSE;
	}
}