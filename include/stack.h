#ifndef STACK_H
#define STACK_H

#include <aio.h>

#define RESIZE_FACTOR 2

typedef void *generic_t;
typedef void (*destructor_t)(void *);

enum stack_error {
    STACK_SUCCESS = 0,
    STACK_NOMEM,
    STACK_EMPTY
};

/**
 * vector: memory space that contains the stack
 * element_size: size of an object contained in the stack
 * length: number of elements in the stack at each time
 * capacity: maximum number of elements that the stack can hold
 * destroy: destructor for the objects contained in the stack (NULL to borrow)
*/

struct stack {
    generic_t *vector;
    size_t element_size;
    size_t length;
    size_t capacity;
    destructor_t destroy;
};

struct stack *stack_create(size_t element_size, size_t capacity, destructor_t destroy);
void stack_destroy(struct stack *s);

int stack_isfull(struct stack *s);
int stack_isempty(struct stack *s);
int stack_logresize(struct stack *s);

int stack_push(struct stack *s, generic_t element);
generic_t stack_pop(struct stack *s);

generic_t *stack_index(struct stack *s, size_t index);

enum stack_error stack_get_errno();

#endif