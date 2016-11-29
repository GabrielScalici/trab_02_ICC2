#include "algoritmos.h"


void quick_sort(Arquivo_CSV* arquivo, int inicio, int fim, int op, int op_Pivo) {
    int i, j, y;
    int pivo;

    i = inicio;
    j = fim;

    //Para esclha do pivo depende do metodo escolhido
    if(op_Pivo == 1){
    	pivo = elemento_meio(inicio, fim);
    }else if(op_Pivo == 2){
    	pivo = elemento_aleatorio(inicio, fim);
    }else{
    	pivo = elemento_mediana(inicio, fim);
    }

    char* conteudo = pegar_conteudo_CSV(arquivo, pivo, op);

    while(i <= j) {
        while(strcmp(pegar_conteudo_CSV(arquivo, i, op), conteudo) < 0 && i < fim) {
            i++;
        }
        while(strcmp(pegar_conteudo_CSV(arquivo, j, op), conteudo) > 0 && j > inicio) {
            j--;
        }
        if(i <= j) {
            trocar_registros_CSV(arquivo, i, j);

            // nao mexer
            i++;
            j--;
        }
    }

    if(j > inicio) {
        quick_sort(arquivo, inicio, j, op, op_Pivo);
    }
    if(i < fim) {
        quick_sort(arquivo, i, fim, op, op_Pivo);
    }
}


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
int busca_sequencial(Arquivo_CSV* arquivo, char* chave, int campo)
{
  int i;
	int lim = pegar_numero_registros_CSV(arquivo);

  // percorrendo sequencialmente os registros
	for(i = 0; i < lim; i++)
  {
		if(strcmp(pegar_conteudo_CSV(arquivo, i, campo), chave) == 0)
    {
		    //Caso tenha encontrado, retorne o numero da linha
		    return i;
		}
  }

  // registro nao encontrado
	return -1;
}


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
int busca_binaria(Arquivo_CSV* arquivo, char* chave, int campo)
{
  return busca_binaria_recursiva(arquivo, chave, campo, 0, pegar_numero_registros_CSV(arquivo)-1);
}


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
int busca_binaria_recursiva(Arquivo_CSV* arquivo, char* chave, int campo, int comeco, int fim)
{
  if(comeco > fim)
    return -1;

  int meio = (comeco + fim) / 2;

  if(strcmp(pegar_conteudo_CSV(arquivo, meio, campo), chave) == 0)
    return meio;

  if(strcmp(pegar_conteudo_CSV(arquivo, meio, campo), chave) < 0)
    return busca_binaria_recursiva(arquivo, chave, campo, meio+1, fim);
  else
    return busca_binaria_recursiva(arquivo, chave, campo, comeco, meio-1);
}


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
int elemento_meio(int inicio, int fim)
{
	//Retornando a posicao do meio, como pivo
	return (inicio + fim) / 2;
}


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
int elemento_aleatorio(int inicio, int fim)
{
	int pos;
	srand(time(NULL));
	//Pegando o valor aletorio
	pos = (rand() % (fim-inicio)) + inicio;
	//retornando a posicao
	return pos;
}


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
int elemento_mediana(int inicio, int fim)
{
  int pos, pos2, pos3;
	int aux;

	//Sorteando duas primeiras posicoes
	pos = (rand() % (fim-inicio)) + inicio;
	pos2 = (rand() % (fim-inicio)) + inicio;

	//Ordenacao simples
	if(pos > pos2){
		aux = pos;
		pos = pos2;
		pos2 = aux;
	}

	//Sorteando terceira posicao
	pos3 = (rand() % (fim-inicio)) + inicio;

	//Ordenacao simples
	if(pos2 > pos3){
		aux = pos2;
		pos2 = pos3;
		pos3 = aux;

		if(pos > pos2){
			aux = pos;
			pos = pos2;
			pos2 = aux;
		}
	}

	//Retornando a posicao da mediana de 3, visto que pos, pos2 e pos3 esta ordenado
	return pos2;
}
