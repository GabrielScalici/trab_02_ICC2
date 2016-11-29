#include "arquivo_csv.h"


/* ESTRUTURA DE UM ARQUIVO CSV */
struct arquivo_csv
{
	int num_linhas;			// numero de linhas
	int num_colunas;		// numero de colunas
	char** titulos;			// títulos das colunas
	char*** conteudo;		// dados
};


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
char* ler_linha(FILE* stream)
{
	// ponteiro para string
	char* linha = NULL;
	int cont = 0;
	char tmp;

	do
	{
		// lendo caracter e realocando string
		fscanf(stream, "%c", &tmp);
		linha = (char*) realloc(linha, sizeof(char) * (cont + 1));
		linha[cont++] = tmp;

	} while(tmp != '\n');		// le até enter

	linha[--cont] = '\0';		// fim da string

	return linha;						// retorna string
}


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
char** separar_string(char* string, int* tam)
{
	// ponteiro para lista
	char** lista = NULL;
	int num_elem = 0;
	int i = 0;

	// verifica se há string para separar
	if(!string)
		return NULL;

	// alloca primeria posição
	lista = (char**) realloc(lista, sizeof(char*) * (num_elem + 1));
	lista[num_elem++] = &string[i];

	// enquando houver string
	while(string[i] != '\0')
	{
		// cria novo elemento no vetor
		if(string[i] == ',')
		{
			string[i] = '\0';
			lista = (char**) realloc(lista, sizeof(char*) * (num_elem + 1));
			lista[num_elem++] = &string[i+1];
		}

		i++;
	}

	// atribui tamanho e retorna referencia
	*tam = num_elem;
	return lista;
}


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
Arquivo_CSV* criar_arquivo_CSV(int num_linhas, int num_colunas)
{
	// allocando heap
	Arquivo_CSV* arquivo = (Arquivo_CSV*) malloc(sizeof(Arquivo_CSV));

	// caso tenha sucesso no armazenamento
	if(arquivo)
	{
		// inicializa os valores
		arquivo->num_linhas = num_linhas;
		arquivo->num_colunas = num_colunas;

		// alocando titulos
		int i, j;
		arquivo->titulos = (char**) malloc(sizeof(char*) * num_colunas);
		for(i = 0; i < num_colunas; ++i)
			arquivo->titulos[i] = NULL;

		// alocando memória para conteúdo
		arquivo->conteudo = (char***) malloc(sizeof(char**) * num_linhas);
		for(i = 0; i < num_linhas; ++i)
		{
			arquivo->conteudo[i] = (char**) malloc(sizeof(char*) * num_colunas);

			// inicializando conteudo como NULL
			for(j = 0; j < num_colunas; j++)
			{
				arquivo->conteudo[i][j] = NULL;
			}
		}
	}

	// retornando referencia
	return arquivo;
}


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
void destruir_arquivo_CSV(Arquivo_CSV* arquivo)
{
	// verifica se arquivo está alocado
	if(!arquivo)
		return;

	int i, j;

	// liberando titulos
	free(arquivo->titulos[0]);
	free(arquivo->titulos);

	// liberando conteúdo
	for(i = 0; i < arquivo->num_linhas; ++i)
	{
		free(arquivo->conteudo[i][0]);
	}
	free(arquivo->conteudo);

	// liberando struct
	free(arquivo);
}


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
Arquivo_CSV* ler_arquivo_CSV(const char* caminho)
{
	// ponteiro para arquivo
	FILE* fp = NULL;

	// abrindo arquivo
	fp = fopen(caminho, "r");
	if(!fp)
	{
			// retorna mensagem de erro
			fprintf(stderr, "Nao foi possivel abrir arquivo: %s\n", caminho);
			return NULL;
	}

	// ponteiro para struct Arquivo_CSV
	Arquivo_CSV* arquivo = NULL;
	int num_campos = 0;
	int num_registros = 0;

	int i = 0;
	char aux;

	// contando os campos
	while(!feof(fp))
	{
		fscanf(fp, "%c", &aux);
		if(aux == ',')
			num_campos++;

		else if(aux == '\n')
		{
			num_campos++;
			break;
		}
	}

	// contando os registros
	while(!feof(fp))
	{
		fscanf(fp, "%c", &aux);
		if(aux == '\n')
			num_registros++;
	}
	num_registros--;
	rewind(fp);

	// criando struct
	arquivo = criar_arquivo_CSV(num_registros, num_campos);

	// armazenando títulos
	char* linha = ler_linha(fp);
	int tam;
	char** lista = separar_string(linha, &tam);
	for(i = 0; i < tam; i++)
	{
		arquivo->titulos[i] = lista[i];
	}

	// armazenando os registros
	int j;
	for(i = 0; i < num_registros; i++)
	{
		linha = ler_linha(fp);
		lista = separar_string(linha, &tam);

		for(j = 0; j < tam; j++)
		{
			arquivo->conteudo[i][j] = lista[j];
		}
	}

	// fechando arquivo e retornando struct
	fclose(fp);
	return arquivo;
}


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
void imprimir_CSV(Arquivo_CSV* arquivo)
{
	// verificando se está alocado
	if(!arquivo)
		return;

	int i, j;

	// imprimindo os títulos
	printf("Titulos:");
	for(i = 0; i < arquivo->num_colunas; i++)
		printf("\t%10s", arquivo->titulos[i]);

	// imprimindo o conteudo
	for(i = 0; i < arquivo->num_linhas; i++)
	{
		printf("\nlinha %d: ", i);
			for(j = 0; j < arquivo->num_colunas; j++)
			{
				printf("\t%10s", arquivo->conteudo[i][j]);
			}
	}

	// quebra linha
	printf("\n\n");
}


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
char* pegar_conteudo_CSV(Arquivo_CSV* arquivo, int registro, int campo)
{
	return arquivo->conteudo[registro][campo];
}


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
int pegar_numero_registros_CSV(Arquivo_CSV* arquivo)
{
	return arquivo->num_linhas;
}


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
char** pegar_titulos_CSV(Arquivo_CSV* arquivo, int* tam)
{
	*tam = arquivo->num_colunas;
	return arquivo->titulos;
}

char** pegar_registro_CSV(Arquivo_CSV* arquivo, int reg)
{
	return arquivo->conteudo[reg];
}


void trocar_registros_CSV(Arquivo_CSV* arquivo, int i, int j)
{
	char** aux = arquivo->conteudo[i];
	arquivo->conteudo[i] = arquivo->conteudo[j];
	arquivo->conteudo[j] = aux;
}
