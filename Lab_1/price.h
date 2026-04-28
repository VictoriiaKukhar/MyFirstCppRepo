#pragma once
#include <stdio.h>

struct Price {
    int gryvnia;
    short int kopiyky;
};

void add(Price& a, Price& b);
void multiply(Price& a, int n);
void roundPrice(Price& a);
void printPrice(Price& p);
void processFile(FILE* f);