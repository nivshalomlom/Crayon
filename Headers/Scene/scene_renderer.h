#ifndef _SCENE_RENDERER_H
#define _SCENE_RENDERER_H

#include "../Buffers/object_buffer.h"
#include "../Graphics/program.h"
#include "../Graphics/camera.h"
#include "../Textures/texture.h"
#include "../Utility/disposable.h"
#include "./Utility/geometry_buffer.h"
#include "./scene.h"

class SceneRenderer : public Disposable
{
    private:
        ObjectBuffer<Camera> cameraBuffer;
        GeometryBuffer geometryBuffer;

        ComputeProgram renderShader;
        Texture2D renderTexture;
        glm::ivec3 dispatchGroups;

        GLint frameCounterLocation; 
        GLuint frameCounter;

        void IncrementFrameCounter() { glUniform1ui(this->frameCounterLocation, ++this->frameCounter); }

    public:
        SceneRenderer(Scene scene, Camera camera, int textureWidth, int textureHeight, GLint imageIndex = 0);

        void SetScene(Scene scene);

        // void ModifyGeometry(GEOMETRY_TYPE type, int index, std::function<Geometry(Geometry)> modification)
        // {
        //     Geometry geometry = this->geometryBuffers[type].Get(index);
        //     geometry = modification(geometry);

        //     this->geometryBuffers[type].Set(geometry, index);
        // }

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
            this->geometryBuffer.Dispose();
            this->renderShader.Dispose();
            this->renderTexture.Dispose();
        }

        const Texture2D RenderTexture() const { return this->renderTexture; }

        const Camera SceneCamera() const { return this->cameraBuffer.GetValue(); }

        // const ArrayBuffer<Geometry> GetAllGeometry(GEOMETRY_TYPE type) const { return this->geometryBuffers[type]; }
};

#endif