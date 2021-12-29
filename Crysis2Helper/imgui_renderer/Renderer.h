#pragma once

#include <string>
#include <sstream>
#include <imgui.h>

#include "Geometry.h"

namespace Casual
{
	static class Renderer
	{

	protected:
		Renderer();
		~Renderer();

	public:
		void Initialize();

		static void BeginScene();
		static void EndScene();

		//static float RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center = false);
		static void Line(const ImVec2& from, const ImVec2& to, ImU32 color, float thickness = 1.0f);

		static void PolyLine(const ImVec2* points, uint32_t numPoints, bool closed, ImU32 color, float thickness = 1.0f);
		static void PolyLine(const ImVec2* points, uint32_t numPoints, bool closed, const ImVec4& color, float thickness = 1.0f);

		void RenderCircle(const ImVec2& position, float radius, ImU32 color, float thickness = 1.0f, uint32_t segments = 16);
		void RenderCircleFilled(const ImVec2& position, float radius, ImU32 color, uint32_t segments = 16);

		static void Rect(const ImVec2& from, const ImVec2& to, ImU32 color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All, float thickness = 1.0f);
		static void Rect(const ImVec2& from, const ImVec2& to, const ImVec4& color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All, float thickness = 1.0f);

		static void RectFilled(const ImVec2& from, const ImVec2& to, ImU32 color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);
		static void RectFilled(const ImVec2& from, const ImVec2& to, const ImVec4& color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);

		static void Triangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 color, float thickness = 1.0f);
		static void Triangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec4& color, float thickness);

		static void TriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 color);
		static void TriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec4& color);

		static void WireSphere(const Vec3& vPos, float radius, ImU32 color);

		//void RenderImage(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, uint32_t color);
		//void RenderImageRounded(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);

	};
}

#define g_sRenderer Casual::Renderer::GetInstance()