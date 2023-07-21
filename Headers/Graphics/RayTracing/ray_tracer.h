#ifndef _RAY_TRACER_H
#define _RAY_TRACER_H

#include "../../Buffers/object_buffer.h"
#include "../program.h"
#include "../camera.h"

#define RESERVOIR_BUCKET_SIZE 4
#define RENDER_IMAGE_INDEX 0

const static size_t RESERVOIR_BYTE_SIZE = RESERVOIR_BUCKET_SIZE * (sizeof(glm::vec4) + sizeof(GLfloat)) + sizeof(GLfloat) + sizeof(GLuint);
const static size_t RESERVOIR_PADDED_BYTE_SIZE = RESERVOIR_BYTE_SIZE + sizeof(glm::vec4) - RESERVOIR_BYTE_SIZE % sizeof(glm::vec4);

class RayTracer : public ComputeProgram
{
    private:
        ObjectBuffer<Camera> cameraBuffer;
        StorageBuffer reservoirBuffer;
        
        ComputeProgram spatialReuse;
        // ComputeProgram temporalReuse;

    public:
        RayTracer(Camera camera, Texture2D renderTexture) : ComputeProgram("./Shaders/Compute/rayTrace.comp")
        {
            this->spatialReuse = ComputeProgram("./Shaders/Compute/spatialReuse.comp");
            renderTexture.BindToImage(RENDER_IMAGE_INDEX);

            glm::ivec2 texSize = renderTexture.Size();
            this->reservoirBuffer = StorageBuffer(RESERVOIR_PADDED_BYTE_SIZE * texSize.x * texSize.y);
            this->reservoirBuffer.BindToStorageBlock(this->Id(), 3, "ReservoirBuffer");

            this->cameraBuffer = ObjectBuffer<Camera>(camera, sizeof(Camera));
            this->cameraBuffer.BindToStorageBlock(this->Id(), 2, "CameraBuffer");
        }

        RayTracer() {}

        void Dispose()
        {
            ComputeProgram::Dispose();

            this->spatialReuse.Dispose();
            this->reservoirBuffer.Dispose();
        }
};

#endif