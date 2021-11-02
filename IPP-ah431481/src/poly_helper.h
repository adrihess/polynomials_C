/** @file
  Pomocnicze funkcje dla biblioteki poly.c kalkulatora wielomianów Polynomials.

  @author Adrian Hess <a.hess3@student.uw.edu.pl>
  @copyright Uniwersytet Warszawski
  @date 2021
*/

#ifndef POPRAWNE_H
#define POPRAWNE_H

#include "poly.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Bezpiecznie alokuje pamięć.
 * Zakańcza pracę programu kodem 1, w przypadku niepowodzenia
 * @param[in] size : rozmiar zaalokowanego obszaru
 * @param[in] sizeOf : rozmiar alokowanej komórki
 * @return : wskaźnik do zaalokowanego obszaru
 */
static inline void *safeMalloc(size_t size, size_t sizeOf) {
    void *ptr = malloc(size * sizeOf);
    if(ptr==NULL)
        exit(1);
    return ptr;
}
/**
 * Bezpiecznie zmienia rozmiar zaalokowanego obszaru.
 * W razie podania zerowego nowego rozmiaru, zwalnia pamięć z użyciem funkcji free()
 * @param[in] ptr : wskaźnik na zaalokowaną pamięć
 * @param[in] new_size : nowy rozmiar
 * @param[in] sizeOf : rozmiar komórki pamięci
 * @return : wskażnik do nowej zaalokowanej pamięci
 */
static inline void *safeRealloc(void *ptr, size_t new_size, size_t sizeOf) {
    if(new_size!=0) {
        ptr = realloc(ptr, new_size * sizeOf);
        if(ptr==NULL)
            exit(1);
    }
    else {
        free(ptr);
        ptr = NULL;
    }
    return ptr;
}

/**
 * Zwraca większą liczbę
 * @param[in] a : long
 * @param[in] b : long
 * @return : max(a,b)
 */
long max(long a, long b);

/**
 * Funkcja uprawszczająca podany wielomian
 * @param[in] p : wielomian do uproszczenia
 * @param[in] deepSimplify : głębokość upraszczania
 */
void Simplify(Poly *p, bool deepSimplify);
/**
 * Funkcja porównująca potegi jednomianów
 * @param[in] m1 : jednomian
 * @param[in] m2 : jednomian
 * @return : wartość dla funkcji qsort()
 */
int CompareExps(const void *m1, const void *m2);
/**
 * Sortuje wielomian według nierosnących potęg jednomianów
 * @param[in] p : wielomian
 */
void Sort(Poly *p);
/**
 * Wymnaża monomian przez stałą x
 * @param[in] m : monomian
 * @param[in] x : stała liczba
 */
void MultiplicateMonos(Mono *m, poly_coeff_t x);
/**
 * Pomocnicza funkcja dla funkcji PolyNeg()
 * neguje podany wielomian
 * @param[in] p : wielomian
 */

void PolyNegHelper(Poly *p);
/**
 * Pomocnicze funkcja, sumująca dwa wielomiany i zwracająca ich sumę.
 * @param[in] p : wielomian
 * @param[in] q : wielomian
 * @return : suma p+q
 */
Poly PolyAddHelper(const Poly *p, const Poly *q);
/**
 * Implementacja binsercza do wykonywania szybkiego potęgowania
 * @param[in] a : podstawa
 * @param[in] b : wykladnik
 * @return : wynik potęgowania
 */
long BinPower(long a, long b);
/**
 * Pomocnicza funkcja, porównujaca dwa wielomiany
 * @param[in] p : wielomian
 * @param[in] q : wielomian
 * @return : true gdy p = q lub false gdy p != q
 */
bool isTheSame(const Poly *p,const Poly *q);
/**
 * Podnosi wielomian do dodatniej, całkowitej potęgi
 * @param[in] p : wielomian
 * @param[in] exp : potega
 * @return : wielomian podniesiony do danej potegi
 */
Poly PolyPower(const Poly *p, int exp);


#endif
