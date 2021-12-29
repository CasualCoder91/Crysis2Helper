#include "Renderer3D.h"

Casual::Renderer3D::Renderer3D(Camera* p_camera, float depth)
	: depth(depth), p_camera(p_camera)
{
	ImGuiIO& io = ImGui::GetIO();
	this->width = io.DisplaySize.x;
	this->height = io.DisplaySize.y;
}

void Casual::Renderer3D::DrawCapsuleOutline(const Vec3& vPos0, const Vec3& vPos1, float radius, ImU32 color)
{
    static const unsigned int size = 20;

    Vec3 points[size];
    Vec3 axisy = vPos1 - vPos0;
    //Vec3 axisy = Vec3(0, 0, 1);
    axisy.Normalize();
    //Vec3 axisx = Vec3(0, 1, 0);
    Vec3 axisx = Vec3(axisy.y, -axisy.x, 0);
    if (axisx.x == 0 && axisx.y == 0) {
        axisx = Vec3(axisy.z, -axisy.x, 0);
    }
    axisx.Normalize();

    for (unsigned int i = 0; i < 10; i++)
    {
        float   a = ((float)i / 9.0f) * PI;
        points[i] = vPos1 + axisx * cosf(a) * radius + axisy * sinf(a) * radius;
    }

    for (unsigned int i = 0; i < 10; i++)
    {
        float   a = PI + ((float)i / 9.0f) * PI;
        points[i + 10] = vPos0 + axisx * cosf(a) * radius + axisy * sinf(a) * radius;
    }

    ImVec2 im_points[size];
    for (unsigned int i = 0; i < size; i++) {
        im_points[i] = scale_to_screen(p_camera->worldToScreen(points[i]));
    }

    Renderer::PolyLine(im_points, 20, true, color);
}

void Casual::Renderer3D::DrawCapsuleOutline(const Vec3& vPos0, const Vec3& vPos1, float radius, const ImVec4& color)
{
    Casual::Renderer3D::DrawCapsuleOutline(vPos0, vPos1, radius, ImGui::ColorConvertFloat4ToU32(color));
}

void Casual::Renderer3D::DrawArrow(const Vec3& vPos, const Vec3& vLength, float width, ImU32 color)
{
    Vec3 points[7];
    Vec3 tris[5 * 3];

    float len = vLength.GetLength();
    if (len < 0.0001f)
    {
        return;
    }

    float headLen = width * 2.0f;
    float headWidth = width * 2.0f;

    if (headLen > len * 0.8f)
    {
        headLen = len * 0.8f;
    }

    Vec3    vDir(vLength / len);
    Vec3    norm(vLength.y, -vLength.x, 0);
    norm.Normalize();

    Vec3    end(vPos + vLength);
    Vec3    start(vPos);

    unsigned int n = 0;
    points[n++] = end;
    points[n++] = end - vDir * headLen - norm * headWidth / 2;
    points[n++] = end - vDir * headLen - norm * width / 2;
    points[n++] = end - vDir * headLen + norm * width / 2;
    points[n++] = end - vDir * headLen + norm * headWidth / 2;
    points[n++] = start - norm * width / 2;
    points[n++] = start + norm * width / 2;

    ImVec2 im_points[7];
    for (unsigned int i = 0; i < 7; i++) {
        im_points[i] = scale_to_screen(p_camera->worldToScreen(points[i]));
    }

    Casual::Renderer::TriangleFilled(im_points[0], im_points[1], im_points[2], color);
    Casual::Renderer::TriangleFilled(im_points[0], im_points[2], im_points[3], color);
    Casual::Renderer::TriangleFilled(im_points[0], im_points[3], im_points[4], color);
    Casual::Renderer::TriangleFilled(im_points[2], im_points[5], im_points[6], color);
    Casual::Renderer::TriangleFilled(im_points[2], im_points[6], im_points[3], color);

    //n = 0;
    //tris[n++] = points[0];
    //tris[n++] = points[1];
    //tris[n++] = points[2];

    //tris[n++] = points[0];
    //tris[n++] = points[2];
    //tris[n++] = points[3];

    //tris[n++] = points[0];
    //tris[n++] = points[3];
    //tris[n++] = points[4];

    //tris[n++] = points[2];
    //tris[n++] = points[5];
    //tris[n++] = points[6];

    //tris[n++] = points[2];
    //tris[n++] = points[6];
    //tris[n++] = points[3];

    //DrawTriangles(tris, n, color);
}

void Casual::Renderer3D::DrawArrow(const Vec3& vPos, const Vec3& vLength, float width, const ImVec4& color)
{
    Casual::Renderer3D::DrawArrow(vPos, vLength, width, ImGui::ColorConvertFloat4ToU32(color));
}



Vec3 Casual::Renderer3D::scale_to_screen(const Vec3& pos)
{
    return Vec3(pos.x * width, pos.y * height, pos.z);
}


