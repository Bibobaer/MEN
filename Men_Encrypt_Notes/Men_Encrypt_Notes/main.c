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
			if (fopen_s(&file, filePath, "w") != 0) {
				printf("File dont open\n");
				return -1;
			}
			printf("You create a new file\n");
			printf("Enter the key: ");
			scanf_s("%s", key, 16);

			int sizebuf = 0;
			char *buf = (char*)malloc((sizebuf + 1)*sizeof(char));
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
		fseek(file, 0, SEEK_END);
		int Size_File = ftell(file);
		fseek(file, 0, SEEK_SET);

		char* buf = (char*)malloc((size_t)(Size_File + 1) * sizeof(char));
		if (!buf) {
			return -1;
		}

		int i = 0;
		char tmp = '0';
		while (fscanf_s(file, "%c", &tmp, 1) != EOF)
			buf[i++] = tmp;

		buf[i] = '\0';
		fclose(file);

		printf("Enter the key: ");
		scanf_s("%s", key, 16);

		XOR_cipher(buf, key, buf);
		printf("%s", buf);

		if (EditBuf(&buf, &Size_File)) {
			system("cls");

			err = fopen_s(&file, filePath, "w");
			if (err != 0)
				return -1;

			printf("%s\n", buf);

			XOR_cipher(buf, key, buf);
			fprintf(file, "%s", buf);
			fclose(file);
			return 0;
		}
		else {
			return -1;
		}
	}
	return 0;
}