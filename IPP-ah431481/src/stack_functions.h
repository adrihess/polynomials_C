/** @file
  Funckje odpowiadające za bezpośrednie operacje na stosie w kalkulatorze wielomianów Polynomials.

  @author Adrian Hess <a.hess3@student.uw.edu.pl>
  @copyright Uniwersytet Warszawski
  @date 2021
*/

#ifndef UNTITLED40_STACK_FUNCTIONS_H
#define UNTITLED40_STACK_FUNCTIONS_H

enum Operations {
     WRONG, GOOD
};


/**
 * To jest struktura przechowująca stos, zaimplementowany jako dynamiczna tablica.
 * Stos ma logarytmiczne powiekszanie i zwalnianie pamięci.
 * Służy do tego pole capacity : aktualny rozmiar stosu
 * Oraz pole max_capacity : maksymalny rozmiar stosy,
 */

struct Stack {
    Poly *tab;
    long capacity;
    long max_capacity;

};
/**
 * To jest typ, przechowujący stos.
 */
typedef struct Stack Stack;
/**
 * To jest funkcja tworząca pusty stos
 * @return pusty stos
 */
Stack init();
/**
 * Funkcja sprawdzająca, czy stos jest pusty.
 * @param[in] stos : stos
 * @return rozmiar stosu = 0
 */
bool isEmpty(Stack *stos);
/**
 * Procedura kładząca wielomian na wierzchołem stosu.
 * @param[in] stos : stos
 * @param[in] p : wielomian
 */
void push(Stack *stos, Poly p);
/**
 * Funkcja kopiująca wielomian z wierzchołka stosu.
 * Funkcja sprawdza, czy operacja zdjęcia jest możliwa.
 * @param[in] stos : stos
 * @param[in] i : numer wiersza wywołania polecenia
 * @return : kopia wielomianu z wierzchołka stosu
 */
Poly top(Stack *stos, long i);
/**
 * Pomocnicza funkcja do wypisywania wielomianiu.
 * @param[in] p : wielomian
 */
void print_helper(Poly p);
/**
 * Funkcja wypisująca wielomian.
 * @param[in] stos : stos
 * @param[in] i : wiersz wywołania komendy
 */
void print(Stack *stos, long i);
/**
 * Funkcja zdejmująca wielomian ze stosu.
 * @param[in] stos : stos
 * @param[in] i : numer wiersza wywołania polecenia
 * @return : wielomian z wierzchołka stosu
 */

Poly pop(Stack *stos);
/**
 * Zdejmuje z wierzchołka stosu dwa wielomiany
 * oraz kładzie ich sumę na stos
 * @param[in] stos : stos
 * @param[in] i :  numer wiersza wywołania polecenia
 * */

void add(Stack *stos, long i);

/**
 * Procerura kłądąca wielomian zerowy na stos.
 * @param[in] stos : stos
 */
void zero(Stack *stos);
/**
 * Procedura sprawdzająca równość dwóch wierzchnich wielomianó na stosi.
 * @param[in] stos : stos
 * @param[in] i : numer wiersza wywołania polecenia
 */
void is_zero(Stack *stos, long i);
/**
 * Procedura dublująca wierzchołęk stosu
 * @param[in] stos : stos
 * @param[in] i : numer wiersza wywołania polecenia
 */
void clone(Stack *stos, long i);
/**
 * Zdejmuje z wierzchołka stosu dwa wielomiany
 * oraz kładzie ich iloczyn na stos
 * @param[in] stos : stos
 * @param[in] i :  numer wiersza wywołania polecenia
 * */


void mul(Stack *stos, long i);
/**
 * Sprawdza, czy wielomian jest współczynnikiem.
 * Wypisuje na standardowe wyjście 1, gdy jest lub 0 w przeciwnym wypadku.
 * @param[in] stos : stos
 * @param[in] i : numer wiersza wywołania polecenia
 */
void is_coeff(Stack *stos, long i);
/**
 * Zdejmuje z wierzchołka stosu dwa wielomiany
 * oraz kładzie ich róźnicę na stos
 * @param[in] stos : stos
 * @param[in] i :  numer wiersza wywołania polecenia
 * */
void sub(Stack *stos, long i);
/**
 * Sprawdza równość dwóch wielomianów z wierzchołka stosu
 * Wypisuje 1 gdy są równe lub 0 gdy nie są
 * @param[in] stos : stos
 * @param[in] i :  numer wiersza wywołania polecenia
 * */
void is_eq(Stack *stos, long i);
/**
 * Wypisuje na standardowe wyjście stopień wielomiany
 * @param[in] stos : stos
 * @param[in] i :  numer wiersza wywołania polecenia
 * */
void deg(Stack *stos, long i);
/**
 * Wypisuje na standardowe wyjście stopień wielomiani
 * ze względu na zmienną
 * @param[in] stos : stos
 * @param[in] i :  numer wiersza wywołania polecenia
 * */
void deg_by(Stack *stos, long var_ind, long i);
/**
 * Zdejmuje wielomian z wierzchołka stosu oraz kładzie
 * na wartość wielomiany w punkciex
 * @param[in] stos : stos
 * @param[in] x : punkt w którym liczymy wartość wielomianu
 * @param[in] i :  numer wiersza wywołania polecenia
 * */
void at(Stack *stos, poly_coeff_t x, long i);
/**
 * Zdejmuje wielomian z wierzchołka stosu
 * oraz kładzie wielomian przeciwny na stosie
 * @param[in] stos : stos
 * @param[in] i : numer wiersza wywołania polecenia
 */
void neg(Stack *stos, long i);
/**
 * Pomocnicza funkcja wywoływana w momencie, gdy nie można
 * wykonać danej operacji z powodu braku wymaganej ilości
 * wielomianów na stosie. Wypisuje odpowiedni komunikat
 * na standardowe wyjście błędów
 * @param[in] i : numer wiersza wywołania polecenia
 */
void underwlof(long i);
/**
 * Wykonuje operację złożenia wielomianów zdejmując wielomian
 * na którym wykonujemy podstawienie oraz daną liczbę
 * wielomianów ze stosu oraz kładzie wynik złożenia na stos
 * @param[in] stos : stos
 * @param[in] ct : ilość wielomianów do złożenia
 * @param[in] i : numer wiersza wywołania polecenia
 */
void compose(Stack *stos, long ct, long i);


#endif //UNTITLED40_STACK_FUNCTIONS_H