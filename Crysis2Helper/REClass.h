#pragma once

#include <stdint.h>
#include <ostream>
#include "Geometry.h"

//all the reversed classes, not realy relevant for this tutorial but check em out if u like.

class IEntity
{
public:
	bool active; //0x0004
	bool N00002372; //0x0005
	bool N00002BA4; //0x0006
	bool N00002376; //0x0007
	uint16_t N00002684; //0x0008
	uint16_t N00002691; //0x000A
	uint32_t entity_id; //0x000C
	uint32_t N00001DC7; //0x0010
	uint32_t N00001DCX; //0x0014
	uint32_t flags; //0x0018
	char pad_001C[8]; //0x001C
	Vec3 position; //0x0024
	Vec4 rotation; //0x0030
	Vec3 scale; //0x0040
	Matrix34 m_worldTM; //0x004C
	char pad_007C[24]; //0x007C
	class GridLocationIt* m_pGridLocationIt; //0x0094
	char pad_0098[24]; //0x0098
	char* Name; //0x00B0

	virtual void Function0();
	virtual uint32_t GetId();
	virtual void Function2();
	virtual void GetClass();
	virtual void GetArchetype();
	virtual void SetFlags(uint32_t flags);
	virtual uint32_t GetFlags();
	virtual void AddFlags(uint32_t flagsToAdd);
	virtual void ClearFlags(uint32_t flagsToClear);
	virtual bool CheckFlags(uint32_t flagsToCheck);
	virtual bool IsGarbage();
	virtual void SetName(const char* sName);
	virtual const char* GetName();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void GetWorldBounds(AABB& bbox);
	virtual void Function26();
	virtual void SetPos(const Vec3& vPos, int nWhyFlags = 0);
	virtual Vec3& GetPos();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void GetWorldAngles(Vec3& angles);
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual bool IsActive();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual bool IsHidden();
	virtual void Invisible(bool bInvisible);
	virtual bool IsInvisible();
	virtual void Function51();
	virtual bool HasAI();
}; //Size: 0x0144

class IEntityIt
{
public:
	virtual void AddRef(); //
	virtual void Release(); //
	virtual bool IsEnd(); //
	virtual IEntity* Next(); //
	virtual IEntity* This(); //
	virtual void MoveFirst(); //
};

class I3DEngine
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void ShutDown();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void get_camera();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void LoadStatObj();
	virtual void FindStatObjectByFilename();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void GetLoadedObjectCount();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void RegisterEntity();
	virtual void Function28();
	virtual void UnRegisterEntity();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void CreateDecal();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void SetSkyColor(float x, float y, float z);
	virtual void SetSunColor(float x, float y, float z);
	virtual void SetSkyBrightness(float fMul);
	virtual void Function52();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual void Function56();
	virtual void Function57();
	virtual void Function58();
	virtual void Function59();
	virtual void Function60();
	virtual void Function61();
}; //Size: 0x0018

class IInput
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void EnableEventPosting(bool bEnable);
	virtual bool IsEventPostingEnabled();
	virtual void PostInputEvent(); //const SInputEvent& event, bool bForce = false
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void EnableDevice(bool enable);
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void ClearKeyState();
	virtual void RetriggerKeyState();
	virtual void Function27();
	virtual bool HasInputDeviceOfType(uintptr_t type); //EInputDeviceType
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
}; //Size: 0x0084

class IHardwareMouse
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void AddListener();
	virtual void RemoveListener();
	virtual void Function7();
	virtual void IncrementCounter();
	virtual void DecrementCounter();
	virtual void GetHardwareMousePosition();
	virtual void SetHardwareMousePosition();
	virtual void GetHardwareMouseClientPosition();
	virtual void SetHardwareMouseClientPosition();
	virtual void Reset(bool bVisibleByDefault);
	virtual void ConfineCursor(bool confine);
	virtual void Hide(bool hide);
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
}; //Size: 0x0040

class IGameFramework
{
public:
	bool m_paused; //0x0004
	bool m_forcedpause; //0x0005
	bool N00001F62; //0x0006
	bool N00001F60; //0x0007
	class ISystem* pISystem; //0x0008
	char pad_000C[1332]; //0x000C

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void PauseGame(bool pause, bool force, unsigned int nFadeOutInMS);
	virtual void IsGameStarted();
	virtual void Function17();
	virtual void Function18();
	virtual void SetLevelPrecachingDone();
	virtual ISystem* GetISystem();

}; //Size: 0x0540

class ITimer
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void EnableTimer(bool bEnable);
	virtual void IsTimerEnabled();
}; //Size: 0x0204

class IEntitySystem
{
public:
	char pad_0004[76]; //0x0004
	class Entity* (*pArraypEnt); //0x0050
	char pad_0054[36]; //0x0054
	class ll_entity_entry* p_linked_list_1; //0x0078
	char pad_007C[8]; //0x007C
	int32_t n_entities; //0x0084
	char pad_0088[12]; //0x0088
	void* N0000233C; //0x0094
	void* N0000287D; //0x0098
	void* N00001F0E; //0x009C
	uint32_t n_entities_2; //0x00A0
	char pad_00A4[20]; //0x00A4
	uint32_t n_entities_3; //0x00B8
	char pad_00BC[4]; //0x00BC

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Update();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual IEntity* GetEntity(uint32_t id);
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual uint32_t GetNumEntities();
	virtual IEntityIt* GetEntityIterator();
}; //Size: 0x00C0

class IConsole
{
public:
	char pad_0008[364]; //0x0008
	bool is_open; //0x0174
	bool N000015F8; //0x0175
	char pad_0176[50]; //0x0176
	class N0000163C* N00001605; //0x01A8
	char pad_01AC[16]; //0x01AC

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void ShowConsole();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void GetCvar();
	virtual void Function22();
	virtual void Function23();
	virtual void PrintLine(const char* line);
	virtual void PrintLinePlus(const char* line); // Append a string in the last console line.
	virtual void GetStatus();
	virtual void Clear();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void IsOpened();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
	virtual void Function50();
	virtual void Function51();
	virtual void Function52();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual void Function56();
	virtual void Function57();
	virtual void Function58();
	virtual void Function59();
}; //Size: 0x01BC

class IScriptSystem
{
public:
	virtual void Function0();
}; //Size: 0x0044

class IRenderer
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
	virtual void Function50();
	virtual void Function51();
	virtual void Function52();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual void Function56();
	virtual void Function57();
	virtual void Function58();
	virtual void Function59();
	virtual void Function60();
	virtual int GetHeight();
	virtual int GetWidth();
	virtual void Function63();
	virtual void Function64();
	virtual void Function65();
	virtual void Function66();
	virtual void Function67();
	virtual void Function68();
	virtual void Function69();
	virtual void Function70();
	virtual void Function71();
	virtual void Function72();
	virtual void Function73();
	virtual void Function74();
	virtual void Function75();
	virtual void Function76();
	virtual void Function77();
	virtual void ProjectToScreen(float fInX, float fInY, float fInZ, float* fOutX, float* fOutY, float* fOutZ);
	virtual void Function79();
	virtual void Function80();
	virtual void GetModelViewMatrix(float* mat);
	virtual void GetProjectionMatrix(float* mat);

}; //Size: 0x00FC

class CAIDebugRenderer
{
public:
	class IRenderer* pIRenderer; //0x0004

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual float GetDebugDrawZ(const Vec3& vPoint, bool bUseTerrainOrWater);
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void DrawArrow(const Vec3& vPos, const Vec3& vLength, float fWidth, const ColorB& color);
	virtual void DrawCapsuleOutline(const Vec3& vPos0, const Vec3& vPos1, float fRadius, const ColorB& color);
	virtual void DrawCircleOutline(const Vec3& vPos, float fRadius, const ColorB& color);
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Draw2dLabel();
	virtual void Function16();
	virtual void __cdecl Draw3dLabel(Vec3 vPos, float fFontSize, const char* text, va_list args);
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void DrawPolyline();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void ProjectToScreen(float fInX, float fInY, float fInZ, float* fOutX, float* fOutY, float* fOutZ);
}; //Size: 0x0040

class CAISystem
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual CAIDebugRenderer* GetAIDebugRenderer();
	virtual void GetNetworkDebugRenderer();
	virtual void SetAIDebugRenderer();
	virtual void SetAINetworkDebugRenderer();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
	virtual void Function50();
	virtual void Function51();
	virtual void Function52();
	virtual void Function53();
	virtual void Function54();
	virtual void Function55();
	virtual void Function56();
	virtual void Function57();
	virtual void Function58();
	virtual void Function59();
	virtual void Function60();
	virtual void Function61();
	virtual void Function62();
	virtual void Function63();
	virtual void Function64();
	virtual void Function65();
	virtual void Function66();
	virtual void Function67();
	virtual void Function68();
	virtual void Function69();
	virtual void Function70();
	virtual void Function71();
	virtual void EnumerateFormationNames();
	virtual void GetGroupCount();

}; //Size: 0x0044

class ISystem
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Update(int updateFlags, int nPauseMode);
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual IHardwareMouse* GetIHardwareMouse();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual void Function41();
	virtual void Function42();
	virtual void Function43();
	virtual void Function44();
	virtual void Function45();
	virtual void Function46();
	virtual void Function47();
	virtual void Function48();
	virtual void Function49();
	virtual void Function50();
	virtual IEntitySystem* GetIEntitySystem();
	virtual void Function52();
	virtual CAISystem* GetCAISystem();
	virtual void Function54();
	virtual void Function55();
	virtual void Function56();
	virtual void Function57();
	virtual I3DEngine* GetI3DEngine();
	virtual IScriptSystem* GetIScriptSystem();
	virtual IConsole* GetIConsole();
	virtual void Function61();
	virtual void Function62();
	virtual void Function63();
	virtual void Function64();
	virtual void Function65();
	virtual void Function66();
	virtual void Function67();
	virtual void Function68();
	virtual IRenderer* GetIRenderer();
	virtual IInput* GetIInput();
	virtual ITimer* GetITimer();
	virtual void Function72();
	virtual void Function73();

	char pad_0004[4]; //0x0004
	class N00001E88* N00001E5A; //0x0008
	class I3DEngine* pI3DEngine; //0x000C
	char pad_0010[4]; //0x0010
	class IScriptSystem* pIScriptSystem; //0x0014
	char pad_0018[8]; //0x0018
	class IInput* pIInput; //0x0020
	char pad_0024[28]; //0x0024
	class N00001EBE* N00001E69; //0x0040
	class ITimer* pITimer; //0x0044
	char pad_0048[8]; //0x0048
	void* N00001E6C; //0x0050
	class IEntitySystem* pIEntitySystem; //0x0054
	class IConsole* pIConsole; //0x0058
	char pad_005C[12]; //0x005C
	class CAISystem* pCAISystem; //0x0068
	char pad_006C[20]; //0x006C
	class IRenderer* pIRenderer; //0x0080
	class IHardwareMouse* pIHardwareMouse; //0x0084
	char pad_0088[4]; //0x0088
	int32_t mainThread; //0x008C
	char pad_0090[2700]; //0x0090
	class N00001E00* N00001D9F; //0x0B1C
	char pad_0B20[240]; //0x0B20

}; //Size: 0x0090

class GridLocationIt
{
public:
	char pad_0000[4]; //0x0000
	class GridLocation* This; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044

class GridLocation
{
public:
	char pad_0000[8]; //0x0000
	class IEntity* pIEntity; //0x0008
	class PhysicalEntity* pPhysicalClass; //0x000C
	char pad_0010[3380]; //0x0010
}; //Size: 0x0D44

class PhysicalEntity
{
public:
	char pad_0000[112]; //0x0000
	Vec3 pos; //0x0070
	Vec4 angle; //0x007C
}; //Size: 0x0114

class CameraEx
{
public:

	virtual void Function0();

	char pad_0004[108]; //0x0004
	Matrix34 m_Matrix; //0x0070
	float m_fov; //0x00A0
	int32_t m_Width; //0x00A4
	int32_t m_Height; //0x00A8
};