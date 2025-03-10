/*
====================
soma
 Soma os valores dos nós da árvore.
====================
*/
int soma( struct TreeNode * root, int * resposta, int * index ) {
	if ( root == NULL ) {
		return 0; // verifica se é nula, para retornar sempre que achar a folha
	}

	int somaEsquerda = soma( root->left, resposta, index ); // vai até o último nó para retornar recursivamente
	int somaDireita = soma( root->right, resposta, index ); // vai até o último nó para retornar recursivamente

	int somaAtual = root->val + somaEsquerda + somaDireita;

	resposta[ *index ] = somaAtual;
	( *index )++; // Incrementa o índice após a soma

	return somaAtual;
}

/*
====================
findFrequentTreeSum
 Encontra as somas de subárvores mais frequentes.
====================
*/
int * findFrequentTreeSum( struct TreeNode * root, int * returnSize ) {
	if ( !root ) {
		*returnSize = 0;
		return NULL; // verifica se a árvore existe
	}

	int * resposta = ( int * )malloc( 10000 * sizeof( int ) ); // aloca valor para retornar a resposta
	int index = 0;

	soma( root, resposta, &index );

	int frequencia = 0;
	int frequencias[ 10000 ] = { 0 };

	for ( int i = 0; i < index; i++ ) {
		for ( int j = 0; j < index; j++ ) {
			if ( resposta[ i ] == resposta[ j ] ) {
				frequencias[ i ]++;
			}
		}
		if ( frequencias[ i ] > frequencia ) {
			frequencia = frequencias[ i ];
		}
	}

	int * resultadoFinal = ( int * )malloc( index * sizeof( int ) ); // aloca espaço para o resultado final
	int contador = 0; // inicializa o contador em zero

	for ( int i = 0; i < index; i++ ) { // percorre todo index da soma
		if ( frequencias[ i ] == frequencia ) { // se a frequência for igual
			int jaInserido = 0; // Evitar inserir valores repetidos
			for ( int k = 0; k < contador; k++ ) {
				if ( resultadoFinal[ k ] == resposta[ i ] ) { // se o valor já existir no resultado final, ativa a flag
					jaInserido = 1;
					break;
				}
			}
			if ( !jaInserido ) {
				resultadoFinal[ contador++ ] = resposta[ i ]; // resultado final recebe a resposta e é incrementado
			}
		}
	}

	*returnSize = contador;
	free( resposta ); // libera a memória alocada antes

	return resultadoFinal;
}
