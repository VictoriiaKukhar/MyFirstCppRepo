#include "price.h"
#include <stdio.h>

void add(Price& a, Price& b) {

    a.gryvnia += b.gryvnia;
    a.kopiyky += b.kopiyky;

    if (a.kopiyky >= 100) {
        a.gryvnia += a.kopiyky / 100;
        a.kopiyky %= 100;
    }
}

void multiply(Price& a, int n) {

    int totalKop =
        (a.gryvnia * 100 + a.kopiyky) * n;

    a.gryvnia = totalKop / 100;
    a.kopiyky = totalKop % 100;
}

void roundPrice(Price& a) {

    int remainder = a.kopiyky % 10;

    if (remainder < 5) {
        a.kopiyky -= remainder;
    }
    else {
        a.kopiyky += (10 - remainder);

        if (a.kopiyky >= 100) {
            a.gryvnia++;
            a.kopiyky -= 100;
        }
    }
}

void printPrice(Price& p) {

    printf("%d грн %02d коп.\n",
           p.gryvnia,
           p.kopiyky);
}

void processFile(FILE* file) {

    char name[50];
    int h;
    short k;
    int count;

    Price total = {0, 0};

    while (fscanf(file,
        "%49s %d %hd %d",
        name,
        &h,
        &k,
        &count) == 4) {

        Price price = {h, k};

        printf("Продукт: %s\n", name);

        printf("Ціна: %d грн %d копійок\n",
               h,
               k);

        printf("Кількість: %d\n\n",
               count);

        multiply(price, count);

        add(total, price);
    }

    fclose(file);

    printf("Загальна сума: ");
    printPrice(total);

    Price rounded = total;

    roundPrice(rounded);

    printf("Сума після округлення: ");
    printPrice(rounded);
}