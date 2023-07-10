#include "../Headers/Scene/scene_renderer.h"

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
}