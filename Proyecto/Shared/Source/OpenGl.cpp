#include "OpenGl.hpp"

#include "Session.hpp"

GLuint fragmentShaderProgram(const string& file_path) {
	GLuint shader_program = glCreateShader(GL_VERTEX_SHADER);

	GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
	const string vertex_code = loadFromFile("./Resources/Shaders/" + file_path + ".vert");
	const char* vertex_code_cstr = vertex_code.c_str();
	glShaderSource(vert_shader, 1, &vertex_code_cstr, NULL);
	glCompileShader(vert_shader);

	checkShaderCompilation(vert_shader, vertex_code);

	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const string fragment_code = loadFromFile("./Resources/Shaders/" + file_path + ".frag");
	const char* fragment_code_cstr = fragment_code.c_str();
	glShaderSource(frag_shader, 1, &fragment_code_cstr, NULL);
	glCompileShader(frag_shader);

	checkShaderCompilation(frag_shader, fragment_code);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vert_shader);
	glAttachShader(shader_program, frag_shader);
	glLinkProgram(shader_program);

	checkProgramLinking(shader_program);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	return shader_program;
}

GLuint computeShaderProgram(const string& file_path) {
	GLuint shader_program;
	string compute_code = preprocessShader("./Resources/Shaders/" + file_path + ".comp");
	writeToFile("./Resources/Shaders/" + file_path + "_Compiled.comp", compute_code);
	const char* compute_code_cstr = compute_code.c_str();
	GLuint comp_shader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(comp_shader, 1, &compute_code_cstr, NULL);
	glCompileShader(comp_shader);

	checkShaderCompilation(comp_shader, compute_code);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, comp_shader);
	glLinkProgram(shader_program);

	checkProgramLinking(shader_program);

	glDeleteShader(comp_shader);

	return shader_program;
}

GLuint renderLayer(const uvec2& resolution) {
	GLuint ID;
	glCreateTextures(GL_TEXTURE_2D, 1, &ID);
	glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureStorage2D (ID, 1, GL_RGBA32F, resolution.x,resolution.y);
	return ID;
}

void bindRenderLayer(const GLuint& program_id, const GLuint& unit, const GLuint& id, const string& name) {
	glUniform1i(glGetUniformLocation(program_id, name.c_str()), unit);
	glBindTextureUnit(unit, id);
}

void checkShaderCompilation(const GLuint& shader, const string& shader_code) {
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
		LOG ENDL ENDL ANSI_R << "[OpenGL]" ANSI_RESET << " Shader Compilation Failed: "; FLUSH;
		printShaderErrorWithContext(shader_code, infoLog);
		exit(100);
	}
}

void checkProgramLinking(const GLuint& program) {
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
		LOG ENDL ENDL ANSI_R << "[OpenGL]" ANSI_RESET << " Program Linking Failed: " << infoLog; FLUSH;
		exit(101);
	}
}

void printShaderErrorWithContext(const string& shaderSource, const string& errorLog) {
	LOG += 1;
	size_t pos = errorLog.find('(');
	if (pos == string::npos) {
		LOG ENDL << "Error: Unable to parse error log."; FLUSH;
		LOG -= 1;
		return;
	}

	size_t endPos = errorLog.find(')', pos);
	if (endPos == string::npos) {
		LOG ENDL << "Error: Unable to parse error log."; FLUSH;
		LOG -= 1;
		return;
	}

	uint64 lineNumber = str_to_ul(errorLog.substr(pos + 1, endPos - pos - 1));

	Tokens lines = f_split(shaderSource, "\n");

	uint64 startLine = max(0ULL, lineNumber - 4);
	uint64 endLine = min(lines.size(), lineNumber + 3);

	for (uint64 i = startLine; i < endLine; ++i) {
		LOG ENDL << (i + 1) << ": " << lines[i];
		if (i == lineNumber - 1) {
			LOG ENDL ANSI_R << "^-- Error here: " ANSI_RESET << errorLog;
		}
	}
	LOG -= 1;
	LOG ENDL ENDL;
	FLUSH;
}