#include "func.h"

void XOR_cipher(char* message, char* key, char* encrypted) {
	for (int i = 0; i < strlen(message); i++) {
		encrypted[i] = message[i] ^ key[i % strlen(key)];
	}
	encrypted[strlen(message)] = '\0';
}

void listFiles(const wchar_t* path) {
	WIN32_FIND_DATAW findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	// Создаем шаблон пути, чтобы найти все файлы в директории
	wchar_t fullPath[MAX_PATH];
	swprintf(fullPath, MAX_PATH, L"%s\\*", path);

	// Находим первый файл в директории
	hFind = FindFirstFileW(fullPath, &findFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		wprintf(L"Ошибка при открытии директории: %s\n", path);
		return;
	}

	// Перебираем все найденные файлы и директории
	do {
		// Игнорируем "." и ".."
		if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0) {
			wprintf(L"\t%s\n", findFileData.cFileName);
		}
	} while (FindNextFileW(hFind, &findFileData) != 0);

	// Закрываем дескриптор поиска
	FindClose(hFind);
}

_Bool EditBuf(char** buf, int* Size_File) {
	if (buf == NULL || *buf == NULL)
		return 0;
	int c;
	while ((c = _getch()) != 13)
	{
		if (c == 8) {
			printf("\b \b");
			(*buf)[--(*Size_File)] = '\0';
			continue;
		}
		else {
			printf("%c", c);
			int k;
			char* NewBuf = (char*)malloc((size_t)(*Size_File + 1) * sizeof(char));
			if (!NewBuf)
				return 0;
			for (k = 0; k < *Size_File; k++)
				NewBuf[k] = (*buf)[k];
			NewBuf[k] = c;
			free(*buf);
			*buf = NewBuf;
			(*Size_File)++;

		}
	}
	(*buf)[*Size_File] = '\0';
	return 1;
}