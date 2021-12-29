#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <stdio.h>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "REClass.h"
#include "CasualLibrary.hpp"
#pragma comment(lib, "CasualLibrary.lib")


#include <dxgi.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include "imgui_renderer/Renderer3D.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
bool show_menu = false;
bool draw_name = false;
bool draw_esp = false;

float sky_color[3] = { 0,0,0};
float sun_color[3] = { 0,0,0};
ImVec4 esp_color(1, 1, 1, 1);

float sky_brightness = 1;

//CAISystem* pCAISystem = nullptr;
IRenderer* pIRenderer = nullptr;
IEntitySystem* pIEntitySystem = nullptr;
IConsole* pIConsole = nullptr;

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	if (show_menu) {

		ImGui::Begin("Test Env", &show_menu);
		ImGui::Text("Options:");
		ImGui::ColorEdit3("Sky Color", sky_color);
		ImGui::ColorEdit3("Sun Color", sun_color);
		ImGui::ColorEdit4("ESP Color", (float*)&esp_color);
		ImGui::SliderFloat("SkyBrightness", &sky_brightness, 0, 1000);
		ImGui::Checkbox("Name", &draw_name);
		ImGui::Checkbox("ESP", &draw_esp);
		ImGui::End();
	}

	if (draw_name || draw_esp) {

		Casual::Renderer::BeginScene();

		//CAIDebugRenderer* pCAIDebugRenderer = pCAISystem->GetAIDebugRenderer();
		IEntityIt* pEntityIter = pIEntitySystem->GetEntityIterator();

		IEntity* pEntity = 0;
		if (pEntityIter)
		{
			pEntity = pEntityIter->This();
		}

		while (pEntity)
		{
			pEntityIter->Next();
			pEntity = pEntityIter->This();
			if (pEntity) {
				//pIConsole->PrintLine(pEntity->GetName());
				if (pEntity->IsActive() && pEntity->HasAI() && !pEntity->CheckFlags(EEntityFlags::ENTITY_FLAG_LOCAL_PLAYER)) {
					if (draw_name) {
						//pCAIDebugRenderer->Draw3dLabel(pEntity->GetPos(), 2, pEntity->GetName(), va_list());
					}
					if (draw_esp) {
						AABB aabb;
						pEntity->GetWorldBounds(aabb);
						float height = aabb.GetSize().z;
						Vec3 center3d = aabb.GetCenter();
						Vec3 bottom_center3d = center3d - Vec3(0, 0, height * 0.5);
						Vec3 top_center3d = center3d + Vec3(0, 0, height * 0.5);

						Vec3 rect_min2d, rect_max2d, top_center2d;
						pIRenderer->ProjectToScreen(aabb.min.x, aabb.min.y, aabb.min.z, &rect_min2d.x, &rect_min2d.y, &rect_min2d.z);
						pIRenderer->ProjectToScreen(aabb.max.x, aabb.max.y, aabb.max.z, &rect_max2d.x, &rect_max2d.y, &rect_max2d.z);
						pIRenderer->ProjectToScreen(top_center3d.x, top_center3d.y, top_center3d.z, &top_center2d.x, &top_center2d.y, &top_center2d.z);

						Camera cam = Camera(pIRenderer);
						Casual::Renderer3D test = Casual::Renderer3D(&cam);

						//test.DrawCapsuleOutline(bottom_center3d, top_center3d, height, esp_color);
						Vec3 offset = Vec3(0, 0.1, 1) * height;

						test.DrawArrow(top_center3d + offset, offset*-1, height/2, esp_color);

						int width = pIRenderer->GetWidth();
						int screen_height = pIRenderer->GetHeight();

						if ((rect_min2d.z >= 0.0f) && (rect_min2d.z <= 1.0f)) {

							ImVec2 im_min = ImVec2(rect_min2d.x * width * 0.01, rect_min2d.y * screen_height * 0.01);
							ImVec2 im_max = ImVec2(rect_max2d.x * width * 0.01, rect_max2d.y * screen_height * 0.01);
							ImVec2 im_top_center = ImVec2(top_center2d.x * width * 0.01, top_center2d.y * screen_height * 0.01);
							ImVec2 im_bottom_right = ImVec2(im_max.x,im_min.y);

							ImVec2 triangle[3] = { im_min, im_top_center, im_bottom_right };

							//Casual::Renderer::PolyLine(triangle, 3, false, esp_color, 2);

							//Casual::Renderer::TriangleFilled(im_min, im_top_center, im_bottom_right, esp_color);
							//Casual::Renderer::RectFilled(im_min, im_max, esp_color);
						}
					}
				}
			}
		}
		Casual::Renderer::EndScene();
	}


	ImGui::EndFrame();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


	return oPresent(pSwapChain, SyncInterval, Flags);
}

HINSTANCE DllHandle;



DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(DllHandle, 0);
	return 0;
}

int WINAPI main()
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);

	uintptr_t module_ptr = Memory::Internal::getModule("Crysis2.exe");

	IGameFramework* pIGameFramework = *(IGameFramework**)(module_ptr + 0x13A0050);

	ISystem* pISystem = pIGameFramework->GetISystem();//*(ISystem**)(module_ptr + 0x1339704);

	I3DEngine* pI3DEngine = pISystem->GetI3DEngine();
	IInput* pIInput = pISystem->GetIInput();
	IHardwareMouse* pIHardwareMouse = pISystem->GetIHardwareMouse();

	pIConsole = pISystem->GetIConsole();
	//pCAISystem = pISystem->GetCAISystem();
	pIEntitySystem = pISystem->GetIEntitySystem();
	pIRenderer = pISystem->GetIRenderer();

	pIConsole->Clear();
	pIConsole->PrintLine("You just got H4CKED bro\n\n");
	pIConsole->PrintLine(" [N0] to toggle menu");
	pIConsole->PrintLine(" [N1] to exit");

	//ll_entity_entry* p_ll_entity_entry = pISystem->pEntitySystem->p_linked_list_1;

	//something_camera* p_renderer = p_system_global_environment->p_something_camera;

	//Camera* camera = p_renderer->get_camera();

	//std::cout << "cam pointer: " << std::hex << camera << std::endl;

	//std::cout << p_system_global_environment << std::endl;
	//std::cout << p_ll_entity_entry << std::endl;

	while (true) {
		Sleep(50);
		pI3DEngine->SetSkyColor(sky_color[0], sky_color[1], sky_color[2]);
		pI3DEngine->SetSunColor(sun_color[0], sun_color[1], sun_color[2]);
		pI3DEngine->SetSkyBrightness(sky_brightness);
		if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
			show_menu = !show_menu;

			if (show_menu) {
				pIGameFramework->PauseGame(true, false, 0);
				pIHardwareMouse->IncrementCounter();
			}
			else 
			{
				pIGameFramework->PauseGame(false, false, 0);
				pIHardwareMouse->DecrementCounter();
			}

			//pIInput->EnableDevice(!show_menu);
		}

		//	//ll_entity_entry* p_ll_entity_entry = p_system_global_environment->pEntitySystem->p_linked_list_1;
		//	//while (p_ll_entity_entry) {
		//	//	if (p_ll_entity_entry->pEntity != 0) {
		//	//		std::cout << "p_linked_list: " << std::hex << p_ll_entity_entry << std::endl;
		//	//		std::cout << "Entity Index: " << std::dec << p_ll_entity_entry->entity_index << std::endl;
		//	//		std::cout << "p_entity: " << std::hex << p_ll_entity_entry->pEntity << std::endl;
		//	//		std::cout << "Entity ID: " << std::dec << p_ll_entity_entry->pEntity->entity_id << std::endl;
		//	//		std::cout << "Entity Position: " << std::dec << p_ll_entity_entry->pEntity->position << std::endl << std::endl;

		//	//		p_ll_entity_entry = p_ll_entity_entry->down;
		//	//	}
		//	//}

		//	Sleep(1000);
		//}
		//pI3DEngine->SetSkyColor(100, 0, 0);
		//pI3DEngine->SetSunColor(0, 0, 100);

		if (GetAsyncKeyState(VK_NUMPAD1)) {
			pIConsole->PrintLine("ight imma head out");
			break;
		}
	}

	//std::cout << "ight imma head out" << std::endl;
	Sleep(1000);
	//fclose(fp);
	//FreeConsole();
	CreateThread(0, 0, EjectThread, 0, 0, 0);

	return 0;
}



BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DllHandle = hModule;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{

	}

	return TRUE;
}