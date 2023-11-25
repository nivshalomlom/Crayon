#ifndef _RAY_TRACER_H
#define _RAY_TRACER_H

#include "../../Buffers/object_buffer.h"
#include "../program.h"
#include "../camera.h"

#define CAMERA_BUFFER_BINDING 2
#define CAMERA_BUFFER_NAME "CameraBuffer"

#define RESERVOIR_BUFFER_BINDING 3
#define RESERVOIR_BUFFER_NAME "ReservoirBuffer"

#define RENDER_IMAGE_INDEX 0
#define RESERVOIR_BUCKET_SIZE 4

const static size_t RESERVOIR_BYTE_SIZE = RESERVOIR_BUCKET_SIZE * (sizeof(glm::vec4) + sizeof(GLfloat)) + sizeof(GLfloat) + sizeof(GLuint);
const static size_t RESERVOIR_PADDED_BYTE_SIZE = RESERVOIR_BYTE_SIZE + sizeof(glm::vec4) - RESERVOIR_BYTE_SIZE % sizeof(glm::vec4);

class RayTracer : public ComputeProgram
{
    private:
        ObjectBuffer<Camera> cameraBuffer;
        StorageBuffer reservoirBuffer;
        ComputeProgram imageLoader;

    public:
        RayTracer(const Camera& camera, const Texture2D& renderTexture) : ComputeProgram("./Shaders/Compute/rayTrace.comp")
        {
            this->imageLoader = ComputeProgram("./Shaders/Compute/reservoirsToImage.comp");
            
            renderTexture.BindToImage(RENDER_IMAGE_INDEX, GL_WRITE_ONLY);
            glm::ivec2 texSize = renderTexture.Size();

            this->reservoirBuffer = StorageBuffer(RESERVOIR_PADDED_BYTE_SIZE * texSize.x * texSize.y);
            this->cameraBuffer = ObjectBuffer<Camera>(camera, sizeof(Camera));
            this->cameraBuffer.BindToStorageBlock(this->Id(), CAMERA_BUFFER_BINDING, CAMERA_BUFFER_NAME);

            this->Mount();
            glUniform2i(glGetUniformLocation(this->Id(), "dimensions"), texSize.x, texSize.y);
        }

        RayTracer() {}

        void Dispatch(glm::ivec3 groups, GLuint barrierMask = GL_ALL_BARRIER_BITS)
        {
            this->reservoirBuffer.BindToStorageBlock(this->Id(), RESERVOIR_BUFFER_BINDING, RESERVOIR_BUFFER_NAME);
            ComputeProgram::Dispatch(groups, barrierMask);

            this->imageLoader.Mount();
            this->reservoirBuffer.BindToStorageBlock(this->imageLoader.Id(), RESERVOIR_BUFFER_BINDING, RESERVOIR_BUFFER_NAME);
            this->imageLoader.Dispatch(groups, barrierMask);

            Camera camera = this->cameraBuffer.GetValue();
            camera.frameCounter++;

            this->cameraBuffer.SetValue(camera);
        }

        void Dispose()
        {
            ComputeProgram::Dispose();

            this->imageLoader.Dispose();
            this->reservoirBuffer.Dispose();
        }

        ObjectBuffer<Camera> ViewCamera() { return this->cameraBuffer; }
};

#endif