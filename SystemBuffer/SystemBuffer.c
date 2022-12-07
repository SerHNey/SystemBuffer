#define _CRT_SECURE_NO_WARNINGS
#include <Stdio.h>
#include <Windows.h>
#include <strsafe.h>

void findnum(TCHAR* text) {
	int i = 0;
	TCHAR message[1024];
	char* mess = calloc(100, sizeof(char));
	while (text[i]) {
		if (text[i] > 96 || text[i] < -1) {
			return 1;
		}
		if (text[i] == 49)
			sprintf(mess, "%s%s", mess, L"Один-");
		if (text[i] == 50)
			sprintf(mess, "%s%s", mess, L"Два-");
		if (text[i] == 51)
			sprintf(mess, "%s%s", mess, L"Три-");
		if (text[i] == 52)
			sprintf(mess, "%s%s", mess, L"Четыре-");
		if (text[i] == 53)
			sprintf(mess, "%s%s", mess, L"Пять-");
		if (text[i] == 54)
			sprintf(mess, "%s%s", mess, L"Шесть-");
		if (text[i] == 55)
			sprintf(mess, "%s%s", mess, L"Семь-");
		if (text[i] == 56)
			sprintf(mess, "%s%s", mess, L"Восемь-");
		if (text[i] == 57)
			sprintf(mess, "%s%s", mess, L"Девять-");
		i++;
	}
	swprintf(message, sizeof(message), L"%s", mess);
	WriteBuffer(message);
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
	int c = 1;
	while (c) {
		TCHAR* text = readBuffer();
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
		c = 0;
	}
	return 0;
}


//int main()
//{
//   
//}
