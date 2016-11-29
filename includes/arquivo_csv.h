#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Strct: Arquivo_CSV
 *
 *  A struct armazena as informações principais para
 * um arquivo csv e seu conteúdo.
 *
 * Atributos:
 *    num_linas:   número de registros
 *    num_colunas: número de campos dos registros
 *    titulos:     vetor com os títulos dos campos
 *    conteúdo:    conteudo de cada registro e campo
 */
typedef struct arquivo_csv Arquivo_CSV;


 /* Funcao: ler_linha
  *
  * 	A função le de um arquivo até o caracter '\n'
  * 	Caso queira ler do terminal use stdin
  *
  * Parametros:
  *    stream: ponteiro para arquivo de leira
  *
  * Retorno:
  *   vetor de caracteres em formato string
  */
char* ler_linha(FILE*);


/* Funcao: separar_string
 *
 * 	A função separa uma string em uma lista de string
 * a partir do caracter ','
 *
 * Parametros:
 *    string: referencia para string completa
 *
 * Retorno:
 *   vetor de strings com o conteudo
 * 	pelo tam retorna o número de strings de resultado
 */
char** separar_string(char*, int*);


/* Funcao: cria_arquivo_csv
 *
 * 	A função aloca memória para armazenar um arquivo CSV
 * são inicializados os valores e o conteudo como NULL
 *
 * Parametros:
 *    num_linhas: número de registros
 *		num_colunas:	número de campos
 *
 * Retorno:
 *   referencia para struct Arquivo_CSV
 */
Arquivo_CSV* criar_arquivo_CSV(int, int);


/* Funcao: destruir_arquivo_CSV
 *
 * A função libera a memória utilizada pela struct Arquivo_CSV
 *
 * Parametros:
 *    arquivo: referencia para srtuct Arquivo_CSV
 *
 * Retorno:
 *   nenhum
 */
void destruir_arquivo_CSV(Arquivo_CSV*);


/* Funcao: ler_arquivo_CSV
 *
 * 	A função le de um arquivo .csv aloca na memoria uma estrutura
 * Arquivo_CSV
 *
 * Parametros:
 *    caminho: caminho até arquivo csv
 *
 * Retorno:
 *   referencia para struct Arquivo_CSV
 */
Arquivo_CSV* ler_arquivo_CSV(const char*);


/* Funcao: imprimir_CSV
 *
 *	funçao para visulizar o arquivo CSV
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *
 * Retorno:
 *   nenhum
 */
void imprimir_CSV(Arquivo_CSV*);


/* Funcao: pegar_conteudo_CSV
 *
 *	funçao que retorna o conteúdo de determinado registro e campo
 *
 * Parametros:
 *    arquivo: 	referencia para struct Arquivo_CSV
 *		registro: número do registro
 *		campo: 		número do campo
 *
 * Retorno:
 *   string do valor contido no campo do registro
 */
char* pegar_conteudo_CSV(Arquivo_CSV*, int, int);


/* Funcao: pegar_numero_registros_CSV
 *
 *	funçao para retornar número de registros em um arquivo csv
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *
 * Retorno:
 *   número de registros
 */
int pegar_numero_registros_CSV(Arquivo_CSV*);


/* Funcao: pegar_titulos_CSV
 *
 *	funçao para retornar vetor de titulos
 *
 * Parametros:
 *    arquivo: referencia para struct Arquivo_CSV
 *		tam para retorno
 *
 * Retorno:
 *  	vetor de titulos
 *		numero de titulos por parametro
 */
char** pegar_titulos_CSV(Arquivo_CSV*, int*);


char** pegar_registro_CSV(Arquivo_CSV*, int);

void trocar_registros_CSV(Arquivo_CSV*, int, int);
