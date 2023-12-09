#include "../Headers/Scene/Utility/scene_loader.h"

BufferInfo* SceneLoader::BUFFERS_INFO = new BufferInfo[SceneLoader::NUM_BUFFERS] {
    BufferInfo(sizeof(Sphere), 0),
    BufferInfo(sizeof(Plane), 1)
};

void SceneLoader::LoadScene(Scene scene)
{
    this->Dispose();
    this->geometryBuffers = new ArrayBuffer<Geometry>*[NUM_BUFFERS];
    
    for (int i = 0; i < NUM_BUFFERS; i++)
    {
        List<Geometry> geometry = scene.GetAllGeometry((GEOMETRY_TYPE) i);
        BufferInfo info = BUFFERS_INFO[i];

        this->geometryBuffers[i] = new ArrayBuffer<Geometry>(geometry.ToArray(), geometry.Count(), info.ItemSize());
        this->geometryBuffers[i]->BindToStorageBlock(info.Binding());
    }
}