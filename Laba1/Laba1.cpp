// Laba1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <string>
#include <format>
#include <windows.h>

float F(float x, float a) // Функция F(x)
{
    return ( (1 / ((x / 8) + 2 * std::pow(std::cos(x), a))) );
}

int main()
{
    setlocale(LC_ALL, "ru");
    std::setlocale(LC_NUMERIC, "C");

    float a = 0;
    std::string input;

    std::cin.clear();
        

    while (true) {

        std::cin >> input;

        try { // Кэтчер исключений
            a = std::stof(input);

            const double mn_n = -std::pow(10, 6);
            const double mx_n = -std::pow(10, -6);
            const double mn_p = std::pow(10, -6);
            const double mx_p = std::pow(10, 6);

            if ( !( (a >= mn_n && a <= mx_n ) || (a >= mn_p && a <= mx_p) || a == 0) ) // проверка, что a находится в заданном диапазоне
            {
                std::cout << "a находится за границами заданного диапазона" << std::endl;
            }
            else
            {
                break;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Не число." << std::endl;
        }
        catch (const std::out_of_range& e) {
            std::cout << "Слишком большое или слишком маленькое число для float." << std::endl;

        }


    }

    int c = 1;

    std::cout << std::string(43, '—') << std::endl; // Верхний отступ от шапки в размере 43 дефисов
    std::cout << std::format("| {:>5} | {:>9} | {:>8} | {:>8} |", "№п.п", "X", "A", "Y") << std::endl; // Форматирование шапки таблицы и значений
    std::cout << std::string(43, '—') << std::endl; // Нижний отступ от шапки в размере 43 дефисов

    for (float x = -12; x <= 13; x += 2.5) {
        float y = F(x, a);

        std::string toInsert;

        if (std::isnan(y)) {
            toInsert = "—N/A-";
        }
        else
        {
            toInsert = std::format("{:.5f}", y);
        }

        std::string result = std::format("| {:>5} | {:>9.5f} | {:>8.5f} | {:>8} |", c, x, a, toInsert); // Форматирование каждой ячейки таблицы

        std::cout << result << std::endl;
        std::cout << std::string(43, '—') << std::endl; // Очередной отступ из 43 дефисов
        c++;
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
