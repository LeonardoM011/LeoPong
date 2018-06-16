#include "Shader.h"
#include <iostream>
#include <fstream>
#include "renderer/Renderer.h"

Shader::Shader(const std::string &filePath) : 
    _filePath(filePath),
    _rendererID(0)
{
    std::string vertexShader = LoadShader("VERTEX_SHADER", filePath);
	std::string fragmentShader = LoadShader("FRAGMENT_SHADER", filePath);
	_rendererID = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader() {
    //GLCall(glDeleteProgram(_rendererID));
}

void Shader::Bind() const {
    GLCall(glUseProgram(_rendererID));
}

void Shader::Delete() const {
	GLCall(glDeleteProgram(_rendererID));
}

void Shader::UnBind() const {
    GLCall(glUseProgram(0));
}

std::string Shader::LoadShader(const std::string& type, const std::string& filePath) {	

	std::ifstream stream(filePath);

	bool isFound = false;
	
	std::string shaderContents = "";
	std::string line;
	while (getline(stream, line)) {

		if (line.find("#shader") != std::string::npos) {
			if (isFound)
				break;
			isFound = false;
			if (line.find(type) != std::string::npos) {
				isFound = true;
				continue;
			}
		}

		if (isFound) {
			shaderContents.append(line);
			shaderContents.append("\n");
		}
		
	}

	return shaderContents;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {

	GLCall(unsigned int shaderid = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(shaderid, 1, &src, nullptr));
	GLCall(glCompileShader(shaderid));

	int result;
	GLCall(glGetShaderiv(shaderid, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &length));
		char *message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(shaderid, length, &length, message));
		std::cerr << "Failed to compile " << type << std::endl << message << std::endl;
		GLCall(glDeleteShader(shaderid));
		return 0;
	}

	return shaderid;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {

	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1f(const std::string &name, float value) {
	GLCall(glUniform1f(GetUniformLocation(name), value));
}
    
void Shader::SetUniform1i(const std::string &name, int value) {
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 matrix) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string &name) {
	if(_uniformLocationCache.find(name) != _uniformLocationCache.end()) {
		return _uniformLocationCache[name];
	} 
    GLCall(int location = glGetUniformLocation(_rendererID, name.c_str()));
	if(location == -1) {
        std::cerr << "Warning: Uniform (" << name << ") not found in shader (" << _filePath << ")" << std::endl; 
    }
	_uniformLocationCache[name] = location;
    return location;
}
