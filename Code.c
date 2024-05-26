#include <stdio.h>
#include <string.h>

// comp표 전역 상수 배열로 선언 및 초기화
// 아래 배열은 a = 0인 경우(어셈블리 코드에 A가 있는 경우)
// a = 1인 경우는 A를 M으로 바꾼 후 a = 0인 경우로 처리한다.
const char comp_code1[18][4] = { 
	{"0"}, {"1"}, {"-1"}, {"D"}, {"A"}, {"!D"}, {"!A"}, {"-D"}, {"-A"},
	{"D+1"}, {"A+1"}, {"D-1"}, {"A-1"}, {"D+A"}, {"D-A"}, {"A-D"}, {"D&A"}, {"D|A"}
};
const char comp_code2[18][7] = { 
	{"101010"},
	{"111111"},
	{"111010"},
	{"001100"},
	{"110000"},
	{"001101"},
	{"110001"},
	{"001111"},
	{"110011"},
	{"011111"},
	{"110111"},
	{"001110"},
	{"110010"},
	{"000010"},
	{"010011"},
	{"000111"},
	{"000000"},
	{"010101"}
};

char* a_commend(int value) {

	char a_code[16] = "000000000000000";

	for (int i = 0; value >= 1; i++) {
		if (value % 2 == 1)
			a_code[14 - i] = '1';
		value /= 2;
	}

	return a_code;
}

char* c_commend(char comp[4], char dest[4], char jump[4]) {

	char c_code[14] = { 0 };

	// comp
	// comp에 A가 포함되어 있으면 a비트는 0
	// comp에 M이 포함되어 있으면 a비트는 1
	c_code[0] = '0'; // a 비트
	char* Mbit = strchr(comp, 'M');
	if (Mbit != NULL) {
		c_code[0] = '1';
		*(Mbit) = 'A';
	}
	for (int i = 0; i < 18; i++) { // c1 ~ c6 비트
		int check = strcmp(comp, comp_code1[i]);
		if (check == 0) {
			strcat_s(c_code, 14, comp_code2[i]);
			break;
		}
	}
	strcat_s(c_code, 14, "000000"); // dest, jump 부분 '0'으로 초기화

	// dest
	char* M = strchr(dest, 'M');
	char* D = strchr(dest, 'D');
	char* A = strchr(dest, 'A');
	if (M != NULL)
		c_code[9] = '1';
	if (D != NULL)
		c_code[8] = '1';
	if (A != NULL)
		c_code[7] = '1';

	// jump
	if (_strcmpi(jump, "JGT") == 0) {    // 대소문자 구분하지 않고 비교
		c_code[12] = '1';
	}
	else if (_strcmpi(jump, "JEQ") == 0) {
		c_code[11] = '1';
	}
	else if (_strcmpi(jump, "JGE") == 0) {
		c_code[11] = '1';
		c_code[12] = '1';
	}
	else if (_strcmpi(jump, "JLT") == 0) {
		c_code[10] = '1';
	}
	else if (_strcmpi(jump, "JNE") == 0) {
		c_code[10] = '1';
		c_code[12] = '1';
	}
	else if (_strcmpi(jump, "JLE") == 0) {
		c_code[10] = '1';
		c_code[11] = '1';
	}
	else if (_strcmpi(jump, "JMP") == 0) {
		c_code[10] = '1';
		c_code[11] = '1';
		c_code[12] = '1';
	}

	return c_code;
}