#include "Main.h"

char HackDir[MAX_PATH];
HardwareBreakpoint* HWBP = NULL;

LONG WINAPI pFirstExceptionHandler(PEXCEPTION_POINTERS Exception)
{
	return EXCEPTION_CONTINUE_SEARCH;
}

void Hook()
{
	HWBP = new HardwareBreakpoint();
	HWBP->AddBreakpoint(0xC913A80);
	HWBP->SetBreakpoints();
}

void Unhook()
{
	HWBP->RemoveBreakpoints();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwCallReason, LPVOID lpReserved)
{
	static HANDLE hExceptionHandler = NULL;

	if (dwCallReason == DLL_PROCESS_ATTACH)
	{
		// Get file path
		GetModuleFileName(hModule, HackDir, MAX_PATH);
		*(strrchr(HackDir, '\\') + 1) =0;

		// Add exception handler
		hExceptionHandler = AddVectoredExceptionHandler(TRUE, pFirstExceptionHandler);
		if (hExceptionHandler == NULL)
		{
			MessageBox(0, GString<0x75, 86>(/* Could not set up exception handler.\nIt is needed for hack to work.\n\nDetaching hack. */ "\x8C\xC6\x2\x71\xBF\x59\x75\xCA\x7\xB1\xB8\x18\x5F\x9\xA\x65\xB\x1C\x6F\xCE\x1E\x69\xBB\x2C\x80\xD7\x67\x85\xD2\x2F\x7B\xD9\x26\x73\x1D\x90\xED\x0\x1B\xC5\xE2\x22\xC7\xE3\x2E\x84\xDB\x30\x87\x21\x35\x92\xD5\x79\x97\xE4\x3C\x9A\x27\x29\x98\x29\x2C\x9A\xDD\x4A\xDD\x50\xAD\xFC\x59\x61\x96\xDD\x46\x9E\xFB\x50\xA5\xF2\x8B\xA9\xF6\x4E\xAC\x3F").String,
				GString<0x75, 5>(/* Error */ "\x35\x11\x16\x2E\x20").String, MB_OK | MB_ICONERROR);

			return FALSE;
		}

		// Hook
		Hook();
		
	}

	if (dwCallReason == DLL_PROCESS_DETACH)
	{
		// Unhook
		Unhook();

		// Remove exception handler
		if (hExceptionHandler != NULL) RemoveVectoredExceptionHandler(hExceptionHandler);
	}

	return TRUE;
}