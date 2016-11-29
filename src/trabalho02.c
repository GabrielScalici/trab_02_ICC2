#include "trabalho02.h"


/* Funcao: imprimir_cabecalho
 *
 *	funçao para imprimir o cabecalho do menu
 *
 * Parametros:
 *
 * Retorno:
 *   nenhum
 */
void imprimir_cabecalho()
{
  // imprimindo menu
  system("clear");
  printf("1 - CARREGAR ARQUIVO CSV\n");
  printf("2 - VISUALIAR O ARQUIVO\n");
  printf("3 - ORDENAR O ARQUIVO\n");
  printf("4 - BUSCAR NO ARQUIVO\n");
  printf("5 - SAIR\n");
  printf(">> Digite uma opcao: ");
}


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
void imprimir_mensagem_erro(const char* mensagem)
{
  // imprime erro e espera usuario digitar Enter
  printf("%s\n", mensagem);
  printf("\n\nPrecione ENTER para continuar...");
  getchar();
}


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
void executa_abrir_arquivo(Arquivo_CSV** arquivo)
{
	// limpa tela e imprime titulo
	system("clear");
	printf("CARREGAR ARQUIVO\n\n");

	// imprime instrucoes
	printf("Para correto funcionamento o arquivo deve estar na pasta \n'files'. Exemplo: nome_arquivo.csv\n");
	printf(">> Digite o nome do arquivo: ");

	// pegando caminho para arquivo
	char* caminho = (char*) malloc(sizeof(char) * 255);
	char* nome_arquivo = ler_linha(stdin);
	caminho[0] = '\0';
	strcat(caminho, "files/");
	strcat(caminho, nome_arquivo);

  // verificando se arquivo já está carregado na memória
	if(*arquivo)
	{
		printf("\nLiberando arquivo previamente carregado.\n");
		destruir_arquivo_CSV(*arquivo);
	}

	printf("\nCarregando arquivo: %s\n\n\n", caminho);

  // lendo arquivo
	*arquivo = ler_arquivo_CSV(caminho);
	if(!(*arquivo))
	{
		printf("Error. Precione ENTER para continuar...");
	}
	else
	{
		printf("Arquivo carregado com sucesso. Precione ENTER para continuar...");
	}

	getchar();

	// liberando string que contem caminho
	free(caminho);
}


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
void executa_visualizar_arquivo(Arquivo_CSV* arquivo)
{
	// limpa tela e imprime titulo
	system("clear");
	printf("VISUALIZAR ARQUIVO\n\n\n");

  // verificando se arquivo está carregado
	if(!arquivo)
	{
		imprimir_mensagem_erro("Nenhum arquivo foi carregado por enquanto, utilize a opcao 1 do menu.");
		return;
	}

	imprimir_CSV(arquivo);

	printf("\n\nPrecione ENTER para continuar...");
	getchar();
}


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
void executa_ordenar_arquivo(Arquivo_CSV* arquivo)
{
  // limpa tela e imprime titulo
	system("clear");
	printf("ORDENAR ARQUIVO\n\n\n");

  int campo;
  int opcao_pivo;

  int i;
	int num_titulos;
	char** titulos = pegar_titulos_CSV(arquivo, &num_titulos);

	for(i = 0; i < num_titulos; i++)
	{
		printf("[%d] - %s\n", i, titulos[i]);
	}
	printf(">> Digite o campo que deseja ordenar: ");
	scanf("%d", &campo);
	getchar();

  printf("\n\n[1] - Elemento meio\n");
  printf("[2] - Elemento aleatorio\n");
  printf("[3] - Mediana de tres\n");
  printf(">> Digite a tecnica que deseja buscar: ");
	scanf("%d", &opcao_pivo);
	getchar();

  quick_sort(arquivo, 0, pegar_numero_registros_CSV(arquivo) - 1, campo, opcao_pivo);

	getchar();
}


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
void executa_buscar_arquivo(Arquivo_CSV* arquivo)
{
	// limpa tela e imprime titulo
	system("clear");
	printf("BUSCAR NO ARQUIVO\n\n\n");

  // verificando se arquivo está carregado
	if(!arquivo)
	{
		imprimir_mensagem_erro("Nenhum arquivo foi carregado por enquanto, utilize a opcao 1 do menu.");
		return;
	}

	int i;
	int num_titulos;
	char** titulos = pegar_titulos_CSV(arquivo, &num_titulos);

	int campo;

	for(i = 0; i < num_titulos; i++)
	{
		printf("[%d] - %s\n", i, titulos[i]);
	}
	printf(">> Digite o campo que deseja buscar: ");
	scanf("%d", &campo);
	getchar();
	if(campo < 0 || campo > num_titulos - 1)
	{
		imprimir_mensagem_erro("Campo invalido");
    return;
	}

	int busca;
	printf("\n[0] - Busca Sequencial\n[1] - Busca Binaria\n");
	printf(">> Digite qual busca deseja usar: ");
	scanf("%d", &busca);
	getchar();
	if(busca < 0 || busca > 1)
	{
		imprimir_mensagem_erro("Busca invalida");
		return;
	}


  printf("\n>> Digite a palavra a buscar: ");
	char* chave = ler_linha(stdin);
	printf("\nPesquisando: %s\n", chave);
  printf("\n\n");

	int reg;

  if(busca == 1)
    reg = busca_sequencial(arquivo, chave, campo);
  else
  {
    reg = busca_binaria(arquivo, chave, campo);
  }

  if(reg < 0)
  {
    imprimir_mensagem_erro("\nRegistro nao foi encontrado.\n");
    return;
  }
  else
  {
    printf("Registro: \n");
    char** cont = pegar_registro_CSV(arquivo, reg);
    for(i = 0; i < num_titulos; i++)
    {
      printf("%s, ", cont[i]);
    }
    imprimir_mensagem_erro("\n\n");
  }
}
