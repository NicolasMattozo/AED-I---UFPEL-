#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// pBuffer = ((op) + (flag) + (tempNome) + (tempIdade) + (tempEmail) + (busca) + (dados))

int main( void ) {


    // Alocação de memória para armazenar todas as variáveis necessárias
	void *pBuffer = malloc(
		sizeof( int ) +	// op    //Opção escolhida pelo usuario
		sizeof( int ) +	// flag    //Flag para verificar leitura do nome
		( 50 * sizeof( char ) ) + // tempNome    //Nome Temporario
		sizeof( int ) + // tempIdade    //Idade Temporaria
		( 50 * sizeof( char ) ) + // tempEmail  //Email Temporario
		( 100 * sizeof( char ) ) + // busca    //Nome a ser Buscado
		( 100 * sizeof( char ) ) // dados    //Dados Cadastrados
	); 

	if ( pBuffer == NULL ) {
		printf( "erro de alocacao / memoria insuficiente" );
	}

	// Criação de ponteiros para o inicio de cada "operação" dentro do pBuffer 
	void *op        = pBuffer; // aponta para inicio do pBuffer
	void *flag      = op + sizeof( int ); // aponta para o inicio de flag
	void *tempNome  = ( char * ) flag + sizeof( int ); // aponta para o inicio de tempNome
	void *tempIdade = ( char * ) tempNome + ( 50 * sizeof( char ) ); // aponta para o inicio de tempIdade
	void *tempEmail = ( char * ) tempIdade + sizeof( int ); // aponta para o inicio de tempEmail
	void *busca     = ( char * ) tempEmail + ( 50 * sizeof( char ) ); // aponta para o inicio de busca
	void *dados     = ( char * ) busca + ( 100 * sizeof( char ) ); // aponta para o inicio de dados
	void *contador  = dados; // ponteiro pro inicio de dados que vai atualizando sempre pro ultimo caracter

	for ( ;; ) {
		printf( "1- Adicionar Pessoa (Nome, Idade, Email)\n 2- Remover Pessoa \n 3- Buscar Pessoa \n 4- Listar todos \n 5- Sair \n \n" );
        printf("Digite a opcao: ");
		scanf( "%d", ( int * ) op );

		switch ( *( int * ) op ) {

			case 1: {    // Adicionar nova pessoa
                printf("\n");
				printf( "Digite o Nome: " );
				scanf( "%s", ( char * ) tempNome );    // Lendo nome do usuário

                printf("\n");
				printf( "Digite a Idade: " );
				scanf( "%d", ( int * ) tempIdade );    // Lendo idade do usuário

                printf("\n");
				printf( "Digite seu Email: " );
				scanf( "%s", ( char * ) tempEmail );    // Lendo email do usuário

                // Realocando memória para armazenar os novos dados
				pBuffer = realloc( pBuffer, ( contador - pBuffer ) + strlen( ( char * ) tempNome ) + 1 + sizeof( int ) + strlen( ( char * ) tempEmail ) + 1 );

				if ( pBuffer == NULL ) {
					printf( "erro de alocacao / memoria insuficiente" );
				}

                // Copiando os dados para o buffer
				memcpy( contador, tempNome, strlen( ( char * ) tempNome ) + 1 );    // copio o nome para pBuffer
				contador = ( char * ) contador + strlen( ( char * ) tempNome ) + 1;    //incrementa o contador

				memcpy( contador, tempIdade, sizeof( int ) );    // copia a idade para pBuffer
				contador = ( char * ) contador + sizeof( int );    //incrementa o contador

				memcpy( contador, tempEmail, strlen( ( char * ) tempEmail ) + 1 );    //copia o email para pBuffer
				contador = ( char * ) contador + strlen( ( char * ) tempEmail ) + 1;    //incrementa o contador

                printf("\n");
				printf( "Cadastro adicionado com sucesso\n" );

				break;
			}

			case 2: {    // Excluindo Cadastro
                printf("\n");
				printf( "Digite o nome que deseja excluir: " );
				scanf( "%s", ( char * ) busca );    // Lendo o nome que será excluído

				void *imprime = ( char * ) dados;    // Início da memória dos dados
				void *inicio = NULL;    // Posição inicial do item a excluir
				void *fim = NULL;    // Posição final do item a excluir

                // Percorre a lista procurando o nome
				while ( ( char * ) imprime < ( char * ) contador ) { //posição inicial de Dados < posição final do pBuffer

					if ( strcmp( ( char * ) imprime, ( char * ) busca ) == 0 ) { //procura pelo nome para excluir
						inicio = imprime;    // Posição inicial do item encontrado
						*( int * ) flag = 1;    //ativa a flag e indica que achou o nome

						void *auxiliar = imprime;

                        //nome
						auxiliar += strlen( ( char * ) auxiliar ) + 1; //++ o auxiliar com o numero de pos do nome

                        //idade
						auxiliar += sizeof( char ) * sizeof( int ); //++ o auxiliar com o numero de pos da idade

                        //email
						auxiliar += strlen( ( char * ) auxiliar ) + 1; //++ o auxiliar com o numero de pos do email

						fim = auxiliar;    //aponto para o final do cadastro da pessoa lida

                         //imprime recebe auxiliar com numero de bytes dado pelo n° total - final do cad da pessoa lida
						memmove( imprime, auxiliar, ( char * ) contador - ( char * ) auxiliar );

                        // realloc no pBuffer para diminuir o espaco de memoria 
						pBuffer = realloc( pBuffer, ( char * ) contador - ( char * ) pBuffer );

                        // arrumo o valor do contador para ele apontar para o novo final 
						contador = ( char * ) inicio + ( ( char * ) contador - ( char * ) fim );

						if ( pBuffer == NULL ) {
							printf( "falha ao alocar memoria\n" );
							exit( 1 );
						}

                        printf("\n");
                        printf( "--------------------------\n" );
						printf( "Registro excluido com sucesso\n" );

					} else {
                        //aqui enquanto ele nao achar ele segue andando de cadastro em cadastro até achar o nome correto
						imprime += strlen( ( char * ) imprime ) + 1 + sizeof( int ) + strlen( ( char * ) imprime ) + 1;
                        
					}
				}

				if ( *( int * ) flag == 1 ) {    //Se o nome foi encontrado ele printa apenas a linha
					printf( "--------------------------\n" );
                    printf("\n");
				} else {
                    printf("\n");
					printf( "--------------------------\n" );
					printf( "Nome nao encontrado\n" );
					printf( "--------------------------\n" );
                    printf("\n");
				}

				break;
			}

			case 3: {    //Buscando Nome
                printf("\n");
				printf( "Digite o nome que deseja buscar: " );
				scanf( "%s", ( char * ) busca );    // Lendo nome para busca

				void *imprime = ( char * ) dados;    // Ponteiro inicial para percorrer os dados

                // Percorre a lista procurando o nome
				while ( ( char * ) imprime < ( char * ) contador ) {//pos inicial de Dados < pos final do pBuffer

					if ( strcmp( ( char * ) imprime, ( char * ) busca ) == 0 ) {

                        *( int * ) flag = 1;    //ativa a flag e indica que achou o nome
                        
                        printf("\n");
                        printf( "--------------------------\n" );

                        
						printf( "Nome: %s\n", ( char * ) imprime );    // Exibe nome
						imprime += strlen( ( char * ) imprime ) + 1; //incrementa o imprime com o numero de pos do nome

                        printf("\n");
						printf( "Idade: %d\n", *( int * )( char * ) imprime );    // Exibe idade
						imprime += sizeof( int ); //incrementa o imprime com o numero de pos do nome

                        printf("\n");
						printf( "Email: %s\n", ( char * ) imprime );    // Exibe email
						imprime += strlen( ( char * ) imprime ) + 1; //incrementa o imprime com o numero de pos do nome 

						*( int * ) flag = 1;    // Define flag como encontrada

					} else {
                        //aqui enquanto ele nao achar ele segue andando de cadastro em cadastro até achar o nome correto
						imprime += strlen( ( char * ) imprime ) + 1 + sizeof( int ) + strlen( ( char * ) imprime ) + 1;
					}
				}

				if ( *( int * ) flag == 1 ) {    //Se o nome foi encontrado ele printa apenas a linha
					printf( "--------------------------\n" );
                    printf("\n");
				} else {
                    printf("\n");
					printf( "--------------------------\n" );
					printf( "Nome nao encontrado\n" );
					printf( "--------------------------\n" );
                    printf("\n");
				}

				break;
			}

			case 4: {    //Listando Nomes
				void *imprime = ( char * ) dados;    // imprime recebe o primeiro nome de pBuffer

                // Verifica se há cadastros
				if ( ( char * ) imprime == ( char * ) contador ) {
                    printf("\n");
					printf( "--------------------------\n" );
					printf( "Nao existem pessoas cadastradas\n" );
					printf( "--------------------------\n" );
                    printf("\n");
				}

                // Percorre e exibe os dados cadastrados
				while ( ( char * ) imprime < ( char * ) contador ) {    //pos inicial de Dados < pos final do pBuffer

                    printf("\n");
                    printf( "--------------------------\n" );
                    
                    
					printf( "Nome: %s\n", ( char * ) imprime );    // Imprime o Nome
					imprime += strlen( ( char * ) imprime ) + 1;    //incrementa o imprime com o numero de pos do nome 

                    printf("\n");
					printf( "Idade: %d\n", *( int * )( char * ) imprime );    // Imprime o Idade
					imprime += sizeof( int );    //incrementa o imprime com o numero de pos do nome 

                    printf("\n");
					printf( "Email: %s\n", ( char * ) imprime );    // Imprime o Email
					imprime += strlen( ( char * ) imprime ) + 1;    //incrementa o imprime com o numero de pos do nome 

					printf( "--------------------------\n" );
                    printf("\n");
				}

				break;
			}

			case 5: {    //Saindo do Programa
				free( pBuffer );    //Libera a memoria alocada por pBuffer
                printf("\n");
				printf( "Programa Finalizado com Sucesso" );  //Exibe mensagem de finalização
				exit( 0 );
			}
		}
	}

	return 0;
}
