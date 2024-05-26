// ���丮 ����: 200����Ʈ ����
// ������ڵ� ����: 100����Ʈ ����

// ������ ������ Ȯ������ ����

#include <stdio.h>
#include <string.h>

extern char* Parser(char line[101]);

int main() {

	printf("Please enter a source file directory\n");
	char dir_asm[201] = { 0 };
	FILE* fp_asm;

	while (1) {
		// .asm ������ ���丮 �Է�
		scanf_s(" %[^\n]s", dir_asm, 201);

		// .asm�� �ƴ� ���
		// strrchr�� .asm�˻� �� m ������ ���� 0(NULL)���� �˻�
		char* asm_ext = strrchr(dir_asm, '.asm');
		if (asm_ext == NULL || *(asm_ext + 1) != NULL) {
			printf("This file is not a asm file\n");
			printf("Please enter a asm file\n");
			continue;
		}

		// ���� �ҷ�����
		fopen_s(&fp_asm, dir_asm, "r");    // ���� �ҷ����⿡ ������ ��� NULL ��ȯ
		if (fp_asm == NULL) {
			printf("Failed to load file\n");
			printf("Please enter a valid direstory\n");
		}
		else {
			printf("The file was loaded successfully\n");
			break;
		}
	}

	// .hack ���� ���丮 ����
	char dir_hack[202] = { 0 };
	strcpy_s(dir_hack, 201, dir_asm);
	char* hack_ext = strrchr(dir_hack, '.asm');    // Ȯ���� ��ġ
	*(hack_ext - 2) = 'h';
	*(hack_ext - 1) = 'a';
	*(hack_ext)     = 'c';
	*(hack_ext + 1) = 'k';
	*(hack_ext + 2) = 0; // NULL ���� ����

	// .hack ���� ���� �� ����
	FILE* fp_hack;
	fopen_s(&fp_hack, dir_hack, "w");
	//if (fp_hack == NULL)
	//	printf("hack file directory error");

	// �� ���ξ� ����
	char line[101] = { 0 };
	while (1) {
		char* a = fgets(line, 101, fp_asm);

		if (a == NULL)
			break;	  // ������ ��

		// Parser ��ƫ�� ����
		char code[17] = { 0 };    // 16��Ʈ + NULL ���� ����
		strcpy_s(code, 17, Parser(line));

		char blank_code[17] = { 0 };
		if (strcmp(code, blank_code) == 0)    // ���� ����
			continue;

		printf("%s\n", code);

		// .hack ���Ͽ� �ڵ� �ۼ�
		fputs(code, fp_hack);
		fputs("\n", fp_hack);
	}

	printf("File compilation succeeded");
	fclose(fp_asm);
	fclose(fp_hack);

	return 0;
}