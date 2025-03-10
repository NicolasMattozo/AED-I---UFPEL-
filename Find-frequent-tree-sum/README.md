# Solução do Problema do LeetCode

**Nome do Problema:** most-frequent-subtree-sum

**Número do Problema:** 508

**Link para o Problema: [https://leetcode.com/problems/most-frequent-subtree-sum/]** 

## Informações Pessoais
- **Nome:** Nicolas Mattozo
- **Matrícula:** 23200570
- **Curso:** Ciência da Computação

- ## Organização dos Arquivos
1. `feito-em-aula.c`: Este arquivo contém a versão inicial do código, que não calculava a frequencia.
2. `feito-em-casa.c`: Este arquivo contém a versão quase certa do código, mas feita sem consulta.
3. `feito-em-casa-corrigido.c`: Este arquivo contém a versão 100% corrigida do código com auxilio de IA.

## Descrição do Problema
Dado o rootde uma árvore binária, retorne a subárvore mais frequente sum . Se houver empate, retorne todos os valores com a frequência mais alta em qualquer ordem.

A soma da subárvore de um nó é definida como a soma de todos os valores do nó formados pela subárvore enraizada naquele nó (incluindo o próprio nó).

**Caso de Teste 1:**

![Caso de Teste 1](teste1.png)

**Caso de Teste 2:**

![Caso de Teste 1](teste2.png)

 **Caso de Teste 3:**

![Caso de Teste 1](teste3.png)

## Observações
- No arquivo `pascal_com_erro.c`, o problema estava na descrição do problema, que acabou não deixando claro qual seria a utilidade do returnColumnSizes e do returnSize, a lógica implementada estava parcialmente correta, porém não funcionaria devido a esses dois ponteiros de retorno, após entender o enunciado do problema e criar o ponteiro para um vetor de arrays, o problema foi resolvido.
- O erro foi corrigido no arquivo `pascal_corrigido.c`.
