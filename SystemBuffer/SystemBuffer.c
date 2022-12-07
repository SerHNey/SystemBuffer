#define _CRT_SECURE_NO_WARNINGS
#include <Stdio.h>
#include <Windows.h>
#include <strsafe.h>

void findnum(LPSTR text) {
	int i = 0;
	while (text[i]) {
		i++;
		if (text[i] > 96 || text[i] < -1) {
			return 1;
		}
	}
	i = 0;
	while (text[i]) {
		if (text[i] == '1')
			WriteBuffer(L"Один");
		if (text[i] == '2')
			WriteBuffer(L"Два");
		if (text[i] == '3')
			WriteBuffer(L"Три");
		if (text[i] == '4')
			WriteBuffer(L"Четыре");
		if (text[i] == '5')
			WriteBuffer(L"Пять");
		if (text[i] == '6')
			WriteBuffer(L"Шесть");
		if (text[i] == '7')
			WriteBuffer(L"Семь");
		if (text[i] == '8')
			WriteBuffer(L"Восемь");
		if (text[i] == '9')
			WriteBuffer(L"Девять");
		i++;
	}
}

TCHAR* readBuffer() {
	TCHAR* message = NULL;
	OpenClipboard(NULL); // Открытие буффера
	HANDLE hWriteToBuffer = GetClipboardData(CF_UNICODETEXT);
	message = GlobalLock(hWriteToBuffer); // Закрытие памяти для считывания буффера
	GlobalUnlock(hWriteToBuffer); // Открытие памят
	CloseClipboard();
	EmptyClipboard();
	return message;
}

int WriteBuffer(LPWSTR buffer) {
	DWORD lenght = wcslen(buffer) + 1;
	HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE, lenght * sizeof(LPWSTR));
	memcpy(GlobalLock(hMem), buffer, lenght * sizeof(LPWSTR));
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hMem);
	CloseClipboard();
	return 0;
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	while (1) {
		LPSTR text = readBuffer();
		LPSTR number;
		TCHAR warning[] = L"Вы нарушили Авторские права, скопировав следующий текст: ";
		TCHAR message[1024];
		swprintf(message, sizeof(message), L"%s%s", warning, text);
		if (*text != NULL) {
			MessageBoxW(NULL, &message, L"Нарушение", MB_OK | MB_ICONWARNING);
			WriteBuffer("");
		}

		findnum(text);
		Sleep(1000);
	}
	return 0;
}


//int main()
//{
//   
//}
