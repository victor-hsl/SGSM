#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct produto {
    char codigo[50];
    char descricao[50];
    char fornecedor [50];
    char validade[50];
    int quantidade;
    double preco;
    struct produto *proximo;
};

typedef struct produto prod;

void carregaProdutos(prod **lst){
    prod *prodArq;
    FILE *ptArq;
    ptArq = fopen("produtos.csv", "r");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUIVO (carregaProdutos).\n");
    }else{
        char linha[300];
        while(fgets(linha, 300, ptArq) != NULL){

            char *token;
            char valores[6][50];
            prodArq = (prod*)malloc(sizeof(prod));

			linha[strcspn(linha, "\n")] = 0;
            token = strtok(linha, ";");
            int i=0;
            while(token!= NULL){
                strcpy(valores[i],token);
                token = strtok(NULL, ";");
                i++;
            }
            strcpy(prodArq->codigo, valores[0]);
            strcpy(prodArq->descricao, valores[1]);
            strcpy(prodArq->fornecedor, valores[2]);
            strcpy(prodArq->validade, valores[3]);
            char quantidade[4];
            strcpy(quantidade, valores[4]);
            prodArq->quantidade = atoi(quantidade);
            char preco[10];
            strcpy(preco, valores[5]);
            prodArq->preco = atof(preco);

            if(*lst == NULL){
                prodArq->proximo = NULL;
                *lst = prodArq;

            }else{
                prod *aux;
                aux = *lst;
                while(aux->proximo != NULL){
                    aux = aux->proximo;
                }
            prodArq->proximo = NULL;
            aux->proximo = prodArq;
            }
        }
        fclose(ptArq);

    }

}

void salvaProdutos(prod **lst){

    FILE *ptArq;
    ptArq = fopen("produtos.csv", "w");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUVO (salvaProduto).\n");
    }else{
        prod *pt;
        pt = *lst;

        while(pt != NULL){

           fprintf(ptArq,"%s;%s;%s;%s;%d;%lf;\n", pt->codigo, pt->descricao, pt->fornecedor, pt->validade, pt->quantidade, pt->preco);
            pt = pt->proximo;
        }
    }
    fclose(ptArq);
}

int verificaProdutos(prod *lst, prod *novo){

    prod *p;
    p = lst;

    while(p != NULL){

        if(strcmp(p->codigo,novo->codigo) == 0){
            return 1;
        }
        p = p->proximo;
    }
    return -1;

}


void cadastraProduto(prod **lst){
    prod *novo;
    novo = (prod *)malloc(sizeof(prod));
    system("cls");
    fflush(stdin);
    printf("\nDIGITE O CODIGO: ");
    scanf("%[^\n]s", novo->codigo);

    fflush(stdin);
    printf("\nDIGITE A DESCRICAO: ");
    scanf("%[^\n]s", novo->descricao);

    fflush(stdin);
    printf("\nDIGITE O NOME DO FORNECEDOR: ");
    scanf("%[^\n]s", novo->fornecedor);

    fflush(stdin);
    printf("\nDIGITE A DATA DE VALIDADE: ");
    scanf("%[^\n]s", novo->validade);

    fflush(stdin);
    printf("\nDIGITE A QUANTIDADE: ");
    scanf("%d", &novo->quantidade);

    fflush(stdin);
    printf("\nDIGITE O PRECO: ");
    scanf("%lf", &novo->preco);

    novo->proximo = NULL;

    if(*lst == NULL){
        *lst = novo;
	}
    else{
        int verificaProd = verificaProdutos(*lst, novo);
        if(verificaProd == 1){
            printf("PRODUTO INFORMADO JA EXISTE..\n\n");
            return;
        }else{
            prod *pt, *ptAux;
            pt = *lst;
            ptAux = NULL;

            while((pt!= NULL) && (strcmp(pt->codigo,novo->codigo)== -1)){
                    ptAux = pt;
                    pt = pt->proximo;
            }
            if(pt== NULL){
                novo->proximo = NULL;
                ptAux->proximo = novo;
            }else if(ptAux == NULL){
                *lst = novo;
                novo->proximo = pt;
            }else{
                ptAux->proximo = novo;
                novo->proximo = pt;
            }
        }
    }
    printf("PRODUTO CADASTRADO COM SUCESSO.\n\n");
}

void pesquisaDescricao(prod *lst){
    prod *produtos = (prod* )malloc(sizeof(prod));
    produtos = lst;
    char descricao[50];
    system("cls");
    printf("\nDESCRICAO DO PRODUTO QUE DESEJA PESQUISAR:");
    fflush(stdin);
    scanf("%[^\n]s", descricao);

    system("cls");
    printf("\n-------PRODUTOS COM A DESCRICAO:--------\n\n");

    while(produtos!= NULL){
        if(strcmp(produtos->descricao,descricao) == 0){
            printf("CODIGO: %s\nDESCRICAO: %s\nFORNECEDOR: %s\nVALIDADE: %s\nQUANTIDADE: %d\nPRECO: %lf\n\n",
                    produtos->codigo, produtos->descricao, produtos->fornecedor, produtos->validade, produtos->quantidade, produtos->preco);
            printf("---------------------------------\n\n");
        }
        produtos = produtos->proximo;
    }


}

void pesquisaFornecedor(prod *lst){
    prod *produtos = (prod*)malloc(sizeof(prod));
    produtos = lst;
    char fornecedor[50];
    system("cls");
    printf("\nNOME DO FORNECEDOR:");
    fflush(stdin);
    scanf("%[^\n]s", fornecedor);

    system("cls");
    printf("\n-----PRODUTOS DO FORNECEDOR:--------\n\n");
    while(produtos!= NULL){
        if(strcmp(produtos->fornecedor,fornecedor) == 0){
            printf("CODIGO: %s\nDESCRICAO: %s\nFORNECEDOR: %s\nVALIDADE: %s\nQUANTIDADE: %d\nPRECO: %lf\n\n",
                    produtos->codigo, produtos->descricao, produtos->fornecedor, produtos->validade, produtos->quantidade, produtos->preco);
            printf("---------------------------------\n\n");
        }
        produtos = produtos->proximo;
    }


}
