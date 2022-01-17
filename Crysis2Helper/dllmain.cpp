#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>
#include <stdio.h>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "REClass.h"
#include "CasualLibrary.hpp"
#pragma comment(lib, "CasualLibrary.lib")


#include "MinHook/MinHook.h"
#if _WIN64 
#pragma comment(lib, "MinHook/libMinHook.x64.lib")
#else
#pragma comment(lib, "MinHook/libMinHook.x86.lib")
#endif

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

#include "eigen-3.4.0/Eigen/Dense" // for dealing with quaternions

#include "Geometry.h" // contains structs for math. Such as Vec3, Matrix34 etc.

typedef void (__stdcall* CmdFreeCamEnable)();
typedef void(__stdcall* CmdFreeCamUnlockCamera)();
CmdFreeCamUnlockCamera freeCamUnlockCamera = (CmdFreeCamUnlockCamera)0x00F3BC98;
CmdFreeCamEnable freeCamEnable = (CmdFreeCamEnable)0x00F3C7F7;

typedef long(__stdcall* present)(IDXGISwapChain*, UINT, UINT);
present p_present;
present p_present_target;
bool get_present_pointer()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetForegroundWindow();
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGISwapChain* swap_chain;
	ID3D11Device* device;

	const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		feature_levels,
		2,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		nullptr,
		nullptr) == S_OK)
	{
		void** p_vtable = *reinterpret_cast<void***>(swap_chain);
		swap_chain->Release();
		device->Release();
		//context->Release();
		p_present_target = (present)p_vtable[8];
		return true;
	}
	return false;
}

WNDPROC oWndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}


bool b_fly = false; // flag defining if fly hack is active
float speed(0.1f); // the speed at which we fly
void OverTheRainbow(); // forward declaration of THE function

bool show_menu = false;
bool init = false;
HWND window = NULL;
ID3D11Device* p_device = NULL;
ID3D11DeviceContext* p_context = NULL;
ID3D11RenderTargetView* mainRenderTargetView = NULL;
HRESULT __stdcall detour_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags)
{
	if (!init)
	{
		if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&p_device)))
		{
			p_device->GetImmediateContext(&p_context);
			DXGI_SWAP_CHAIN_DESC sd;
			p_swap_chain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			p_device->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(p_device, p_context);
			init = true;
		}
		else
			return p_present(p_swap_chain, sync_interval, flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (show_menu) {

		ImGui::Begin("Test Env", &show_menu);
		ImGui::Text("Options:");
		ImGui::Checkbox("Fly", &b_fly);
		ImGui::SliderFloat("Speed", &speed, 0.01, 1);
		ImGui::End();
	}

	if (b_fly) {
		OverTheRainbow();
	}

	ImGui::EndFrame();
	ImGui::Render();

	p_context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return p_present(p_swap_chain, sync_interval, flags);
}

HINSTANCE dll_handle;
DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(dll_handle, 0);
	Sleep(100);
	return 0;
}

VOID SetCurrentThreadId(DWORD dwThreadId)
{
	_asm
	{
		mov eax, fs: [0x18] ;
		mov ecx, dwThreadId;
		mov[eax + 0x24], ecx;
	}
}


IEntity* me = nullptr;
int WINAPI main()
{

	#pragma region init_dx11
	if (!get_present_pointer())
	{
		return 1;
	}

	MH_STATUS status = MH_Initialize();
	if (status != MH_OK)
	{
		return 1;
	}

	if (MH_CreateHook(reinterpret_cast<void**>(p_present_target), &detour_present, reinterpret_cast<void**>(&p_present)) != MH_OK) {
		return 1;
	}

	if (MH_EnableHook(p_present_target) != MH_OK) {
		return 1;
	}
	#pragma endregion

	// all this just to get the entity and from there the writable position. All game specific stuff.
	uintptr_t module_ptr = Memory::Internal::getModule("Crysis2.exe");

	IGameFramework* pIGameFramework = *(IGameFramework**)(module_ptr + 0x13A0050);
	ISystem* pISystem = pIGameFramework->GetISystem();

	IInput* pIInput = pISystem->GetIInput();
	IHardwareMouse* pIHardwareMouse = pISystem->GetIHardwareMouse();

	IEntitySystem* pIEntitySystem = pISystem->GetIEntitySystem();
	me = pIEntitySystem->GetEntity(30583);


	while (true) {
		Sleep(50);
		if (GetAsyncKeyState(VK_ESCAPE) & 1) {
			show_menu = !show_menu;

			if (show_menu) {
				//if we show the menu we pause the game and show the mouse. Again: game specific
				pIGameFramework->PauseGame(true, false, 0);
				pIHardwareMouse->IncrementCounter();
			}
			else 
			{
				//if we hide the menu we unpause the game and hide the cursor.
				pIGameFramework->PauseGame(false, false, 0);
				pIHardwareMouse->DecrementCounter();
			}
			Sleep(500);
		}

		//break the loop -> time for cleanup and unloading
		if (GetAsyncKeyState(VK_NUMPAD1)) {
			break;
		}
	}

	#pragma region cleanup

	if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK) {
		return 1;
	}
	if (MH_Uninitialize() != MH_OK) {
		return 1;
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = NULL; }
	if (p_context) { p_context->Release(); p_context = NULL; }
	if (p_device) { p_device->Release(); p_device = NULL; }
	SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc));

	CreateThread(0, 0, EjectThread, 0, 0, 0);
	#pragma endregion

	return 0;
}

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		dll_handle = hModule;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{

	}

	return TRUE;
}

// implementation of the fly hack as shown in the video 
void OverTheRainbow() {

	PhysicalEntity* pMyPhysicalEntity = me->m_pGridLocationIt->This->pPhysicalClass; // get the class instance containing the writable position
	CameraEx* pCameraEx = (CameraEx*)0x017A8E30; // get the camera to find those vectors
	Vec3 viewDir = pCameraEx->m_Matrix.GetColumn1(); // the view direction vector. Already normalized.
	Vec3 up = pCameraEx->m_Matrix.GetColumn2(); // the up vector, also normalized
	Vec3 right = viewDir.cross(up); // the right vector created by taking the cross product. Since both other vectors are normalized so is this one.

	//get user input
	SHORT numpad4 = GetAsyncKeyState(VK_NUMPAD4); // 4, left
	SHORT numpad5 = GetAsyncKeyState(VK_NUMPAD5); // 5, backward
	SHORT numpad6 = GetAsyncKeyState(VK_NUMPAD6); // 6, right
	SHORT numpad7 = GetAsyncKeyState(VK_NUMPAD7); // 7, down
	SHORT numpad8 = GetAsyncKeyState(VK_NUMPAD8); // 8, forward
	SHORT numpad9 = GetAsyncKeyState(VK_NUMPAD9); // 9, up

	Vec3 oldPos = pMyPhysicalEntity->pos; // current player position, will be changed
	Vec3 velocity = Vec3(0, 0, 0); // set velocity to 0 here. You may also not do that but then it is hard to manover ;)

	if (numpad8 != 0) // Forward
		velocity = velocity + viewDir;

	if (numpad5 != 0) // Backward
		velocity = velocity - viewDir;

	if (numpad9 != 0) // Up
		velocity = velocity + up;

	if (numpad7 != 0) // Down
		velocity = velocity - up;

	if (numpad6 != 0) // Right
		velocity = velocity + right;

	if (numpad4 != 0) // Left
		velocity = velocity - right;

	velocity.Normalize();

	// I left those comments below in here. Maybe it helps you understand how to use the Eigen library to get the euler angles from a quaternion

	//Eigen::Quaternionf q = Eigen::Quaternionf(pMyPhysicalEntity->angle.w, 
	//	pMyPhysicalEntity->angle.x, pMyPhysicalEntity->angle.y, pMyPhysicalEntity->angle.z);
	//Eigen::Vector3f euler = q.toRotationMatrix().eulerAngles(0, 1, 2);

	// Set new position.
	pMyPhysicalEntity->pos = oldPos + velocity * speed;

}