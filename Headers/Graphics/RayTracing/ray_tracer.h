#ifndef _RAY_TRACER_H
#define _RAY_TRACER_H

#include "../../Buffers/object_buffer.h"
#include "../program.h"
#include "../camera.h"

#define CAMERA_BUFFER_BINDING 2
#define PREV_CAMERA_BUFFER_BINDING 3
#define TEMPORAL_RESERVOIR_BUFFER_BINDING 4
#define SPATIAL_RESERVOIR_BUFFER_BINDING 5
#define RESERVOIR_HIT_INFO_BINDING 6

#define RENDER_IMAGE_INDEX 0

const static size_t RESERVOIR_BYTE_SIZE =  sizeof(glm::vec4) + 2 * sizeof(GLfloat) + 2 * sizeof(GLuint);
const static size_t RESERVOIR_PADDED_BYTE_SIZE = RESERVOIR_BYTE_SIZE + sizeof(glm::vec4) - RESERVOIR_BYTE_SIZE % sizeof(glm::vec4);

const static size_t RESERVOIR_HIT_INFO_BYTE_SIZED = sizeof(glm::vec4);

class RayTracer : public ComputeProgram
{
    private:
        ObjectBuffer<Camera>* cameraBuffer;
        ObjectBuffer<Camera>* prevCameraBuffer;

        StorageBuffer* temporalReservoirBuffer;
        StorageBuffer* spatialReservoirBuffer;
        StorageBuffer* reservoirHitInfoBuffer;
        
        ComputeProgram spatialReuse;
        ComputeProgram imageLoader;
        GLuint samplingDistanceLocation;

    public:
        RayTracer(const Camera& camera, const Texture2D& renderTexture) : ComputeProgram("./Shaders/Compute/rayTrace.comp")
        {
            this->spatialReuse = ComputeProgram("./Shaders/Compute/spatialReuse.comp");
            this->imageLoader = ComputeProgram("./Shaders/Compute/reservoirsToImage.comp");
            this->samplingDistanceLocation = glGetUniformLocation(this->spatialReuse.Id(), "samplingDistance");
            
            renderTexture.BindToImage(RENDER_IMAGE_INDEX, GL_WRITE_ONLY);
            glm::ivec2 texSize = renderTexture.Size();

            this->cameraBuffer = new ObjectBuffer<Camera>(camera, sizeof(Camera));
            this->cameraBuffer->BindToStorageBlock(CAMERA_BUFFER_BINDING);

            this->prevCameraBuffer = new ObjectBuffer<Camera>(camera, sizeof(Camera));
            this->prevCameraBuffer->BindToStorageBlock(PREV_CAMERA_BUFFER_BINDING);

            this->temporalReservoirBuffer = new StorageBuffer(RESERVOIR_PADDED_BYTE_SIZE * texSize.x * texSize.y);
            this->temporalReservoirBuffer->BindToStorageBlock(SPATIAL_RESERVOIR_BUFFER_BINDING);

            this->spatialReservoirBuffer = new StorageBuffer(RESERVOIR_PADDED_BYTE_SIZE * texSize.x * texSize.y);
            this->spatialReservoirBuffer->BindToStorageBlock(TEMPORAL_RESERVOIR_BUFFER_BINDING);

            this->reservoirHitInfoBuffer = new StorageBuffer(RESERVOIR_HIT_INFO_BYTE_SIZED * texSize.x * texSize.y);
            this->reservoirHitInfoBuffer->BindToStorageBlock(RESERVOIR_HIT_INFO_BINDING);

            this->Mount();
            glUniform2i(glGetUniformLocation(this->Id(), "dimensions"), texSize.x, texSize.y);

            this->spatialReuse.Mount();
            glUniform2i(glGetUniformLocation(this->spatialReuse.Id(), "dimensions"), texSize.x, texSize.y);
        }

        RayTracer() {}

        void Dispatch(glm::ivec3 groups, GLuint barrierMask = GL_ALL_BARRIER_BITS)
        {
            ComputeProgram::Dispatch(groups, barrierMask);

            this->spatialReuse.Mount();
            for (int i = 0, dst = 1; i < 3; i++, dst *= 3)
            {
                glUniform1i(this->samplingDistanceLocation, dst);
                this->spatialReuse.Dispatch(groups, barrierMask);
            }

            this->imageLoader.Mount();
            this->imageLoader.Dispatch(groups, barrierMask);

            Camera camera = this->cameraBuffer->GetValue();
            this->prevCameraBuffer->SetValue(camera);

            camera.frameCounter++;
            this->cameraBuffer->SetValue(camera);
        }

        void Dispose()
        {
            ComputeProgram::Dispose();

            this->spatialReuse.Dispose();
            this->imageLoader.Dispose();
            this->cameraBuffer->Dispose();
            this->prevCameraBuffer->Dispose();
            this->temporalReservoirBuffer->Dispose();
            this->reservoirHitInfoBuffer->Dispose();

            delete this->cameraBuffer;
            delete this->prevCameraBuffer;
            delete this->temporalReservoirBuffer;
            delete this->reservoirHitInfoBuffer;
        }

        Camera GetCamera() { return this->cameraBuffer->GetValue(); }

        void SetCamera(Camera camera) { this->cameraBuffer->SetValue(camera); }
};

#endif