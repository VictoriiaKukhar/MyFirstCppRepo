#include "money.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Set console to support UTF-8 (for Windows)
    system("chcp 65001 > nul");
    
    FILE* file = NULL;
    errno_t err;
    
    // Open file for reading
    err = fopen_s(&file, "prices.txt", "r");
    
    if (err != 0 || file == NULL) {
        printf("Error opening file prices.txt!\n");
        printf("Make sure the file exists in the program folder.\n");
        system("pause");
        return 1;
    }
    
    Money total = {0, 0};  // Total purchase amount
    Money price;           // Item price
    int quantity;          // Item quantity
    int itemCount = 0;     // Item counter
    
    printf("=== PURCHASE TOTAL CALCULATION ===\n\n");
    
    // Read data from file
    // Format: each line contains three numbers: hryvnias kopiykas quantity
    while (fscanf_s(file, "%d %hd %d", &price.grn, &price.kop, &quantity) == 3) {
        itemCount++;
        
        // Display item information
        printf("Item #%d:\n", itemCount);
        printf("  Price: ");
        printMoney(price);
        printf("\n  Quantity: %d pcs\n", quantity);
        
        // Calculate cost for this item
        Money itemTotal = multiplyMoney(price, quantity);
        printf("  Cost: ");
        printMoney(itemTotal);
        printf("\n\n");
        
        // Add to total amount
        total = addMoney(total, itemTotal);
    }
    
    fclose(file);
    
    if (itemCount == 0) {
        printf("File is empty or has incorrect format!\n");
        printf("The file should contain lines with three numbers: hryvnias kopiykas quantity\n");
    } else {
        // Display results
        printf("=== RESULTS ===\n");
        printf("Total amount: ");
        printMoney(total);
        printf("\n");
        
        // Round the total
        Money rounded = roundMoney(total);
        printf("Amount to pay (after rounding): ");
        printMoney(rounded);
        printf("\n");
    }
    
    printf("\n");
    system("pause");
    return 0;
} 