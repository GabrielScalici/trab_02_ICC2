#include <stdio.h>
#include <stdlib.h>
#include "arquivo_csv.h"
#include "algoritmos.h"


/* Funcao: imprimir_cabecalho
 *
 *	funçao para imprimir o cabecalho do menu
 *
 * Parametros:
 *
 * Retorno:
 *   nenhum
 */
void imprimir_cabecalho();


/* Funcao: busca_sequencial
 *
 *	funçao para imprimir mensagem de erro ao usuário
 *
 * Parametros:
 *    mensagem: mesagem de error
 *
 * Retorno:
 *   nenhum
 */
void imprimir_mensagem_erro(const char*);


/* Funcao: executa_abrir_arquivo
 *
 *	funçao para executar a funcionalidade abrir arquivo
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *
 * Retorno:
 *   nenhum
 */
void executa_abrir_arquivo(Arquivo_CSV**);


/* Funcao: executa_abrir_arquivo
 *
 *	funçao para executar a funcionalidade visulizar arquivo
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *
 * Retorno:
 *   nenhum
 */
void executa_visualizar_arquivo(Arquivo_CSV*);


/* Funcao: executa_ordenar_arquivo
 *
 *	funçao para executar a funcionalidade ordenar arquivo
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *
 * Retorno:
 *   nenhum
 */
void executa_ordenar_arquivo(Arquivo_CSV*);


/* Funcao: executa_buscar_arquivo
 *
 *	funçao para executar a funcionalidade buscar no arquivo
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *
 * Retorno:
 *   nenhum
 */
void executa_buscar_arquivo(Arquivo_CSV*);
