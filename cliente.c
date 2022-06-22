#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct cliente {
    char nome[50];
    char cpf[50];
    char endereco[50];
    char bairro[50];
    char cidadeEstado[50];
    char tel[50];
    struct cliente *proximo;
};

typedef struct cliente clnt;

void carregaClientes(clnt **lst){
    clnt *clntArq;
    FILE *ptArq;
    ptArq = fopen("clientes.csv", "r");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUIVO (carregaClientes).\n");
    }else{
        char linha[300];
        while(fgets(linha, 300, ptArq) != NULL){

            char *token;
            char valores[6][50];
            clntArq = (clnt*)malloc(sizeof(clnt));

			linha[strcspn(linha, "\n")] = 0;
            token = strtok(linha, ";");
            int i=0;
            while(token!= NULL){
                strcpy(valores[i],token);
                token = strtok(NULL, ";");
                i++;
            }
            strcpy(clntArq->nome, valores[0]);
            strcpy(clntArq->cpf, valores[1]);
            strcpy(clntArq->endereco, valores[2]);
            strcpy(clntArq->bairro, valores[3]);
            strcpy(clntArq->cidadeEstado, valores[4]);
            strcpy(clntArq->tel, valores[5]);

            if(*lst == NULL){
                clntArq->proximo = NULL;
                *lst = clntArq;

            }else{
                clnt *aux;
                aux = *lst;
                while(aux->proximo != NULL){
                    aux = aux->proximo;
                }
            clntArq->proximo = NULL;
            aux->proximo = clntArq;
            }
        }
        fclose(ptArq);

    }

}

void salvaClientes(clnt **lst){

    FILE *ptArq;
    ptArq = fopen("clientes.csv", "w");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUVO (salvaClientes).\n");
    }else{
        clnt *pt;
        pt = *lst;

        while(pt != NULL){

           fprintf(ptArq,"%s;%s;%s;%s;%s;%s;\n", pt->nome, pt->cpf, pt->endereco, pt->bairro, pt->cidadeEstado, pt->tel);
            pt = pt->proximo;
        }
    }
    fclose(ptArq);
}

int verificaClientes(clnt *lst, clnt *novo){

    clnt *p;
    p = lst;

    while(p != NULL){

        if(strcmp(p->cpf, novo->cpf) == 0){
            return 1;
        }
        p = p->proximo;
    }
    return -1;

}


void cadastraCliente(clnt **lst){
    clnt *novo;
    novo = (clnt *)malloc(sizeof(clnt));
    system("cls");
    fflush(stdin);
    printf("\nDIGITE O NOME DO CLIENTE: ");
    scanf("%[^\n]s", &novo->nome);

    fflush(stdin);
    printf("\nDIGITE CPF: ");
    scanf("%[^\n]s", &novo->cpf);

    fflush(stdin);
    printf("\nDIGITE O ENDERECO DO CLIENTE: ");
    scanf("%[^\n]s", &novo->endereco);

    fflush(stdin);
    printf("\nDIGITE O BAIRRO: ");
    scanf("%[^\n]s", &novo->bairro);

    fflush(stdin);
    printf("\nDIGITE CIDADE E O ESTADO: ");
    scanf("%[^\n]s", &novo->cidadeEstado);

    fflush(stdin);
    printf("\nDIGITE O TELEFONE DO CLIENTE: ");
    scanf("%[^\n]s", &novo->tel);

    novo->proximo = NULL;

    if(*lst == NULL){
        *lst = novo;
	}
    else{
        int verificaClnt = verificaClientes(*lst, novo);
        if(verificaClnt == 1){
            printf("CPF INFORMADO JA EXISTE...\n\n");
            return;
        }else{
            clnt *pt, *ptAux;
            pt = *lst;
            ptAux = NULL;

            while((pt!= NULL) && (strcmp(pt->cpf,novo->cpf)== -1)){
                    ptAux = pt;
                    pt = pt->proximo;
            }
            if(pt == NULL){
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
    printf("CLIENTE CADASTRADO COM SUCESSO.\n\n");
}

void pesquisaNome(clnt *lst){
    clnt *clientes;
    clientes = lst;
    char nome[50];
    system("cls");
    printf("\nNOME DO CLIENTE QUE DESEJA PESQUISAR:");
    fflush(stdin);
    scanf("%[^\n]s", nome);

    system("cls");
    printf("\n----CLIENTES COM O NOME:-----\n\n");
    while(clientes!= NULL){
        if(strcmp(clientes->nome,nome) == 0){
            printf("NOME: %s\nCPF: %s\nENDERECO: %s\nBAIRRO: %s\nCIDADE ESTADO: %s\nTEL: %s\n\n",
                    clientes->nome, clientes->cpf, clientes->endereco, clientes->bairro, clientes->cidadeEstado, clientes->tel);
            printf("-------------------------------\n\n");
        }
        clientes = clientes->proximo;
    }


}
