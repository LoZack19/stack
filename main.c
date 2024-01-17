#include <stdio.h>
#include <stdlib.h>
#include <include/stack.h>

#define STACK_SIZE 200

int main() {
    struct stack *s = stack_create(sizeof(int), 1, free);
    if (s == NULL) {
        printf("Failed to create stack.\n");
        return 1;
    }

    for (int i = 0; i < STACK_SIZE; i++) {
        int *element = malloc(sizeof(*element));
        *element = i;
        if (stack_push(s, element) < 0) {
            printf("Failed to push element onto stack.\n");
            free(element);
            stack_destroy(s);
            return 1;
        }
    }

    while (!stack_isempty(s)) {
        int *element = (int *)stack_pop(s);
        if (element == NULL) {
            printf("Failed to pop element from stack.\n");
            return 1;
        }
        printf("Popped element: %d\n", *element);
        free(element);
    }

    stack_destroy(s);
    return 0;
}
