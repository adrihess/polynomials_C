/** @file
  Funkcje przetwarzające wczytane dane do kalkulatora wielomianów w projekcie Polynomials.

  @author Adrian Hess <a.hess3@student.uw.edu.pl>
  @copyright Uniwersytet Warszawski
  @date 2021
*/

#ifndef CALC_PROCESSING_H
#define CALC_PROCESSING_H

/**
 * Pomocnicza struktura ułatwiająca parsowanie wielomianów.
 * Pole Mono zawiera sparsowany monomian.
 * Pole wsk zawiera wskaźnik do następnego znaku.
 */
typedef struct Mono_helper_structure {
    Mono temp;
    char *next_ptr;
}Mono_helper_structure;
/**
 * Pomocnicza struktura ułatwiająca parsowanie wielomianów.
 * Pole Mono zawiera sparsowany wielomian.
 * Pole wsk zawiera wskaźnik do następnego znaku.
 */
typedef struct Poly_helper_structure {
    Poly temp;
    char *next_ptr;
}Poly_helper_structure;
/**
 * Wywołuje odpowiednie polecenie majace trzy litery, lub zwraca błędną wartość
 * aby polecenie spróbować wywołać jako polecenie z parametrem
 * @param[in] stack : stos
 * @param[in] tab : tablica znaków
 * @param[in] i : numer linii
 * @param[in] isCorrect : zmienna logiczna
 * @return : nazwa polecenia lub błąd (polecenie WRONG) która uruchamia funkcje With_parameters
 */
enum Operations Three_letter(Stack *stack, char *tab, int i, bool *isCorrect);
/**
 * Wywołuje odpowiednie polecenie majace cztery litery, lub zwraca błędną wartość
 * aby polecenie spróbować wywołać jako polecenie z parametrem
 * @param[in] stack : stos
 * @param[in] tab : tablica znaków
 * @param[in] i : numer linii
 * @param[in] isCorrect : zmienna logiczna
 * @return : nazwa polecenia lub błąd (polecenie WRONG) która uruchamia funkcje With_parameters
 */
enum Operations Four_letter(Stack *stack, char *tab,  bool *isCorrect);
/**
 * Wywołuje odpowiednie polecenie majace pięć liter, lub zwraca błędną wartość
 * aby polecenie spróbować wywołać jako polecenie z parametrem
 * @param[in] stack : stos
 * @param[in] tab : tablica znaków
 * @param[in] i : numer linii
 * @param[in] isCorrect : zmienna logiczna
 * @return : nazwa polecenia lub błąd (polecenie WRONG) która uruchamia funkcje With_parameters
 */
enum Operations Five_letter(Stack *stack, char *tab, int i, bool *isCorrect);
/**
 * Wywołuje odpowiednie polecenie majace siedem liter, lub zwraca błędną wartość
 * aby polecenie spróbować wywołać jako polecenie z parametrem
 * @param[in] stack : stos
 * @param[in] tab : tablica znaków
 * @param[in] i : numer linii
 * @param[in] isCorrect : zmienna logiczna
 * @return : nazwa polecenia lub błąd (polecenie WRONG) która uruchamia funkcje With_parameters
 */
enum Operations Sevem_letter(Stack *stack, char *tab, int i, bool *isCorrect);
/**
 * Wywołuje odpowiednie polecenie majace osiem liter, lub zwraca błędną wartość
 * aby polecenie spróbować wywołać jako polecenie z parametrem
 * @param[in] stack : stos
 * @param[in] tab : tablica znaków
 * @param[in] i : numer linii
 * @param[in] isCorrect : zmienna logiczna
 * @return : nazwa polecenia lub błąd (polecenie WRONG) która uruchamia funkcje With_parameters
 */
enum Operations Eight_letter(Stack *stack, char *tab, int i, bool *isCorrect);
/**
 * Wywołuje odpowiednie polecenie z parametrem, lub zwraca błędną wartość
 * @param[in] stack : stos
 * @param[in] tab : tablica znaków
 * @param[in] i : numer linii
 * @param[in] isCorrect : zmienna logiczna
 * @return : nazwa polecenia lub błąd (polecenie WRONG)
 */
enum Operations With_parameter(Stack *stack, char *tab, int size, int i, bool *isCorrect);


/**
 * Parsuje wielomian w postaci tablicy znaków do struktury Poly
 * @param[in] tab : tablica
 * @param[in] rozm : rozmiar tablicy
 * @return : wielomian
 */
Poly Parse(char *tab, size_t size);
/**
 * Pomocnicza funkcja do parsowania wielomianów
 * @param[in] tab : tablica
 * @param[in] size : rozmiar
 * @return : pomocnicza struktura zawielająca sparsowany wielomian oraz wskaźnik do nastepnego elementu
 */
Poly_helper_structure Parse_helper_2(char *tab, size_t size);
/**
 * Pomocnicza funkcja do parsowania wielomianów
 * @param[in] tab : tablica
 * @param[in] size : rozmiar
 * @return : pomocnicza struktura zawielająca sparsowany monomian oraz wskaźnik do nastepnego elementu
 */
Mono_helper_structure Parse_helper_1(char *tab, size_t size);
/**
 * Dodaje jednomian do listy jednomianów.
 * W razie potrzeby zwiększa rozmiar tablicy monomianów dwukrotnie
 * @param[in] arr : wskaźnik do tablicy jednomianów
 * @param[in] size : rozmiar tablicy jednomianów
 * @param[in] max_size : zaalokowany rozmiar tablicy
 * @param[in] newMono : monomian
 */
void AddMono(Mono **arr, size_t size, size_t *max_size, Mono newMono);

/**
 * Przetwarza wczytane polecenie, odpowiada za sprawdzanie jego poprawności oraz wywoływanie odpowiedniej funkcji
 * z biblioteki poly.h, gdy jest ono poprawne
 * @param[in] tab : tablica znaków
 * @param[in] len : długość tablicy
 * @param[in] res : enum
 * @param[in] stack : stos
 * @param[in] i : numer wiersza
 * @param[in] isCorrect : pomocnicza zmienna sprawdzająca poprawność
 */
void ExpressionProcessing(char *tab, long len, enum Operations res, Stack *stack, int i, bool *isCorrect);
/**
 * Przetwarza wczyrany wielomian, odpowiada za kontrolowanie poprawności wczytanego wielomianu.
 * @param[in] tab : tablica znaków
 * @param[in] len : długość tablicy
 * @param[in] stack : stos
 * @param[in] i : numer wiersza
 */
void PolyProcessing(char *tab, long len,  Stack *stack, long i);
/**
 * Interpretuje wczytane dane, wywołuje inne funkcje odpowiadające za rozpoznanie polecenia lub wielomianu.
 * Odpowiada za kontrolę wywoływania funkcji z biblioteki poly.h
 * @param[in] stack : stos
 * @param[in] lines : liczba linii
 * @param[in] tab : dwuwymiarowa tablica znaków
 * @param[in] tab3 : pomocnicza tablica zawierajaca informacje o nieinterpretowanych liniach oraz długośc poszczególenj linii
 */
void Interpreter(Stack*stack, long lines, char **tab, int *tab3);



#endif
