#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderGeneric.h"
#include "Texture2D.h"

class SpriteRenderer {
private:
	ShaderGeneric shader;
	GLuint VAO;
	void Init();
public:
	SpriteRenderer(ShaderGeneric& sh);
	~SpriteRenderer();

	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), 
					GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
};