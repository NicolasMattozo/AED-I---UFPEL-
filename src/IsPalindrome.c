/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool isPalindrome(struct ListNode* head) {

    typedef struct nodo{
        int numero;
        struct nodo *prox;
    }nodo;

    typedef struct stack{
        nodo *pilha;
    }stack;

    void init(stack *stack){
        stack->pilha = NULL;
    }

    void push(stack *stack, char c){
        nodo *novoNodo = (nodo *) malloc(sizeof(nodo));
        novoNodo->numero = c;
        novoNodo->prox = stack->pilha;
        stack->pilha = novoNodo;
    }

    int pop(stack *stack){
        nodo *temp = stack->pilha;
        int c = temp->numero;
        stack->pilha = temp->prox;
        free(temp);
        return c;
    }
    
    int top(stack *stack){
        return stack->pilha->numero;
    }

    bool IsEmpty(stack *stack){
        if(stack->pilha == NULL){
            return true;
        }
        return false;
    }

    void clear(stack *stack){
        nodo *temp = stack->pilha;
        nodo *temp2;
        while (temp != NULL){
            temp2 = temp;
            temp = temp->prox;
            free(temp2);
        }
        stack->pilha = NULL;
    }
    
    stack p;
    init(&p);
    
    struct ListNode *temp = head;

    // Passo 1: Empilha todos os elementos da lista
    while (temp != NULL) {
        push(&p, temp->val);
        temp = temp->next;
    }

    // Passo 2: Percorre novamente e compara com o topo da pilha
    temp = head;
    while (temp != NULL) {
        if (temp->val != pop(&p)) {
            return false; // Se um valor for diferente, não é palíndromo
        }
        temp = temp->next;
    }

    return true; // Se passou por toda a lista sem diferenças, é palíndromo
}

