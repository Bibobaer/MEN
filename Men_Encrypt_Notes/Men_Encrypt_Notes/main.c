#include "func.h"

int main() {
	FILE* file;
	char filename[32];
	char key[16];
	
	const wchar_t* path = L"Crypt_Files";
	printf("Files:\n");
	listFiles(path);

	printf("\nEnter name file: ");
	scanf_s("%s", filename, 32);
	filename[strlen(filename)] = '\0';
	char filePath[64] = "Crypt_Files\\";
	strcat_s(filePath, 64, filename);

	errno_t err = fopen_s(&file, filePath, "r");
	if (err != 0) {
		if (err == 2) {
			if (strcmp(filePath, "Crypt_Files\\out.txt") == 0) {
				printf("You cant use this file name\n");
				return -1;
			}
			if (fopen_s(&file, filePath, "w") != 0) {
				printf("File dont open\n");
				return -1;
			}
			printf("You create a new file\n");
			printf("Enter the key: ");
			scanf_s("%s", key, 16);

			int sizebuf = 0;
			char *buf = (char*)malloc((size_t)(sizebuf + 1)*sizeof(char));
			if (!buf) {
				return -1;
			}
			if (EditBuf(&buf, &sizebuf)) {
				system("cls");

				printf("%s", buf);
				XOR_cipher(buf, key, buf);

				fprintf(file, "%s", buf);

				fclose(file);
				return 0;
			}
			else {
				return -1;
			}
		}
		printf("File dont open\n");
		return -1;
	}
	else {
		int sizebuf = 4096;

		char* buf = (char*)malloc((size_t)(sizebuf+ 1) * sizeof(char));
		if (!buf) {
			return -1;
		}

		printf("Enter the key: ");
		scanf_s("%s", key, 16);

		char command[128];

		FILE* out;
		err = fopen_s(&out, "Crypt_Files\\out.txt", "w");
		if (err != 0)
			return -1;
		int tmp_sizebuf = sizebuf;
		size_t cntbytes = fread(buf, sizeof(char), sizebuf, file);
		while (cntbytes != 0) {
			buf[cntbytes] = '\0';
			XOR_cipher(buf, key, buf);
			printf("%s", buf);
			if (EditBuf(&buf, &cntbytes)) {
				system("cls");
				printf("%s\n", buf);
				XOR_cipher(buf, key, buf);
				fprintf(out, "%s", buf);
			}
			else {
				return -1;
			}
			cntbytes = fread(buf, sizeof(char), tmp_sizebuf, file);
		}
		fclose(file);
		fclose(out);

		sprintf_s(command, 128, "del %s", filePath);
		system(command);
		sprintf_s(command, 128, "rename Crypt_Files\\out.txt %s", filename);
		system(command);
	}
	return 0;
}