#include <stdlib.h>


#include "poly.h"
#include "poly_helper.h"
#include "stack_functions.h"
#include "calc_load.h"
#include "calc_processing.h"
#include "calc.h"

void StackControl() {

    Stack stack = init();

    char **tab  = safeMalloc(4 , sizeof(char*));
    int *tab3 = safeMalloc(4,sizeof(int));

    long lines = loadLines(&tab, &tab3);
    Interpreter(&stack, lines, tab, tab3);
    free(tab3);
    for(int i=0; i<lines; i++) {
        free(tab[i]);
    }
    free(tab);
    for(int i=0; i<stack.capacity;i++) {
        PolyDestroy(&stack.tab[i]);
    }
    if(stack.max_capacity > 0)
        free(stack.tab);


}

int main(void) {

    StackControl();
    return 0;

}