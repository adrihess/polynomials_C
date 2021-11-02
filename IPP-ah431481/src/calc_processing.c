#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>


#include "poly.h"
#include "poly_helper.h"
#include "stack_functions.h"
#include "helper_functions.h"
#include "calc_processing.h"


enum Operations Three_letter(Stack *stack, char *tab, int i, bool *isCorrect) {

    char add_pattern[4] = {'A','D', 'D', '\n'};
    char sub_pattern[4] = {'S','U', 'B', '\n'};
    char mul_pattern[4] = {'M','U', 'L', '\n'};
    char neg_pattern[4] = {'N','E', 'G', '\n'};
    char deg_pattern[4] = {'D','E', 'G', '\n'};
    char pop_pattern[4] = {'P','O', 'P', '\n'};

    if(CompareWithPattern(tab, pop_pattern, 4)) {
        if(!isEmpty(stack)) {
            Poly temp = pop(stack);
            PolyDestroy(&temp);}
        else
            underwlof(i);
        (*isCorrect) |= true;
        return GOOD;
    }
    else if(CompareWithPattern(tab, sub_pattern, 4)) {
        sub(stack,i);
        (*isCorrect) |= true;
        return GOOD;
    } else if(CompareWithPattern(tab, mul_pattern, 4)) {
        mul(stack,i);
        (*isCorrect) |= true;
        return GOOD;
    } else if(CompareWithPattern(tab, neg_pattern, 4)) {
        neg(stack,i);
        (*isCorrect) |= true;
        return GOOD;
    } else if(CompareWithPattern(tab, deg_pattern, 4)) {
        deg(stack,i);
        (*isCorrect) |= true;
        return GOOD;
    } else if(CompareWithPattern(tab, add_pattern, 4)) {
        add(stack,i);
        (*isCorrect) |= true;
        return GOOD;
    }else {
        (*isCorrect) |= false;
        return WRONG;
    }
}


enum Operations Four_letter(Stack *stack, char *tab,  bool *isCorrect) {

    char zero_pattern[5] = {'Z','E', 'R','O', '\n'};

    if(CompareWithPattern(tab, zero_pattern, 5)) {
        zero(stack);
        (*isCorrect) |= true;
        return GOOD;}
    else {
        (*isCorrect) |= false;
        return WRONG;
    }
}


enum Operations Five_letter(Stack *stack, char *tab, int i, bool *isCorrect) {

    char clone_pattern[6] = {'C','L', 'O','N','E', '\n'};
    char is_eq_pattern[6] = {'I','S', '_','E','Q', '\n'};
    char print_pattern[6] = {'P','R', 'I','N','T', '\n'};

    if(CompareWithPattern(tab, print_pattern, 6)) {
        print(stack, i);
        (*isCorrect) |= true;
        return GOOD;
    }

    else if(CompareWithPattern(tab, is_eq_pattern, 6)) {
        is_eq(stack,i);
        (*isCorrect) |= true;
        return GOOD;
    }
    else if(CompareWithPattern(tab, clone_pattern, 6)) {
        clone(stack, i);
        (*isCorrect) |= true;
        return GOOD;
    }
    else {
        return WRONG;
    }
}


enum Operations Sevem_letter(Stack *stack, char *tab, int i, bool *isCorrect) {

    char is_zero_pattern[8] = {'I','S','_','Z','E', 'R','O', '\n'};

    if(CompareWithPattern(tab, is_zero_pattern, 7)) {
        is_zero(stack,i);
        (*isCorrect) |= true;
        return GOOD;}

    else {
        return WRONG;
    }
}


enum Operations Eight_letter(Stack *stack, char *tab, int i, bool *isCorrect) {

    char is_coeff_pattern[9] = {'I','S','_','C','O', 'E','F','F', '\n'};

    if(CompareWithPattern(tab, is_coeff_pattern, 9)) {
        is_coeff(stack,i);
        (*isCorrect) |= true;
        return GOOD;}
    else {
        return WRONG;
    }
}


enum Operations With_parameter(Stack *stack, char *tab, int size, int i, bool *isCorrect) {

    char at_pattern[2] = {'A','T'};
    char deg_by_pattern[6] = {'D','E','G','_','B','Y'};
    char compose_pattern[7] = {'C','O','M','P','O', 'S','E'};

    if(size >= 2) {
        if(CompareWithPattern(tab, at_pattern, 2)) {
            (*isCorrect) |= true;

            if(!checkCorrect(3, size, tab)) {
                AtWrongValueSignal(i);
                return WRONG;
            }
            char *ptr;
            long double x = strtold(tab+3, &ptr);

            if(!isCorrectAt(x) || tab == ptr || errno != 0) {
                AtWrongValueSignal(i);
                return WRONG;
            }

            at(stack, (poly_coeff_t)x,i);
            return GOOD;
        }
    }

    if(size >= 6) {
        if(CompareWithPattern(tab, deg_by_pattern, 6)) {
            (*isCorrect) |= true;
            if(!checkCorrect(7, size, tab)) {
                DegByWrongValueSignal(i);
                return WRONG;
            }
            char *ptr;
            long double x = strtold(tab+7, &ptr);

            if(tab[7] == '-' || !isCorrectComposeArg(x) || tab == ptr || errno != 0) {
                DegByWrongValueSignal(i);
                return WRONG;
            }

            deg_by(stack, (long)x,i);
            (*isCorrect) |= true;
            return GOOD;
        }
    }

    if(size >= 7) {
        if(CompareWithPattern(tab, compose_pattern, 7)) {
            (*isCorrect) |= true;
            if(!checkCorrect(8, size, tab)) {
                ComposeWrongValueSignal(i);
                return WRONG;
            }
            char *ptr;
            long double x = strtold(tab+8, &ptr);

            if(tab[7] == '-' || !isCorrectdegBy(x) || tab == ptr || errno != 0) {
                ComposeWrongValueSignal(i);
                return WRONG;
            }
            compose(stack, (long)x,i);
            (*isCorrect) |= true;
            return GOOD;
        }

    }
    return WRONG;
}


Mono_helper_structure Parse_helper_1(char *tab, size_t size) {

    Mono temp;
    char *ptr;

    Poly_helper_structure help = Parse_helper_2(tab, size);
    tab = help.next_ptr;
    temp.p = help.temp;

    if(*tab == COMMA) {
        tab++;
    }

    temp.exp = (poly_exp_t)strtold(tab, &ptr);
    tab = ptr;
    while(*tab == RIGHT_PARENTHESIS) {
        tab++;
    }

    return (Mono_helper_structure) {
            .temp = temp,
            .next_ptr=tab
    };
}


void AddMono(Mono **arr, size_t size, size_t *max_size, Mono newMono) {

    if(size > *max_size) {
        *max_size *= 2;
        *arr = safeRealloc(*arr, *max_size , sizeof(Mono));

    }
    (*arr)[size-1] = newMono;
}


Poly_helper_structure Parse_helper_2(char *tab, size_t size) {

    char *ptr;
    poly_coeff_t x = (poly_coeff_t)strtold(tab, &ptr);
    if(x!=0 || tab != ptr) {
        return (Poly_helper_structure) {
                .temp = PolyFromCoeff(x),
                .next_ptr =ptr
        };
    }

    size_t size_new = 0;
    size_t max_size = 2;
    Mono *arr = safeMalloc(max_size ,sizeof(Mono));

    while(true) {

        tab++;
        Mono_helper_structure help = Parse_helper_1(tab, size);
        tab = help.next_ptr;

        size_new++;
        AddMono(&arr, size_new, &max_size, help.temp);
        if(*tab != PLUS || *tab == '\n') {
            break;

        } else if(*tab == PLUS) {
            tab++;
        }

    }
    arr = safeRealloc(arr, size_new , sizeof(Mono));
    struct Poly_helper_structure nowy;
    nowy.temp=PolyAddMonos(size_new, arr);
    nowy.next_ptr=tab;
    free(arr);
    return nowy;

}


Poly Parse(char *tab, size_t size) {

    Poly_helper_structure temp = Parse_helper_2(tab, size);
    Sort(&temp.temp);
    Simplify(&temp.temp, false);
    return temp.temp;
}


void ExpressionProcessing(char *tab, long len, enum Operations res, Stack *stack, int i, bool *isCorrect) {

    switch (len) {
        case 3:
            res = Three_letter(stack, tab, i + 1, isCorrect);
            break;
        case 4:
            res = Four_letter(stack, tab,  isCorrect);
            break;
        case 5:
            res = Five_letter(stack, tab, i + 1, isCorrect);
            break;
        case 7:
            res = Sevem_letter(stack, tab, i + 1, isCorrect);
            break;
        case 8:
            res = Eight_letter(stack, tab, i + 1, isCorrect);
            break;
        default:
            res = WRONG;
            break;
    }

    if (res == WRONG)
        res = With_parameter(stack, tab, len, i + 1, isCorrect);
}


void PolyProcessing(char *tab, long len,  Stack *stack, long i) {
    char *tabu = tab;

    if (isCorrectPoly(tabu, len+1)) {

        Poly res = Parse(tabu, len);
        push(stack, res);
    } else {
        WrongPolySignal(i+1);
    }
}


void Interpreter(Stack*stack, long lines, char **tab, int *tab3) {

    enum Operations res = GOOD;
    bool isCorrect = false;

    for(long i=0; i<lines; i++) {
        if(tab3[i] != 0) {

            if((tab[i][0] >= FIRST_ASCII_BIG_LETTER && tab[i][0] <= LAST_ASCII_BIG_LETTER)
               ||   (tab[i][0] >= FIRST_ASCII_SMALL_LETTER && tab[i][0] <= LAST_ASCII_SMALL_LETTER )) {
                ExpressionProcessing(tab[i], tab3[i], res, stack, i, &isCorrect);
                if(isCorrect == false) {
                    WrongCommandSignal(i+1);
                }
                isCorrect = false;
            } else {
                PolyProcessing(tab[i], tab3[i], stack, i);
            }
        }
    }

}