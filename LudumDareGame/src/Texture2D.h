#pragma once

#include <glad/glad.h>

class Texture2D {
public:
	GLuint id;
	GLuint width, height;
	GLuint internalFormat, imageFormat;
	GLuint wrapS;
	GLuint wrapT;
	GLuint filterMin;
	GLuint filterMag;

	Texture2D();
	void Generate(GLuint width, GLuint height, unsigned char* data);
	void Bind();
};