#pragma once

#include "Geometry.h"

namespace Casual
{
    class Camera {
    public:
        virtual Vec3 worldToScreen(const Vec3& wold_pos) = 0;

    };
}