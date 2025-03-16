typedef struct { //cria uma estrutura para fazer um vetor que vai ter o lucro relacionado a dificuldade
    int dificuldade;
    int lucro;
} trabalho;

int compare(const void* a, const void* b) {
    return ((trabalho*)a)->dificuldade - ((trabalho*)b)->dificuldade;

    //ordena por dificuldade em ordem crescente
}

int maxProfitAssignment(int* dificuldade, int dificuldadeT, int* lucro, int lucroT, int* trabalhador, int trabalhadorT) { //mudei o nome do prototipo da funcao para entender melhor (não sei inglês)
    trabalho* trabalhos = (trabalho *) malloc ((dificuldadeT) * sizeof(trabalho)); // Aloca apenas o necessário (dificuldadeT)

    for (int i = 0; i < dificuldadeT; i++) { //bota as dificuldades e lucros nos seus respectivos lugares
        trabalhos[i].dificuldade = dificuldade[i];
        trabalhos[i].lucro = lucro[i];
    }
    
    qsort(trabalhos, dificuldadeT, sizeof(trabalho), compare); // qsort para ordenar pela dificuldade

    for (int i = 1; i < dificuldadeT; i++) {  //atualiza os lucros para eles nao diminuirem
        if (trabalhos[i].lucro < trabalhos[i - 1].lucro) {
            trabalhos[i].lucro = trabalhos[i - 1].lucro;
        }
    }

    int resposta = 0;
    for (int i = 0; i < trabalhadorT; i++) { //itera sobre numero de trabalhadores
        int habilidade = trabalhador[i]; //cada trabalhador tem apenas uma habilidade

        int lucroTrabalho = 0;
        for (int j = 0; j < dificuldadeT; j++) { //percorre o array novamente
            if (trabalhos[j].dificuldade <= habilidade) {  // se ele pode fazer o trabalho
                lucroTrabalho = trabalhos[j].lucro; //atualiza o lucro
            } else {
                break;  // se ja ta ordenado, nao precisa verificar mais trabalhos
            }
        }

        resposta += lucroTrabalho; // adiciona o lucro valido na resposta
    }

    return resposta; //retorna resposta
}
