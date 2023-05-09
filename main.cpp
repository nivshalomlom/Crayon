#include "./Headers/Textures/texrenderer.h"
#include "./Headers/Graphics/window.h"
#include "../Headers/Scene/scene_renderer.h"

using namespace std;
using namespace glm;

/*
REPEAT FOR X RAYS PER PIXEL

var ray = computeRay();
var closest = 0;

foreach geometry in geometries:
    if intersects(geometry, ray, out hit) && (closest == 0 || closest.dst > hit.dst):
        closest = dst;

var color = hitColor(hit);
if ray.canBounce:
    var reflected = reflect(hit, ray);
    color = BRDF(hit, shoot(reflected));

return color
*/

int main(int argc, char **argv)
{
    Window window = Window(1280, 720, "Ray Tracing Demo", 60);
    Camera camera = Camera(vec3(0, 0, 0), 30.0f, 16.0f / 9.0f, 5, 20);
    Scene scene = Scene();

    scene.Add(Sphere(vec3(-5, -1, 20), 1, Material(vec3(0.5, 0.0, 0.0))), SPHERE_TYPE);
    scene.Add(Sphere(vec3(-1, 0, 20), 2, Material(vec3(0.0, 0.5, 0.0))), SPHERE_TYPE);
    scene.Add(Sphere(vec3(4.5, 1, 20), 3, Material(vec3(0.0, 0.0, 0.5))), SPHERE_TYPE);
    scene.Add(Plane(vec3(0, -2, 20), vec3(7.0), Material(vec3(0.0, 0.5, 0.5))), PLANE_TYPE);
    SceneRenderer* sceneRenderer = new SceneRenderer(scene, camera, 1280, 720);

    TextureRenderer* textureRenderer = new TextureRenderer();
    Texture2D renderTexture = sceneRenderer->RenderTexture();

    window.ToggleFpsCounter();
    window.Show([sceneRenderer, textureRenderer, renderTexture](Window* window, float dt) 
    {
        sceneRenderer->Render();
        textureRenderer->RenderToScreen(renderTexture, ivec2(0), ivec2(1280, 720));
    });

    window.Dispose();
    scene.Dispose();
    sceneRenderer->Dispose();
    textureRenderer->Dispose();

    return 0;
}