#include <stdlib.h>
#include <string.h>
#include <include/stack.h>

enum stack_error stack_errno = STACK_SUCCESS;

struct stack *stack_create(size_t element_size, size_t capacity, destructor_t destroy)
{
    struct stack *s;

    s = malloc(sizeof(*s));
    if (!s){
        stack_errno = STACK_NOMEM;
        return NULL;
    }

    s->vector = malloc(capacity*sizeof(*s->vector));
    if (!s->vector) {
        stack_errno = STACK_NOMEM;
        free(s);
        return NULL;
    }

    s->element_size = element_size;
    s->length = 0;
    s->capacity = capacity;
    s->destroy = destroy;

    return s;
}

void stack_destroy(struct stack *s)
{
    if (s->destroy) {
        for (size_t i = 0; i < s->length; i++)
            s->destroy(s->vector[i]);
    }

    free(s->vector);
    free(s);
}

int stack_isfull(struct stack *s)
{
    return s->length >= s->capacity;
}

int stack_isempty(struct stack *s)
{
    return s->length <= 0;
}

int stack_logresize(struct stack *s)
{
    generic_t *temp;

    temp = realloc(s->vector, s->capacity * RESIZE_FACTOR * sizeof(*temp));
    if (!temp) {
        stack_errno = STACK_NOMEM;
        return -1;
    }

    s->vector = temp;
    s->capacity *= RESIZE_FACTOR;
    return 0;
}

int stack_push(struct stack *s, generic_t element)
{
    int err;

    if (stack_isfull(s)) {
        err = stack_logresize(s);
        if (err < 0)
            return err;
    }

    s->vector[s->length] = element;
    s->length += 1;

    return 0;
}

generic_t stack_pop(struct stack *s)
{
    generic_t element;

    if (stack_isempty(s)) {
        stack_errno = STACK_EMPTY;
        return NULL;
    }

    s->length -= 1;
    element = s->vector[s->length];

    return element;
}

generic_t *stack_index(struct stack *s, size_t index)
{
    return &s->vector[index];
}

enum stack_error stack_get_errno()
{
    return stack_errno;
}