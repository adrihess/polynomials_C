#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


#include "poly.h"
#include "stack_functions.h"

void underwlof(long i) {

    fprintf(stderr, "ERROR %ld STACK UNDERFLOW\n", i);
}

Stack init() {

    return (Stack) {
            .capacity = 0,
            .max_capacity = 0,
            .tab = NULL,
    };
}

bool isEmpty(Stack *stack) {

    if(stack->capacity > 0)
        return false;
    else
        return true;
}

void push(Stack *stack, Poly p) {

    if(stack->capacity == 0) {
        stack->capacity = 1;
        stack->max_capacity = 4;
        stack->tab = malloc(stack->max_capacity*sizeof(Poly));
        stack->tab[0] = p;
    } else {
        stack->capacity++;

        if(stack->capacity > stack->max_capacity) {
            stack->max_capacity *= 2;
            stack->tab = realloc(stack->tab, stack->max_capacity * sizeof(Poly));
        }
        stack->tab[stack->capacity - 1] = p;
    }
}


bool isZeros(Poly *p) {
    assert(p!=NULL);

    if(p->arr == NULL)
        return true;
    for(size_t i=0; i<p->size; i++) {
        if(p->arr[i].exp != 0)
            return false;
        if(!isZeros(&p->arr[i].p))
            return false;
    }
    return true;

}

void print_helper(Poly p) {

    if(p.arr == NULL) {
        fprintf(stdout,"%ld", p.coeff);
        return;}
    else {

        for(size_t i=p.size; i>0; i--) {

            if(p.size==1 && (p.arr[i-1].exp == 0 || p.arr[i-1].p.coeff == 0 ) && isZeros(&p.arr[i-1].p)   )
                print_helper(p.arr[i-1].p);
            else {
                fprintf(stdout,"(");
                print_helper(p.arr[i-1].p);
                fprintf(stdout,",%d)", p.arr[i-1].exp);
                if(i > 1)
                    fprintf(stdout,"+");}

        }
    }
}


void print(Stack *stack, long i) {

    if(isEmpty(stack)) {
        underwlof(i);
        return;
    }

    Poly temp = top(stack, i);

    print_helper(temp);
    fprintf(stdout,"\n");

}



Poly pop(Stack *stack) {


    if(stack->capacity == 1) {
        Poly res = stack->tab[0];

        stack->capacity=0;
        stack->max_capacity=0;
        free(stack->tab);

        return res;
    } else {
        Poly res = stack->tab[stack->capacity -1];

        stack->capacity--;

        assert(stack->max_capacity %2 == 0);

        if( stack->capacity ==  (stack->max_capacity/2) &&  stack->capacity%2==0 ) {
            stack->max_capacity /= 2;
            stack->tab = realloc(stack->tab, stack->max_capacity * sizeof(Poly));
        }
        return res;

    }

}

Poly top(Stack *stack, long i) {

    if(isEmpty(stack)) {
        underwlof(i);

    }
    return stack->tab[stack->capacity - 1];
}


void add(Stack *stack, long i) {

    if(stack->capacity < 2) {
        underwlof(i);
        return;
    }
    Poly temp1 = pop(stack);
    Poly temp2 = pop(stack);
    Poly res = PolyAdd(&temp1, &temp2);
    push(stack, res);
    PolyDestroy(&temp1);
    PolyDestroy(&temp2);
}

void zero(Stack *stack) {

    push(stack, PolyFromCoeff(0));
}

bool is_coeff_pom(Poly *p) {

    if(PolyIsCoeff(p))
        return true;
    else {
        for(size_t i=0; i<p->size; i++) {
            if(p->arr[i].exp != 0 || !is_coeff_pom(&p->arr[i].p))
                return false;
        }
    }
    return true;
}

void is_coeff(Stack *stack, long i) {

    if(isEmpty(stack)) {
        underwlof(i);
        return;

    }
    Poly *temp = &(stack->tab[stack->capacity - 1]);

    if( is_coeff_pom(temp)  ){
        fprintf(stdout, "%d\n", 1);
    } else {
        fprintf(stdout, "%d\n", 0);
    }
}

void is_zero(Stack *stack, long i) {

    if(isEmpty(stack)) {
        underwlof(i);
        return;

    }
    else if( PolyIsZero(&(stack->tab[stack->capacity - 1]))) {
        fprintf(stdout, "%d\n", 1);
    } else {
        fprintf(stdout, "%d\n", 0);
    }
}
void clone(Stack *stack, long i) {

    if(isEmpty(stack)) {
        underwlof(i);
        return;

    }
    Poly temp = top(stack, i);
    push(stack, PolyClone(&temp));
}
void mul(Stack *stack, long i) {

    if(stack->capacity < 2) {
        underwlof(i);
        return;
    }
    Poly temp1 = pop(stack);
    Poly temp2 = pop(stack);
    push(stack, PolyMul(&temp1, &temp2));
    PolyDestroy(&temp1);
    PolyDestroy(&temp2);
}
void sub(Stack *stack, long i) {

    if(stack->capacity < 2) {
        underwlof(i);
        return;
    }
    Poly temp1 = pop(stack);
    Poly temp2 = pop(stack);
    push(stack, PolySub(&temp1, &temp2));
    PolyDestroy(&temp1);
    PolyDestroy(&temp2);
}
void is_eq(Stack *stack, long i) {

    if(stack->capacity < 2) {
        underwlof(i);
        return;
    }
    else if( PolyIsEq(&(stack->tab[stack->capacity - 2]), &(stack->tab[stack->capacity - 1]))) {
        fprintf(stdout, "%d\n", 1);
    } else {
        fprintf(stdout, "%d\n", 0);
    }
}

void deg(Stack *stack, long i) {

    if(isEmpty(stack)) {
        underwlof(i);
        return;
    } else
        fprintf(stdout, "%d\n", PolyDeg(&(stack->tab[stack->capacity - 1])));

}
void deg_by(Stack *stack, long var_ind, long i) {

    if(isEmpty(stack)) {
        underwlof(i);
        return;
    } else
        fprintf(stdout, "%d\n", PolyDegBy(&(stack->tab[stack->capacity - 1]), var_ind));

}
void at(Stack *stack, poly_coeff_t x, long i) {

    if(isEmpty(stack)) {
        underwlof(i);
        return;
    }
    Poly temp = pop(stack);
    Poly nowy = PolyAt(&temp, x);
    push(stack, nowy);
    PolyDestroy(&temp);
}
void neg(Stack *stack, long i) {
    if(isEmpty(stack)) {
        underwlof(i);
        return;
    }
    Poly temp = pop(stack);
    push(stack, PolyNeg(&temp));
    PolyDestroy(&temp);
}

void compose(Stack *stack, long ct, long i) {
    if(stack->capacity < ct || ct < 0) {
        underwlof(i);
        return;
    }

    Poly q[ct];

    Poly p = pop(stack);
    size_t t = ct;
    long ct2 = ct;

    while( ct>0 ) {
        q[ct-1] = pop(stack);
        ct--;
    }

    Poly res = PolyCompose(&p, t, q);
    push(stack, res);
    PolyDestroy(&p);
    for(long tt=0; tt<ct2; tt++) {
        PolyDestroy(&q[tt]);
    }

}