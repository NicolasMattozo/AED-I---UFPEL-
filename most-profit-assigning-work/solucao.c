typedef struct {
	int dificuldade;
	int lucro;
} trabalho;

/*
====================
Compare
	Compara dois trabalhos pela dificuldade
====================
*/
int Compare( const void *a, const void *b ) {
	return ( ( trabalho * )a )->dificuldade - ( ( trabalho * )b )->dificuldade;
}

/*
====================
MaxProfitAssignment
	Calcula o lucro máximo possível para os trabalhadores com base em suas habilidades
====================
*/
int maxProfitAssignment( int *dificuldade, int dificuldadeT, int *lucro, int lucroT, int *trabalhador, int trabalhadorT ) {
	trabalho *trabalhos = ( trabalho * )malloc( dificuldadeT * sizeof( trabalho ) );

	for ( int i = 0; i < dificuldadeT; i++ ) {
		trabalhos[i].dificuldade = dificuldade[i];
		trabalhos[i].lucro = lucro[i];
	}

	qsort( trabalhos, dificuldadeT, sizeof( trabalho ), Compare );

	for ( int i = 1; i < dificuldadeT; i++ ) {
		if ( trabalhos[i].lucro < trabalhos[i - 1].lucro ) {
			trabalhos[i].lucro = trabalhos[i - 1].lucro;
		}
	}

	int resposta = 0;
	for ( int i = 0; i < trabalhadorT; i++ ) {
		int habilidade = trabalhador[i];
		int lucroTrabalho = 0;

		for ( int j = 0; j < dificuldadeT; j++ ) {
			if ( trabalhos[j].dificuldade <= habilidade ) {
				lucroTrabalho = trabalhos[j].lucro;
			} else {
				break;
			}
		}

		resposta += lucroTrabalho;
	}

	return resposta;
}
