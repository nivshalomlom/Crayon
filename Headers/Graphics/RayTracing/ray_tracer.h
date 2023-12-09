#ifndef _RAY_TRACER_H
#define _RAY_TRACER_H

#include "../../Buffers/object_buffer.h"
#include "../program.h"
#include "../camera.h"

#define CAMERA_BUFFER_BINDING 2
#define TEMPORAL_RESERVOIR_BUFFER_BINDING 3
#define SPATIAL_RESERVOIR_BUFFER_BINDING 4

#define RENDER_IMAGE_INDEX 0

const static size_t RESERVOIR_BYTE_SIZE = sizeof(glm::vec4) + 2 * sizeof(GLfloat) + sizeof(GLuint);
const static size_t RESERVOIR_PADDED_BYTE_SIZE = RESERVOIR_BYTE_SIZE + sizeof(glm::vec4) - RESERVOIR_BYTE_SIZE % sizeof(glm::vec4);

class RayTracer : public ComputeProgram
{
    private:
        StorageBuffer* temporalReservoirBuffer;
        StorageBuffer* spatialReservoirBuffer;

        ObjectBuffer<Camera>* cameraBuffer;
        ComputeProgram* imageLoader;

    public:
        RayTracer(const Camera& camera, const Texture2D& renderTexture) : ComputeProgram("./Shaders/Compute/rayTrace.comp")
        {
            this->imageLoader = new ComputeProgram("./Shaders/Compute/reservoirsToImage.comp");
            
            renderTexture.BindToImage(RENDER_IMAGE_INDEX, GL_WRITE_ONLY);
            glm::ivec2 texSize = renderTexture.Size();

            this->temporalReservoirBuffer = new StorageBuffer(RESERVOIR_PADDED_BYTE_SIZE * texSize.x * texSize.y);
            this->temporalReservoirBuffer->BindToStorageBlock(TEMPORAL_RESERVOIR_BUFFER_BINDING);

            this->spatialReservoirBuffer = new StorageBuffer(RESERVOIR_PADDED_BYTE_SIZE * texSize.x * texSize.y);
            this->spatialReservoirBuffer->BindToStorageBlock(SPATIAL_RESERVOIR_BUFFER_BINDING);

            this->cameraBuffer = new ObjectBuffer<Camera>(camera, sizeof(Camera));
            this->cameraBuffer->BindToStorageBlock(CAMERA_BUFFER_BINDING);

            this->Mount();
            glUniform2i(glGetUniformLocation(this->Id(), "dimensions"), texSize.x, texSize.y);
        }

        void Dispatch(glm::ivec3 groups, GLuint barrierMask = GL_ALL_BARRIER_BITS)
        {
            ComputeProgram::Dispatch(groups, barrierMask);

            this->imageLoader->Mount();
            this->imageLoader->Dispatch(groups, barrierMask);

            Camera camera = this->cameraBuffer->GetValue();
            camera.frameCounter++;

            this->cameraBuffer->SetValue(camera);
        }

        void Dispose()
        {
            ComputeProgram::Dispose();
            this->cameraBuffer->Dispose();
            this->imageLoader->Dispose();
            this->temporalReservoirBuffer->Dispose();
            this->spatialReservoirBuffer->Dispose();

            delete this->cameraBuffer;
            delete this->imageLoader;
            delete this->temporalReservoirBuffer;
            delete this->spatialReservoirBuffer;
        }

        ObjectBuffer<Camera>* ViewCamera() { return this->cameraBuffer; }
};

#endif