#include "../Headers/Scene/scene_renderer.h"

BufferInfo* SceneRenderer::BUFFERS_INFO = new BufferInfo[SceneRenderer::NUM_BUFFERS] {
    BufferInfo("SphereBuffer", sizeof(Sphere), 0),
    BufferInfo("PlaneBuffer", sizeof(Plane), 1)
};

SceneRenderer::SceneRenderer(Scene scene, Camera camera, int textureWidth, int textureHeight, GLint imageIndex)
{
    this->renderShader = ComputeProgram("./Shaders/Compute/rayTrace.comp");
    this->renderTexture = Texture2D(textureWidth, textureHeight);
    
    this->renderTexture.BindToImage(imageIndex);
    this->dispatchGroups = glm::ivec3(
        ceilf(textureWidth / 32.0f), 
        ceilf(textureHeight / 32.0f),
        1
    );

    this->geometryBuffers = NULL;
    this->SetScene(scene);

    this->cameraBuffer = ObjectBuffer<Camera>(camera, sizeof(Camera));
    this->cameraBuffer.BindToStorageBlock(this->renderShader.Id(), 2, "CameraBuffer");
}

void SceneRenderer::SetScene(Scene scene)
{
    if (this->geometryBuffers != NULL)
    {
        for (int i = 0; i < NUM_BUFFERS; i++)
            this->geometryBuffers[i].Dispose();

        delete [] this->geometryBuffers;
    }

    this->geometryBuffers = new ArrayBuffer<Geometry>[NUM_BUFFERS];
    for (int i = 0; i < NUM_BUFFERS; i++)
    {
        List<Geometry> geometry = scene.GetAllGeometry((GEOMETRY_TYPE) i);
        BufferInfo info = BUFFERS_INFO[i];

        this->geometryBuffers[i] = ArrayBuffer<Geometry>(geometry.ToArray(), geometry.Count(), info.ItemSize());
        this->geometryBuffers[i].BindToStorageBlock(this->renderShader.Id(), info.Binding(), info.Name());
    }
}