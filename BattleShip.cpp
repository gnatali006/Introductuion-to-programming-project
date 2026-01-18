/**
*
* Solution to course project # 5
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Natali Georgieva
* @idnumber 8MI0600678* @compiler GCC
*
* <>
*
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <fstream>
const int numberOfShips = 10;
const int firstAndLastCoord = 4;
int tableSize;
enum GameStatus { RUNNING, EXIT_SAVE };
GameStatus status = RUNNING;
void mySwap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}
int myAbs(int a) {
	if (a < 0) {
		return -a;
	}
	return a;
}
void printTable(char** tableOfPlayer, char** tableOfComputer) {
	const int MAX_DIGIT = 9;
	std::cout << "   ";
	for (int i = 0; i < tableSize; i++) {
		if (i < MAX_DIGIT)
			std::cout << i << "  ";
		else
			std::cout << i << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < tableSize; i++) {
		std::cout << i;
		if (i <= MAX_DIGIT)
			std::cout << "  ";
		else
			std::cout << " ";
		for (int j = 0; j < tableSize; j++) {
			std::cout << tableOfComputer[i][j] << "  ";
		}
		std::cout << "| ";
		for (int j = 0; j < tableSize; j++) {
			std::cout << tableOfPlayer[i][j] << "  ";
		}
		std::cout << "\n";
	}
}
void printTableOfPlayer(char** table) {
	std::cout << "   ";
	for (int i = 0; i < tableSize; i++) {
		if (i < 9)
			std::cout << i << "  ";
		else
			std::cout << i << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < tableSize; i++) {
		std::cout << i;
		if (i <= 9)
			std::cout << "  ";
		else
			std::cout << " ";
		for (int j = 0; j < tableSize; j++) {
			std::cout << table[i][j] << "  ";
		}
		std::cout << "\n";
	}
}
void clearScreen() {
	system("cls");
}
char** createTable(int tableSize) {
	char** table = new char* [tableSize];
	for (int i = 0; i < tableSize; i++) {
		table[i] = new char[tableSize];
		for (int j = 0; j < tableSize; j++) {
			table[i][j] = '~';
		}
	}
	return table;
}
void deleteTable(char** table) {
	if (table == nullptr)
		return;
	for (int i = 0; i < tableSize; i++) {
		delete[]table[i];
	}
	delete[]table;
}
int getValidInput() {
	int x;
	while (!(std::cin >> x)) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Inavlid input. Enter the number again: ";
	}
	return x;
}
void saveGame(char** tableOfComputer, char** tableOfPlayer, int computersShips[][firstAndLastCoord],
	int playersShips[][firstAndLastCoord], bool currentTurn) {
	std::ofstream ofs("savegame.txt");
	if (!ofs) return;
	ofs << tableSize << " " << currentTurn << "\n";
	if (!ofs.is_open()) {
		std::cout << "The file cannot open to save the data.";
		return;
	}
	for (int i = 0; i < tableSize;i++) {
		for (int j = 0; j < tableSize; j++) {
			ofs << tableOfComputer[i][j];
		}
		ofs << "\n";
	}
	for (int i = 0; i < tableSize;i++) {
		for (int j = 0; j < tableSize; j++) {
			ofs << tableOfPlayer[i][j];
		}
		ofs << "\n";
	}
	for (int i = 0; i < numberOfShips; i++) {
		for (int j = 0; j < firstAndLastCoord; j++) {
			ofs << computersShips[i][j] << " ";
		}
		ofs << "\n";
	}
	for (int i = 0; i < numberOfShips; i++) {
		for (int j = 0; j < firstAndLastCoord; j++) {
			ofs << playersShips[i][j] << " ";
		}
		ofs << "\n";
	}
	ofs.close();
	std::cout << "The game has been saved successfully!";
	Sleep(2000);

	status = EXIT_SAVE;
}
bool loadGame(char**& tableOfComputer, char**& tableOfPlayer, int computersShips[][firstAndLastCoord],
	int playersShips[][firstAndLastCoord], bool& currentTurn) {
	std::ifstream ifs("savegame.txt");
	int newSize;
	ifs >> newSize >> currentTurn;

	if (!ifs.is_open()) {
		return false;
	}
	if (tableOfComputer != nullptr) {
		deleteTable(tableOfComputer);
		tableOfComputer = nullptr;

	}
	if (tableOfPlayer != nullptr) {
		deleteTable(tableOfPlayer);
		tableOfPlayer = nullptr;
	}
	tableSize = newSize;
	tableOfComputer = createTable(tableSize);
	tableOfPlayer = createTable(tableSize);
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < tableSize; j++) {
			ifs >> tableOfComputer[i][j];
		}
	}
	for (int i = 0; i < tableSize; i++) {
		for (int j = 0; j < tableSize; j++) {
			ifs >> tableOfPlayer[i][j];
		}
	}
	for (int i = 0; i < numberOfShips; i++) {
		for (int j = 0; j < firstAndLastCoord; j++) {
			ifs >> computersShips[i][j];
		}
	}
	for (int i = 0; i < numberOfShips; i++) {
		for (int j = 0; j < firstAndLastCoord; j++) {
			ifs >> playersShips[i][j];
		}
	}
	ifs.close();
	return true;
}
bool areCoordinatesCorrect(char** table, int& firstR, int& secondR, int& firstC, int& secondC, int length) {
	if (length == 1) {
		if (firstR >= tableSize || firstR < 0 || firstC >= tableSize || firstC < 0) {
			std::cout << "Invalid coordinates. Type new ones:\n";
			return false;
		}
		if (table[firstR][firstC] != '~') {
			std::cout << "You already have a ship here. Type new coordinates:\n";
			return false;
		}
		return true;
	}
	if (firstR >= tableSize || firstR < 0 || firstC >= tableSize || firstC < 0 || secondR >= tableSize || secondR < 0 || secondC >= tableSize || secondC < 0) {
		std::cout << "Invalid coordinates.\n";
		return false;
	}
	if ((firstR != secondR && myAbs(firstR - secondR) + 1 != length) || (firstC != secondC && myAbs(firstC - secondC) + 1 != length)) {
		std::cout << "Invalid length of ship.\n";
		return false;
	}
	int i = 0;
	if (firstR > secondR)mySwap(firstR, secondR);
	if (firstC > secondC)mySwap(firstC, secondC);
	if (firstR != secondR) {
		i = firstR;
		while (i <= secondR) {
			if (table[i++][firstC] != '~') {
				std::cout << "You already have a ship here.";
				return false;
			}
		}
	}
	if (firstC != secondC) {
		i = firstC;
		while (i <= secondC) {
			if (table[firstR][i++] != '~')
			{
				std::cout << "You already have a ship here.";
				return false;
			}
		}
	}
	return true;
}
void locateShipManually(char** table, int tableOfShips[][firstAndLastCoord], int currInd, int length) {
	int firstR, firstC, secondR, secondC;
	printTableOfPlayer(table);
	bool valid = false;
	while (!valid) {
		if (length == 1) {
			firstR = getValidInput();
			firstC = getValidInput();
		}
		else {
			firstR = getValidInput();
			firstC = getValidInput();
			secondR = getValidInput();
			secondC = getValidInput();
		}
		if (areCoordinatesCorrect(table, firstR, secondR, firstC, secondC, length)) {
			valid = true;
		}
	}
	tableOfShips[currInd][0] = firstR;
	tableOfShips[currInd][1] = firstC;
	if (length == 1) {
		table[firstR][firstC] = '#';
		tableOfShips[currInd][2] = firstR;
		tableOfShips[currInd][3] = firstC;
		return;
	}
	tableOfShips[currInd][2] = secondR;
	tableOfShips[currInd][3] = secondC;
	int i = 0;
	if (firstR != secondR) {
		i = firstR;
		while (i <= secondR) {
			table[i++][firstC] = '#';
		}
	}
	if (firstC != secondC) {
		i = firstC;
		while (i <= secondC) {
			table[firstR][i++] = '#';
		}
	}
}
void manuallyLocateShips(char** table, int tableOfShips[][firstAndLastCoord]) {
	std::cout << "Type start and end coordinates for the first ship with length 4. It can be located horizontally or vertically.\n";
	int length = 4;
	int currInd = 0;
	locateShipManually(table, tableOfShips, currInd, length);
	clearScreen();
	currInd++;

	length = 3;
	for (int i = 0; i < 2; i++) {
		std::cout << "Type start and end coordinates for a ship with length 3.\n";
		locateShipManually(table, tableOfShips, currInd, length);
		clearScreen();
		currInd++;
	}

	length = 2;
	for (int i = 0; i < 3; i++) {
		std::cout << "Type start and end coordinates for a ship with length 2.\n";
		locateShipManually(table, tableOfShips, currInd, length);
		clearScreen();
		currInd++;
	}

	length = 1;
	for (int i = 0; i < 4; i++) {
		std::cout << "Type 1 coordinate for a ship with length 1.\n";
		locateShipManually(table, tableOfShips, currInd, length);
		clearScreen();
		currInd++;
	}
}
bool canPlace(char** table, int shipSize, int firstCoord, int secondCoord, bool direction) {
	int f, s;
	if (table == nullptr) return false;
	for (int i = 0; i < shipSize; i++) {
		f = firstCoord + (direction ? i : 0);
		s = secondCoord + (direction ? 0 : i);
		if (f >= tableSize || s >= tableSize) return false;
		if (table[f][s] != '~') return false;
	}
	return true;
}
void locateShipAutomatically(char** table, int tableOfShips[][firstAndLastCoord], int currInd, int sizeOfShip, bool isPlayersTable) {
	int firstCoord, secondCoord, direction;
	do {
		firstCoord = rand() % tableSize;
		secondCoord = rand() % tableSize;
		direction = rand() % 2; //0 for horizontal, 1 for vertical
	} while (!canPlace(table, sizeOfShip, firstCoord, secondCoord, direction));

	tableOfShips[currInd][0] = firstCoord;
	tableOfShips[currInd][1] = secondCoord;
	for (int i = 0; i < sizeOfShip; i++) {
		if (!direction) {
			if (isPlayersTable) {
				table[firstCoord][secondCoord + i] = '#';
			}
			if (i == sizeOfShip - 1) {
				tableOfShips[currInd][2] = firstCoord;
				tableOfShips[currInd][3] = secondCoord + i;
			}
		}
		else {
			if (isPlayersTable) {
				table[firstCoord + i][secondCoord] = '#';
			}
			if (i == sizeOfShip - 1) {
				tableOfShips[currInd][2] = firstCoord + i;
				tableOfShips[currInd][3] = secondCoord;
			}
		}
	}
}
void automaticallyLocateShips(char** table, int tableOfShips[][firstAndLastCoord], bool isPlayersTable) {
	int currInd = 0;
	for (int i = 0; i < 1; i++) {
		locateShipAutomatically(table, tableOfShips, currInd, 4, isPlayersTable);
		currInd++;
	}
	for (int i = 0; i < 2; i++) {
		locateShipAutomatically(table, tableOfShips, currInd, 3, isPlayersTable);
		currInd++;
	}
	for (int i = 0; i < 3; i++) {
		locateShipAutomatically(table, tableOfShips, currInd, 2, isPlayersTable);
		currInd++;
	}
	for (int i = 0; i < 4; i++) {
		locateShipAutomatically(table, tableOfShips, currInd, 1, isPlayersTable);
		currInd++;
	}
}
bool isAHit(char** table, int tableOfShips[][firstAndLastCoord], int firstCoord, int secondCoord, int i) {
	if (firstCoord >= tableOfShips[i][0] && firstCoord <= tableOfShips[i][2] && secondCoord >= tableOfShips[i][1] && secondCoord <= tableOfShips[i][3]) {
		table[firstCoord][secondCoord] = 'X';
		return true;
	}
	return false;
}
bool isShipSunk(char** table, int tableOfShips[][firstAndLastCoord], int firstCoord, int secondCoord, int i) {
	if (tableOfShips[i][0] != tableOfShips[i][2]) {
		int currentCoord = tableOfShips[i][0];
		while (currentCoord <= tableOfShips[i][2]) {
			if (table[currentCoord++][tableOfShips[i][1]] != 'X') return false;
		}
	}
	if (tableOfShips[i][1] != tableOfShips[i][3]) {
		int currentCoord = tableOfShips[i][1];
		while (currentCoord <= tableOfShips[i][3]) {
			if (table[tableOfShips[i][0]][currentCoord++] != 'X') return false;
		}
	}
	tableOfShips[i][0] = -1;
	return true;
}
bool isGameOver(int tableOfShips[][firstAndLastCoord]) {
	for (int i = 0; i < numberOfShips; i++) {
		if (tableOfShips[i][0] != -1) {
			return false;
		}
	}
	return true;
}
bool areShootCoordsCorrect(char** table, int firstCoord, int secondCoord) {
	if (firstCoord < 0 || firstCoord >= tableSize || secondCoord < 0 || secondCoord >= tableSize) {
		std::cout << "Invalid coordinates.";
		return false;
	}
	if (table[firstCoord][secondCoord] != '~') {
		std::cout << "You have already shot there!\nType new coordinates:\n";
		return false;
	}
	return true;
}
void playersTurn(char** tableOfComputer, int computersShips[][firstAndLastCoord], int playersShips[][firstAndLastCoord], char** tableOfPlayer, bool& currentTurn) {
	if (status == EXIT_SAVE) {
		return;
	}
	currentTurn = 1;
	int firstCoord;
	int secondCoord;
	bool hit = true;
	std::cout << "Shoot by choosing coordinates or type -1 to save and exit the game.\n";
	while (hit) {
		firstCoord = getValidInput();
		if (firstCoord == -1) {
			saveGame(tableOfComputer, tableOfPlayer, computersShips, playersShips, currentTurn);
			return;
		}
		secondCoord = getValidInput();
		if (!areShootCoordsCorrect(tableOfComputer, firstCoord, secondCoord)) {
			continue;
		}
		hit = false;
		for (int i = 0; i < numberOfShips; i++) {
			if (computersShips[i][0] == -1)
				continue;
			if (isAHit(tableOfComputer, computersShips, firstCoord, secondCoord, i)) {
				std::cout << "You got a hit! It's your turn again.\n";
				hit = true;
				if (isShipSunk(tableOfComputer, computersShips, firstCoord, secondCoord, i)) {
					std::cout << "The ship is sunk!\n";
				}
				if (isGameOver(computersShips)) {
					return;
				}
				break;
			}
		}
		if (!hit) {
			std::cout << "You missed!";
			tableOfComputer[firstCoord][secondCoord] = 'o';
		}
		Sleep(1500);
		clearScreen();
		printTable(tableOfPlayer, tableOfComputer);
	}
}
void computersTurn(char** tableOfPlayer, int playersShips[][firstAndLastCoord], char** tableOfComputer) {
	int firstCoord, secondCoord;
	bool isMiss = true;
	do {
		isMiss = true;
		do {
			firstCoord = rand() % tableSize;
			secondCoord = rand() % tableSize;
		} while (tableOfPlayer[firstCoord][secondCoord] == 'o' || tableOfPlayer[firstCoord][secondCoord] == 'X');
		for (int i = 0; i < numberOfShips; i++) {
			if (playersShips[i][0] == -1) continue;
			if (isAHit(tableOfPlayer, playersShips, firstCoord, secondCoord, i)) {
				isMiss = false;
				isShipSunk(tableOfPlayer, playersShips, firstCoord, secondCoord, i);
				if (isGameOver(playersShips)) {
					return;
				}
				break;
			}
		}
		if (isMiss) {
			tableOfPlayer[firstCoord][secondCoord] = 'o';
		}
	} while (!isMiss);
}
void startOfGame(char**& tableOfComputer, char**& tableOfPlayer, int computersShips[][firstAndLastCoord],
	int playersShips[][firstAndLastCoord], int& difficulty, int& method, int choice) {
	std::cout << "Choose game difficulty:\n1) Calm Waters (table 10x10) 2) Rough Seas (table 12x12) 3) Storm of Steel (table 15x15)\nType 1, 2 or 3:\n";
	difficulty = getValidInput();
	while (difficulty > 3 || difficulty < 1) {
		std::cout << "You didn't type correct data.";
		difficulty = getValidInput();
	}
	switch (difficulty) {
	case 1:
		tableSize = 10;
		break;
	case 2:
		tableSize = 12;
		break;
	case 3:
		tableSize = 15;
		break;
	}
	tableOfPlayer = createTable(tableSize);
	tableOfComputer = createTable(tableSize);
	clearScreen();
	std::cout << "How do you wanna locate your ships?\n1)Manually by coordinates\n2)Automatically\nType 1 or 2 depending on your choice.\n";
	method = getValidInput();
	while (method < 1 || method > 2) {
		std::cout << "You didn't type correct data.";
		method = getValidInput();
	}
	clearScreen();
	if (method == 1) {
		manuallyLocateShips(tableOfPlayer, playersShips);
	}
	if (method == 2) {
		automaticallyLocateShips(tableOfPlayer, playersShips, 1);
	}
	clearScreen();
	automaticallyLocateShips(tableOfComputer, computersShips, 0);
}
void playGame(char**& tableOfComputer, char**& tableOfPlayer, int computersShips[][firstAndLastCoord],
	int playersShips[][firstAndLastCoord], int& difficulty, int& method, bool& currentTurn, int choice) {
	if (choice == 1) {
		startOfGame(tableOfComputer, tableOfPlayer, computersShips, playersShips, difficulty, method, choice);
	}
	printTable(tableOfPlayer, tableOfComputer);
	while (status == RUNNING) {
		currentTurn = true;
		playersTurn(tableOfComputer, computersShips, playersShips, tableOfPlayer, currentTurn);
		if (status == EXIT_SAVE) {
			break;
		}
		currentTurn = false;
		if (isGameOver(computersShips)) {
			std::cout << "You won!";
			Sleep(1000);
			remove("savegame.txt");
			break;
		}
		computersTurn(tableOfPlayer, playersShips, tableOfComputer);
		if (isGameOver(playersShips)) {
			std::cout << "You lost! :(";
			Sleep(1000);
			remove("savegame.txt");
			break;
		}
	}
}

int main()
{
	srand(time(0));
	int choice, difficulty, method;
	bool currentTurn;
	char** tableOfPlayer = nullptr;
	int playersShips[numberOfShips][firstAndLastCoord];
	char** tableOfComputer = nullptr;
	int computersShips[numberOfShips][firstAndLastCoord];
	std::cout << "1.New game\n2.Load Game\n";
	choice = getValidInput();
	clearScreen();
	while (choice != 1 && choice != 2) {
		std::cout << "Invalid choice.";
		std::cin >> choice;
	}
	if (choice == 2) {
		if (!loadGame(tableOfComputer, tableOfPlayer, computersShips, playersShips, currentTurn)) {
			std::cout << "There isn't a saved game. Starting new one...\n";
			choice = 1;
		}
		else {
			playGame(tableOfComputer, tableOfPlayer, computersShips, playersShips, difficulty, method, currentTurn, 2);
		}
	}
	if (choice == 1) {
		playGame(tableOfComputer, tableOfPlayer, computersShips, playersShips, difficulty, method, currentTurn, 1);
	}
	deleteTable(tableOfPlayer);
	tableOfPlayer = nullptr;
	deleteTable(tableOfComputer);
	tableOfComputer = nullptr;
}
