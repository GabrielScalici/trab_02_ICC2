#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmos.h"
#include "arquivo_csv.h"
#include "trabalho02.h"


enum ESTADOS
{
	ABRIR_ARQUIVO = 1,
	VISUALIZAR_ARQUIVO,
	ORDENAR_ARQUIVO,
	BUSCAR_ARQUIVO,
	SAIR
};


int main(int argc, char** argv)
{
	// declarando arquivo
	Arquivo_CSV* arquivo = NULL;

	int opcao_usuario;
	do {
		imprimir_cabecalho();
		scanf("%d", &opcao_usuario);
		getchar();

		// escolhendo qual estado executar
		switch (opcao_usuario)
		{
			case ABRIR_ARQUIVO:
				executa_abrir_arquivo(&arquivo);
			break;

			case VISUALIZAR_ARQUIVO:
				executa_visualizar_arquivo(arquivo);
			break;

			case ORDENAR_ARQUIVO:
				executa_ordenar_arquivo(arquivo);
			break;

			case BUSCAR_ARQUIVO:
				executa_buscar_arquivo(arquivo);
			break;

			case SAIR:
			break;

			default:
				printf("Opcao invalida. Tente novamente\n");
			break;
		}
	} while(opcao_usuario != SAIR);

	// liberando arquivo
	destruir_arquivo_CSV(arquivo);
	printf("\nFinalizando programa. Precione ENTER para continuar...\n\n\n");
	return 0;
}
