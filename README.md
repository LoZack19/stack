# Stack Library Documentation

## Overview
This library provides a generic stack data structure. The stack can hold elements of any type and size.

## Data Types
- `generic_t`: A type representing a generic element that can be stored in the stack.
- `destructor_t`: A function pointer type for a destructor function for the elements stored in the stack.

## Enumerations
- `stack_error`: An enumeration of possible errors that can occur during stack operations.

## Structures
- `struct stack`: The main stack structure, which includes:
  - `vector`: The memory space that contains the stack.
  - `element_size`: The size of an object contained in the stack.
  - `length`: The number of elements in the stack at each time.
  - `capacity`: The maximum number of elements that the stack can hold.
  - `destroy`: A destructor for the objects contained in the stack.

## Functions
- `stack_create(size_t element_size, size_t capacity, destructor_t destroy)`: Creates a new stack with the specified element size, capacity, and destructor function.
- `stack_destroy(struct stack *s)`: Destroys the stack, freeing its memory.
- `stack_isfull(struct stack *s)`: Checks if the stack is full.
- `stack_isempty(struct stack *s)`: Checks if the stack is empty.
- `stack_logresize(struct stack *s)`: Resizes the stack.
- `stack_push(struct stack *s, generic_t element)`: Pushes an element onto the stack.
- `stack_pop(struct stack *s)`: Pops an element from the stack.
- `stack_index(struct stack *s, size_t index)`: Returns a pointer to the element at the specified index in the stack.
- `stack_get_errno()`: Returns the last error that occurred during a stack operation.

## Example of usage

Here is an example of usage for simple C datatypes which fit into a `void *`:

```c
#include <stdio.h>
#include "stack.h"

int main() {
    // Create a stack for int elements
    struct stack *s = stack_create(sizeof(int), 10, NULL);

    // Push some elements onto the stack
    for (int i = 0; i < 10; i++) {
        stack_push(s, (void *)(intptr_t)i);
    }

    // Pop all elements from the stack and print them
    while (!stack_isempty(s)) {
        int element = (int)(intptr_t)stack_pop(s);
        printf("%d\n", element);
    }

    // Destroy the stack
    stack_destroy(s);

    return 0;
}

```

Here is an example of usage for ojects which require to be freed. The elements destructor is specified in the stack costructor, which implicitly tells the stack that it owns them.

```c
#include <stdio.h>
#include "stack.h"

int main() {
    // Create a stack for int elements
    struct stack *s = stack_create(sizeof(int), 10, free);

    // Push some elements onto the stack
    for (int i = 0; i < 10; i++) {
        int *element = malloc(sizeof(int));
        *element = i;
        stack_push(s, element);
    }

    // Pop all elements from the stack and print them
    while (!stack_isempty(s)) {
        int *element = stack_pop(s);
        printf("%d\n", *element);
        free(element);
    }

    // Destroy the stack
    stack_destroy(s);

    return 0;
}
```