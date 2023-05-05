#ifndef _SCENE_RENDERER_H
#define _SCENE_RENDERER_H

#include "../Buffers/array_bufffer.h"
#include "../Graphics/program.h"
#include "../Graphics/camera.h"
#include "../Textures/texture.h"
#include "../Utility/disposable.h"
#include "./scene.h"

struct BufferInfo
{
    private:
        const char* name;
        size_t itemSize;
        int binding;

    public:
        BufferInfo(const char* name, size_t itemSize, int binding)
        {
            this->name = name;
            this->itemSize = itemSize;
            this->binding = binding;
        }

        const char* Name() const { return this->name; }

        const size_t ItemSize() const { return this->itemSize; }
        
        const int Binding() const { return this->binding; }
};

class SceneRenderer : public Disposable
{
    private:
        static const int NUM_BUFFERS = PLANE_TYPE + 1;
        static BufferInfo* BUFFERS_INFO;

        ArrayBuffer<Geometry>* geometryBuffers;
        ComputeProgram renderShader;
        Texture2D renderTexture;
        glm::ivec3 dispatchGroups;

    public:
        SceneRenderer(Scene scene, Camera camera, int textureWidth, int textureHeight, GLint imageIndex = 0)
        {
            this->renderShader = ComputeProgram("./Shaders/Compute/render.comp");
            this->renderTexture = Texture2D(textureWidth, textureHeight);
            
            this->renderTexture.BindToImage(imageIndex);
            this->dispatchGroups = glm::ivec3(
                ceilf(textureWidth / 32.0f), 
                ceilf(textureHeight / 32.0f),
                1
            );
        }

        void SetScene(Scene scene)
        {
            if (this->geometryBuffers != nullptr)
            {
                for (int i = 0; i < NUM_BUFFERS; i++)
                    this->geometryBuffers[i].Dispose();

                delete [] this->geometryBuffers;
            }

            this->geometryBuffers = new ArrayBuffer<Geometry>[NUM_BUFFERS];
            for (int i = 0; i < NUM_BUFFERS; i++)
            {
                List<Geometry> geometry = scene.GetAllGeometry((GEOMETRY_TYPE) (i - 1));
                BufferInfo info = BUFFERS_INFO[i];

                this->geometryBuffers[i] = ArrayBuffer<Geometry>(geometry.ToArray(), geometry.Count(), info.ItemSize());
                this->geometryBuffers[i].BindToStorageBlock(this->renderShader.Id(), info.Binding(), info.Name());
            }
        }

        void MutateGeometry(GEOMETRY_TYPE type, int index, std::function<Geometry(Geometry)> mutation)
        {
            Geometry geometry = this->geometryBuffers[type].Get(index);
            geometry = mutation(geometry);

            this->geometryBuffers[type].Set(&geometry, index);
        }

        void Render()
        {
            this->renderShader.Mount();
            this->renderShader.Dispatch(
                this->dispatchGroups,
                GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
            );
        }

        void Dispose()
        {
            delete [] this->geometryBuffers;
            this->renderShader.Dispose();
            this->renderTexture.Dispose();
        }

        Texture2D RenderTexture() { return this->renderTexture; }
};

BufferInfo* SceneRenderer::BUFFERS_INFO = new BufferInfo[NUM_BUFFERS] {
    BufferInfo("SphereBuffer", sizeof(Sphere), 0),
    BufferInfo("PlaneBuffer", sizeof(Plane), 1)
};

#endif