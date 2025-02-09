typedef struct nodo_t {
    double diferenca; // diferenca ao adicionar um estudante
    int pass;         // alunos que passarão no exame
    int total;        // alunos na turma
    struct nodo_t *prox;
} nodo_t;

typedef struct fila_t {
    nodo_t *inicio;
    nodo_t *ultimo;
} fila_t;

/*
====================
Init
 Inicializa a fila.
====================
*/
fila_t *Init( void ) {
    fila_t *f = (fila_t *)malloc( sizeof( fila_t ) );
    f->inicio = NULL;
    f->ultimo = NULL;
    return f;
}

/*
====================
Push
 Adiciona um novo nó à fila com base na diferença (prioridade).
====================
*/
void Push( fila_t *fila, double diferenca, int pass, int total ) {
    nodo_t *novoNodo = (nodo_t *)malloc( sizeof( nodo_t ) );
    novoNodo->diferenca = diferenca;
    novoNodo->pass = pass;
    novoNodo->total = total;
    novoNodo->prox = NULL;

    if ( fila->inicio == NULL || fila->inicio->diferenca <= diferenca ) {
        novoNodo->prox = fila->inicio;
        fila->inicio = novoNodo;
    } else {
        nodo_t *temp = fila->inicio;
        while ( temp->prox != NULL && temp->prox->diferenca > diferenca ) {
            temp = temp->prox;
        }
        novoNodo->prox = temp->prox;
        temp->prox = novoNodo;
    }
}

/*
====================
Pop
 Remove e retorna o nó de maior prioridade (início da fila).
====================
*/
nodo_t *Pop( fila_t *fila ) {
    if ( fila->inicio == NULL ) {
        return NULL;
    }

    nodo_t *temp = fila->inicio;
    fila->inicio = temp->prox;
    return temp;
}

/*
====================
MaxAverageRatio
 Calcula a média máxima das razões após adicionar alunos extras.
====================
*/
double maxAverageRatio( int **classes, int classesSize, int *classesColSize, int extraStudents ) {
    fila_t *f = Init();
    double mediaTotal = 0.0f;

    for ( int i = 0; i < classesSize; i++ ) {
        int nExame = classes[i][0];
        int total = classes[i][1];
        double MediaLinha = (double)nExame / total;

        double diferenca = ( (double)( nExame + 1 ) / ( total + 1 ) ) - MediaLinha;

        Push( f, diferenca, nExame, total );
    }

    for ( int i = 0; i < extraStudents; i++ ) {
        nodo_t *turma = Pop( f );

        turma->pass = turma->pass + 1;
        turma->total = turma->total + 1;

        double novodiferenca = ( (double)( turma->pass + 1 ) / ( turma->total + 1 ) ) - ( (double)turma->pass / turma->total );

        Push( f, novodiferenca, turma->pass, turma->total );
    }

    nodo_t *temp = f->inicio;
    while ( temp != NULL ) {
        mediaTotal += (double)temp->pass / temp->total;
        temp = temp->prox;
    }

    return mediaTotal / classesSize;
}