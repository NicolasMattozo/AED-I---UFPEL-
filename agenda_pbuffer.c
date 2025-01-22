#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{


void *tempNome = malloc(500 * sizeof(char)); //Cria um ponteiro buff para servir de suporte para armazenar as informações
void *tempIdade = malloc(10 * sizeof(int));
void *tempEmail = malloc(500 * sizeof(char));
void *escolha = malloc(sizeof(int)); //Cria o ponteiro escolha, para armazenar a opção escolhida
void *pBuffer = malloc(1); //Cria o ponteiro pBuffer, para armazenar os dados
void *contador = pBuffer; // Ponteiro 'void' usado como contador para o próximo espaço




 for (;;)
    {

        printf("1- Adicionar Pessoa (Nome, Idade, email)\n 2- Remover Pessoa \n 3- Buscar Pessoa \n 4- Listar todos \n 5- Sair \n");
        scanf("%d", (int *)escolha);

    switch (*(int *)escolha) {


    case 1:
                printf("Digite o Nome: ");
                scanf("%s", (char *)tempNome); // Armazeno a informação no buffer temporário

                printf("Digite a Idade: ");
                scanf("%d", (int *)tempIdade); // Armazeno a informação no buffer temporário

                printf("Digite seu Email: ");
                scanf("%s", (char *)tempEmail); // Armazeno a informação no buffer temporário

                // Calculo o novo tamanho necessário para o buffer
                void *novoBuffer = realloc(pBuffer, (contador - pBuffer) + strlen((char *)tempNome) + 1 + sizeof(int) + strlen((char *)tempEmail) + 1);

                if (novoBuffer == NULL)
                {
                    printf("Nao foi possivel alocar memoria.\n");
                    exit(1);
                }
                pBuffer = novoBuffer;

                // Copio os dados para o buffer realocado
                memcpy(contador, tempNome, strlen((char *)tempNome) + 1); // copio o nome para meu pBuffer
                contador = (char *)contador + strlen((char *)tempNome) + 1; // muda o contador para o proximo lugar disponivel

                memcpy(contador, tempIdade, sizeof(int)); // copio a idade
                contador = (char *)contador + sizeof(int); // muda o contador

                memcpy(contador, tempEmail, strlen((char *)tempEmail) + 1); // copio o email
                contador = (char *)contador + strlen((char *)tempEmail) + 1; // movo o contador

                printf("Cadastro adicionado com sucesso.\n");

                break;



    case 2:
            //     {
            //     printf("Digite o nome que deseja buscar: ");
            //     scanf("%s", (char *)tempBusca);

            //     void *imprime = (char *)pBuffer;  // imprime recebe o primeiro nome de pBuffer
            //     while ((char *)imprime < (char *)contador) { //posição inicial de pBuffer < posição final do pBuffer

            //         if(*(char *)imprime == *(char *)tempBusca)
            //         {
                    
            //         printf("Nome: %s\n", (char *)imprime); // Imprime o nome
            //         imprime += strlen((char *)imprime) + 1; //incrementa o imprime com o numero de pos do nome

                    
            //         printf("Idade: %d\n", *(int *)(char *)imprime); // Imprime a idade
            //         imprime += sizeof(int); //incrementa o imprime com o numero de pos da idade

                    
            //         printf("Email: %s\n", (char *)imprime); // Imprime o email
            //         imprime += strlen((char *)imprime) + 1; //incrementa o imprime com o numero de pos do email

            //         printf("--------------------------\n");
                    
            //         }
            //         else{
            //         imprime += strlen((char *)imprime) + 1;
            //         imprime += sizeof(int);
            //         imprime += strlen((char *)imprime) + 1;
            //         }
            //     }
            //     free(tempBusca);
            // }
    case 3:
            {
                void *flag = malloc (sizeof(int));
                *(int *)flag = 0;
                void *tempBusca = malloc(500 * sizeof(char));
                printf("Digite o nome que deseja buscar: ");
                scanf("%s", (char *)tempBusca);

                void *imprime = (char *)pBuffer;  // imprime recebe o primeiro nome de pBuffer
                while ((char *)imprime < (char *)contador) { //posição inicial de pBuffer < posição final do pBuffer

                    if(*(char *)imprime == *(char *)tempBusca)
                    {
                    
                    printf("Nome: %s\n", (char *)imprime); // Imprime o nome
                    imprime += strlen((char *)imprime) + 1; //incrementa o imprime com o numero de pos do nome

                    
                    printf("Idade: %d\n", *(int *)(char *)imprime); // Imprime a idade
                    imprime += sizeof(int); //incrementa o imprime com o numero de pos da idade

                    
                    printf("Email: %s\n", (char *)imprime); // Imprime o email
                    imprime += strlen((char *)imprime) + 1; //incrementa o imprime com o numero de pos do email

                    printf("--------------------------\n");
                    *(int *)flag = 1;
                    
                    }
                    else{
                    imprime += strlen((char *)imprime) + 1;
                    imprime += sizeof(int);
                    imprime += strlen((char *)imprime) + 1;
                    }
                }
                free(tempBusca);
                if(*(int *)flag == 0){
                    printf("Nome nao encontrado\n");
                }
            }
            break;
    case 4:
                {
                void *imprime = (char *)pBuffer;  // imprime recebe o primeiro nome de pBuffer
                while ((char *)imprime < (char *)contador) { //posição inicial de pBuffer < posição final do pBuffer
                    
                    printf("Nome: %s\n", (char *)imprime); // Imprime o nome
                    imprime += strlen((char *)imprime) + 1; //incrementa o imprime com o numero de pos do nome

                    
                    printf("Idade: %d\n", *(int *)(char *)imprime); // Imprime a idade
                    imprime += sizeof(int); //incrementa o imprime com o numero de pos da idade

                    
                    printf("Email: %s\n", (char *)imprime); // Imprime o email
                    imprime += strlen((char *)imprime) + 1; //incrementa o imprime com o numero de pos do email

                    printf("--------------------------\n");
                }
            }
            break;
    case 5:
                free(tempNome);
                free(tempIdade);
                free(tempEmail);
                free(escolha);
                free(pBuffer);
                free(contador);
                printf("Programa Finalizado com Sucesso");
                exit(0);
        }
    }
    return 0;

}