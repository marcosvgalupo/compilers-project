// #include <stdio.h>
// #include <stdlib.h>


// typedef struct listaCampos * ptno;

// struct listaCampos{
//     char id[100];
//     int tip;
//     int posicao;
//     int deslocamento;
//     int tamanho;
//     ptno prox;
// };

// ptno insere(ptno L, char id[100], int tipo, int posicao, int tamanho) {
//     ptno p, new;
//     new = (ptno)malloc(sizeof(struct listaCampos));
//     strcpy(new->id, id);
//     new->tip = tipo;
//     new->posicao = posicao;
//     new->tamanho = tamanho;
//     new->prox = NULL;
//     p = L;
//     while (p && p->prox)
//         p = p->prox;
//     if (p)
//         p->prox = new;
//     else
//         L = new;
//     return L;
// }

// // ptno busca(ptno L, char info)
// // {
// //     while (L && L->info != info)
// //         L = L->prox;
// //     return L;
// // }

// // void mostra(ptno L)
// // {
// //     printf("[");
// //     while (L)
// //     {
// //         if (L->prox)
// //             printf("%c,", L->info);
// //         else
// //             printf("%c", L->info);
// //         L = L->prox;
// //     }
// //     printf("]\n");
// // }

// // int main () {
// //     ptno L = NULL;
// //     L = insere(L, 'b');
// //     L = insere(L, 'a');
// //     L = insere(L, 'x');
// //     mostra(L);
// //     if (busca(L,'c'))
// //         puts("achou");
// //     else
// //         puts("não achou");
// // }