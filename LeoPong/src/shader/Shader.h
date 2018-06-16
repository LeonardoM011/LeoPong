#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string &filePath);
    ~Shader();
    void Bind() const;
    void UnBind() const;
	void Delete() const;
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void SetUniform1f(const std::string &name, float value);
    void SetUniform1i(const std::string &name, int value);
    void SetUniformMat4f(const std::string &name, const glm::mat4 matrix);
private:
    std::string LoadShader(const std::string& type, const std::string& filePath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    int GetUniformLocation(const std::string &name);
    unsigned int _rendererID;
    std::string _filePath;
    std::unordered_map<std::string, int> _uniformLocationCache;
};