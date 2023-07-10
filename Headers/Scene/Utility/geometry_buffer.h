#ifndef _GEOMETRY_BUFFER
#define _GEOMETRY_BUFFER

#include "../../Buffers/array_bufffer.h"
#include "../../Geometry/geometry.h"
#include "../../Utility/enumerable.h"
#include "../scene.h"

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

class GeometryBuffer : public Disposable
{
    private:
        static const int NUM_BUFFERS = PLANE_TYPE + 1;
        static BufferInfo* BUFFERS_INFO;

        ArrayBuffer<Geometry>* geometryBuffers;

    public:
        GeometryBuffer() 
        {
            this->geometryBuffers = NULL;
        }

        void SetScene(Scene scene, GLuint progID);

        void Dispose() { this->geometryBuffers->Dispose(); }

        const ArrayBuffer<Geometry> GetGeometry(GEOMETRY_TYPE type) const { return this->geometryBuffers[type]; }
};

#endif