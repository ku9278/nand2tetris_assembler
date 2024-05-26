#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char* a_commend(int value);
extern char* c_commend(char comp[4], char dest[4], char jump[4]);

char* Parser(char line[101]) {

	char code[17] = { 0 };    // 16��Ʈ + NULL ���� ����

	int line_len = strlen(line);

	// �ּ� ����
	char* comment = strchr(line, '//');
	if (comment != NULL) {
		while (*comment != 0) {
			*comment = 0;
			comment ++;
		}
	}
	// \n ���� (�ּ� ������ ��� \n�� ���� ���ŵ�)
	else {
		line[line_len - 1] = 0;
		line_len -= 1;
	}

	// ���� ����
	char blank_line[100] = { 0 };
	if (strcmp(line, blank_line) == 0) {
		return code;
	}

	// A_COMMEND
	if (line[0] == '@') {
		code[0] = '0';

		// value ����
		line[0] = '0';
		int value = atoi(line);

		// value�� Code ���� ����
		char a_code[16] = { 0 };
		strcpy_s(a_code, 16, a_commend(value));

		strcat_s(code, 17, a_code);
	}
	// C_COMMEND
	else {
		code[0] = '1';
		code[1] = '1';
		code[2] = '1';

		char comp[4] = { 0 };
		char dest[4] = { 0 };
		char jump[4] = { 0 };

		char comp_code[8] = { 0 };
		char dest_code[4] = { 0 };
		char jump_code[4] = { 0 };

		// dest ����
		char* equal = strchr(line, '=');
		if (equal != NULL) {
			int dest_len = equal - line;
			for (int i = 0; dest_len > i; i++)
				dest[i] = line[i];

			// line���� dest�κ� ����
			for (int i = 0; i < line_len; i++)
				line[0 + i] = line[dest_len + 1 + i];
		}
		
		// jump ����
		char* semicolon = strchr(line, ';');
		if (semicolon != NULL) {
			// jump�� ��� 3�����̴�
			jump[0] = *(semicolon + 1);
			jump[1] = *(semicolon + 2);
			jump[2] = *(semicolon + 3);

			// line���� jump �κ� ����
			*(semicolon + 0) = 0;
			*(semicolon + 1) = 0;
			*(semicolon + 2) = 0;
			*(semicolon + 3) = 0;
		}
		
		// comp ����
		int comp_len = strlen(line);
		for (int i = 0; i < comp_len; i++)
			comp[i] = line[i];

		// comp, dest, jump�� Code ���� ����
		char c_code[14] = { 0 };
		strcpy_s(c_code, 14, c_commend(comp, dest, jump));

		strcat_s(code, 17, c_code);
	}

	return code;
}