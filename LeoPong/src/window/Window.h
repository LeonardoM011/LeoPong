#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>

class Window {
public:
    Window(const std::string &title, int width, int height);
    ~Window();
    void Swap() const;
    void Update();
    bool ShouldClose() const;
    void Terminate() const;
    double GetDelta() const { return _deltaTime; }
    int GetFPS() const { return _FPS; }
	static bool IsKeyDown(int key) { return keydown[key]; }
private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static std::unordered_map<int, bool> keydown;
    GLFWwindow *_window;
    int _width;
    int _height;
    double _lastTime;
    double _currentTime;
    double _fLastTime;
    double _deltaTime;
    int _nFrames;
    int _FPS;
};