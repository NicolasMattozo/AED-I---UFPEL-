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



 for (;;)
    {

        printf("1- Adicionar Pessoa (Nome, Idade, email)\n 2- Remover Pessoa \n 3- Buscar Pessoa \n 4- Listar todos \n 5- Sair \n" );
        scanf("%d", (int *)escolha);


        switch (*(int *)escolha)
        {
        case 1:

            printf("Digite o Nome: ");
            scanf("%s", (char *)tempNome); //Armazeno a informação no buff

            printf("Digite a Idade:");
            scanf("%d", (int *)tempIdade); //Armazeno a informação no buff
           
            printf("Digite seu Email:");
            scanf("%s", (char *)tempEmail); //Armazeno a informação no buff

            void *novoBuffer = realloc(pBuffer, strlen((char *)tempNome) + sizeof(int) + strlen((char *)tempEmail));


            if (novoBuffer == NULL)
            {
                printf("nao foi possivel alocar memoria \n");
                exit(1);
            }
            pBuffer = novoBuffer;

            memcpy(pBuffer, tempNome, strlen((char *)tempNome) + 1);

            memcpy((char *)pBuffer + strlen((char *)tempNome) + 1, tempIdade, sizeof(int));

            memcpy((char *)pBuffer + strlen((char *)tempNome) + 1 + sizeof(int), tempEmail, strlen((char *)tempEmail) + 1);

            printf("Seu nome é: %s\n", (char *)pBuffer);
            printf("Sua idade é: %d\n", *(int *)((char *)pBuffer + strlen((char *)pBuffer) + 1));
            printf("Seu email é: %s\n", (char *)((char *)pBuffer + strlen((char *)pBuffer) + 1 + sizeof(int)));
            break;


        case 2:
            printf("teste");
            break;
        case 3:
            printf("teste");
            break;
        case 4:
            printf("teste");
            break;
        case 5:
            printf("teste");
            exit(1);
        }
    }
    return 0;

    free(pBuffer);
}