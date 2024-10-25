#include "lifo.h"
#include "double.h"
#include <stdio.h>
#include <stdint.h>  // Required for intptr_t

int main() {
    // Pile de double
    stack_t l1 = stacks_new(2, double_fprintf, double_delete, double_equal);
    double* pv;

    // Add integers (which will be converted to double) and doubles
    printf("Ajout de 10, 20, 30, 40, 50, 60, 70 : \n");

    // Integers are cast to pointers and passed to double_new
    l1 = stacks_push(double_new((void*)(intptr_t)10), l1);
    l1 = stacks_push(double_new((void*)(intptr_t)20), l1);
    
    // Double values are passed by reference using the address-of operator
    pv = double_new(&(double){30.0});
    l1 = stacks_push(pv, l1);
    
    pv = double_new(&(double){40.0});
    l1 = stacks_push(pv, l1);
    
    l1 = stacks_push(double_new((void*)(intptr_t)50), l1);
    l1 = stacks_push(double_new((void*)(intptr_t)60), l1);
    l1 = stacks_push(double_new((void*)(intptr_t)70), l1);

    // Print the contents of the stack
    stacks_printf(l1);

    // Pop an element from the stack
    pv = stacks_pop(l1);
    printf("Defiler : %lf\n", *pv);

    // Free the popped element after use
    double_delete(pv);

    // Print the stack after popping
    stacks_printf(l1);

    // Pop another element from the stack
    pv = stacks_pop(l1);
    printf("Defiler : %lf\n", *pv);

    // Free the popped element
    double_delete(pv);

    // Print the stack again
    stacks_printf(l1);

    // Clean up the entire stack
    printf("Liberation de la pile\n");
    l1 = stacks_delete(l1);

    return EXIT_SUCCESS;
}
