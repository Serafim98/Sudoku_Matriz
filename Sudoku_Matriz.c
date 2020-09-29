//Luis Serafim

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 9


typedef struct celula{
    int valor;
    int lin, col;
    struct celula *prox;
    struct celula *ant;
} t_celula;



t_celula *primeiro; //Primeiro elemento
t_celula *ultimo; //Ultimo elemento


//Protótipos de funções
t_celula* criar_celula(int lin, int col, int valor);
void inserir(t_celula *novo);
void deletar(int lin, int col);
int vazia();
t_celula* existe_celula(int lin, int col);
void imprimir_elementos();
void imprimir_matriz();



t_celula* criar_celula(int lin, int col, int valor){ //Cria uma celula e retorna o ponteiro;

    t_celula * novo;

    novo = (t_celula*)malloc(sizeof(t_celula));

    if(!novo){
        printf("Erro ao alocar memoria!!\n");
        exit(1);
    }


    novo->valor = valor;
    novo->lin = lin;
    novo->col = col;

    return novo;
}


void inserir(t_celula *novo){ //Insere um elemento em uma coluna e linha específica se a posição for vazia


    t_celula* cel = existe_celula(novo->lin, novo->col);

    if(!cel){

        if(!ultimo){

            novo->prox = NULL;
            novo->ant = NULL;

            ultimo = novo;
            primeiro = novo;
        }
        else{

            t_celula *p, *ant;


            p = primeiro;
            ant = p->ant;


            while(p){

                if((p->lin < novo->lin) || ((p->lin == novo->lin) && (p->lin + p->col) < (novo->lin + novo->col))){

                    ant = p;
                    p = p->prox;
                }
                else{

                    if(p->ant){

                        p->ant->prox = novo;

                        novo->prox = p;

                        novo->ant = p->ant;

                        p->ant = novo;

                        return;
                    }


                    novo->prox = p;
                    novo->ant = NULL;
                    p->ant = novo;
                    primeiro = novo;

                    return;
                }
            }

            ant->prox = novo;

            novo->prox = NULL;

            novo->ant = ant;

            ultimo = novo;
        }
    }
    else{

        cel->valor = novo->valor;
    }
}


void deletar(int lin, int col){ //Deleta o elemento de uma linha e coluna específica

    if(existe_celula(lin, col)){

        if(primeiro->lin == lin && primeiro->col == col){

            t_celula *prox = primeiro->prox;

            free(primeiro);

            if(prox)
                prox->ant = NULL;

            primeiro = prox;

            return;
        }

        t_celula *p = primeiro->prox;

        while(p){

            if(p->lin == lin && p->col == col){

                if(p->prox){

                    p->ant->prox = p->prox;

                    p->prox->ant = p->ant;
                }
                else{

                    p->ant->prox = NULL;

                    ultimo = p->ant;
                }

                free(p);
                return;
            }
            p = p->prox;
        }
    }
}



int vazia(){ //Verifica se a Matriz é vazia
    if(!ultimo)
        return 1;
    return 0;
}


t_celula* existe_celula(int lin, int col){ //Verifica se existe um número na linha e coluna específica

    t_celula* p = primeiro;

    while(p){
        if(lin == p->lin && col == p->col)
            return p;
        p = p->prox;
    }
    return NULL;
}


void imprimir_matriz(){ //Exibe a Matriz SUDOKU
    if(!vazia()){

        int total_linhas = ultimo->lin;

        int total_colunas = -1;
        t_celula* p = primeiro;
        while(p){
            if(p->col > total_colunas)
                total_colunas = p->col;
            p = p->prox;
        }

        for(int i = 0; i < total_linhas; i++){

            for(int j = 0; j < total_colunas; j++){

                t_celula* cel = existe_celula(i+1 , j+1);

                if(cel)
                    printf("%d\t", cel->valor);
                else
                    printf("▢\t");
            }
            printf("\n");
        }
    }
    else
        printf("\nLista vazia!!\n");
}

int checkHorizontal() { // Verifica se há numeros repetidos na horizontal da matriz
    t_celula *p = primeiro;
    int total_linhas = ultimo->lin;
    int total_colunas = -1;

    while (p) {
        if (p->col > total_colunas)
            total_colunas = p->col;
        p = p->prox;
    }

    int sdk = 1;

    for (int i = 0; i < total_linhas && sdk; i++) {

        for (int j = 0; j < total_colunas && sdk; j++) {

            for (int k = 0; k < total_colunas && sdk; k++) {
                t_celula *cel = existe_celula(i + 1, j + 1);
                t_celula *cel2 = existe_celula(i + 1, k + 1);
                if ((j != k) && (cel->valor == cel2->valor));
                sdk = 0;
            }
        }
    }
    return sdk;
}

int checkVertical(){ // Verifica se há números repetidos na vertical da matriz
    t_celula *p = primeiro;
    int total_linhas = ultimo->lin;
    int total_colunas = -1;

    while (p) {
        if (p->col > total_colunas)
            total_colunas = p->col;
        p = p->prox;
    }

    int sdk = 1;

    for (int i = 0; i < total_linhas && sdk; i++) {

        for (int j = 0; j < total_colunas && sdk; j++) {

            for (int k = 0; k < total_colunas && sdk; k++) {
                t_celula *cel = existe_celula(i + 1, j + 1);
                t_celula *cel2 = existe_celula(k + 1, j + 1);
                if ((i != k) && (cel->valor == cel2->valor));
                sdk = 0;
            }
        }
    }
    return sdk;
}


void GeraMatrizSudoku() {
    int n = 3;
    srand( (unsigned)time(NULL) );
    int x = rand() % 10;
    int lin, col, valor;
    for (int i = 0; i < n; i++, x++) {
        for (int j = 0; j < n; j++, x+=n) {
            for (int k = 0; k < n*n; k++, x++) {
                lin = n * i + j;
                col = k;
                valor = (x % (n * n)) + 1;
                t_celula *novo = criar_celula(lin+1, col+1, valor);
                inserir(novo);
            }
        }
    }
}


void Remove(){

    int i, j;
    srand( (unsigned)time(NULL) );
    for(int k=0; k<49; k++){
        i = 1 + (rand() % 10);
        j = 1 + (rand() % 10);
        deletar(i, j);
    }
}

void Escolha() {
    int valor, i, j, cont = 1;
    while (cont < 32) {
        printf("Valor %d de 32 lacunas\n", cont);
        printf("Digite o valor a ser inserido: ");
        scanf("\n%d", &valor);
        if ((valor < 0) || (valor > 9)) {
            printf("\nValor inválido\n\n");
            continue;
        }

        printf("\nInsira a linha (1 a 10): ");
        scanf("\n%d", &i);
        if ((i < 1) || (i > 10)) {
            printf("\nLinha inválida\n");
            continue;
        }
        printf("\nInsira a coluna (1 a 10): ");
        scanf("%d", &j);
        if ((j < 1) || (j > 10)) {
            printf("\nColuna inválida\n");
            continue;
        }
        if (existe_celula(i, j)) {
            printf("\nJá existe um valor nessa posição\n");
            continue;
        } else {
            t_celula *novo = criar_celula(i, j, valor);
            inserir(novo);
            cont++;
            imprimir_matriz();
        }
    }
}

int main(void){

    GeraMatrizSudoku();

    printf("\nImprimindo a Matriz Sudoku:\n");
    Remove();
    imprimir_matriz();
    Escolha();
    if((checkHorizontal())&&(checkVertical())) {
        printf("%d", checkVertical());
        printf("%d", checkHorizontal());
        printf("Parabéns SUDOKU resolvido com sucesso!");
    }
    else printf("Solução Incorreta");

    return 0;
}

