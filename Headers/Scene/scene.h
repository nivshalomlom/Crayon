#ifndef _SCENE_H
#define _SCENE_H

#include "../Geometry/primitives.h"
#include "../Utility/list.h"
#include "../common.h"

enum GEOMETRY_TYPE
{
    SPHERE_TYPE = 0,
    PLANE_TYPE
};

class Scene
{
    private:
        List<Geometry>* geometries;

    public:
        Scene()
        {
            this->geometries = new List<Geometry>[PLANE_TYPE];
            for (int i = 0; i < PLANE_TYPE; i++)
                this->geometries[i] = List<Geometry>();
        }

        void Add(Geometry geometry, GEOMETRY_TYPE type) { this->geometries[type].Add(geometry); }

        List<Geometry> GetAllGeometry(GEOMETRY_TYPE type) { return this->geometries[type]; }
};

#endif