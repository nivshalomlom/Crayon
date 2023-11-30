#ifndef _SCENE_RENDERER_H
#define _SCENE_RENDERER_H

#include "../Graphics/RayTracing/ray_tracer.h"
#include "../Buffers/object_buffer.h"
#include "../Graphics/program.h"
#include "../Graphics/camera.h"
#include "../Textures/texture.h"
#include "../Utility/disposable.h"
#include "./Utility/scene_loader.h"
#include "./scene.h"

class SceneRenderer : public Disposable
{
    private:
        SceneLoader sceneLoader;
        RayTracer* rayTracer;

        glm::ivec3 dispatchGroups;
        Texture2D renderTexture;

    public:
        SceneRenderer(Scene scene, Camera camera, int textureWidth, int textureHeight);

        void LoadScene(Scene scene) { this->sceneLoader.LoadScene(scene, this->rayTracer); }

        void Render()
        {
            this->rayTracer->Mount();
            this->rayTracer->Dispatch(
                this->dispatchGroups,
                GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT
            );
        }

        void Dispose()
        {
            this->sceneLoader.Dispose();
            this->rayTracer->Dispose();
            this->renderTexture.Dispose();

            delete this->rayTracer;
        }

        const Texture2D RenderTexture() const { return this->renderTexture; }

        const ArrayBuffer<Geometry>* GetGeometry(GEOMETRY_TYPE type) const { return this->sceneLoader.GetGeometry(type); }
};

#endif