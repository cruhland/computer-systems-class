
#ifndef _STACK_H_
#define _STACK_H_

/*
 * Given the following definition, 
 * implement the stack functions listed below
 */
typedef (char *) stack_elem;

typedef struct {
    stack_elem *data;
    int logical_size;
    int allocated_size;
} stack;

void stack_init(stack *s);
void stack_destroy(stack *s);
void stack_push(stack *s, stack_elem elem);
stack_elem *top(stack *s);
void stack_pop(stack *s);
int stack_size(stack *s);

#endif
