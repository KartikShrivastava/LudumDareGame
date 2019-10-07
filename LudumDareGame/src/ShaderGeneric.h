#pragma once

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderGeneric {
private:
	void CheckCompileErrors(GLuint object, std::string type);
public:
	GLuint id;

	ShaderGeneric() {}

	ShaderGeneric& Bind();
	void CompileShaderGeneric(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource = nullptr);
	void SetFloat(const GLchar* name, GLfloat value, GLboolean bindShader = false);
	void SetInteger(const GLchar* name, GLint value, GLboolean bindShader = false);
	void SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean bindShader = false);
	void SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean bindShader = false);
	void SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean bindShader = false);
	void SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean bindShader = false);
	void SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean bindShader = false);
	void SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean bindShader = false);
	void SetMatrix4f(const GLchar* name, const glm::mat4& matrix, GLboolean bindShader = false);
};