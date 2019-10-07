#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game {
private:
	float frame = 0;
	int sign = 1;
	glm::vec2 avocadoPosition;
	glm::vec2 avocadoSize;
	int waterDropPos;
	bool moving = false;
	int thunderCount = 0;

public:
	GameState state;
	GLboolean keys[1024];
	GLuint width, height;
	Game(GLuint w, GLuint h);
	~Game();
	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};