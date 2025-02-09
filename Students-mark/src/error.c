typedef struct nodoFila_t {
    int alunos;
    struct nodoFila_t *prox;
} nodoFila_t;

typedef struct fila_t {
    nodoFila_t *inicio;
    nodoFila_t *ultimo;
} fila_t;

/*
====================
InitFila
 Inicializa a fila.
====================
*/
fila_t *InitFila( void ) {
    fila_t *f = (fila_t *)malloc( sizeof( fila_t ) );
    f->inicio = NULL;
    f->ultimo = NULL;
    return f;
}

/*
====================
Enqueue
 Adiciona um novo nó à fila.
====================
*/
void Enqueue( fila_t *f, int c ) {
    nodoFila_t *novoNodo = (nodoFila_t *)malloc( sizeof( nodoFila_t ) );
    novoNodo->alunos = c;
    novoNodo->prox = NULL;

    if ( f->inicio == NULL ) {
        f->inicio = novoNodo;
        f->ultimo = novoNodo;
    } else {
        f->ultimo->prox = novoNodo;
        f->ultimo = novoNodo;
    }
}

/*
====================
Dequeue
 Remove e retorna o nó do início da fila.
====================
*/
int Dequeue( fila_t *f ) {
    if ( f->inicio == NULL ) {
        return -1;
    }

    nodoFila_t *temp = f->inicio;
    int c = temp->alunos;
    f->inicio = temp->prox;

    if ( f->inicio == NULL ) {
        f->ultimo = NULL;
    }

    free( temp );
    return c;
}

/*
====================
Peek
 Retorna o valor do nó no início da fila sem removê-lo.
====================
*/
int Peek( fila_t *f ) {
    if ( f->inicio == NULL ) {
        return -1;
    }
    return f->inicio->alunos;
}

/*
====================
IsEmptyF
 Verifica se a fila está vazia.
====================
*/
bool IsEmptyF( fila_t *f ) {
    return ( f->inicio == NULL );
}

/*
====================
MaxAverageRatio
 Calcula a média máxima das razões após adicionar alunos extras.
====================
*/
double maxAverageRatio( int **classes, int classesSize, int *classesColSize, int extraStudents ) {
    /*
    A ideia é botar todas as classes na fila, depois tirar de dois em dois da fila e
    calcular a média por classes. Em seguida, reinserir na lista e calcular a média total.
    */

    int valor1;
    int valor2;
    double media = 0.0f;

    fila_t *f = InitFila();                                               // Inicializa a fila
    int **mediaAprovados = (int **)malloc( classesSize * sizeof( int * ) ); // Aloca o número de linhas
    int *mediaFinal = (int *)malloc( classesSize * sizeof( int ) );

    /////////////////////////// FAZ A MÉDIA POR LINHAS ///////////////////////////////////////

    for ( int i = 0; i < classesSize; i++ ) { // Número de classes retorna quantas classes existem
        for ( int j = 0; j < 2; j++ ) {       // Cada classe tem 2 valores: pass e total
            Enqueue( f, classes[i][j] );      // Insere os valores na fila [(0)pass, (1)total]
        }
    }

    for ( int i = 0; i < classesSize; i++ ) { // Número de classes retorna quantas classes existem
        mediaAprovados[i] = (int *)malloc( sizeof( int ) ); // Aloca espaço para cada linha

        for ( int j = 0; j < 1; j++ ) { // Calcula a média para cada classe
            valor1 = Dequeue( f );      // Remove o primeiro valor (pass)
            valor2 = Dequeue( f );      // Remove o segundo valor (total)

            mediaAprovados[i][j] = ( valor1 / valor2 ); // Armazena a média
        }
    }

    /////////////////////////////// FAZ A MÉDIA TOTAL SOMANDO LINHAS ///////////////////////////////////////

    for ( int i = 0; i < classesSize; i++ ) { // Número de classes retorna quantas classes existem
        for ( int j = 0; j < 1; j++ ) {       // Cada classe tem 1 valor de média
            Enqueue( f, mediaAprovados[i][j] ); // Insere as médias na fila
        }
    }

    for ( int i = 0; i < classesSize; i++ ) { // Número de classes retorna quantas classes existem
        mediaAprovados[i] = (int *)malloc( sizeof( int ) ); // Aloca espaço para cada linha

        for ( int j = 0; j < 1; j++ ) { // Soma todas as médias
            media += Dequeue( f );      // Soma os valores
        }
    }

    media = ( media / classesSize ) + ( extraStudents / 100 ); // Calcula a média final

    /////////////////////////////////////////////////////////////////////////////////////////////////////

    return media;
}