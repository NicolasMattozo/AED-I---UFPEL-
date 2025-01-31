#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//pBuffer = ((op)+(flag)+(tempNome)+(tempIdade)+(tempEmail)+(busca)+(dados))

int main(void)
{

void *pBuffer = malloc(
sizeof(int) + //op
sizeof(int) + //flag
(50 * sizeof(char)) +  //tempNome
(sizeof(int)) + //tempIdade
(50 * sizeof(char)) + //tempEmail
(100 * sizeof(char)) + //busca
(100 * sizeof(char)) //dados
); 

if(pBuffer == NULL)
{
    printf("erro de alocacao / memoria insuficiente");
}

//VOU CRIAR PONTEIROS PARA APONTAR PARA O INICIO DE CADA DADO DENTRO DO pbuffer

void *op = pBuffer; //aponta p inicio do pbuffer
void *flag = op + sizeof(int); //aponta pro inicio de flag
void *tempNome = (char *)flag + sizeof(int); //aponta pro inicio de tempnome
void *tempIdade = (char *)tempNome + (50 * sizeof(char)); //aponta pro inicio de tempidade
void *tempEmail = (char *)tempIdade + sizeof(int); //aponta pro inicio de tempEmail
void *busca = (char *)tempEmail + (50 * sizeof(char)); //aponta pro inicio de busca
void *dados = (char *)busca + (100 * sizeof(char)); //aponta pro inicio de dados
void *contador = dados; //ponteiro pro inicio de dados que vai atualizando sempre pro ultimo caracter

 for (;;)
    {

        printf("1- Adicionar Pessoa (Nome, Idade, email)\n 2- Remover Pessoa \n 3- Buscar Pessoa \n 4- Listar todos \n 5- Sair \n");
        scanf("%d", (int *)op);

    switch (*(int *)op) {


    case 1:
                printf("Digite o Nome: ");
                scanf("%s",(char *)tempNome); // armazeno a informação no buffer temporário

                printf("Digite a Idade: ");
                scanf("%d", (int *)tempIdade); // armazeno a informação no buffer temporário

                printf("Digite seu Email: ");
                scanf("%s", (char *)tempEmail); // armazeno a informação no buffer temporário

                // Calculo o novo tamanho necessário para o buffer
                pBuffer = realloc(pBuffer, (contador - pBuffer) + strlen((char *)tempNome) + 1 + sizeof(int) + strlen((char *)tempEmail) + 1);

                if(pBuffer == NULL)
                    {
                        printf("erro de alocacao / memoria insuficiente");
                    }

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
                printf("Digite o nome que deseja excluir: ");
                scanf("%s", (char *)busca);

                void *imprime = (char *)dados; // imprime recebe o primeiro nome de pBuffer
                void *inicio = NULL;      // Posição inicial do item a excluir
                void *fim = NULL;         // Posição final do item a excluir
                                          

                while ((char *)imprime < (char *)contador) { //posição inicial de Dados < posição final do pBuffer

                    if (strcmp((char *)imprime, (char *)busca) == 0)//procura pelo nome para excluir
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
                    imprime += strlen((char *)imprime) + 1 + sizeof(int) + strlen((char *)imprime) + 1; 
                    //aqui enquanto ele nao achar ele segue andando de cadastro em cadastro até achar o nome correto

                    }
                }

               if(*(int *)flag == 1){
                    printf("--------------------------\n");
                }else{
                    printf("--------------------------\n");
                    printf("Nome nao encontrado\n");
                    printf("--------------------------\n");
                }

            }   
            break;
    case 3:
            {
    
                printf("Digite o nome que deseja buscar: ");
                scanf("%s", (char *)busca);

                void *imprime = (char *)dados;  // imprime recebe o primeiro nome de pBuffer
                while ((char *)imprime < (char *)contador) { //posição inicial de Dados < posição final do pBuffer

                    if(strcmp((char *)imprime, (char *)busca) == 0)
                    {
                    
                    printf("Nome: %s\n", (char *)imprime); // Imprime o nome
                    imprime += strlen((char *)imprime) + 1; //incrementa o imprime com o numero de pos do nome

                    
                    printf("Idade: %d\n", *(int *)(char *)imprime); // Imprime a idade
                    imprime += sizeof(int); //incrementa o imprime com o numero de pos da idade

                    
                    printf("Email: %s\n", (char *)imprime); // Imprime o email
                    imprime += strlen((char *)imprime) + 1; //incrementa o imprime com o numero de pos do email


                    *(int *)flag = 1; //se leu o nome ele ativa essa flag
                    
                    }
                    else{
                    imprime += strlen((char *)imprime) + 1 + sizeof(int) + strlen((char *)imprime) + 1; 
                    //aqui enquanto ele nao achar ele segue andando de cadastro em cadastro até achar o nome correto

                    }
                }
                if(*(int *)flag == 1){
                    printf("--------------------------\n");
                }else{
                    printf("--------------------------\n");
                    printf("Nome nao encontrado\n");
                    printf("--------------------------\n");
                }
            }
            break;
    case 4:
                {
                void *imprime = (char *)dados;  // imprime recebe o primeiro nome de pBuffer

                if((char *)imprime == (char *)contador){
                    printf("--------------------------\n");
                    printf("Nao existem pessoas cadastradas\n");
                    printf("--------------------------\n");
                }


                while ((char *)imprime < (char *)contador) { //posição inicial de Dados < posição final do pBuffer
                    
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
        {
                free(pBuffer);
                printf("Programa Finalizado com Sucesso");
                exit(0);
        }
    }
}
    return 0;
}
