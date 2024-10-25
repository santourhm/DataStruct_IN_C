#include "table.h"
#include <stdio.h>

// Function to test all functionalities of the table
void test_new_table(int n) {
    printf("==> Starting new table test\n");
    
    // Create a new table
    table_t tab = new_table(n);
    if (tab == NULL) {
        printf("<== Test failed: Unable to create table.\n");
        return;
    } else {
        printf("<== Table created successfully.\n");
    }

    // Fill the table with initial values
    tab->data[0] = 3.5;
    tab->data[1] = 2.1;
    tab->data[2] = -1.2;
    tab->data[3] = 4.8;
    tab->data[4] = 7.4;

    // Print the current table
    printf("Initial table:\n");
    printf_table(tab);

    // Test the min_table function
    int min_val = min_table(tab);
    printf("The index of the minimum value in the table: %d\n", min_val);

    // Test the max_table function
    int max_val = max_table(tab);
    printf("The index of the maximum value in the table: %d\n", max_val);

    // Append a new value to the table
    if (append_table(10.5, tab)) {
        printf("Value 10.5 appended successfully.\n");
    } else {
        printf("Failed to append value.\n");
    }
    printf("Table after append:\n");
    printf_table(tab);

    // Insert a new value at index 2
    if (insert_at_table(55.0, 2, tab)) {
        printf("Value 55.0 inserted successfully at index 2.\n");
    } else {
        printf("Failed to insert value at index 2.\n");
    }
    printf("Table after insertion at index 2:\n");
    printf_table(tab);

    // Remove the value at index 4
    if (remove_at_table(4, tab)) {
        printf("Value at index 4 removed successfully.\n");
    } else {
        printf("Failed to remove value at index 4.\n");
    }
    printf("Table after removal at index 4:\n");
    printf_table(tab);

    // Delete the table and free memory
    tab = delete_table(tab);
    if (tab == NULL) {
        printf("<== Table deleted successfully.\n");
    } else {
        printf("<== Failed to delete the table.\n");
    }
}

int main(void) {
    // Test table creation and functionality with size 5
    test_new_table(5);

    return 0;
}
