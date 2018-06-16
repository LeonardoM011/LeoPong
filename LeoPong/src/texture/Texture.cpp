#include "Texture.h"
#include "vendor/stb/stb_image.h"

Texture::Texture(const std::string &filePath) :
    _rendererID(0),
    _filePath(""),
    _localBuffer(nullptr),
    _width(0),
    _height(0),
    _bPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    _localBuffer = stbi_load(filePath.c_str(), &_width, &_height, &_bPP, 4);

    GLCall(glGenTextures(1, &_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(_localBuffer) {
        stbi_image_free(_localBuffer);
    } else {
        ASSERT(false)
    }
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &_rendererID));
}

void Texture::Bind(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, _rendererID));
}

void Texture::UnBind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
