#include <iostream>

#include "ShaderGeneric.h"

void ShaderGeneric::CheckCompileErrors(GLuint object, std::string type){
	GLint success;
	GLchar infoLog[1024];
	if (type != "Program") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "Shader compilation failed for " << type << " shader. Error log:\n" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "Program linking falied. Error log:\n" << infoLog << std::endl;
		}
	}
}

ShaderGeneric& ShaderGeneric::Bind(){
	glUseProgram(id);
	return *this;
}

void ShaderGeneric::CompileShaderGeneric(const GLchar * vertexSource, const GLchar * fragmentSource, const GLchar * geometrySource){
	GLuint vertexID, fragmentID, geometryID;

	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexSource, NULL);
	glCompileShader(vertexID);
	CheckCompileErrors(vertexID, "Vertex");

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentSource, NULL);
	glCompileShader(fragmentID);
	CheckCompileErrors(fragmentID, "Fragment");

	if (geometrySource != nullptr) {
		geometryID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryID, 1, &geometrySource, NULL);
		glCompileShader(geometryID);
		CheckCompileErrors(geometryID, "Geometry");
	}

	id = glCreateProgram();
	glAttachShader(id, vertexID);
	glAttachShader(id, fragmentID);
	if (geometrySource != nullptr)
		glAttachShader(id, geometryID);
	glLinkProgram(id);
	CheckCompileErrors(id, "Program");

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	if (geometrySource != nullptr)
		glDeleteShader(geometryID);
}

void ShaderGeneric::SetFloat(const GLchar * name, GLfloat value, GLboolean bindShader){
	if (bindShader)
		Bind();
	glUniform1f(glGetUniformLocation(id, name), value);
}

void ShaderGeneric::SetInteger(const GLchar * name, GLint value, GLboolean bindShader) {
	if (bindShader)
		Bind();
	glUniform1i(glGetUniformLocation(id, name), value);
}

void ShaderGeneric::SetVector2f(const GLchar * name, GLfloat x, GLfloat y, GLboolean bindShader) {
	if (bindShader)
		Bind();
	glUniform2f(glGetUniformLocation(id, name), x, y);
}

void ShaderGeneric::SetVector2f(const GLchar * name, const glm::vec2& value, GLboolean bindShader) {
	if (bindShader)
		Bind();
	glUniform2fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
}

void ShaderGeneric::SetVector3f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLboolean bindShader) {
	if (bindShader)
		Bind();
	glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void ShaderGeneric::SetVector3f(const GLchar * name, const glm::vec3 & value, GLboolean bindShader) {
	if (bindShader)
		Bind();
	glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
}

void ShaderGeneric::SetVector4f(const GLchar * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean bindShader) {
	if (bindShader)
		Bind();
	glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}

void ShaderGeneric::SetVector4f(const GLchar * name, const glm::vec4 & value, GLboolean bindShader) {
	if (bindShader)
		Bind();
	glUniform4fv(glGetUniformLocation(id, name), 1, glm::value_ptr(value));
}

void ShaderGeneric::SetMatrix4f(const GLchar * name, const glm::mat4 & matrix, GLboolean bindShader) {
	if (bindShader)
		Bind();
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
