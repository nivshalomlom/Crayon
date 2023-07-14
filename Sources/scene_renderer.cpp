#include "../Headers/Scene/scene_renderer.h"

const static GLuint RESERVOIR_BUCKET_SIZE = 4;
const static size_t RESERVOIR_BYTE_SIZE = RESERVOIR_BUCKET_SIZE * (sizeof(glm::vec4) + sizeof(GLfloat)) + sizeof(GLfloat) + sizeof(GLuint);
const static size_t RESERVOIR_PADDED_BYTE_SIZE = RESERVOIR_BYTE_SIZE + sizeof(glm::vec4) - RESERVOIR_BYTE_SIZE % sizeof(glm::vec4);

SceneRenderer::SceneRenderer(Scene scene, Camera camera, int textureWidth, int textureHeight, GLint imageIndex)
{
    this->renderShader = ComputeProgram("./Shaders/Compute/rayTrace.comp");
    this->renderTexture = Texture2D(textureWidth, textureHeight);
    
    this->frameCounterLocation = glGetUniformLocation(this->renderShader.Id(), "frameCounter");
    this->frameCounter = 0;

    this->renderTexture.BindToImage(imageIndex);
    this->dispatchGroups = glm::ivec3(
        ceilf(textureWidth / 32.0f),
        ceilf(textureHeight / 32.0f),
        1
    );

    this->geometryBuffer = GeometryBuffer();
    this->geometryBuffer.SetScene(scene, this->renderShader.Id());

    this->cameraBuffer = ObjectBuffer<Camera>(camera, sizeof(Camera));
    this->cameraBuffer.BindToStorageBlock(this->renderShader.Id(), 2, "CameraBuffer");

    this->reservoirBuffer = StorageBuffer(RESERVOIR_PADDED_BYTE_SIZE * textureWidth * textureHeight);
    this->reservoirBuffer.BindToStorageBlock(this->renderShader.Id(), 3, "ReservoirBuffer");
}