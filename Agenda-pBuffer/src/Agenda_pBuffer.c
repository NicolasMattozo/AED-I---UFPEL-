#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
====================
AGENDA PBUFFER

Nome: Nicolas Mattozo
Curso: Ciência da Computação - UFPEL

ORGANIZAÇÃO DO BUFFER = (op) + (flag) + (tempNome) + (tempIdade) + (tempEmail) + (busca) + (dados)
====================
*/
int main( void ) {
	void *pBuffer = malloc( 312 );

	if ( pBuffer == NULL ) {
		printf( "erro de alocacao / memoria insuficiente" );
		exit( 1 );
	}

	// Ponteiros para cada dado dentro do pBuffer
	int *op = ( int * )pBuffer;
	int *flag = ( int * )( ( char * )pBuffer + sizeof( int ) );
	char *tempNome = ( char * )flag + sizeof( int );
	int *tempIdade = ( int * )( tempNome + 50 );
	char *tempEmail = ( char * )tempIdade + sizeof( int );
	char *busca = tempEmail + 50;
	char *dados = busca + 100;
	char *contador = dados; // Atualiza conforme necessário

	// Inicializa as variáveis
	*op = 0;          // Inicializa op
	*flag = 0;        // Inicializa flag
	memset( tempNome, 0, 50 );  // Limpa tempNome
	*tempIdade = 0;   // Inicializa tempIdade
	memset( tempEmail, 0, 50 ); // Limpa tempEmail
	memset( busca, 0, 100 );    // Limpa busca
	memset( dados, 0, 100 );    // Limpa dados

	for ( ;; ) {
		printf( "1- Adicionar Pessoa (Nome, Idade, Email)\n" );
		printf( "2- Remover Pessoa\n" );
		printf( "3- Buscar Pessoa\n" );
		printf( "4- Listar todos\n" );
		printf( "5- Sair\n" );

		*flag = 0;  // Inicializa flag

		scanf( "%3d", op );

		switch ( *op ) {
			case 1: {    //Adicionar pessoa
				printf( "Digite o Nome: " );
				scanf( "%49s", tempNome );

				printf( "Digite a Idade: " );
				scanf( "%d", tempIdade );
				getchar();

				printf( "Digite seu Email: " );
				scanf( "%49s", tempEmail );

				void *novoFim = ( char * )contador //Calcula o novo fim para realocar memória
					+ strlen( tempNome ) + 1  // Nome
					+ sizeof( int )           // Idade
					+ strlen( tempEmail ) + 1; // Email

				// Realoca pBuffer
				void *novoPBuffer = realloc( pBuffer, ( char * )novoFim - ( char * )pBuffer );

				if ( novoPBuffer == NULL ) {
					printf( "Erro de alocacao / memoria insuficiente\n" );
					exit( 1 );
				} else {
					contador = ( char * )novoPBuffer + ( ( char * )contador - ( char * )pBuffer ); //Atualiza Contador
					pBuffer = novoPBuffer;
				}

				// Atualiza pBuffer e ajusta os ponteiros
				op = ( int * )pBuffer;
				flag = ( int * )( ( char * )pBuffer + sizeof( int ) );
				tempNome = ( char * )flag + sizeof( int );
				tempIdade = ( int * )( tempNome + 50 );
				tempEmail = ( char * )tempIdade + sizeof( int );
				busca = tempEmail + 50;
				dados = busca + 100;

				// Copia os novos dados para a área realocada
				memcpy( contador, tempNome, strlen( tempNome ) + 1 ); // Copia o nome
				contador += strlen( tempNome ) + 1;

				memcpy( contador, tempIdade, sizeof( int ) ); // Copia a idade
				contador += sizeof( int );

				memcpy( contador, tempEmail, strlen( tempEmail ) + 1 ); // Copia o email
				contador += strlen( tempEmail ) + 1;

				printf( "Cadastro adicionado com sucesso\n" );

				break;
			}

			case 2: {
				printf( "Digite o nome que deseja excluir: " );
				scanf( "%99s", busca );

				char *imprime = dados; // Imprime aponta para o inicio de dados
				void *fim = NULL;

				while ( ( char * )imprime < ( char * )contador ) {
					if ( strcmp( imprime, busca ) == 0 ) {
						printf( "NOME ENCONTRADO \n" );

						*flag = 1;

						void *auxiliar = NULL;
						auxiliar = imprime; // Auxiliar recebe o endereço do primeiro caracter do nome buscado
						auxiliar += strlen( ( char * )auxiliar ) + 1;
						auxiliar += 4;
						auxiliar += strlen( ( char * )auxiliar ) + 1;

						fim = auxiliar;  // Fim aponta para o endereço do ultimo caracter do nome buscado

						memmove( imprime, fim, ( char * )contador - ( char * )fim );

						contador = ( char * )contador - ( ( char * )fim - ( char * )imprime ); //Atualiza contador

						void *novoPBuffer = realloc( pBuffer, ( char * )contador - ( char * )pBuffer );

						if ( novoPBuffer == NULL ) {
							printf( "falha ao alocar memoria\n" );
							exit( 1 );
						}

						pBuffer = novoPBuffer;

						op = ( int * )pBuffer;
						flag = ( int * )( ( char * )pBuffer + sizeof( int ) );
						tempNome = ( char * )flag + sizeof( int );
						tempIdade = ( int * )( tempNome + 50 );
						tempEmail = ( char * )tempIdade + sizeof( int );
						busca = tempEmail + 50;
						dados = busca + 100;
						if ( contador == dados ) {
							contador = dados;
						}

						printf( "Registro excluido com sucesso\n" );

						break;
					} else {
						// Caso o nome não seja encontrado, continua verificando
						imprime += strlen( ( char * )imprime ) + 1;  // Avança para o próximo campo (nome)
						imprime += sizeof( int );                   // Avança para o próximo campo (idade)
						imprime += strlen( ( char * )imprime ) + 1;  // Avança para o próximo campo (email)
					}
				}

				if ( *flag == 1 ) {
					printf( "--------------------------\n" );
				} else {
					printf( "--------------------------\n" );
					printf( "Nome nao encontrado\n" );
					printf( "--------------------------\n" );
				}

				break;
			}

			case 3: {
				printf( "Digite o nome que deseja buscar: \n" );
				scanf( "%99s", busca );

				char *imprime = dados;
				while ( ( char * )imprime < ( char * )contador ) {
					if ( strcmp( imprime, busca ) == 0 ) { //Compara os nomes
						printf( "NOME ENCONTRADO \n \n" );

						printf( "Nome: %s\n", ( char * )imprime );
						imprime += strlen( ( char * )imprime ) + 1;

						printf( "Idade: %d\n", *( int * )( char * )imprime );
						imprime += 4;

						printf( "Email: %s\n", ( char * )imprime );
						imprime += strlen( ( char * )imprime ) + 1;

						*flag = 1;
					} else {
						// Caso o nome não seja encontrado, continua verificando
						imprime += strlen( ( char * )imprime ) + 1;  // Avança para o próximo campo (nome)
						imprime += sizeof( int );                   // Avança para o próximo campo (idade)
						imprime += strlen( ( char * )imprime ) + 1;  // Avança para o próximo campo (email)
					}
				}

				if ( *flag == 1 ) {
					printf( "--------------------------\n" );
				} else {
					printf( "--------------------------\n" );
					printf( "Nome nao encontrado\n" );
					printf( "--------------------------\n" );
				}

				break;
			}

			case 4: {
				char *imprime = dados;

				if ( imprime == contador || *imprime == '\0' ) {
					printf( "--------------------------\n" );
					printf( "Nao existem pessoas cadastradas\n" );
					printf( "--------------------------\n" );
					break;
				}

				while ( imprime < contador ) {
					printf( "Nome: %s\n", ( char * )imprime );
					imprime += strlen( ( char * )imprime ) + 1;

					printf( "Idade: %d\n", *( int * )imprime );
					imprime += sizeof( int );

					printf( "Email: %s\n", ( char * )imprime );
					imprime += strlen( ( char * )imprime ) + 1;

					printf( "--------------------------\n" );
				}

				break;
			}

			case 5: {
				free( pBuffer );
				printf( "Programa Finalizado com Sucesso" );
				exit( 0 );
			}
		}
	}

	return 0;
}