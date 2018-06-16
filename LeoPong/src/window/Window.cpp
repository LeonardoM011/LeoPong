#include "Window.h"
#include <iostream>

std::unordered_map<int, bool> Window::keydown;

Window::Window(const std::string &title, int width, int height) :
    _width(width),
    _height(height),
    _window(nullptr),
    _lastTime(0.0),
    _currentTime(0.0),
    _fLastTime(0.0),
    _deltaTime(0.0),
    _nFrames(0),
    _FPS(60)
{
    // Initializing glfw and checking for failure
    if (!glfwInit())
        std::cerr << "GLFW failed to initialize!" << std::endl;

    // Seting GLFW Context to OpenGL version 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating Window
    _window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    // Checking Window creation for failure
    if (!_window) {
        // Terminating GLFW
        glfwTerminate();
        std::cerr << "WINDOW failed to create!" << std::endl;
    }

    // Making Context of Window Current for the calling thread
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(0);

    // Initializing GLEW and checking for failure
    if (glewInit() != GLEW_OK) {
		std::cerr << "Glew init failed!" << std::endl;
	}
    
    glfwSetKeyCallback(_window, key_callback);
    
    _lastTime = glfwGetTime();
    _fLastTime = glfwGetTime();
}

Window::~Window() {

}

void Window::Swap() const {
    // Swap Window Bufferss
    glfwSwapBuffers(_window);
}

void Window::Update() {
    _currentTime = glfwGetTime();
    _deltaTime = _currentTime - _lastTime;
    _lastTime = _currentTime;
    _nFrames++;
    if(_currentTime - _fLastTime > 1.0) {
        _FPS = _nFrames;
        _nFrames = 0;
        _fLastTime = _currentTime;
    }

    // Process Input
    glfwPollEvents();
}

bool Window::ShouldClose() const {
    // Return True if clicked the X button
    return glfwWindowShouldClose(_window);
}

void Window::Terminate() const {
    // Terminate glfw
    glfwTerminate();
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		keydown[key] = true;
	}
	if (action == GLFW_RELEASE) {
		keydown[key] = false;
	}
}
