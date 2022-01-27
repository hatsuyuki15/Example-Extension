#include "Extension.h"

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

bool ProcessSentence(std::wstring& sentence, SentenceInfo sentenceInfo)
{
	if (sentenceInfo["current select"] && sentenceInfo["process id"] != 0)
	{
		for (int retry = 0; retry < 10; retry++) {
			if (OpenClipboard(FindWindowW(NULL, L"Textractor"))) {
				HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, (sentence.size() + 2) * sizeof(wchar_t));
				memcpy(GlobalLock(hMem), sentence.c_str(), (sentence.size() + 2) * sizeof(wchar_t));
				EmptyClipboard();
				SetClipboardData(CF_UNICODETEXT, hMem);
				GlobalUnlock(hMem);
				CloseClipboard();
				break;
			}
			else {
				Sleep(15);
			}
		}
	}
	return false;
}
