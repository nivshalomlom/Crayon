#include "./Headers/Textures/texrenderer.h"
#include "./Headers/Textures/texture.h"
#include "./Headers/Graphics/program.h"
#include "./Headers/Graphics/window.h"
#include "./Headers/Graphics/camera.h"
#include "./Headers/Buffers/array_bufffer.h"
#include "./Headers/Geometry/primitives.h"

using namespace std;
using namespace glm;

int main(int argc, char **argv)
{
    Window* window = new Window(1280, 720, "Ray Tracing Demo", 60);

    ComputeProgram* render = new ComputeProgram("./Shaders/Compute/render.comp");
    TextureRenderer* renderer = new TextureRenderer();

    Camera camera = Camera(vec3(0, 0, 0), 25.0f, 16.0f / 9.0f, 5, 20);
    Sphere spheres[] = {
        Sphere(vec3(0, 0, 20), 3, Material(vec3(0.5, 0.0, 0.0)))
    };

    StorageBuffer* cameraBuffer = new StorageBuffer(&camera, sizeof(Camera));
    ArrayBuffer<Sphere>* sphereBuffer = new ArrayBuffer<Sphere>(spheres, 1, sizeof(Sphere));

    cameraBuffer->BindToStorageBlock(render->Id(), 2, "CameraBuffer");
    sphereBuffer->BindToStorageBlock(render->Id(), 0, "SphereBuffer");

    Texture2D* texture = new Texture2D(1280, 720);
    texture->BindToImage(0, GL_READ_WRITE);

    window->ToggleFpsCounter();
    window->Show([render, texture, renderer](Window* window, float dt) 
    {
        ivec2 size = window->Size();
        render->Mount();
        
        render->Dispatch(
            vec3(ceilf(size.x / 32.0f), ceilf(size.y / 32.0f), 1),
            GL_SHADER_IMAGE_ACCESS_BARRIER_BIT  
        );

        renderer->RenderToScreen(
            *texture, 
            ivec2(0), size
        );
    });

    window->Dispose();
    texture->Dispose();
    render->Dispose();
    renderer->Dispose();

    return 0;
}