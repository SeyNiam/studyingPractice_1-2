/* Найти в двумерном массиве максимальный элемент в каждой диагонали, параллельной главной. */
#include <iostream>
#include <fstream> // Общий файловый поток с возможностями как ofstream, так и ifstream, которые позволяют ему создавать, читать и записывать информацию в файлы
#include <cstdlib> // содержит srand() и rand()
#include <ctime> // содержит time()

using namespace std;

int safeInput(void); // Прототип функции, позволяющей избежать краха программы при некорректном вводе со стороны пользователя
int* maxFinder(int*, int**, int, int); // Функция для нахождения максимального элемента в каждой диагонали, параллельной главной
void arrayInit(int**, int, int); // Функция инициализации и вывода массива на экран

int main()
{
	int endFlag = 1; // Флаг, который останавливает приложение
	// Глобальный цикл, который предотвращает завершение программы без желания пользователя
	do {
		int N, K; // Переменные, задающая размер массива
		int* max; // Объявление указателя на массив сумм диагоналей

		// Запрос размеров массива у пользователя
		cout << endl << "Please input the number of rows and columns of the array: ";
		cout << "\n>> ";
		cin >> N >> K;
		while (safeInput()) {
			cout << "Please enter integer values: ";
			cout << "\n>> ";
			cin >> N >> K;
		}


		// Создание массива
		int** array = new int* [N]; // Объявление указателя на массив и выделение объема памяти, необходимого для хранения запрашиваемого массива
		for (int i = 0; i < N; i++) {
			array[i] = new int[K];
		}


		// Инициализация и вывод созданного массива на экран
		cout << endl;
		srand(time(NULL)); // srand() получает в виде параметра текущее системное время, которое при каждом запускe программы будет разным
		arrayInit(array, N, K);


		// Запись исходного массива в файл
		ofstream MyFile;
		MyFile.open("test.txt", ios::trunc); // Открытие файла с удалением содержимого, если оно имелось
		if (MyFile.is_open()) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < K; j++) {
					MyFile << array[i][j] << " \t";
				}
				MyFile << endl;
			}
			MyFile << endl << endl;
		}
		else {
			cout << "Something went wrong";
		}
		MyFile.close();

		
		// Выделение массиву диагоналей объёма памяти размером N + K - 1
		int DIO = N + K - 1;
		max = new int[DIO]; 
		// Присвоение каждому элементу массива минимально возможного значения int
		for (int i = 0; i < DIO; i++) {
			max[i] = -2147483648;
		} 


		// Вызов функции для нахождения максимального элемента в каждой диагонали, параллельной главной
		max = maxFinder(max, array, N, K);


		// Вывод максимального элемента в каждой диагонали, параллельной главной, на экран и запись в файл
		cout << endl;
		MyFile.open("test.txt", std::ios::app); // std::ios::app - это значение "добавления" в открытом режиме. Новые данные будут записаны в конец файла
		if (MyFile.is_open()) {
			for (int k = 1; k < DIO; k++) {
				cout << k << ": " << max[k] << "\n";
				MyFile << k << ": " << max[k] << "\n";
			}
			MyFile << endl << endl;
		}
		else {
			cout << "Something went wrong";
		}
		MyFile.close();


		// Освобождение выделенной массивам памяти
		delete[] max;
		for (int i = 0; i < N; i++) {
			delete[]array[i];
		}


		// Предложение пользователю повторно запустить программу или выйти
		cout << "\n\nPlease choose from the following:\n\t1 - Run program again.\n\t2 - Exit.\n";
		do {
			cout << "\n>> ";
			cin >> endFlag;
			safeInput();
			if (endFlag != 1 && endFlag != 2) {
				cout << "Incorrect answer. Please try again.";
				endFlag = 0;
			}
		} while (endFlag == 0);
		switch (endFlag) {
		case 1: endFlag = 1; break;
		case 2: endFlag = 0; break;
		default: printf("Incorrect answer. The program will be closed."); endFlag = 0; break;
		}

	} while (endFlag); // Если флаг равен 0, то выход из цикла 
	return 0;
}


// Функция, позволяющая избежать краха программы при некорректном вводе со стороны пользователя
int safeInput(void) {
	if (cin.fail()) // Если предыдущее извлечение оказалось неудачным,
	{
		cin.clear(); // то cin возвращается в 'обычный' режим работы
		cin.ignore(32767, '\n'); // и значения предыдущего ввода удаляются из входного буфера
		return 1;
	}
	return 0;
}

// Функция для нахождения максимального элемента в каждой диагонали, параллельной главной
int* maxFinder(int *max, int **array, int N, int K) {
	int x = 0; // Счётчик массива сумм диагоналей
	int i, j, k; // Счётчики, использующиеся для обхода массива и сравнения номеров его элементов

	for (i = 0; i < N; i++) {
		for (j = 0; j < K; j++) {
			if (i != j) {
				for (k = -K; k < N; k++) {
					if (i - j == k) {

						if (max[x] < array[i][j]) {
							max[x] = array[i][j];
						}

						if (i < j) {
							x++;
						}
						else {
							x--;
						}
					}
				}
			}
			else {
				x = 1;
			}
		}
		x = j + i;
	}
	return max;
}

// Функция инициализации и вывода массива на экран
void arrayInit(int** array, int N, int K) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K; j++) {
			array[i][j] = rand() % 50 - rand() % 50; // Заполнение массива случайными значениями в диапазоне от -49 до 49 включительно
			cout << array[i][j] << " \t"; // Печать элементов одномерного массива array
		}
		cout << endl;
	}
}