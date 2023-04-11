#include <Windows.h>
#include "main.h"

SAMPFUNCS *SF = new SAMPFUNCS();

void __stdcall mainloop(){
	static bool initialized = false;
	if (!initialized) {
		if (GAME && GAME->GetSystemState() == eSystemState::GS_PLAYING_GAME && SF->getSAMP()->IsInitialized()) {
			initialized = true;
			SF->Log("OpenTabWithChat.sf: Loaded");
		}
	}
	if (GetAsyncKeyState(9) && SF->getSAMP()->getInput()->iInputEnabled) {
		SF->getSAMP()->getScoreboard()->Enable(!(SF->getSAMP()->getScoreboard()->iIsEnabled));
		while (GetAsyncKeyState(9)) { Sleep(100); }
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved){
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
		SF->initPlugin(mainloop, hModule);
	return TRUE;
}