#include "srcthread.h"
#include "native.hpp"


DWORD64 g_dwThreadCollectionPtr;
GtaThread_VTable gGtaThreadOriginal;
GtaThread_VTable gGtaThreadNew;
std::vector<std::function<void(ScriptThread)>> g_Tick;

int AddScript(std::function<void(ScriptThread)> script) {
	g_Tick.push_back(script);
	return g_Tick.size();
}

void DeleteScript(int scriptID) {
	g_Tick.at(scriptID) = {};
}

eThreadState hijackedThread(GtaThread* This) {
	eThreadState state = gGtaThreadOriginal.Run(This);

	
	// INVOKE YOUR NATIVE HERE
	for (auto script : g_Tick) {
		auto player = PLAYER::PLAYER_PED_ID();
		PLAYER::SET_PLAYER_INVINCIBLE(player, true);
		script((ScriptThread)This->GetContext()->ScriptHash);
	}
	//------------------------
	return state;
}

rage::pgPtrCollection<GtaThread>* GetGtaThreadCollection() {
	using GetThreadCollection_t = rage::pgPtrCollection<GtaThread>* (*)();
	GetThreadCollection_t GetThreadCollection_ordinal = (GetThreadCollection_t)GetProcAddress(GetModuleHandleA("rage-scripting-five"), "?GetThreadCollection@scrEngine@rage@@SAPEAV?$pgPtrCollection@VGtaThread@@@2@XZ");
	return GetThreadCollection_ordinal();
}

void HookScripts() {

	rage::pgPtrCollection<GtaThread>* threadCollection = GetGtaThreadCollection();

	if (!threadCollection) {
		return;
	}

	for (UINT16 i = 0; i < threadCollection->count(); i++) {

		GtaThread* pThread = threadCollection->at(i);

		if (!pThread)
			continue;

		if (pThread->GetContext()->ScriptHash != FishThread) {
			continue;
		}

		// Hijack thread and let it tick our thread
		if (gGtaThreadOriginal.Deconstructor == NULL) {
			memcpy(&gGtaThreadOriginal, (DWORD64*)((DWORD64*)pThread)[0], sizeof(gGtaThreadOriginal));
			memcpy(&gGtaThreadNew, &gGtaThreadOriginal, sizeof(GtaThread_VTable));
			gGtaThreadNew.Run = hijackedThread;
		}

		if (((DWORD64*)pThread)[0] != (DWORD64)&gGtaThreadNew)((DWORD64*)pThread)[0] = (DWORD64)&gGtaThreadNew;

	}
}

DWORD WINAPI hookScripts(LPVOID lpParam) {
	while (true) {
		HookScripts();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return 0;
}

void AttachScripthook() {
	CreateThread(0, 0, hookScripts, 0, 0, 0);
}