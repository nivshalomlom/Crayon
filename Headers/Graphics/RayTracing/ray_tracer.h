#ifndef _RAY_TRACER_H
#define _RAY_TRACER_H

#include "../../Buffers/object_buffer.h"
#include "../program.h"
#include "../camera.h"

#define CAMERA_BUFFER_BINDING 2
#define TEMPORAL_RESERVOIR_BUFFER_BINDING 3
#define SPATIAL_RESERVOIR_BUFFER_BINDING 4
#define RESERVOIR_INFO_BUFFER_BINDING 5

#define RENDER_IMAGE_INDEX 0

const static size_t RESERVOIR_BYTE_SIZE = sizeof(glm::vec4) + 2 * sizeof(GLfloat) + sizeof(GLuint) + /* PADDDING: */ sizeof(GLfloat);
const static size_t RESERVOIR_INFO_BYTE_SIZE = sizeof(glm::vec4);

class RayTracer : public ComputeProgram
{
    private:
        StorageBuffer* temporalReservoirBuffer;
        StorageBuffer* spatialReservoirBuffer;
        StorageBuffer* reservoirInfoBuffer;

        ObjectBuffer<Camera>* cameraBuffer;
        ComputeProgram* imageLoader;

    public:
        RayTracer(const Camera& camera, const Texture2D& renderTexture) : ComputeProgram("./Shaders/Compute/rayTrace.comp")
        {
            this->imageLoader = new ComputeProgram("./Shaders/Compute/reservoirsToImage.comp");
            renderTexture.BindToImage(RENDER_IMAGE_INDEX, GL_WRITE_ONLY);
            
            glm::ivec2 texSize = renderTexture.Size();
            size_t numPixels = texSize.x * texSize.y;

            this->temporalReservoirBuffer = new StorageBuffer(RESERVOIR_BYTE_SIZE * numPixels);
            this->temporalReservoirBuffer->BindToStorageBlock(TEMPORAL_RESERVOIR_BUFFER_BINDING);

            this->spatialReservoirBuffer = new StorageBuffer(RESERVOIR_BYTE_SIZE * numPixels);
            this->spatialReservoirBuffer->BindToStorageBlock(SPATIAL_RESERVOIR_BUFFER_BINDING);

            this->reservoirInfoBuffer = new StorageBuffer(RESERVOIR_INFO_BYTE_SIZE * numPixels);
            this->reservoirInfoBuffer->BindToStorageBlock(RESERVOIR_INFO_BUFFER_BINDING);

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
            this->reservoirInfoBuffer->Dispose();

            delete this->cameraBuffer;
            delete this->imageLoader;
            delete this->temporalReservoirBuffer;
            delete this->spatialReservoirBuffer;
            delete this->reservoirInfoBuffer;
        }

        ObjectBuffer<Camera>* ViewCamera() { return this->cameraBuffer; }
};

#endif