#pragma once

#include <string>
#include <map>
#include <glad/glad.h>

#include "ShaderGeneric.h"
#include "Texture2D.h"

class ResourceManager {
private:
	ResourceManager(){}
	static ShaderGeneric LoadShaderFromFile(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	static Texture2D LoadTextureFromFile(const char* file, GLboolean alpha);
public:
	static std::map<std::string, ShaderGeneric> shaders;
	static std::map<std::string, Texture2D> textures;

	static ShaderGeneric LoadShader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath, std::string name);
	static ShaderGeneric& GetShader(std::string name);

	static Texture2D LoadTexture(const GLchar* texturePath, GLboolean alpha, std::string name);
	static Texture2D& GetTexture(std::string name);

	static void Clear();
};