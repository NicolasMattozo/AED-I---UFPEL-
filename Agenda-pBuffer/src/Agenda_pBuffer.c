#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// pBuffer = ((op) + (flag) + (tempNome) + (tempIdade) + (tempEmail) + (busca) + (dados))

int main( void ) {

	void *pBuffer = malloc(
		sizeof( int ) +	// op
		sizeof( int ) +	// flag
		( 50 * sizeof( char ) ) + // tempNome
		sizeof( int ) + // tempIdade
		( 50 * sizeof( char ) ) + // tempEmail
		( 100 * sizeof( char ) ) + // busca
		( 100 * sizeof( char ) ) // dados
	);

	if ( pBuffer == NULL ) {
		printf( "erro de alocacao / memoria insuficiente" );
	}

	// VOU CRIAR PONTEIROS PARA APONTAR PARA O INICIO DE CADA DADO DENTRO DO pBuffer
	void *op        = pBuffer; // aponta p inicio do pBuffer
	void *flag      = ( char * ) op + sizeof( int ); // aponta pro inicio de flag
	void *tempNome  = ( char * ) flag + sizeof( int ); // aponta pro inicio de tempNome
	void *tempIdade = ( char * ) tempNome + ( 50 * sizeof( char ) ); // aponta pro inicio de tempIdade
	void *tempEmail = ( char * ) tempIdade + sizeof( int ); // aponta pro inicio de tempEmail
	void *busca     = ( char * ) tempEmail + ( 50 * sizeof( char ) ); // aponta pro inicio de busca
	void *dados     = ( char * ) busca + ( 100 * sizeof( char ) ); // aponta pro inicio de dados
	void *contador  = dados; // ponteiro pro inicio de dados que vai atualizando sempre pro ultimo caracter

	// Inicializa as variáveis
	*( int * ) op = 0;    // Inicializa op
    *( int * ) flag = 0;  // Inicializa flag
    memset( tempNome, 0, 50 );  // Limpa tempNome
    *( int * )tempIdade = 0;   // Inicializa tempIdade
    memset( tempEmail, 0, 50 ); // Limpa tempEmail
    memset( busca, 0, 100 );    // Limpa busca
    memset( dados, 0, 100 );    // Limpa dados

	for ( ;; ) {
        printf( "1- Adicionar Pessoa (Nome, Idade, Email)\n" );
        printf( "2- Remover Pessoa\n" );
        printf( "3- Buscar Pessoa\n" );
        printf( "4- Listar todos\n" );
        printf( "5- Sair\n" );

		*( int * ) flag = 0;  // Inicializa flag

        scanf( "%3d", ( int * ) op );

		switch ( *(int * ) op ) {

			case 1: {

				printf( "Digite o Nome: " );
				scanf( "%49s", ( char * ) tempNome );

				printf( "Digite a Idade: " );
				scanf( "%d", ( int * ) tempIdade );

				printf("Digite seu Email: ");
				scanf( "%49s", ( char * ) tempEmail );

				// Calcula o novo tamanho necessário do buffer
				void *novo_fim = ( char * ) contador 
				+ strlen( ( char * ) tempNome ) + 1  // Nome
		        + sizeof( int )                 // Idade
		        + strlen( ( char * ) tempEmail ) + 1; // Email

				// Realoca pBuffer
				pBuffer = realloc( pBuffer, ( char * ) novo_fim - ( char * ) pBuffer );
    
				if ( pBuffer == NULL ) {
			        printf( "Erro de alocacao / memoria insuficiente\n" );
			        exit( 1 );
		    	}
    
				// Atualiza pBuffer e ajusta os ponteiros
				op        = pBuffer;
				flag      = ( char * ) op + sizeof( int );
				tempNome  = ( char * ) flag + sizeof( int );
				tempIdade = ( char * ) tempNome + ( 50 * sizeof( char ) );
				tempEmail = ( char * ) tempIdade + sizeof( int );
				busca     = ( char * ) tempEmail + ( 50 * sizeof( char ) );
				dados     = ( char * ) busca + ( 100 * sizeof( char ) );

				// Atualiza contador para apontar para o fim correto
				*( char * ) contador = ( char * ) novo_fim - ( char * ) pBuffer + ( ( char * ) contador - ( char * ) dados ) + 1;

				// Copia os novos dados para a área realocada
				memcpy( contador, tempNome, strlen( ( char *) tempNome ) + 1 );
				contador = ( char * ) contador + strlen( ( char * ) tempNome ) + 1;

				memcpy( contador, tempIdade, sizeof( int ) );
				contador = ( char * ) contador + sizeof( int );

				memcpy( contador, tempEmail, strlen( ( char * ) tempEmail ) +  1);
				contador = ( char * ) contador + strlen( ( char * ) tempEmail ) + 1;

				printf( "Cadastro adicionado com sucesso\n" );

				break;
			}

			case 2: {
				printf( "Digite o nome que deseja excluir: " );
				scanf( "%99s", ( char * ) busca );

				void *imprime = dados; //Imprime aponta para o inicio de dados
				void *fim = NULL;

				while ( imprime < contador ) {
					if ( strcmp( imprime, busca ) == 0 ) {

						printf( "NOME ENCONTRADO \n" );
						
						*( int * ) flag = 1;

						void *auxiliar = NULL;
						auxiliar = imprime; //auxiliar recebe o endereço do primeiro caracter do nome buscado
						auxiliar += strlen( ( char * ) auxiliar ) + 1;
						auxiliar += sizeof( char ) * sizeof( int );
						auxiliar += strlen( ( char * ) auxiliar ) + 1;

						fim = auxiliar;  //fim aponta para o endereço do ultimo caracter do nome buscado

						memmove( imprime, fim, ( char * ) contador - ( char * ) fim );

						contador = ( char * )contador - ( ( char * ) fim - ( char * ) imprime );

						pBuffer = realloc( pBuffer, ( char * ) contador - ( char * ) pBuffer );

						if ( pBuffer == NULL ) {
							printf( "falha ao alocar memoria\n" );
							exit( 1 );
						}

						op        = pBuffer;
						flag      = ( char * ) op + sizeof( int );
						tempNome  = ( char * ) flag + sizeof( int );
						tempIdade = ( char * ) tempNome + ( 50 * sizeof( char ) );
						tempEmail = ( char * ) tempIdade + sizeof( int );
						busca     = ( char * ) tempEmail + ( 50 * sizeof( char ) );

						printf( "Registro excluido com sucesso\n" );

						break;

					} else {
						// Caso o nome não seja encontrado, continua verificando
                        imprime += strlen( ( char * ) imprime ) + 1;  // Avança para o próximo campo (nome)
                        imprime += sizeof( int );                   // Avança para o próximo campo (idade)
                        imprime += strlen( ( char * ) imprime ) + 1;  // Avança para o próximo campo (email)
					}
				}

				if ( *( int * ) flag == 1 ) {
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
				scanf( "%99s", ( char * ) busca );

				void *imprime = dados;
				while ( imprime < contador ) {
					if ( strcmp( imprime, busca ) == 0 ) {

						printf( "NOME ENCONTRADO \n \n" );

						printf( "Nome: %s\n", ( char * ) imprime );
						imprime += strlen( ( char * ) imprime ) + 1;

						printf( "Idade: %d\n", *( int * )( char * ) imprime );
						imprime += sizeof( int );

						printf( "Email: %s\n", ( char * ) imprime );
						imprime += strlen( ( char * ) imprime ) + 1;

						*( int * ) flag = 1;

					} else {
						// Caso o nome não seja encontrado, continua verificando
                        imprime += strlen( ( char * ) imprime ) + 1;  // Avança para o próximo campo (nome)
                        imprime += sizeof( int );                   // Avança para o próximo campo (idade)
                        imprime += strlen( ( char * ) imprime ) + 1;  // Avança para o próximo campo (email)
					}
				}

				if ( *( int * ) flag == 1 ) {
					printf( "--------------------------\n" );
				} else {
					printf( "--------------------------\n" );
					printf( "Nome nao encontrado\n" );
					printf( "--------------------------\n" );
				}

				break;
			}

			case 4: {
				void *imprime = dados;

				if ( imprime == contador ) {
					printf( "--------------------------\n" );
					printf( "Nao existem pessoas cadastradas\n" );
					printf( "--------------------------\n" );
					break;
				}

				while ( imprime < contador ) {

					printf( "Nome: %s\n", ( char * ) imprime );
					imprime += strlen( ( char * ) imprime ) + 1;

					printf( "Idade: %d\n", *( int * )( char * ) imprime );
					imprime += sizeof( int );

					printf( "Email: %s\n", ( char * ) imprime );
					imprime += strlen( ( char * ) imprime ) + 1;

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
