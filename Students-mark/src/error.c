typedef struct nodoFila
{
    int alunos;
    struct nodoFila *prox;
} nodoFila;

typedef struct fila
{
    nodoFila *inicio;
    nodoFila *ultimo;
} fila;

// Funções da fila
fila *initFila()
{
    fila *f = (fila *)malloc(sizeof(fila));
    f->inicio = NULL;
    f->ultimo = NULL;
    return f;
}

void enqueue(fila *f, int c)
{
    nodoFila *novoNodo = (nodoFila *)malloc(sizeof(nodoFila));
    novoNodo->alunos = c;
    novoNodo->prox = NULL;

    if (f->inicio == NULL)
    {
        f->inicio = novoNodo;
        f->ultimo = novoNodo;
    }
    else
    {
        f->ultimo->prox = novoNodo;
        f->ultimo = novoNodo;
    }
}

int dequeue(fila *f)
{
    if (f->inicio == NULL)
        return -1;
    nodoFila *temp = f->inicio;
    int c = temp->alunos;
    f->inicio = temp->prox;
    if (f->inicio == NULL)
        f->ultimo = NULL;
    free(temp);
    return c;
}

int peek(fila *f)
{
    if (f->inicio == NULL)
        return -1;
    return f->inicio->alunos;
}

bool IsEmptyF(fila *f)
{
    return (f->inicio == NULL);
}

double maxAverageRatio(int **classes, int classesSize, int *classesColSize, int extraStudents)
{

    /*
    a ideia é botar todos as classes na fila, depois eu vou tirando de dois em dois da fila e já
    vou fazendo a media por classes, depois novamente insiro na lista e faço novamente a media, so que dessa vez a media total.
    */

    // pass = numero de alunos que passsam no exame
    // total = total de alunos
    int valor1;
    int valor2;
    double media;

    fila *f = initFila();                                               // inicio minha fila
    int **mediaAprovados = (int **)malloc(classesSize * sizeof(int *)); // aloco o numero de linhas
    int *mediaFinal = (int *)malloc(classesSize * sizeof(int));

    ///////////////////////////FAZ A MEDIA POR LINHAS///////////////////////////////////////

    for (int i = 0; i < classesSize; i++)
    { // numero de classes me retorna quantas classes eu tenho

        for (int j = 0; j < 2; j++)
        {                              // sabendo que tem n° de alunos apv exame e numero total de alunos
            enqueue(f, classes[i][j]); // bota os dois na fila [(0)pass, (1)total]
        }
    }

    for (int i = 0; i < classesSize; i++)
    { // numero de classes me retorna quantas classes eu tenho

        mediaAprovados[i] = (int *)malloc(sizeof(int)); // aloco duas colunas para cada linha

        for (int j = 0; j < 1; j++)
        { // sabendo que tem n° de alunos apv exame e numero total de alunos

            valor1 = dequeue(f); // boto o primeiro valor no valor1
            valor2 = dequeue(f); // boto o segundo valor no valor2

            mediaAprovados[i][j] = (valor1 / valor2); // mediaaprovados recebe o a media
        }
    }

    ///////////////////////////////FAZ A MEDIA TOTAL SOMANDO LINHAS///////////////////////////////////////

    for (int i = 0; i < classesSize; i++)
    { // numero de classes me retorna quantas classes eu tenho

        for (int j = 0; j < 1; j++)
        {                                     // sabendo que tem n° de alunos apv exame e numero total de alunos
            enqueue(f, mediaAprovados[i][j]); // bota os dois na fila [(0)pass, (1)total]
        }
    }

    for (int i = 0; i < classesSize; i++)
    { // numero de classes me retorna quantas classes eu tenho

        mediaAprovados[i] = (int *)malloc(sizeof(int)); // aloco duas colunas para cada linha

        for (int j = 0; j < 1; j++)
        { // sabendo que tem n° de alunos apv exame e numero total de alunos

            media += dequeue(f); // soma todos os valores;
        }
    }

    media = (media / classesSize) + (extraStudents / 100); // FINALMENTE CHEGA NA MEDIA

    /////////////////////////////////////////////////////////////////////////////////////////////////////

    return media;

    // ainda nao sei de que forma usar o extraStudents e preciso confirmar se classesSize realmente retorna o que eu preciso
}
