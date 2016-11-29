#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "arquivo_csv.h"


void quick_sort(Arquivo_CSV*, int, int, int, int);


/* Funcao: busca_sequencial
 *
 *	funçao para buscar um valor em um arquivo CSV
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *    chave:   string a ser buscado
 *    campo:   qual dos campos deseja buscar
 *
 * Retorno:
 *   número do registro que se encontra o campo, ou -1 caso nao exista
 */
int busca_sequencial(Arquivo_CSV*, char*, int);


/* Funcao: busca_binaria
 *
 *	funçao controla a chamada para busca busca binaria.
 * retorna indice do registro onde foi encontrado o campo ou -1 caso nao exista.
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *    chave:   string a ser buscado
 *    campo:   qual dos campos deseja buscar
 *
 * Retorno:
 *   número do registro que se encontra o campo, ou -1 caso nao exista
 */
int busca_binaria(Arquivo_CSV*, char*, int);


/* Funcao: busca_binaria_recursiva
 *
 *	funçao que busca recursivamente.
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *    chave:   string a ser buscado
 *    campo:   qual dos campos deseja buscar
 *    comeco:  posicao inicial para calcular meio
 *    fim:     posicao final para calcular meio
 *
 * Retorno:
 *   número do registro que se encontra o campo, ou -1 caso nao exista
 */
int busca_binaria_recursiva(Arquivo_CSV*, char*, int, int, int);


/* Funcao: elemento_meio
 *
 *	funçao que retorna o indice do meio de dois outros
 *
 * Parametros:
 *    inicio: indice inicial
 *    fim:    indice final
 *
 * Retorno:
 *   indice resultado
 */
int elemento_meio(int, int);


/* Funcao: elemento_aleatorio
 *
 *	funçao que retorna o indice aleatório no meio de dois outros
 *
 * Parametros:
 *    inicio: indice inicial
 *    fim:    indice final
 *
 * Retorno:
 *   indice resultado
 */
int elemento_aleatorio(int, int);


/* Funcao: elemento_mediana
 *
 *	funçao que retorna o indice mediano de tres valores escolhidos aleatoriamente
 * no meio de dois outros.
 *
 * Parametros:
 *    inicio: indice inicial
 *    fim:    indice final
 *
 * Retorno:
 *   indice resultado
 */
int elemento_mediana(int, int);
