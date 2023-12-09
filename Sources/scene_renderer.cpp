#include "../Headers/Scene/scene_renderer.h"

SceneRenderer::SceneRenderer(Scene scene, Camera camera, int textureWidth, int textureHeight)
{
    this->renderTexture = Texture2D(textureWidth, textureHeight);
    this->rayTracer = new RayTracer(camera, this->renderTexture);

    this->dispatchGroups = glm::ivec3(
        ceilf(textureWidth / 32.0f),
        ceilf(textureHeight / 32.0f),
        1
    );

    this->sceneLoader = SceneLoader();
    this->sceneLoader.LoadScene(scene);
}