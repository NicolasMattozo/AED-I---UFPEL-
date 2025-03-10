/*
====================
soma
 Soma os valores dos nós da árvore.
====================
*/
int * soma( struct TreeNode * root, int * resposta, int * index ) {
	if ( root == NULL ) {
		return NULL; // verifica se é nula, para retornar sempre que achar a folha
	}

	soma( root->left, resposta, index ); // vai até o ultimo nó para retornar recursivamente
	soma( root->right, resposta, index ); // vai até o ultimo nó para retornar recursivamente

	if ( ( root->left != NULL ) && ( root->right != NULL ) ) {
		// Soma o valor do nó atual e dos filhos
		resposta[ *index ] = root->val + root->right->val + root->left->val;
		( *index )++;  // Incrementa o índice após a soma
	}

	return resposta;
}

/*
====================
findFrequentTreeSum
 Encontra as somas de subárvores mais frequentes.
====================
*/
int * findFrequentTreeSum( struct TreeNode * root, int * returnSize ) {
	if ( !root ) {
		NULL; // verifica se a arvore existe
	}

	int * resposta = ( int * )malloc( 10000 * sizeof( int ) ); // aloca valor para retornar a resposta

	int index = 0;

	soma( root, resposta, &index );

	*returnSize = index;

	return resposta;
}
