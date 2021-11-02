#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


#include "helper_functions.h"
#include "poly_helper.h"
#include "calc_load.h"


int loadLines(char ***tab, int **tab3) {

    size_t size_y = 1;
    size_t size_x = 0;
    size_t max_size_y = 4;
    size_t max_size_x = 4;
    long i=0;
    long prev_i = -1;

    bool onlyWhiteChars= true;
    bool isComment = false;

    int temp = SPACE;
    while(temp != END) {
        temp = getchar();
        if(temp!= SPACE && temp != NEWLINE && temp !=END)
            onlyWhiteChars = false;

        if(prev_i < i) {
            prev_i = i;
            (*tab)[i] = safeMalloc(max_size_x , sizeof(char*));

            if(temp == SHARP)
                isComment = true;

        }
        else if(size_x > max_size_x) {
            max_size_x *= 2;
            (*tab)[i] = safeRealloc((*tab)[i], max_size_x , sizeof(char*));

        }

        if(temp != END)
            (*tab)[i][size_x] = temp;
        else
            (*tab)[i][size_x] = NEWLINE;

        size_x++;

        if(temp == NEWLINE || temp == END) {
            max_size_x = 2;
            size_y++;
            if(size_y > max_size_y) {
                max_size_y *= 2;
                (*tab) = safeRealloc((*tab), max_size_y , sizeof(char*));
                (*tab3) = safeRealloc((*tab3), max_size_y , sizeof(int));

            }

            if(onlyWhiteChars || isComment) {
                (*tab3)[i] = 0;
            } else {
                (*tab3)[i] = size_x-1;
            }
            size_x=0;
            onlyWhiteChars=true;
            isComment=false;
            i++;

        }
    }
    (*tab) = safeRealloc((*tab), size_y , sizeof(char*));

    return i;
}