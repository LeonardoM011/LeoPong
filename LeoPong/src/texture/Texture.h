#pragma once
#include <string>
#include "renderer/Renderer.h"

class Texture {
public:
    Texture(const std::string &filePath);
    ~Texture();
    void Bind(unsigned int slot = 0) const;
    void UnBind() const;
    inline int GetWidth() const { return _width; }
    inline int GetHeight() const { return _height; }
private:
    unsigned int _rendererID;
    std::string _filePath;
    unsigned char *_localBuffer;
    int _width;
    int _height;
    int _bPP;
};