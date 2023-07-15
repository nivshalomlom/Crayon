#ifndef _SCENE_RENDERER_H
#define _SCENE_RENDERER_H

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
        ObjectBuffer<Camera> cameraBuffer;
        SceneLoader sceneLoader;
        StorageBuffer reservoirBuffer;

        ComputeProgram renderShader;
        ComputeProgram spatialReuse;

        glm::ivec3 dispatchGroups;
        Texture2D renderTexture;

        GLint frameCounterLocation; 
        GLuint frameCounter;

        void IncrementFrameCounter() { glUniform1ui(this->frameCounterLocation, ++this->frameCounter); }

    public:
        SceneRenderer(Scene scene, Camera camera, int textureWidth, int textureHeight, GLint imageIndex = 0);

        void LoadScene(Scene scene) { this->sceneLoader.LoadScene(scene, this->renderShader.Id()); }

        void ModifyCamera(std::function<Camera(Camera)> modification) 
        {
            Camera camera = modification(this->cameraBuffer.GetValue());
            this->cameraBuffer.SetValue(camera);
        }

        void Render()
        {
            this->renderShader.Mount();
            this->renderShader.Dispatch(
                this->dispatchGroups,
                GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
            );

            this->IncrementFrameCounter();
        }

        void Dispose()
        {
            this->sceneLoader.Dispose();
            this->renderShader.Dispose();
            this->renderTexture.Dispose();
            this->reservoirBuffer.Dispose();
        }

        const Texture2D RenderTexture() const { return this->renderTexture; }

        const Camera SceneCamera() const { return this->cameraBuffer.GetValue(); }

        const ArrayBuffer<Geometry> GetGeometry(GEOMETRY_TYPE type) const { return this->sceneLoader.GetGeometry(type); }
};

#endif