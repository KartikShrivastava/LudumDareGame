#include "ResourceManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "expat/stb_image/stb_image.h"

std::map<std::string, ShaderGeneric> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

ShaderGeneric ResourceManager::LoadShaderFromFile(const char * vertexPath, const char * fragmentPath, const char * geometryPath){
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try {
		std::ifstream vertexFile(vertexPath);
		std::ifstream fragmentFile(fragmentPath);

		vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		
		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();

		if (geometryPath) {
			std::ifstream geometryFile(geometryPath);
			std::stringstream geometryStream;
			geometryStream << geometryFile.rdbuf();

			geometryFile.close();

			geometryCode = geometryStream.str();
		}
	}
	catch(std::exception e){
		std::cout << "Failed to read shader files. Error log:\n" << e.what() << std::endl;
	}

	ShaderGeneric shader;
	const GLchar* v = vertexCode.c_str();
	const GLchar* f = fragmentCode.c_str();
	const GLchar* g = geometryCode.c_str();
	shader.CompileShaderGeneric(v, f, geometryPath ? g : nullptr);
	return shader;
}

ShaderGeneric ResourceManager::LoadShader(const GLchar * vertexPath, const GLchar * fragmentPath, const GLchar * geometryPath, std::string name){
	shaders[name] = LoadShaderFromFile(vertexPath, fragmentPath, geometryPath);
	return shaders[name];
}

ShaderGeneric& ResourceManager::GetShader(std::string name){
	return shaders[name];
}

Texture2D ResourceManager::LoadTextureFromFile(const char * file, GLboolean alpha){
	Texture2D texture;
	//if (alpha) {
		//texture.internalFormat = GL_RGBA;
		//texture.imageFormat = GL_RGBA;
	//}
	int width, height, nChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nChannels, 0);
	if (nChannels == 1) {
		texture.internalFormat = GL_RED;
		texture.imageFormat = GL_RED;
	}
	if (nChannels == 3) {
		texture.internalFormat = GL_RGB;
		texture.imageFormat = GL_RGB;
	}
	if (nChannels == 4) {
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}

	if (data) {
		texture.Generate(width, height, data);
	}
	else {
		std::cout << "Unable to load texture." << std::endl;
	}
	stbi_image_free(data);
	return texture;
}

Texture2D ResourceManager::LoadTexture(const GLchar * texturePath, GLboolean alpha, std::string name){
	textures[name] = LoadTextureFromFile(texturePath, alpha);
	return textures[name];
}

Texture2D& ResourceManager::GetTexture(std::string name){
	return textures[name];
}

void ResourceManager::Clear(){
	for (auto i : shaders)
		glDeleteProgram(i.second.id);

	for (auto i : textures)
		glDeleteTextures(1, &i.second.id);
}
