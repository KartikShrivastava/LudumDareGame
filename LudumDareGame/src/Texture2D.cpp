#include "Texture2D.h"

Texture2D::Texture2D() : width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMag(GL_LINEAR), filterMin(GL_LINEAR){
	glGenTextures(1, &id);
}

void Texture2D::Generate(GLuint w, GLuint h, unsigned char* data){
	width = w;
	height = h;
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind(){
	glBindTexture(GL_TEXTURE_2D, id);
}
