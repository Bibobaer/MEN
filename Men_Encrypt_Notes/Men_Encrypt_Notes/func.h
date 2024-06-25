#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

void XOR_cipher(char* message, char* key, char* encrypted);
void listFiles(const wchar_t* path);

_Bool EditBuf(char** buf, int* Size_File);