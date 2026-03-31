#include "money.h"
#include <stdio.h>

// Додавання двох грошових сум
Money addMoney(Money a, Money b) {
    Money result;
    result.grn = a.grn + b.grn;
    result.kop = a.kop + b.kop;
    
    // Якщо копійок більше 99, переводимо в гривні
    if (result.kop >= 100) {
        result.grn += result.kop / 100;
        result.kop = result.kop % 100;
    }
    
    return result;
}

// Множення ціни на кількість
Money multiplyMoney(Money price, int count) {
    Money result;
    // Переводимо все в копійки, множимо, потім конвертуємо назад
    int totalKop = (price.grn * 100 + price.kop) * count;
    
    result.grn = totalKop / 100;
    result.kop = totalKop % 100;
    
    return result;
}

// Заокруглення копійок згідно з завданням
// (монети до 10 копійок виведені з обігу)
Money roundMoney(Money m) {
    Money result = m;
    
    // Правило: якщо копійок < 10 - відкидаємо
    //          якщо копійок >= 10 - округлюємо до 1 гривні
    if (result.kop < 10) {
        result.kop = 0;  // відкидаємо дрібні монети
    } else {
        // Додаємо 1 гривню, копійки обнуляємо
        result.grn += 1;
        result.kop = 0;
    }
    
    return result;
}

// Виведення грошової суми на екран
void printMoney(Money m) {
    // Виводимо копійки завжди двома цифрами
    printf("%d UAH %02d kop", m.grn, m.kop);
}