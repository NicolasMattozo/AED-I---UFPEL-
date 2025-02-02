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
void *contador = pBuffer; 

if(tempNome == NULL || tempIdade == NULL || tempEmail == NULL || escolha == NULL || pBuffer == NULL)
{
    printf("Alocacao falhou");
    exit(1);
}


 for (;;)
    {

        printf("1- Adicionar Pessoa (Nome, Idade, email)\n 2- Remover Pessoa \n 3- Buscar Pessoa \n 4- Listar todos \n 5- Sair \n");
        scanf("%d", (int *)escolha);

    switch (*(int *)escolha) {


    case 1:
                printf("Digite o Nome: ");
                scanf("%s", (char *)tempNome); // armazeno a informação no buffer temporário

                printf("Digite a Idade: ");
                scanf("%d", (int *)tempIdade); // armazeno a informação no buffer temporário

                printf("Digite seu Email: ");
                scanf("%s", (char *)tempEmail); // armazeno a informação no buffer temporário

                // Calculo o novo tamanho necessário para o buffer
                void *novoBuffer = realloc(pBuffer, (contador - pBuffer) + strlen((char *)tempNome) + 1 + sizeof(int) + strlen((char *)tempEmail) + 1);

                if (novoBuffer == NULL)
                {
                    printf("Nao foi possivel alocar memoria\n");
                    exit(1);
                }
                pBuffer = novoBuffer;

                // copio os dados para o buffer realocado
                memcpy(contador, tempNome, strlen((char *)tempNome) + 1); // copio o nome para meu pBuffer
                contador = (char *)contador + strlen((char *)tempNome) + 1; // muda o contador para o proximo lugar disponivel

                memcpy(contador, tempIdade, sizeof(int)); // copio a idade
                contador = (char *)contador + sizeof(int); // muda o contador

                memcpy(contador, tempEmail, strlen((char *)tempEmail) + 1); // copio o email
                contador = (char *)contador + strlen((char *)tempEmail) + 1; // movo o contador

                printf("Cadastro adicionado com sucesso\n");

                break;



    case 2:
            {
                void *flag = malloc (sizeof(int));
                if(flag == NULL)
                {
                    printf("Alocacao falhou");
                    exit(1);
                }
                *(int *)flag = 0; //apenas uma flag para saber se o nome foi encontrado


                void *tempBusca = malloc(500 * sizeof(char));
                if(tempBusca == NULL)
                {
                    printf("Alocacao falhou");
                    exit(1);
                }


                printf("Digite o nome que deseja excluir: ");
                scanf("%s", (char *)tempBusca);

                void *imprime = (char *)pBuffer; // imprime recebe o primeiro nome de pBuffer
                void *inicio = NULL;      // Posição inicial do item a excluir
                void *fim = NULL;         // Posição final do item a excluir
                                          

                while ((char *)imprime < (char *)contador) { //posição inicial de pBuffer < posição final do pBuffer

                    if (strcmp((char *)imprime, (char *)tempBusca) == 0)//procura pelo nome para excluir
                    {
                        inicio = imprime;  // Posição inicial do item encontrado

                        *(int *)flag = 1; //ativa a flag e indica que achou o nome

                    void *auxiliar = imprime;
                    //nome
                    auxiliar += strlen((char *)auxiliar) + 1; //++ o imprime com o numero de pos do nome
                    //idade
                    auxiliar += sizeof(char) * sizeof(int); //++ o imprime com o numero de pos da idade
                    //email
                    auxiliar += strlen((char *)auxiliar) + 1; //++ o imprime com o nº de pos do email

                    fim = auxiliar; //aponto para o final do cadastro da pessoa lida

                    memmove(imprime, auxiliar, (char *)contador - (char *)auxiliar); 
                    //jogo para imprime o meu auxiliar com numero de bytes dado pelo numero total - final do cad da pessoa lida

                    pBuffer = realloc(pBuffer, (char *)contador - (char *)pBuffer);
                    // realloc no pBuffer para diminuir o espaco de memoria 

                    contador = (char *)inicio + ((char *)contador - (char *)fim);
                    // arrumo o valor do contador para ele apontar para o novo final 

                    if(pBuffer == NULL)
                    {
                        printf("falha ao alocar memoria\n");
                        exit(1);
                    }

                    printf("Registro excluido com sucesso\n");
                    
                    }else{
                    imprime += strlen((char *)imprime) + 1;
                    imprime += sizeof(int);
                    imprime += strlen((char *)imprime) + 1;
                    }
                }

                if(*(int *)flag == 0){
                    printf("Nome nao encontrado\n");
                }

                 free(tempBusca); //free no tempBusca para não acontecer erros
                 free(flag); //free no flag para não acontecer erros

            }   
            break;
    case 3:
            {
                void *flag = malloc (sizeof(int));
                *(int *)flag = 0; //apenas uma flag para saber se o nome foi encontrado
                void *tempBusca = malloc(500 * sizeof(char));
                printf("Digite o nome que deseja buscar: ");
                scanf("%s", (char *)tempBusca);

                void *imprime = (char *)pBuffer;  // imprime recebe o primeiro nome de pBuffer
                while ((char *)imprime < (char *)contador) { //posição inicial de pBuffer < posição final do pBuffer

                    if(strcmp((char *)imprime, (char *)tempBusca) == 0)
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
                free(tempBusca); //free no tempBusca para não acontecer erros
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