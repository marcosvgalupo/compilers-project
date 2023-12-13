// Tabela de Simbolos

enum 
{
    INT,
    LOG,
    REG
};

#define TAM_TAB 100

#include <stdio.h>
#include <stdlib.h>


typedef struct listaCampos * ptno;

struct listaCampos{
    char id[100];
    int tip;
    int posicao;
    int deslocamento;
    int tamanho;
    ptno prox;
};

ptno insere(ptno L, char id[100], int tipo, int posicao, int tamanho) {
    ptno p, new;
    new = (ptno)malloc(sizeof(struct listaCampos));
    strcpy(new->id, id);
    new->tip = tipo;
    new->posicao = posicao;
    new->tamanho = tamanho;
    new->prox = NULL;
    p = L;
    while (p && p->prox)
        p = p->prox;
    if (p)
        p->prox = new;
    else
        L = new;
    return L;
}

// ptno busca(ptno L, char info)
// {
//     while (L && L->info != info)
//         L = L->prox;
//     return L;
// }

void mostra(ptno L)
{
    while (L)
    {
        printf("(");
        if (L->prox){
            printf("%s,%d,%d,%d,%d", L->id, L->tip, L->posicao, L->deslocamento, L->tamanho);
            printf(") => ");
        }
        else{
            printf("%s,%d,%d,%d,%d", L->id, L->tip, L->posicao, L->deslocamento, L->tamanho);
            printf(")");
        }
        L = L->prox;
    }
}

// int main () {
//     ptno L = NULL;
//     L = insere(L, 'b');
//     L = insere(L, 'a');
//     L = insere(L, 'x');
//     mostra(L);
//     if (busca(L,'c'))
//         puts("achou");
//     else
//         puts("não achou");
// }

char nomeTipo[3][4]={"INT", "LOG", "REG"};

struct elemTabSimbolos {
    char id[100]; // nome do identificador
    int end;     //endereço
    int tip;    //tipo
    int tam;
    int pos;
    ptno listaDeCampos;
} tabSimb[TAM_TAB], elemTab;

int posTab = 0; // indica a proxima posição livre para inserir

int buscaSimbolo (char *s) {
    int i;
    for(i = posTab - 1; strcmp(tabSimb[i].id, s) && i >= 0; i--);
    if ( i == -1) {
        char msg[200];
        sprintf(msg, "Identificador [%s] não encontrado!", s);
        yyerror (msg);
    }
    return i; 

}

void insereSimbolo (struct elemTabSimbolos elem) {
    int i;
    if(posTab == TAM_TAB)
        yyerror ("Tabela de Simbolos cheia!");
    for(i = posTab - 1; strcmp(tabSimb[i].id, elem.id) && i >= 0; i--)
        ;
    if(i != -1){
        char msg[200];
        sprintf(msg, "Identificador [%s] duplicado", elem.id);
        yyerror (msg);
    }
    tabSimb[posTab++] = elem;
}

void mostraTabela (){
    puts("Tabela de Simbolos");
    puts("-----------------------------------------------------------");
    printf("%30s | %3s | %3s | %3s | %3s| %3s\n","ID", "END", "TIPO", "TAM", "POS", "CAMPOS");
    for (int i = 0; i < 50; i++)
        printf("--");
    for (int i = 0; i < posTab; i++){
        printf("\n%30s | %3d | %3s  | %3d | %2d |",
            tabSimb[i].id,
            tabSimb[i].end,
            nomeTipo[tabSimb[i].tip],
            tabSimb[i].tam,
            tabSimb[i].pos
        );
        if(tabSimb[i].tip == REG){
            mostra(tabSimb[i].listaDeCampos);
        }
    }
    puts(" ");
}

// Pilha Semantica
#define TAM_PIL 100
int pilha[TAM_PIL];
int topo = -1;

void empilha (int valor) {
    if(topo == TAM_PIL)
        yyerror("Pilha semantica cheia!");
    pilha[++topo] = valor;
}

int desempilha (void) {
    if(topo == -1)
        yyerror("Pilha semantica vazia!");
    return pilha[topo--];
}

// tipo1 e tipo2 são os tipos esperados na expressão
// ret é o tipo que será empilhado com resultado da expressão
void testaTipo (int tipo1, int tipo2, int ret) {
    int t1 = desempilha();
    int t2 = desempilha();
    if (t1 != tipo1 || t2 != tipo2) 
        yyerror("Incompatibilidade de tipo!");
    empilha(ret);
}


//retorna o tamanho do tipo da variável atual
int tamRegistro(ptno lista){
    int tam = 0;
    while(lista){
        tam +=  (lista->tip == INT) ?  1 :
                (lista->tip == LOG) ?  1 :
                (lista->tip == REG) ? 2 : 0;
        lista = lista->prox; 
    }
} 