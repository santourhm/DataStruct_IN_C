#include "list.h"

// Function to print an integer
void print_int(void* data, FILE* fp) {
    int* int_data = (int*)data;
    fprintf(fp, "%d ", *int_data);
}

// Function to delete an integer (free memory)
void* delete_int(void* data) {
    free(data);  // Free the allocated memory for the integer
    return NULL;
}

// Function to compare two integers (for searching)
int compare_int(void* a, void* b) {
    int* int_a = (int*)a;
    int* int_b = (int*)b;
    return (*int_a == *int_b);
}

// A simple visiting function to print the node value and a custom message
void simple_visitor(void* data, void* param) {
    int* int_data = (int*)data;
    char* msg = (char*)param;
    printf("%s: %d\n", msg, *int_data);
}

// Execute a function on each node's value (used in list_visit)
int exec_on_value(void* data, void* param) {
    int* int_data = (int*)data;
    int* stop_val = (int*)param;

    printf("Value: %d\n", *int_data);
    return (*int_data == *stop_val);  // Stop if the value matches stop_val
}

// Optionally execute a function on each link (used in list_visit)
int exec_on_link(list_t l, void* param) {
    // For demonstration, we just return 0 to continue traversal
    return 0;
}

int main() {
    // Create a new list with functions to print, delete, and compare integers
    list_t my_list = list_new(print_int, delete_int, compare_int);

    // Check if the list is empty
    if (list_is_empty(my_list)) {
        printf("List is empty!\n");
    }

    // Add some integers to the list
    for (int i = 1; i <= 5; i++) {
        int* value = (int*)malloc(sizeof(int));
        *value = i;
        my_list = list_add_first(value, my_list);
    }

    // Print the list
    printf("List after adding elements: ");
    list_printf(my_list);

    // Remove the first element
    my_list = list_del_first(my_list);
    printf("List after removing first element: ");
    list_printf(my_list);

    // Add element to the end of the list
    int* last_value = (int*)malloc(sizeof(int));
    *last_value = 10;
    my_list = list_add_last(last_value, my_list);
    printf("List after adding element to the end: ");
    list_printf(my_list);

    // Search for an element
    int search_value = 3;
    link_t found = list_find(&search_value, my_list);
    if (found) {
        printf("Element %d found in the list.\n", search_value);
    } else {
        printf("Element %d not found in the list.\n", search_value);
    }

    // Remove an element
    int remove_value = 2;
    my_list = list_remove(&remove_value, my_list);
    printf("List after removing element %d: ", remove_value);
    list_printf(my_list);

    // Get the length of the list
    printf("Length of the list: %lu\n", list_length(my_list));

    // Visit the list using simple visitor
    char* visitor_msg = "Visiting";
    list_simple_visit(my_list, simple_visitor, visitor_msg);

    // Use the more complex list visitor
    int stop_value = 4;
    list_visit(my_list, exec_on_value, exec_on_link, &stop_value);

    // Delete the list
    my_list = list_delete(my_list);

    return 0;
}
