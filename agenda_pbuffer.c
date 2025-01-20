#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{

void *pBuffer = malloc(500 * sizeof(void *)); //Cria o ponteiro pBuffer, para armazenar os dados
void *escolha = malloc(sizeof(int)); //Cria o ponteiro escolha, para armazenar a opção escolhida


 for (;;)
    {

        printf("1- Adicionar Pessoa (Nome, Idade, email)\n 2- Remover Pessoa \n 3- Buscar Pessoa \n 4- Listar todos \n 5- Sair \n" );
        scanf("%d", (int *)escolha);

        
        switch (*(int *)escolha)
        {
        case 1:
            printf("teste");
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