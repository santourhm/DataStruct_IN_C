#include "lifo.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Create a new stack
stack_t stacks_new(unsigned int n, void (*print_data)(void*, FILE*), void* (*delete_data)(void*), int (*equal_data)(void*, void*)) {
    stack_t stack = malloc(sizeof(*stack));
    if (stack == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for stack\n");
        return NULL;
    }
    
    stack->data = malloc(n * sizeof(*stack->data));
    if (stack->data == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for stack data\n");
        free(stack);  // Free stack memory if data allocation fails
        return NULL;
    }
    
    stack->max_size = n;
    stack->actual_size = 0;
    stack->delete_data = delete_data;
    stack->equal_data = equal_data;
    stack->fprintf_data = print_data;
    
    return stack;
}

// Push element onto the stack
stack_t stacks_push(void* e, stack_t table) {
    assert(table != NULL);

    // Handle resizing if needed
    if (table->actual_size >= table->max_size) {
        table->max_size *= 2;  // Double the stack size
        table->data = realloc(table->data, table->max_size * sizeof(*table->data));
        if (table->data == NULL) {
            fprintf(stderr, "Error: Failed to reallocate memory for stack\n");
            return NULL;
        }
    }
    
    table->data[table->actual_size] = e;
    table->actual_size++;
    
    return table;
}

// Pop element from the stack
void* stacks_pop(stack_t table) {
    assert(table != NULL);
    assert(table->actual_size > 0);  // Make sure the stack is not empty
    
    void* popped_value = table->data[table->actual_size - 1];
    table->actual_size--;
    return popped_value;
}

// Peek at the top element of the stack
void* stacks_peek(stack_t table) {
    assert(table != NULL);
    assert(table->actual_size > 0);  // Ensure the stack is not empty
    
    return table->data[table->actual_size - 1];
}

// Check if the stack is empty
int stacks_is_empty(stack_t l) {
    return (l == NULL || l->actual_size == 0);
}

// Print the stack
void stacks_printf(stack_t table) {
    stacks_fprintf(table, stdout);
}

// Print the stack to a file pointer
void stacks_fprintf(stack_t table, FILE* fp) {
    assert(table != NULL);
    
    if (stacks_is_empty(table)) {
        fprintf(fp, "The stack is empty\n");
        return;
    }
    
    for (unsigned int i = 0; i < table->actual_size; i++) {
        table->fprintf_data(table->data[i], fp);
    }
    fprintf(fp, "\n");
}

// Delete the stack and free memory
stack_t stacks_delete(stack_t table) {
    assert(table != NULL);

    for (unsigned int i = 0; i < table->actual_size; i++) {
        table->delete_data(table->data[i]);  // Free each element's memory
    }

    free(table->data);  // Free the data array
    free(table);  // Free the stack structure
    
    return NULL;
}
