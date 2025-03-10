/*
====================
soma
 Soma os valores dos nós da árvore e armazena os resultados.
====================
*/
int soma( struct TreeNode * root, int * resposta, int * index ) {
	if ( root == NULL ) {
		return 0; // verifica se é nula, para retornar sempre que achar a folha
	}

	int somaEsquerda = soma( root->left, resposta, index ); // vai até o último nó para retornar recursivamente
	int somaDireita = soma( root->right, resposta, index ); // vai até o último nó para retornar recursivamente

	int somaAtual = root->val + somaEsquerda + somaDireita; // soma o valor do pai + filhos

	resposta[ *index ] = somaAtual; // resposta recebe o valor da soma atual
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

	int frequencia = 0; // inicializa frequência 
	int frequencias[ 10000 ] = { 0 }; // inicializa array de frequência com zero em todas as posições 

	for ( int i = 0; i < index; i++ ) { // passa por todos valores das somas
		for ( int j = 0; j < index; j++ ) { // passa novamente por todos valores das somas
			if ( resposta[ i ] == resposta[ j ] ) { // compara eles para ver se são iguais
				frequencias[ i ]++; // se sim, incrementa a frequência
			}
		}
		if ( frequencias[ i ] > frequencia ) { // verifica se a frequência lida é maior que a frequência máxima
			frequencia = frequencias[ i ]; // a frequência recebe o maior valor de frequência
		}
	}

	int * resultadoFinal = ( int * )malloc( index * sizeof( int ) ); // aloca espaço para o resultado final 
	int contador = 0; // inicializa o contador em zero 

	for ( int i = 0; i < index; i++ ) { // percorre todo índice da soma
		if ( frequencias[ i ] == frequencia ) { // se a frequência for igual à máxima
			resultadoFinal[ contador++ ] = resposta[ i ]; // resultado final recebe a resposta e é incrementado
		}
	}

	*returnSize = contador; // indica o tamanho de returnSize
	free( resposta ); // libera a memória alocada antes

	return resultadoFinal;
}
