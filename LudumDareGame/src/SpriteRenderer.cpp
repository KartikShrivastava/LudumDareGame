#include "SpriteRenderer.h"

void SpriteRenderer::Init(){
	GLfloat verts[] = {
		0.0f, 1.0f,		0.0f, 1.0f,	//position		texCoords
		1.0f, 0.0f,		1.0f, 0.0f,
		0.0f, 0.0f,		0.0f, 0.0f,

		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f
	};
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SpriteRenderer::SpriteRenderer(ShaderGeneric& sh){
	shader = sh;
	Init();
}

SpriteRenderer::~SpriteRenderer(){
	glDeleteVertexArrays(1, &VAO);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color){
	shader.Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position,0.0f));
	
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.SetMatrix4f("u_model", model);
	shader.SetVector3f("u_color", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}
