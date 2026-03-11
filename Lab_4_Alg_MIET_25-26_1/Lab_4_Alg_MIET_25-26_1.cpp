#include <iostream>
#include <conio.h> //перехват нажатия клавиш

using namespace std;

//Размеры дискретного рабочего поля (ДРП) (можнопоиграть)
const int SIZE = 24;

//Функция для вывода поля на экран//

void printField(int field[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (field[i][j] == 1) {
                cout << "& "; //Живая клетка
            }
            else {
                cout << ". "; //Мёртвая клетка
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

int countLiveNeighbors(int field[SIZE][SIZE], int row, int col) {//f подсчета живых соседей (с учетом зацикленности поля размером SIZExSIZE)
    int count = 0;

    //Проходит по 8 соседям (от -1 до +1 по строкам и столбцам)
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;//Пропускает саму себя

            //Условие зацикленности поля (по сути тороидальность, где верхний край соединен с нижним, а левый с правым)(!)
            //Добавляем SIZE перед взятием остатка, чтобы избежать отрицательных чисел //(сказать про проблему остатка от отрицательного числа в С++) 
            //Например, если row = 0, а i = -1, то (0 - 1 + 24) % 24 = 23 (это будет уже последняя строка)
            int r = (row + i + SIZE) % SIZE;
            int c = (col + j + SIZE) % SIZE;

            count += field[r][c]; //Если клетка жива (1), то count увеличится
        }
    }
    return count;
}

void nextGeneration(int field[SIZE][SIZE]) {//f вычисления следующего поколения
    //Создаем ВРЕМЕННОЕ поле для нового поколения (иначе, если менять текущее поле сразу, испортятся расчеты для соседних клеток)(!)
    int nextField[SIZE][SIZE] = { 0 };

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            int neighbors = countLiveNeighbors(field, i, j);

            if (field[i][j] == 1) { //Если клетка ЖИВА
                //Правило 2 и 3: выживает, если 2 или 3 соседа
                if (neighbors == 2 || neighbors == 3) {
                    nextField[i][j] = 1;
                }
                else {
                    nextField[i][j] = 0; //Иначе умирает от одиночества или перенаселения
                }
            }
            else { //Если клетка МЕРТВА
                //Правило 1: оживает, если ровно 3 соседа
                if (neighbors == 3) {
                    nextField[i][j] = 1;
                }
            }
        }
    }

    // Копируем новое поколение обратно в основное поле
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            field[i][j] = nextField[i][j];
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");//Локализация кириллицы

    //Инициализация поля нулями
    int drp[SIZE][SIZE] = { 0 };

    //Пример интересной начальной конфигурации (можнопоиграть)
    //1. Глайдер (планер) - фигура, которая ползет по диагонали
    drp[1][2] = 1;
    drp[2][3] = 1;
    drp[3][1] = 1;
    drp[3][2] = 1;
    drp[3][3] = 1;

    //2. Мигалка (осциллятор) - линия из трех клеток
    drp[10][10] = 1;
    drp[10][11] = 1;
    drp[10][12] = 1;

    //Пункт 1: Вывод начального состояния
    cout << "--- Исходное состояние ДРП ---\n";
    printField(drp);

    //Пункт 2: Вывод после одной итерации
    cout << "--- Состояние после 1-й итерации ---\n";
    nextGeneration(drp);
    printField(drp);

    //Пункт 3: Интерактивный цикл
    cout << "Нажимайте любую клавишу для следующего шага.\n";
    cout << "Для выхода нажмите Escape (Esc)...\n";

    while (true) {
        int key = _getch(); //Ожидание ввода

        if (key == 27) {//ASCII(27) = Escape
            break;
        }

        //Вычисение следующей эволюции
        nextGeneration(drp);

        system("cls");

        printField(drp);
    }

    return 0;
}