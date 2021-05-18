#include "sokoban.h"
#include "utill.h"

int DEBUGRESULT;
char directKey[4] = { LEFT, RIGHT, UP, DOWN };
/*
 * * : ����
 * @ : ���
 * # : ��
 * . : �����
 */
const char Stage[MAXSTAGE][SIZEY][SIZEX] = {
		{
			"########",
			"###   ##",
			"#.@*  ##",
			"### *.##",
			"#.##* ##",
			"# # . ##",
			"#* ***.#",
			"#   .  #",
			"########",
		},
		{
			"########",
			"#  #  @#",
			"#   *# #",
			"#.** . #",
			"# #.#*##",
			"#     ##",
			"#    .##",
			"########",
			"########",
		}
};
char result[2][RESULT];

char MainMenu() {
	int i;
	char choice;

	gotoxy(STARTX, STARTY);
	for (i = 0; i < 40; i++) { printf("="); }

	gotoxy(20 - STARTX, STARTY + 2);
	printf("1. Game Start\n");			// `15~28, 7
	gotoxy(20 - STARTX, STARTY + 3);
	printf("2. Setting\n");				// 15~25, 8
	gotoxy(20 - STARTX, STARTY + 4);
	printf("3. Producted by\n");		// 15~30, 9
	gotoxy(STARTX, STARTY + 9);
	for (i = 0; i < 40; i++) { printf("="); }

	
	while (1) {
		gotoxy(20 - STARTX, STARTY + 6);
		printf("Input Number(1~3, 0=end) : ");
		choice = getchar();
		getchar();

		if (choice < '0' || choice > '3') {
			gotoxy(12 - STARTX, STARTY + 7);
			printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���.");
			Sleep(1000);
			system("cls");
			return MainMenu();
		}
		return choice;
	}
}

int* LoadMap(int curStage) {
	int i, j;
	int index = 0;
	static int curPos[2];
	

	for (i = 0; i != SIZEY; i++) {
		for (j = 0; j < SIZEX; j++) {
			if (Stage[curStage][i][j] == '@') {
				curPos[INDEXY] = i, curPos[INDEXX] = j;
			}
			else if (Stage[curStage][i][j] == '.') {
				DEBUGRESULT++;
				result[INDEXY][index] = i;
				result[INDEXX][index++] = j;
			}
			gotoxy(STARTX+j, STARTY+i), putchar(Stage[curStage][i][j]);
		}
	}
	
	/* LOG */
	gotoxy(DEBUGX, 0);
	printf("int : %d %d\n", curPos[INDEXY], curPos[INDEXX]);

	gotoxy(DEBUGX + 20, 0);
	printf("Status Log");

	gotoxy(DEBUGX + 40, 0);
	printf("��ġ�� �ö��ִ� ���� ��");

	return curPos;
}

void GameLoop() {
	int curStage = 0;
	bool gameover = true;
	while (curStage != MAXSTAGE) {
		if (!GameStart(curStage)) {
			system("cls");
			GameOver();
			return;
		}
		system("cls");
		DEBUGRESULT = 0;
		curStage++;
	}
}

bool GameStart(int curStage) {
	int* curPos = LoadMap(curStage);
	bool stageClear = false;
	char move;

	char stage[SIZEY][SIZEX];
	memcpy(stage, Stage[curStage], sizeof(Stage[curStage]));

	while ((move = _getch()) != EOF) {
		if (move == BACKSPACE) return false;
		if (move == ESC) return false;

		MovePlayer(move, stage, curPos);
		if (StageDone(stage)) {
			return true;
		}
		resetpoint(stage);
		gotoxy(DEBUGX, DEBUGY + 3);
		printf("cur : %d %d\n", curPos[INDEXX], curPos[INDEXY]);
	}
}

void MovePlayer(char move, char stage[][SIZEX], int* curPos) {
	static int DEBUGINDEX = 0;
	
	int chX, chY;

	if (move == ESC) exit(0);
	if (move == -32) {
		move = _getch();
		switch (move) {
		case LEFT:
			chX = -1; chY = 0;
			break;
		case RIGHT:
			chX = 1; chY = 0;
			break;
		case UP:
			chX = 0; chY = -1;
			break;
		case DOWN:
			chX = 0; chY = 1;
			break;
		default:
			gotoxy(0, 0);
			printf("����Ű�� �Է��ؿ�");
		}
	}



	gotoxy(DEBUGX, DEBUGY + 1);
	printf("cur : %d %d\n", curPos[INDEXX], curPos[INDEXY]);
	gotoxy(DEBUGX, DEBUGY + 2);
	printf("x y : %d %d",chX, chY);
	
	gotoxy(DEBUGX + 40, DEBUGY + 1);
	printf("count : %d", DEBUGRESULT);


	/* ����� ���� �ε�ĥ�� */
	if (stage[curPos[INDEXY] + chY][curPos[INDEXX] + chX] == '#') {
		gotoxy(DEBUGX, DEBUGY + 3);
		printf("��"); return; }

	/* ���� �ж� */
	if (stage[curPos[INDEXY] + chY][curPos[INDEXX] + chX] == '*') {
		gotoxy(DEBUGX+20, DEBUGY + DEBUGINDEX++);
		printf("���ڹа�����");
		/* ���� �� �� or ����*/
		if (stage[curPos[INDEXY] + chY * 2][curPos[INDEXX] + chX * 2] == '#' ||
			stage[curPos[INDEXY] + chY * 2][curPos[INDEXX] + chX * 2] == '*') {
			return;
		}

		/* ���� �� ��ĭ */
		else if (stage[curPos[INDEXY] + chY * 2][curPos[INDEXX] + chX * 2] == ' ' || 
			stage[curPos[INDEXY] + chY * 2][curPos[INDEXX] + chX * 2] == '.') {
			gotoxy(STARTX + curPos[INDEXX] + chX * 2, STARTY + curPos[INDEXY] + chY * 2);
			stage[curPos[INDEXY] + chY*2][curPos[INDEXX] + chX*2] = '*';
			_putch('*');
		}

	}

	gotoxy(STARTX + curPos[INDEXX], STARTY + curPos[INDEXY]);
	stage[curPos[INDEXY]][curPos[INDEXX]] = ' ';
	_putch(' ');

	curPos[INDEXY] += chY;
	curPos[INDEXX] += chX;
	gotoxy(STARTX + curPos[INDEXX], STARTY + curPos[INDEXY]);
	stage[curPos[INDEXY]][curPos[INDEXX]] = '@';
	_putch('@');

}

bool StageDone(char stage[][SIZEX]) {
	int i;

	for (i = 0; i != DEBUGRESULT; i++) {
		/* ���ڰ� ��ǥ������ �ϳ��� ������ ���� */
		if (stage[result[INDEXY][i]][result[INDEXX][i]] != '*') {
			gotoxy(DEBUGX + 10, DEBUGY);
			printf("����");
			return false;
		}
	}

	gotoxy(DEBUGX + 10, DEBUGY);
	printf("����");
	return true;
}

void resetpoint(char stage[][SIZEX]) {
	int i;

	for (i = 0; i != DEBUGRESULT; i++) {
		/* ��ǥ������ ���ڳ� ����� ������� */
		if (stage[result[INDEXY][i]][result[INDEXX][i]] != '*' &&
			stage[result[INDEXY][i]][result[INDEXX][i]] != '@') {
			gotoxy(STARTX + result[INDEXX][i], STARTY + result[INDEXY][i]);
			stage[result[INDEXY][i]][result[INDEXX][i]] = '.';
			_putch('.');
		}
	}
}

void Setting(char input) {
	char ch;
	
	gotoxy(STARTX - 2, STARTY + 8);
	printf("�ٲٽ� Ű�� �Է��ϼ���"); // 25
	
	gotoxy(STARTX + 23, STARTY + 8);
	ch = _getch();

	gotoxy(0, 0);
	printf("%c : %d", ch, ch);
	if (ch == -32) {
		ch = _getch();
		gotoxy(0, 1);
		printf("%c : %d %c", ch, ch, '��');
		if (ch == LEFT)  directKey[input - '1'] = 'L';
		else if (ch == RIGHT)  directKey[input - '1'] = 'R';
		else if (ch == UP)  directKey[input - '1'] = 'U';
		else if (ch == DOWN)  directKey[input - '1'] = 'D';
	}
	else if(input >= '1' && input <= '4'){
		directKey[input-'1'] = ch;
	}
	getchar(); // ���������
}

void SettingMenu() {
	char input;

	
	while (1) {
		system("cls");
		SettingView();
		if ((input = getchar()) == EOF) return;
		getchar();//���������
		if (input == BACKSPACE || input == '0') return;
		
		Setting(input);
		Sleep(1000);
	}
	
}

void SettingView() {
	gotoxy(STARTX + 10, STARTY);
	printf("Ű���� ����");
	gotoxy(STARTX, STARTY + 2);
	printf("1. LEFT  : %c", directKey[0]);
	gotoxy(STARTX, STARTY + 3);
	printf("2. RIGHT : %c", directKey[1]);
	gotoxy(STARTX, STARTY + 4);
	printf("3. UP    : %c", directKey[2]);
	gotoxy(STARTX, STARTY + 5);
	printf("3. DOWN  : %c", directKey[3]);//12

	gotoxy(STARTX - 2, STARTY + 6);
	printf("���� �� = 0");
	gotoxy(STARTX - 2, STARTY + 7);
	printf("�ٲٽ� ������ ��ȣ �Է��ϼ��� : ");//32

	gotoxy(STARTX + 30, STARTY + 7);
}

void GameOver() {
	gotoxy(STARTX + 5, STARTY + 5);
	printf("Game over");
}