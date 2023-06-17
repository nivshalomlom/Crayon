#ifndef _TEXTURE_FILE_H
#define _TEXTURE_FILE_H

#include "../common.h"

class TextureFile
{
    private:
        GLenum colorForamt;

    public:
        TextureFile(GLenum colorFormat)
        {
            this->colorForamt = colorForamt;
        }

        virtual glm::ivec2 Dimensions() = 0;

        virtual std::byte* GetBytes() = 0;

        GLenum Format() { return this->colorForamt; }
};

#endif