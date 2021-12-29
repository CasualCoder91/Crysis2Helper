#include "Renderer.h"

#include <imgui_internal.h>

namespace Casual
{

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::Initialize()
	{
		ImGuiIO& io = ImGui::GetIO();

		//io.Fonts->AddFontFromMemoryTTF(g_fFont, sizeof(g_fFont), 14.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
		//m_pFont = io.Fonts->AddFontFromMemoryTTF(g_fFont, sizeof(g_fFont), 32.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());
	}

	void Renderer::BeginScene()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
		ImGui::Begin("##Backbuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
	}



	void Renderer::EndScene()
	{
		//ImGui::GetWindowDrawList()->PushClipRectFullScreen();
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->PushClipRectFullScreen();

		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(2);
	}

	//float Renderer::RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center)
	//{
	//	ImGuiWindow* window = ImGui::GetCurrentWindow();

	//	float a = (color >> 24) & 0xff;
	//	float r = (color >> 16) & 0xff;
	//	float g = (color >> 8) & 0xff;
	//	float b = (color) & 0xff;

	//	std::stringstream stream(text);
	//	std::string line;

	//	float y = 0.0f;
	//	int i = 0;

	//	while (std::getline(stream, line))
	//	{
	//		ImVec2 textSize = m_pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

	//		if (center)
	//		{
	//			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) + 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	//			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) - 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	//			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) + 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	//			window->DrawList->AddText(m_pFont, size, { (position.x - textSize.x / 2.0f) - 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());

	//			window->DrawList->AddText(m_pFont, size, { position.x - textSize.x / 2.0f, position.y + textSize.y * i }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), line.c_str());
	//		}
	//		else
	//		{
	//			window->DrawList->AddText(m_pFont, size, { (position.x) + 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	//			window->DrawList->AddText(m_pFont, size, { (position.x) - 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	//			window->DrawList->AddText(m_pFont, size, { (position.x) + 1.0f, (position.y + textSize.y * i) - 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());
	//			window->DrawList->AddText(m_pFont, size, { (position.x) - 1.0f, (position.y + textSize.y * i) + 1.0f }, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, a / 255.0f }), line.c_str());

	//			window->DrawList->AddText(m_pFont, size, { position.x, position.y + textSize.y * i }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), line.c_str());
	//		}

	//		y = position.y + textSize.y * (i + 1);
	//		i++;
	//	}

	//	return y;
	//}

	void Renderer::Line(const ImVec2& from, const ImVec2& to, ImU32 color, float thickness)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->AddLine(from, to, color, thickness);
	}

	void Renderer::PolyLine(const ImVec2* points, uint32_t numPoints, bool closed, ImU32 color, float thickness)
	{
		assert(numPoints >= 2);
		assert(!closed || numPoints >= 3);

		ImGuiWindow* window = ImGui::GetCurrentWindow();
		for (uint32_t i = 0; i < numPoints-1; ++i)
		{
			window->DrawList->AddLine(points[i], points[i+1], color, thickness);
		}
		if (closed)
		{
			window->DrawList->AddLine(points[numPoints - 1], points[0], color, thickness);
		}
	}

	void Renderer::PolyLine(const ImVec2* points, uint32_t numPoints, bool closed, const ImVec4& color, float thickness)
	{
		Renderer::PolyLine(points, numPoints, closed, ImGui::ColorConvertFloat4ToU32(color), thickness);
	}

	void Renderer::RenderCircle(const ImVec2& position, float radius, uint32_t color, float thickness, uint32_t segments)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (color >> 24) & 0xff;
		float r = (color >> 16) & 0xff;
		float g = (color >> 8) & 0xff;
		float b = (color) & 0xff;

		window->DrawList->AddCircle(position, radius, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), segments, thickness);
	}

	void Renderer::RenderCircleFilled(const ImVec2& position, float radius, uint32_t color, uint32_t segments)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		float a = (color >> 24) & 0xff;
		float r = (color >> 16) & 0xff;
		float g = (color >> 8) & 0xff;
		float b = (color) & 0xff;

		window->DrawList->AddCircleFilled(position, radius, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), segments);
	}

	void Renderer::Rect(const ImVec2& from, const ImVec2& to, const ImU32 color, float rounding, uint32_t roundingCornersFlags, float thickness)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->AddRect(from, to, color, rounding, roundingCornersFlags, thickness);
	}

	void Renderer::Rect(const ImVec2& from, const ImVec2& to, const ImVec4& color, float rounding, uint32_t roundingCornersFlags, float thickness)
	{
		Renderer::Rect(from, to, ImGui::ColorConvertFloat4ToU32(color), rounding, roundingCornersFlags, thickness);
	}

	void Renderer::RectFilled(const ImVec2& from, const ImVec2& to, ImU32 color, float rounding, uint32_t roundingCornersFlags)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->AddRectFilled(from, to, color, rounding, roundingCornersFlags);
	}

	void Renderer::RectFilled(const ImVec2& from, const ImVec2& to, const ImVec4& color, float rounding, uint32_t roundingCornersFlags)
	{
		Renderer::RectFilled(from, to, ImGui::ColorConvertFloat4ToU32(color), rounding, roundingCornersFlags);
	}

	void Renderer::Triangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col, float thickness)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->AddTriangle(a, b, c, col,thickness);
	}

	void Renderer::Triangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec4& color, float thickness)
	{
		Renderer::Triangle(a, b, c, ImGui::ColorConvertFloat4ToU32(color), thickness);
	}

	void Renderer::TriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 color)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->AddTriangleFilled(a, b, c, color);
	}

	void Renderer::TriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec4& color)
	{
		Renderer::TriangleFilled(a, b, c, ImGui::ColorConvertFloat4ToU32(color));
	}

	//void Renderer::RenderImage(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, uint32_t color)
	//{
	//	ImGuiWindow* window = ImGui::GetCurrentWindow();

	//	float a = (color >> 24) & 0xFF;
	//	float r = (color >> 16) & 0xFF;
	//	float g = (color >> 8) & 0xFF;
	//	float b = (color) & 0xFF;

	//	window->DrawList->AddImage(pTexture, from, to, { 0.0f, 0.0f }, { 1.0f, 1.0f }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }));
	//}

	//void Renderer::RenderImageRounded(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding, uint32_t roundingCornersFlags)
	//{
	//	ImGuiWindow* window = ImGui::GetCurrentWindow();

	//	float a = (color >> 24) & 0xFF;
	//	float r = (color >> 16) & 0xFF;
	//	float g = (color >> 8) & 0xFF;
	//	float b = (color) & 0xFF;

	//	window->DrawList->AddImageRounded(pTexture, from, to, { 0.0f, 0.0f }, { 1.0f, 1.0f }, ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags);
	//}
}