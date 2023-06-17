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

        GLenum Format() { return this->colorForamt; }
        
        virtual glm::ivec2 Dimensions() = 0;

        virtual std::byte* ReadBytes() = 0;

        virtual TextureFile* WriteBytes(Texture2D texture) = 0;
};

#endif