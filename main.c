// 디렉토리 길이: 200바이트 까지
// 어셈블리코드 길이: 100바이트 까지

// 문법적 오류는 확인하지 않음

#include <stdio.h>
#include <string.h>

extern char* Parser(char line[101]);

int main() {

	printf("Please enter a source file directory\n");
	char dir_asm[201] = { 0 };
	FILE* fp_asm;

	while (1) {
		// .asm 파일의 디렉토리 입력
		scanf_s(" %[^\n]s", dir_asm, 201);

		// .asm이 아닐 경우
		// strrchr로 .asm검색 후 m 다음의 값이 0(NULL)인지 검사
		char* asm_ext = strrchr(dir_asm, '.asm');
		if (asm_ext == NULL || *(asm_ext + 1) != NULL) {
			printf("This file is not a asm file\n");
			printf("Please enter a asm file\n");
			continue;
		}

		// 파일 불러오기
		fopen_s(&fp_asm, dir_asm, "r");    // 파일 불러오기에 실패할 경우 NULL 반환
		if (fp_asm == NULL) {
			printf("Failed to load file\n");
			printf("Please enter a valid direstory\n");
		}
		else {
			printf("The file was loaded successfully\n");
			break;
		}
	}

	// .hack 파일 디렉토리 생성
	char dir_hack[202] = { 0 };
	strcpy_s(dir_hack, 201, dir_asm);
	char* hack_ext = strrchr(dir_hack, '.asm');    // 확장자 위치
	*(hack_ext - 2) = 'h';
	*(hack_ext - 1) = 'a';
	*(hack_ext)     = 'c';
	*(hack_ext + 1) = 'k';
	*(hack_ext + 2) = 0; // NULL 종료 문자

	// .hack 파일 생성 및 열기
	FILE* fp_hack;
	fopen_s(&fp_hack, dir_hack, "w");
	//if (fp_hack == NULL)
	//	printf("hack file directory error");

	// 한 라인씩 추출
	char line[101] = { 0 };
	while (1) {
		char* a = fgets(line, 101, fp_asm);

		if (a == NULL)
			break;	  // 파일의 끝

		// Parser 모튤로 전달
		char code[17] = { 0 };    // 16비트 + NULL 종료 문자
		strcpy_s(code, 17, Parser(line));

		char blank_code[17] = { 0 };
		if (strcmp(code, blank_code) == 0)    // 공백 제거
			continue;

		printf("%s\n", code);

		// .hack 파일에 코드 작성
		fputs(code, fp_hack);
		fputs("\n", fp_hack);
	}

	printf("File compilation succeeded");
	fclose(fp_asm);
	fclose(fp_hack);

	return 0;
}