/** @file
  Główne funkcje kalkulatora wielomianów Polynomials.

  @author Adrian Hess <a.hess3@student.uw.edu.pl>
  @copyright Uniwersytet Warszawski
  @date 2021
*/
#ifndef CALC_H
#define CALC_H

/**
 * Funkcja odpowiadajaca za rozpoczącie wczytywania danych, inicjacje stosu,
 * przeinterpretowanie wczyranych wyrażeń oraz zwolnienie pamięci po przetworzeniu wczytanych danych.
 */
void StackControl();
/**
 * Funkcja main.
 * @return 0 gdy sie poprawnie zakońćzy - normalnie zakonćzony wątek
 */
int main(void);

#endif
