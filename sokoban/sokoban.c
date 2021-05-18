#include "sokoban.h"
#include "utill.h"

int main() {
	char choice;

	while (1) {
		system("cls");
		choice = MainMenu();
		
		switch (choice) {
		case '0':
			gotoxy(0, STARTY + 11);
			return 0;
		case '1':
			system("cls");
			GameLoop();
			break;
		case '2':
			system("cls");
			SettingMenu();
			break;
		}

		
	}
	
	return 0;
}