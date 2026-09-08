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
    int inputLen = 0;

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
                for (char c : std::to_string(a))
                {
                    if (c == '-') continue;
                    if (c == '.') break;
                    inputLen++;
                }

                break;
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Не число." << std::endl;
        }


    }

    int c = 1;

    std::cout << inputLen << std::endl;
    std::cout << std::string(41 + inputLen, '—') << std::endl; // Верхний отступ от шапки в размере 43 дефисов
    std::cout << std::format("| {:>5} | {:>9} | {:>{}} | {:>8} |", "№п.п", "X", "A", inputLen + 6, "Y") << std::endl; // Форматирование шапки таблицы и значений
    std::cout << std::string(41 + inputLen, '—') << std::endl; // Нижний отступ от шапки в размере 43 дефисов

    for (float x = -12; x <= 13; x += 2.5) {
        float y = F(x, a);

        std::string toInsert;

        if (!std::isfinite(y)) {
            toInsert = "—N/A-";
        }
        else
        {
            toInsert = std::format("{:.5f}", y);
        }

        std::string result = std::format("| {:>5} | {:>9.5f} | {:>{}.5f} | {:>8} |", c, x, a, inputLen + 6, toInsert); // Форматирование каждой ячейки таблицы

        std::cout << result << std::endl;
        std::cout << std::string(41 + inputLen, '—') << std::endl; // Очередной отступ из 43 дефисов
        c++;
    }

    return 0;
}