/** @file
  Funkcja wczytująca dane do kalkulatora wielomianów Polynomials.

  @author Adrian Hess <a.hess3@student.uw.edu.pl>
  @copyright Uniwersytet Warszawski
  @date 2021
*/

#ifndef CALC_LOAD_H
#define CALC_LOAD_H

#include "defined_constants.h"
/**
 * Wczytuje z przekierowanego strumienia dane do kalkulatora wielomianów.
 *
 * @param[in] tab : tablica do wczytania znaków
 * @param[in] tab3 : pomocnicza tablica przechowująca dane o białych linii lub komentarzy
 * @return : int liczba wczytanych linii
 */
int loadLines(char ***tab, int **tab3);

#endif
