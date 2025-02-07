typedef struct nodo
{
    double diferenca; // diferenca ao adicionar um estudante
    int pass;         // alunos que passarão no exame
    int total;        // alunos na turma
    struct nodo *prox;
} nodo;

typedef struct fila
{
    nodo *inicio;
    nodo *ultimo;
} fila;

// Função para inicializar a fila
fila *init()
{
    fila *f = (fila *)malloc(sizeof(fila));
    f->inicio = NULL;
    f->ultimo = NULL;
    return f;
}

void push(fila *fila, double diferenca, int pass, int total)
{
    nodo *novoNodo = (nodo *)malloc(sizeof(nodo));
    novoNodo->diferenca = diferenca;
    novoNodo->pass = pass;
    novoNodo->total = total;
    novoNodo->prox = NULL;

    if (fila->inicio == NULL || fila->inicio->diferenca <= diferenca)
    {

        novoNodo->prox = fila->inicio;
        fila->inicio = novoNodo;
    }
    else
    {

        nodo *temp = fila->inicio;
        while (temp->prox != NULL && temp->prox->diferenca > diferenca)
        {
            temp = temp->prox;
        }
        novoNodo->prox = temp->prox;
        temp->prox = novoNodo;
    }
}

nodo *pop(fila *fila)
{
    if (fila->inicio == NULL)
    {
        return NULL;
    }

    nodo *temp = fila->inicio;
    fila->inicio = temp->prox;
    return temp;
}

double maxAverageRatio(int **classes, int classesSize, int *classesColSize, int extraStudents)
{
    fila *f = init();
    double mediaTotal = 0.0;

    for (int i = 0; i < classesSize; i++)
    {
        int nExame = classes[i][0];
        int total = classes[i][1];
        double MediaLinha = (double)nExame / total;

        double diferenca = ((double)(nExame + 1) / (total + 1)) - MediaLinha;

        push(f, diferenca, nExame, total);
    }

    for (int i = 0; i < extraStudents; i++)
    {
        nodo *turma = pop(f);

        turma->pass = turma->pass + 1;
        turma->total = turma->total + 1;

        double novodiferenca = ((double)(turma->pass + 1) / (turma->total + 1)) - ((double)turma->pass / turma->total);

        push(f, novodiferenca, turma->pass, turma->total);
    }
    nodo *temp = f->inicio;
    while (temp != NULL)
    {
        mediaTotal += (double)temp->pass / temp->total;
        temp = temp->prox;
    }

    return mediaTotal / classesSize;
}