#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "price.h"

int main() {

    // Встановлюємо UTF-8 для Windows
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // Українська локаль
    setlocale(LC_ALL, ".UTF-8");

    FILE* my_file;

    fopen_s(&my_file, "input.txt", "r");

    if (my_file == NULL) {
        printf("Error opening input.txt\n");
        return 1;
    }

    processFile(my_file);

    return 0;
    
}