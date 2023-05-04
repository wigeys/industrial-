#include <iostream>
#include <Windows.h> // Для работы с консолью
#include <ctime> // Для генерации случайных чисел
#include <conio.h>

using namespace std;

// Константы для игрового поля
const int ROWS = 20;
const int COLUMNS = 50;

// Константы для уровня сложности 1
const int SPEED_INCREASE_TIME = 10; // Каждые 10 секунд увеличиваем скорость на 1
const float SPEED_INCREASE_AMOUNT = 0.1; // На сколько увеличиваем скорость

// Константы для уровня сложности 2
const int OBSTACLE_INCREASE_TIME = 30; // Каждые 30 секунд увеличиваем количество препятствий на 1
const int MAX_OBSTACLES = 5; // Максимальное количество препятствий

// Константы для уровня сложности 3
const int MAX_OBSTACLE_TYPES = 3; // Количество типов препятствий
const char OBSTACLE_TYPES[MAX_OBSTACLE_TYPES] = { 'o', '*', '+' }; // Символы для отображения разных типов препятствий
const int OBSTACLE_CHANCE = 5; // Вероятность появления препятствия нового типа (от 1 до 10)

// Функция для получения случайного числа в заданном диапазоне
int random(int min, int max) {
	return min + rand() % (max - min + 1);
}

int main() {
	// Инициализация игрового поля
	char gameBoard[ROWS][COLUMNS];
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (i == ROWS - 1) {
				gameBoard[i][j] = '_'; // Создание дороги внизу
			}
			else {
				gameBoard[i][j] = ' '; // Заполнение остального поля пробелами

			}
		}
	}
	char startOver = 'YES';

	while (true) {
		// код игры

		cout << "DO YOU WANT TO PLAY? (YES/NO): ";
		cin >> startOver;

		if (startOver == 'Y' || startOver == 'y') {
			// если игрок хочет сыграть еще раз, начинаем игру заново
			break;
		}
		else if (startOver == 'N' || startOver == 'n') {
			// если игрок не хочет играть, закрываем консоль
			cout << "Goodbye!" << endl;
			exit(0); // завершаем программу
		}
	}
	// Инициализация игрока и препятствий
	int playerRow = ROWS - 2;
	int playerColumn = COLUMNS / 2;
	int obstacles[MAX_OBSTACLES][2];
	int obstacleCount = 1;
	obstacles[0][0] = 0;
	obstacles[0][1] = random(0, COLUMNS - 1);

	// Инициализация счетчиков времени и расстояния
	int timeCounter = 0;
	int distanceCounter = 0;

	// Инициализация переменных для уровня сложности 1
	float speed = 1.0;
	int speedIncreaseTimer = 0;

	// Инициализация переменных для уровня сложности 2
	int obstacleIncreaseTimer = 0;

	// Инициализация переменных для уровня сложности 3
	int obstacleTypes[MAX_OBSTACLES];
	for (int i = 0; i < MAX_OBSTACLES; i++) {
		obstacleTypes[i] = 0; // Изначально все препятствия одного типа
	}

	// Основной игровой цикл
	while (true) {
		// Отображение игрового поля
		system("cls"); // Очистка консоли
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLUMNS; j++) {
				if (i == playerRow && j == playerColumn) {
					cout << "|X|";
				}
				else if (i == playerRow + 1 && j == playerColumn) {
					cout << "|/\\|";
				}
				else if (i == playerRow + 2 && j == playerColumn) {
					cout << "|/_\\|";  //отображение игрока
				}
				else {
					bool obstacleFound = false;
					for (int k = 0; k < obstacleCount; k++) {
						if (obstacles[k][0] == i && obstacles[k][1] == j) {
							cout << OBSTACLE_TYPES[obstacleTypes[k]]; // Отображение препятствия
							obstacleFound = true;
							break;
						}
					}
					if (!obstacleFound) {
						cout << gameBoard[i][j]; // Отображение остальной части игрового поля
					}
				}
			}
			cout << endl;
		}


		// Обработка пользовательского ввода
		if (GetAsyncKeyState(VK_LEFT)) {
			playerColumn--;
			if (playerColumn < 0) {
				playerColumn = 0;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			playerColumn++;
			if (playerColumn >= COLUMNS) {
				playerColumn = COLUMNS - 1;
			}
		}

		// Обновление препятствий
		for (int i = 0; i < obstacleCount; i++) {
			obstacles[i][0]++;
			if (obstacles[i][0] >= ROWS) {
				obstacles[i][0] = 0;
				obstacles[i][1] = random(0, COLUMNS - 1);
				obstacleTypes[i] = random(0, MAX_OBSTACLE_TYPES - 1); // Выбираем случайный тип препятствия для нового препятствия
			}
		}

		// Увеличение сложности
		timeCounter++;
		if (timeCounter % 10 == 0) { // Уровень сложности 1
			speedIncreaseTimer++;
			if (speedIncreaseTimer >= SPEED_INCREASE_TIME) {
				speedIncreaseTimer = 0;
				speed += SPEED_INCREASE_AMOUNT;
			}
		}
		if (timeCounter % 30 == 0) { // Уровень сложности 2
			obstacleIncreaseTimer++;
			if (obstacleIncreaseTimer >= OBSTACLE_INCREASE_TIME && obstacleCount < MAX_OBSTACLES) {
				obstacleIncreaseTimer = 0;
				obstacleCount++;
			}
		}
		if (timeCounter % 60 == 0) { // Уровень сложности 3
			for (int i = 0; i < MAX_OBSTACLES; i++) {
				if (random(1, 10) <= OBSTACLE_CHANCE && obstacleTypes[i] < MAX_OBSTACLE_TYPES - 1) {
					obstacleTypes[i]++;
				}
			}
		}

		// Проверка столкновения
		for (int i = 0; i < obstacleCount; i++) {
			if (obstacles[i][0] == playerRow && obstacles[i][1] == playerColumn) {
				cout << "Game Over!" << endl;
				cout << "You traveled " << distanceCounter << " Meters." << endl;
				system("pause");
				return 0;
			}
		}
		// Обновление счетчика времени
		timeCounter++;
		// Обновление расстояния
		distanceCounter++;

		// Отображение счетчика времени и расстояния
		cout << "Time: " << timeCounter << endl;

		cout << "Distance: " << distanceCounter << " Meters" << endl;

		// Задержка перед следующим обновлением
		Sleep(50 / (int)speed);
	}

	// Конец программы
	return 0;
}