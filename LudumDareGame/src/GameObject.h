#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"

class GameObject {
public:
	glm::vec2 position, size, velocity;
	glm::vec3 color;
	GLfloat rotation;
	Texture2D sprite;

	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 col = glm::vec3(1.0f), glm::vec2 vel = glm::vec2(0.0f,0.0f));

	virtual void Draw(SpriteRenderer& renderer);
};