#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Функция-интерпретатор диалекта Brainfuck//->
void executeBrainfuck(const string& code) {
    char memory[10] = { 0 }; // Память ВМ - 10 байтов
    int ip = 0; //Указатель на текущую ячейку

    for (char cmd : code) {
        switch (cmd) {
        case '+': //Увеличить значение в текущей ячейке
            memory[ip]++;
            break;
        case '-': //Уменьшить значение в текущей ячейке
            memory[ip]--;
            break;
        case '<': //Перейти в предыдущую ячейку (если возможно)
            if (ip > 0) ip--;
            break;
        case '>': //Перейти в следующую ячейку (если возможно)
            if (ip < 9) ip++;
            break;
        case '[': //Проинициализировать значение в ячейке числом 120
            memory[ip] = 120; //ASCII(120) = 'x'
            break;
        case ']': //Проинициализировать значение в ячейке числом 45
            memory[ip] = 45; //ASCII(45) = '-'
            break;
        case '!': //Вывести на экран текущую ячейку, перейти в право //(видимо защита от выхода за границы 10 байтов)(?)
            cout << memory[ip];
            if (ip < 9) ip++;  
            break;
        case '?': //Скопировать значение текущей ячейки иво все ячейки справа
            //Цикл копирования значения текущей ячейки во все ячейки справа
            for (int i = ip + 1; i < 10; ++i) {
                memory[i] = memory[ip];
            }
            break;
        }
    }
    cout << endl;
}//<-

int main() {
    setlocale(LC_ALL, "Russian"); // Для корректного вывода кириллицы в консоль

    //ПУНКТ 1: Вывод таблицы ASCII//

    cout << "--- ТАБЛИЦА ASCII ---\n";
    //Начало с 32, так как символы от 0 до 31 - управляющие 
    for (int i = 32; i < 256; ++i) {
        cout << i << ":" << (char)i << "\t";
        if (i % 8 == 0) cout << "\n";
    }
    cout << "\n\nВНИМАНИЕ: Таблица ASCII ставит в соответствие числовым кодам символы. "
        << "Базовая часть (0-127) содержит латинские буквы, цифры и знаки препинания. "
        << "Расширенная часть (128-255) используется для национальных алфавитов (например, кириллицы), "
        << "поэтому в разных кодировках символы после 127 могут отличаться.\n\n";


    //ПУНКТ 2: Вывод фразы "КАФЕДРА ПКИМС РУЛИТ!"//

    cout << "--- ВЫПОЛНЕНИЕ ПРОГРАММЫ BRAINFUCK ---\n";
    string target = "КАФЕДРА ПКИМС РУЛИТ!";

    //Генерация кода программным методом, чтобы не зависеть от кодировки ОС!
    //Сначала выполняем обязательные команды варианта (это условие лабы):
    //[ (задаст 120) -> ? (скопирует везде) -> > (шаг вправо) -> ] (задаст 45) -> < (шаг влево)
    string generated_code = "[?>]<";
    unsigned char current_val = 120; // Так как мы вернулись в ячейку 0, а там было 120

    //Установление соответствия между комбинациями плюсов и минусов и каждой буквой фразы
    for (size_t i = 0; i < target.length(); ++i) {
        unsigned char target_val = static_cast<unsigned char>(target[i]);

        while (current_val < target_val) { generated_code += "+"; current_val++; }
        while (current_val > target_val) { generated_code += "-"; current_val--; }
        generated_code += "!<"; //Прим.: '!' и '<' эффективны, поэтому 10 байтов достаточно
    }

    cout << "BRAINFUCK-код (КОМАНДЫ: +, -, <, >, [, ], !, ?):\n";
    cout << generated_code << "\n\nРезультат: ";

    executeBrainfuck(generated_code);


    //ПУНКТ 3: Чтение кода из файла//

    cout << "\n--- ЧТЕНИЕ КОДА ИЗ ФАЙЛА ---\n";
    cout << "Введите имя файла (например, test.bf): ";
    string filename;
    cin >> filename;

    ifstream file(filename);
    if (file.is_open()) {
        string file_code = "";
        string line;
        while (getline(file, line)) {
            file_code += line;
        }
        file.close();

        cout << "Считанный код: " << file_code << "\n";
        cout << "Результат выполнения:\n";
        executeBrainfuck(file_code);
    }
    else {
        cout << "ОШИБКА: Не удалось открыть файл '" << filename << "'. Убедитесь, что он создан в папке с программой\n";
    }

    return 0;
}