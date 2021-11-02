/** @file
  Pomocnicze funkcje dla projektu Polynomials

  @author Adrian Hess  <a.hess3@student.uw.edu.pl>
  @copyright Uniwersytet Warszawski
  @date 2021
*/

#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "defined_constants.h"
/**
 * Funkcja wypisuje na standardowe wyjście błędów
 * informację i błędnym wielomianie
 * @param[in] i : numer wiersza
 */
void WrongPolySignal(long i);
/**
 * Funkcja wypisuje na standardowe wyjście błędów
 * informację o błędnym poleceniu
 * @param[in] i : numer wiersza
 */
void WrongCommandSignal(long i);
/**
 * Funkcja wypisuje na standardowe wyjście błędów
 * informację o złym parammetrze polecenia dla funkcji PolyAt
 * @param[in] i : numer wiersza
 */
void AtWrongValueSignal(long i);
/**
 * Funkcja wypisuje na standardowe wyjście błędów
 * informację o złym parammetrze polecenia dla funkcji PolyDegBy
 * @param[in] i : numer wiersza
 */
void DegByWrongValueSignal(long i);
/**
 * Funkcja wypisuje na standardowe wyjście błędów
 * informację o złym parammetrze polecenia dla funkcji PolyCompose
 * @param[in] i : numer wiersza
 */
void ComposeWrongValueSignal(long i);
/**
 * Sprawdza, czy wczytana liczba jest poprawną potęgą wielomianu
 * @param[in] exp : wczytana liczba
 * @return : true jeżeli jest poprawną, false jeżeli jest niepoprawną potęgą
 */
bool isCorrectExp(long double exp);
/**
 * Sprawdza, czy dany znak jest cyfrą
 * @param[in] temp : znak
 * @return : true jeżlei jest, false jeżeli nie jest cyfrą
 */
bool isDigit(char temp);
/**
 * Porównuje kilka początkowych znaków w tablicy tab ze znakami
 * w tablicy wzorcowej
 * @param[in] tab : tablica
 * @param[in] pattern : wzorzec
 * @param[in] size : liczba porównywanych znaków
 * @return : true jeżeli sa identyczne ze wzorcem, false jeżeli nie są
 */
bool CompareWithPattern(const char *tab, const char *pattern, int size);
/**
 * Sprawdza, czy wczytana liczba jest dobrym parametrem dla funkcji PolyCompose
 * @param[in] ct : liczba
 * @return : true gdy jest, false gdy nie
 */
bool isCorrectComposeArg(long double ct);
/**
 * Sprawdza, czy znak jest spacją
 * @param[in] t : znak
 * @return : true jeżeli tak, false jeżeli nie
 */
bool isSpace(char t);
/**
 * Sprawdza czy składnia polecenia z parametrem jest poprawna
 * @param[in] start : początek sekwencji do porównania
 * @param[in] end : koniec sekwencji do porównania
 * @param[in] tab : tablica do porównania
 * @return true gdy jest, false gdy nie
 */
bool checkCorrect(int start, int end, char *tab);
/**
 * Sprawdza poprawnośc wczytanego argumentu dla funkcji PolyDegBy
 * @param[in] x : wczytany parametr
 * @return : true gdy jest poprawny, false gdy nie
 */
bool isCorrectdegBy(long double x);
/**
 * Sprawdza poprawnośc wczytanego argumentu dla funkcji PolyAt
 * @param[in] x : wczytany parametr
 * @return : true gdy jest poprawny, false gdy nie
 */
bool isCorrectAt(long double x);
/**
 * Sprawdza poprawność znaku we wczytanym wielomianie
 * @param[in] t : znak
 * @return : true gdy znak może być we wczytanym wielomianie,false gdy nie może
 */
bool isLegalChar(char t);
/**
 * Sprawdza, czy wczyrana sekwencja znaków jest poprawnym wielomianem
 * @param[in] tab : tablica znaków
 * @param[in] len : długość tablicy
 * @return : true gdy jest poprawnym wielomiane, false gdy nie
 */
bool isCorrectPoly(char *tab, int len);


#endif //UNTITLED40_HELPER_FUNCTIONS_H
