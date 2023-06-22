#include "./Headers/Textures/texture_buffer.h"
#include "./Headers/Graphics/window.h"
#include "./Headers/Scene/scene_renderer.h"
#include "./Headers/PostProcessing/bloom.h"
#include "./Headers/PostProcessing/tone_mapping.h"

#define WIDTH 1920
#define HEIGHT 1080

using namespace std;
using namespace glm;

int main(int argc, char **argv)
{
    Window window = Window(WIDTH, HEIGHT, "Ray Tracing Demo", 60);
    Camera camera = Camera(vec3(0, 0, 0), 30.0f, float(WIDTH) / HEIGHT, 5, 20);

    Scene scene = Scene();
    scene.Add(Sphere(vec3(-5, -1, 20), 1, Material(vec3(0.0), vec3(100, 50, 0), 1.0)), SPHERE_TYPE);
    scene.Add(Sphere(vec3(-1, 0, 20), 2, Material(vec3(0.0, 0.5, 0.0))), SPHERE_TYPE);
    scene.Add(Sphere(vec3(4.5, 1, 20), 3, Material(vec3(0.0), vec3(0, 50, 100), 1.0)), SPHERE_TYPE);
    scene.Add(Plane(vec3(0, -2, 20), vec3(7.0), Material(vec3(1.0))), PLANE_TYPE);

    SceneRenderer* sceneRenderer = new SceneRenderer(scene, camera, WIDTH, HEIGHT);
    TextureBuffer* textureRenderer = new TextureBlitBuffer();

    Texture2D renderTexture = sceneRenderer->RenderTexture();
    textureRenderer->AddPostProcessing(new BloomProgram(0.8, 0.8));
    textureRenderer->AddPostProcessing(new ToneMappingProgram(0.1, 2.2));

    window.ToggleFpsCounter();
    window.Show([sceneRenderer, textureRenderer, renderTexture](Window* window, float dt) 
    {
        sceneRenderer->Render();
        textureRenderer->RenderToBuffer(renderTexture, ivec2(0), ivec2(WIDTH, HEIGHT));
    });

    window.Dispose();
    scene.Dispose();
    sceneRenderer->Dispose();
    textureRenderer->Dispose();

    return 0;
}