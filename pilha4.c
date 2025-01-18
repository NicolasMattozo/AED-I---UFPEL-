#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countStudents(int* students, int studentsSize, int* sandwiches, int sandwichesSize);

int main(){
    int studentsSize = 4;
    int sandwichesSize = 4;
    int sandwiches[] = {0,1,0,1};
    int students[] = {1,1,0,0};
    int resultado = countStudents(students, studentsSize, sandwiches, sandwichesSize);

    printf("o resultado é %d", resultado);


}

int countStudents(int* students, int studentsSize, int* sandwiches, int sandwichesSize) {

    typedef struct nodo{
        int sanduiche;
        struct nodo *prox;
    }nodo;

    nodo *pilha = NULL;
    nodo *ultimo = NULL;
    
    void push(nodo **topo, nodo **ultimo, int c)
    {
        nodo *novoNodo = (nodo *) malloc (sizeof(nodo));

        if(novoNodo == NULL)
        {
            return; //verifica se é possivel alocar memoria 
        }


        if(*topo == NULL)
        {
            *ultimo = novoNodo;
        }

        novoNodo->sanduiche = c;
        novoNodo->prox = *topo;
        *topo = novoNodo;
    }

    int pop(nodo **topo)
    {   
         if(*topo == NULL)
         {
            return -1;
         }
         nodo *temp = *topo;
         int c = temp->sanduiche;
         *topo = (*topo)->prox;
         free(temp);
         return c;     
    }

    int top(nodo *topo)
    {
        if(topo != NULL)
        {
            return topo->sanduiche;
        }else{
            return -1;
        }
    }
    int count = 0;
  int i = -1;

     for(int l = 0; l < sandwichesSize; l++)
    {
        push(&pilha, &ultimo, sandwiches[l]); //empilha os sanduiches
    }

    for(int l = 0; l < studentsSize; l++){ //aqui ele conta o numero de estudantes
    
    if(students[l] == top(pilha))
    {
        pop(&pilha); ///CASO O ESTUDANTE CONSIGA PEGAR DE PRIMEIRA O SEU SANDUICHE
        i++;
    }
    else {
        int temporario = students[i]; //se ele nao conseguir, passa ele p uma variavel temp
        int k = i; // pega o valor do indice que ele esta
        for(int j = i+1; j < studentsSize; j++) //faz um for contando do indice +1
        {
            students[k] = students[j]; //realoca os valores de students
            k++; //pega o proximo indice para realocar valores
        }
        students[studentsSize-1] = temporario; //bota no ultimo indice o valor temporario
        count++;
    }
    }

    int variavel = 0;
    int flag = 0;

    if(pilha != NULL)
    {
        flag = 1;
    }
    while (pilha != NULL){ //literalmente aqui ele conta se ainda tem sanduba na pilha
        variavel++; //se tem entao ele faz o count 
        pop(&pilha); //e desempilha o sanduba 
    }
    
    if(count == variavel && flag == 1){
        return variavel-count;
    }else{
        return variavel+1;
    }
}