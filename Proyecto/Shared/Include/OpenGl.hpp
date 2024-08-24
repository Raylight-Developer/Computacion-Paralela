#pragma once

#include "Include.hpp"
#include "Ops.hpp"

GLuint fragmentShaderProgram(const string& file_path);
GLuint computeShaderProgram(const string& file_path);
GLuint renderLayer(const uvec2& resolution);
void   bindRenderLayer(const GLuint& program_id, const GLuint& unit, const GLuint& id, const string& name);

void checkShaderCompilation(const GLuint& shader, const string& shader_code);
void checkProgramLinking(const GLuint& program);
void printShaderErrorWithContext(const string& shaderSource, const string& errorLog);

template <typename T>
GLuint ssboBinding(const GLuint& binding, const GLuint& size, const T& data) {
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, buffer);
	return buffer;
}