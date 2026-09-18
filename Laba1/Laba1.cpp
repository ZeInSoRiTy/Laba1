#include <iostream>
#include <math.h>
#include <string>
#include <format>
#include <windows.h>
#include <regex>

enum class ValidationError {
    None,
    EmptyInput,
    InvalidChars,
    LeadingZeros,
    EmptyDot,
    NegativeZero,
    PositiveZero
};

ValidationError validate(const std::string& input) {
    if (input.empty()) {
        return ValidationError::EmptyInput;
    }
    if (input.back() == '.') {
        return ValidationError::EmptyDot;
    }
    if (!std::regex_match(input, std::regex(R"(^[+-]?\d*[.,]?\d*$)"))) {
        return ValidationError::InvalidChars;
    }
    if (std::regex_match(input, std::regex(R"(^-0+([.,].0+)?$)"))) {
        return ValidationError::NegativeZero;
    }
    if (std::regex_match(input, std::regex(R"(^\+0+([.,].0+)?$)"))) {
        return ValidationError::PositiveZero;
    }
    if (std::regex_match(input, std::regex(R"(^[+-]?0\d+([.,]\d+)?$)"))) {
        return ValidationError::LeadingZeros;
    }
    if (!std::regex_match(input, std::regex(R"(^[+-]?(0|[1-9]\d*)([.,]\d+)?$)"))) {
        return ValidationError::InvalidChars;
    }

    return ValidationError::None;
}

std::string returnValidation(const std::string& input) {
    switch (validate(input)) {
        case ValidationError::None:
            return "Valid";
        case ValidationError::EmptyInput:
            return "Введена пустая строка. Пожалуйста, не будьте динозавром и введите число в формате <число.дробь> или 0";
        case ValidationError::InvalidChars:
            return "Во вводе присутствуют буквы, специальные символы, пустые пробелы или ввод в целом некорректен. Пожалуйста, не будьте динозавром и введите число в формате <число.дробь> или 0";
        case ValidationError::EmptyDot:
            return "Число не может оканчиваться на точку. Пожалуйста, не будьте динозавром и введите число в формате <число.дробь> или 0";
        case ValidationError::NegativeZero:
            return "Введен отрицательный ноль, это недопустимо. Пожалуйста, не будьте динозавром и введите число в формате <число.дробь> или 0";
        case ValidationError::PositiveZero:
            return "Введен положительный ноль, это недопустимо. Пожалуйста, не будьте динозавром и введите число в формате <число.дробь> или 0";
        case ValidationError::LeadingZeros:
            return "Введено число с ведущими нулями. Пожалуйста, не будьте динозавром и введите число в формате <число.дробь> или 0";
    }
    return "Неизвестная ошибка. Поздравляю, вы динозавр";
}

float F(float x, float a) // Функция F(x)
{
    return ( (1 / ((x / 8) + 2 * std::pow(std::cos(x), a))) );
}

int main()
{
    setlocale(LC_ALL, "ru");
    std::setlocale(LC_NUMERIC, "C");

    double a = 0;
    std::string input;


    int inputLen = 0;

    std::cin.clear();
        

    while (true) {

        std::cout << "Введите значение параметра a: ";
        if (!std::getline(std::cin, input)) {
            break;
        }

        std::string validResult = returnValidation(input);

        if (validResult != "Valid") {
            std::cout << validResult << std::endl << std::endl;
            continue;
        }

        std::replace(input.begin(), input.end(), ',', '.');

        a = std::stod(input);

        const double mn_n = -std::pow(10, 6);
        const double mx_n = -std::pow(10, -6);
        const double mn_p = std::pow(10, -6);
        const double mx_p = std::pow(10, 6);

        if (!((a >= mn_n && a <= mx_n) || (a >= mn_p && a <= mx_p) || a == 0)) // проверка, что a находится в заданном диапазоне
        {
            std::cout << "a находится за границами заданного диапазона" << std::endl << std::endl;
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

    int c = 1;

    std::cout << std::string(43 + inputLen, '—') << std::endl; // Верхний отступ от шапки в размере 41+n дефисов
    std::cout << std::format("| {:>5} | {:>9} | {:>{}} | {:>9} |", "№п.п", "X", "A", inputLen + 7, "Y") << std::endl; // Форматирование шапки таблицы и значений
    std::cout << std::string(43 + inputLen, '—') << std::endl; // Нижний отступ от шапки в размере 41+n дефисов

    for (float x = -12; x <= 13; x += 2.5) {
        float y = F(x, a);

        std::string toInsert;

        if (!std::isfinite(y)) {
            toInsert = "—N/A-";
        }
        else
        {
            toInsert = std::format("{:.6f}", y);
        }

        std::string result = std::format("| {:>5} | {:>9.5f} | {:>{}.6f} | {:>9} |", c, x, a, inputLen + 7, toInsert); // Форматирование каждой ячейки таблицы

        std::cout << result << std::endl;
        std::cout << std::string(43 + inputLen, '—') << std::endl; // Очередной отступ из 41+n дефисов
        c++;
    }

    return 0;
}