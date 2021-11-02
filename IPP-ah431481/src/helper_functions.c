#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#include "helper_functions.h"


void WrongPolySignal(long i) {

    fprintf(stderr, "ERROR %ld WRONG POLY\n", i);
}
void WrongCommandSignal(long i) {

    fprintf(stderr, "ERROR %ld WRONG COMMAND\n", i);
}
void AtWrongValueSignal(long i) {

    fprintf(stderr,"ERROR %ld AT WRONG VALUE\n", i);
}
void DegByWrongValueSignal(long i) {

    fprintf(stderr,"ERROR %ld DEG BY WRONG VARIABLE\n", i);
}
void ComposeWrongValueSignal(long i) {

    fprintf(stderr,"ERROR %ld COMPOSE WRONG PARAMETER\n", i);
}


bool isCorrectExp(long double exp) {

    if(exp < MIN_EXP || exp > MAX_EXP)
        return false;
    return true;
}


bool isDigit(char temp) {

    if(temp == '0' || temp == '1' ||temp == '2' ||temp == '3' ||temp == '4' ||temp == '5' ||temp == '6' ||
       temp == '7' ||temp == '8' ||temp == '9')
        return true;

    return false;
}


bool CompareWithPattern(const char *tab, const char *pattern, int size) {

    for(int i=0; i<size; i++) {
        if(tab[i] != pattern[i])
            return false;
    }
    return true;
}

bool isCorrectComposeArg(long double ct) {

    if(ct < 0 || ct > MAX_DEG)
        return false;
    return true;
}

bool isSpace(char t) {

    if(t == SPACE )
        return true;
    return false;
}



bool checkCorrect(int start, int end, char *tab) {

    if(!isSpace(tab[start-1]))
        return false;

    if(tab[start] != MINUS && !isDigit(tab[start]))
        return false;

    for(int i=start+1; i<end; i++) {
        if(!isDigit(tab[i]))
            return false;
    }
    return tab[end] =='\n';
}

bool isCorrectdegBy(long double x) {

    if(x < 0 || x > MAX_DEG) {
        return false;
    }
    return true;
}



bool isCorrectAt(long double x) {
    if(x > MAX_AT || x < MIN_AT)
        return false;
    return true;
}

bool isLegalChar(char t) {
    if(isDigit(t) || t==LEFT_PARENTHESIS || t==RIGHT_PARENTHESIS || t == COMMA || t== PLUS || t==MINUS) {
        return true;
    }
    return false;
}

bool isCorrectPoly(char *tab, int len) {

    bool haveDigit=false;
    bool loadNumber=true;
    bool compare = true;
    int numberOfComma=0;
    int numberOfParenthesis=0;
    long double ct=0.0L;

    char *ptr;
    for(int i=0; i < len-1; i++) {
        if(loadNumber) {
            ct = strtold(&tab[i], &ptr);
            loadNumber = false;}

        if(!isLegalChar(tab[i]) || ( compare &&  isDigit(tab[i]) &&  !isCorrectAt(ct)   ) )
            return false;

        if(compare && i>0 && isDigit(tab[i])  && tab[i-1]==COMMA && !isCorrectExp(ct))
            return false;

        compare = false;

        if(!haveDigit && isDigit(tab[i]))
            haveDigit=true;

        if(!isDigit(tab[i])) {
            loadNumber=true;
            compare = true;
        }

        if(tab[i] == RIGHT_PARENTHESIS) {
            numberOfParenthesis++;
            if(i<len-1 && ( tab[i+1] == RIGHT_PARENTHESIS || tab[i+1] == LEFT_PARENTHESIS ) )
                return false;
        }
        else if(tab[i] == PLUS) {
            if(i==0 || i==len-1 || tab[i-1]!=RIGHT_PARENTHESIS|| tab[i+1]!=LEFT_PARENTHESIS)
                return false;
        }
        else if(tab[i] == COMMA) {
            numberOfComma++;
            if(i==0 || i==len-1 || !isDigit(tab[i+1]) || tab[i-1]==LEFT_PARENTHESIS)
                return false;
        }
        else if(tab[i] == LEFT_PARENTHESIS) {
            numberOfParenthesis++;
        }

    }
    bool good = numberOfComma*2 == numberOfParenthesis;

    return good && haveDigit;

}

