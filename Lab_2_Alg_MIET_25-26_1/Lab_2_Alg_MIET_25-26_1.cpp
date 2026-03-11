#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdio>//костыль для проверки
#include <iomanip>

// =========================================================================
// Для задания 3: Функция сортировки вставками (insertion sort)
// =========================================================================
void insertion_sort_1(std::vector<int>& arr) {//сравнение ключа с j (элемент сразу слева)
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        // Сдвиг элементов, которые больше key, на 1 позицию вперед
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; //итерация
    }
}

int main() {
    // Для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");

    // =========================================================================
    // ЗАДАНИЕ 1: Работа с векторами
    // =========================================================================
    std::cout << "--- ЗАДАНИЕ 1: Работа с векторами ---\n";

    // 1. Объявление вектора (дин массив)
    std::vector<int> my_vector;

    // 2. Добавление элементов в конец
    for (int i = 1; i <= 5; ++i) {
        my_vector.push_back(i * 10); // Векторы: 10, 20, 30, 40, 50
    }

    // 3. Вставка элемента '15' по второму индексу (спросить про тупость с begin-ом!!!)
    my_vector.insert(my_vector.begin() + 1, 15);

    // 4. Удаление 3-го элемента
    my_vector.erase(my_vector.begin() + 2);

    std::cout << "Вектор после вставки и удаления: ";

    // 5. Применение алгоритма for_each для вывода
    std::for_each(my_vector.begin(), my_vector.end(), [](int n) {std::cout << n << " ";}); //lambda f
    std::cout << "\n";

    // 6. Применение алгоритма random_shuffle 
    // (спросить почему в C++17 и выше он удален!!!) 
    std::random_shuffle(my_vector.begin(), my_vector.end());

    std::cout << "Вектор после random_shuffle: ";
    std::for_each(my_vector.begin(), my_vector.end(), [](int n) { std::cout << n << " "; });//lambda f
    std::cout << "\n\n";


    // =========================================================================
    // ЗАДАНИЕ 2: Сравнение printf и std::cout
    // =========================================================================
    std::cout << "--- Выполняется вывод 10 000 элементов... ---\n";
    // ВНИМАНИЕ: все НОРМАЛЬНО (сказать)
    // Таблицы с результатами в конце вывода

    const int ITERS = 10000;
    long long time_printf[4]; // 0:char, 1:int, 2:double, 3:string
    long long time_cout[4];

    char c_val = 'X';
    int i_val = 42;
    double d_val = 3.14159;
    const char* s_val = "PKIMS RULEZ";

    // --- Измерение времени работы (ИВР) printf ---
    auto start = std::chrono::high_resolution_clock::now();                                     //старт секундомера (регистрация точки во времени)
    for (int i = 0; i < ITERS; ++i) printf("%c ", c_val);                                       //цикл типа
    auto end = std::chrono::high_resolution_clock::now();                                       //остановка секундомера
    time_printf[0] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();//измерение промежутка, мкс

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERS; ++i) printf("%d ", i_val);
    end = std::chrono::high_resolution_clock::now();
    time_printf[1] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERS; ++i) printf("%f ", d_val);
    end = std::chrono::high_resolution_clock::now();
    time_printf[2] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERS; ++i) printf("%s ", s_val);
    end = std::chrono::high_resolution_clock::now();
    time_printf[3] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    //ИВР std::cout (времени вывода)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERS; ++i) std::cout << c_val << " ";
    end = std::chrono::high_resolution_clock::now();
    time_cout[0] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERS; ++i) std::cout << i_val << " ";
    end = std::chrono::high_resolution_clock::now();
    time_cout[1] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERS; ++i) std::cout << d_val << " ";
    end = std::chrono::high_resolution_clock::now();
    time_cout[2] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERS; ++i) std::cout << s_val << " ";
    end = std::chrono::high_resolution_clock::now();
    time_cout[3] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "\n\n";


    // =========================================================================
    // ЗАДАНИЕ 3: Сравнение сортировок
    // =========================================================================
    std::cout << "--- Выполняется сравнение сортировок... ---\n";

    int sizes[] = { 3, 5, 10 };
    long long time_insertion[3];
    long long time_stdsort[3];

    for (int k = 0; k < 3; ++k) {
        int size = sizes[k];
        std::vector<int> v_orig(size);
        // Заполнение случайными числами в обратном порядке (худший случай для наибольшей работы)
        for (int i = 0; i < size; ++i) v_orig[i] = size - i;

        // Тестирование сортировки вставками
        std::vector<int> v_ins = v_orig;
        start = std::chrono::high_resolution_clock::now();
        insertion_sort_1(v_ins);
        end = std::chrono::high_resolution_clock::now();
        time_insertion[k] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();//слишком быстрая работа, поэтому лучше нс

        // Тестирование std::sort
        std::vector<int> v_std = v_orig;
        start = std::chrono::high_resolution_clock::now();
        std::sort(v_std.begin(), v_std.end());
        end = std::chrono::high_resolution_clock::now();
        time_stdsort[k] = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }


    // =========================================================================
    // ВЫВОД (ТАБЛИЦЫ)
    // =========================================================================
    std::cout << "===============================================================\n";
    std::cout << "Время вывода 10 000 элементов (в микросекундах)\n";
    std::cout << "---------------------------------------------------------------\n";
    std::cout << std::left << std::setw(15) << ""//(сказать про setw)
        << std::setw(10) << "char"
        << std::setw(10) << "int"
        << std::setw(10) << "double"
        << std::setw(18) << "\"PKIMS RULEZ\"" << "\n";

    std::cout << std::left << std::setw(15) << "printf"
        << std::setw(10) << time_printf[0]
        << std::setw(10) << time_printf[1]
        << std::setw(10) << time_printf[2]
        << std::setw(18) << time_printf[3] << "\n";

    std::cout << std::left << std::setw(15) << "std::cout"
        << std::setw(10) << time_cout[0]
        << std::setw(10) << time_cout[1]
        << std::setw(10) << time_cout[2]
        << std::setw(18) << time_cout[3] << "\n";
    std::cout << "===============================================================\n\n";

    std::cout << "===============================================================\n";
    std::cout << "Сравнение сортировок (в наносекундах)\n";
    std::cout << "---------------------------------------------------------------\n";
    std::cout << std::left << std::setw(20) << ""
        << std::setw(15) << "3 элемента"
        << std::setw(15) << "5 элементов"
        << std::setw(15) << "10 элементов" << "\n";

    std::cout << std::left << std::setw(20) << "insertion_sort_1"
        << std::setw(15) << time_insertion[0]
        << std::setw(15) << time_insertion[1]
        << std::setw(15) << time_insertion[2] << "\n";

    std::cout << std::left << std::setw(20) << "std::sort"
        << std::setw(15) << time_stdsort[0]
        << std::setw(15) << time_stdsort[1]
        << std::setw(15) << time_stdsort[2] << "\n";
    std::cout << "===============================================================\n";

    return 0;
}