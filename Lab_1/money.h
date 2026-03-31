#ifndef MONEY_H
#define MONEY_H

// Структура для представлення грошей (гривні та копійки)
struct Money {
    int grn;        // гривні
    short int kop;  // копійки
};

// Прототипи функцій для роботи з Money
Money addMoney(Money a, Money b);           // додавання двох сум
Money multiplyMoney(Money price, int count); // множення ціни на кількість
Money roundMoney(Money m);                   // заокруглення копійок
void printMoney(Money m);                     // виведення на екран

#endif