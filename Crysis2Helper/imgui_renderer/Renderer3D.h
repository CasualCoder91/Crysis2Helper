#pragma once

#include "Renderer.h"
#include "Camera.h"

namespace Casual
{
    class Renderer3D : public Renderer
    {
    private:
        float width;
        float height;
        float depth;
        Camera* p_camera;

    public:
        Renderer3D(Camera* p_camera, float depth = 1.0f);

        void DrawCapsuleOutline(const Vec3& vPos0, const Vec3& vPos1, float radius, ImU32 color);
        void DrawCapsuleOutline(const Vec3& vPos0, const Vec3& vPos1, float radius, const ImVec4& color);

        void DrawArrow(const Vec3& vPos, const Vec3& vLength, float width, ImU32 color);
        void DrawArrow(const Vec3& vPos, const Vec3& vLength, float width, const ImVec4& color);


    private:
        Vec3 scale_to_screen(const Vec3& pos);
    };

}

