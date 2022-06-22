#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "produto.h"
//define o registro de compra
struct compra{
    char codigo[50];
    char cpf[50];
    int quantidade;
    struct compra *proximo;
};

typedef struct compra cmpr;


void carregaCompras(cmpr **lst){
    //LISTA DO TIPO COMPRA QUE RECEBE OS DADOS DO ARQUIVO
    cmpr *cmprArq;
    //TENTA ABRIR O ARQUIVO
    FILE *ptArq;
    ptArq = fopen("compras.csv", "r");
    //CASO NAO CONSIGA OU SEJA A PRIMEIRA EXECUCAO DO PROG IMPRIME PARA O USUARIO
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUIVO (carregaCompras).\n");
    }else{
        char linha[150];
        //WHILE PARA LER UMA LINHA POR VEZ
        while(fgets(linha, 150, ptArq) != NULL){
            //INICIALIZA UMA MATRIZ PARA RECEBER AS CADEIAS
            char *token;
            char valores[3][50];
            cmprArq = (cmpr* )malloc(sizeof(cmpr));
            //DEFINE O CARACTER PARA SEPARAR AS CADEIAS
			linha[strcspn(linha, "\n")] = 0;
            token = strtok(linha, ";");
            int i=0;
            //LE UMA LINHA E QUANDO ENCONTRA ; COLOCA EM UMA POSICAO DA MATRIZ
            while(token!= NULL){
                strcpy(valores[i],token);
                token = strtok(NULL, ";");
                i++;
            }
            //ATRIBUI OS DADOS DA LINHA A UMA CELULA DA LISTA
            strcpy(cmprArq->codigo, valores[0]);
            strcpy(cmprArq->cpf, valores[1]);
            char quantidade[50];
            strcpy(quantidade, valores[2]);
            cmprArq->quantidade = atoi(quantidade);
            //SE A LISTA FOR VAZIA TORNA A CELULA O COMECO
            if(*lst == NULL){
                cmprArq->proximo = NULL;
                *lst = cmprArq;

            }else{
            //CASO CONTRARIO COLOCA A CELULA NO FIM DA LISTA
                cmpr *aux;
                aux = *lst;
                while(aux->proximo != NULL){
                    aux = aux->proximo;
                }
            cmprArq->proximo = NULL;
            aux->proximo = cmprArq;
            }
        }
        //FECHA O ARQUIVO
        fclose(ptArq);
    }
}

void salvaCompras(cmpr **lst){
    //TENTA ABRIR O ARQUIVO EM MODO DE ESCRITA
    FILE *ptArq;
    ptArq = fopen("compras.csv", "w");
    //CASO NAO CONSIGA IMPRIME UMA MENSAGEM AO USUARIO
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUVO (salvaCompras).\n");
    }else{
        //ATRIBUI O INICIO DA LISTA A UM PONTEIRO PARA NAO PERDER O ENDEREÇO DE LST
        cmpr *pt;
        pt = *lst;
        //ENQUANTO OUVER CELULA NA LISTA GRAVA O CONTEUDO DE CADA CELULA EM UMA LINHA
        while(pt != NULL){

           fprintf(ptArq,"%s;%s;%d;\n", pt->codigo, pt->cpf, pt->quantidade);
            pt = pt->proximo;
        }
    }
    //FECHA O ARQUIVO
    fclose(ptArq);
}

int verificaCodigo(char codigoP[50]){
    /* ESSA FUNCAO TEM O MESMO CORPO DO CARREGA EMPRESTIMO PRATICAMENTE
        A DIFERENCA EH QUE ELA VAI CARREGAR OS ALUNOS E CHECAR SE O ALUNO CORRESPONDENTE AO RGA rgaA EXISTE
        RETORNA 1 CASO ELE EXISTA, E 0 SE NAO
    */
    char codigo[50];
    FILE *ptArq;
    ptArq = fopen("produtos.csv", "r");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUIVO (verificaProdutos).\n");
    }else{
        char linha[300];
        while(fgets(linha, 300, ptArq) != NULL){

            char *token;
            char valores[6][50];

			linha[strcspn(linha, "\n")] = 0;
            token = strtok(linha, ";");
            int i=0;
            while(token!= NULL){
                strcpy(valores[i],token);
                token = strtok(NULL, ";");
                i++;
            }
            //ATE AQUI TUDO EH IGUAL
            strcpy(codigo, valores[0]);
            // A DIFERENCA EH QUE NAO PRECISO COLOCAR OS DADOS DAS LINHAS EM UMA CELULA DE LISTA, SOH PRECISO DELES ENQUANTO FACO A VERIFICACAO
            if(strcmp(codigo, codigoP) == 0){
                return 1;
            }
        }
        fclose(ptArq);

    }
    return 0;
}

int verificaCpf(char cpfC[50]){
    // MESMA UTILIDADE DA FUNCAO ACIMA, MAS PARA CHECAR SE UM LIVRO EXISTE, 1 CASO SIM, 0 NAO
    char cpf[50];
    FILE *ptArq;
    ptArq = fopen("clientes.csv", "r");
    if(ptArq == NULL){
        printf("OCORREU UM PROBLEMA AO ABRIR O ARQUIVO (carregaClientes).\n");
    }else{
        char linha[300];
        while(fgets(linha, 300, ptArq) != NULL){

            char *token;
            char valores[6][50];

			linha[strcspn(linha, "\n")] = 0;
            token = strtok(linha, ";");
            int i=0;
            while(token!= NULL){
                strcpy(valores[i],token);
                token = strtok(NULL, ";");
                i++;
            }
            strcpy(cpf, valores[1]);

            if(strcmp(cpf, cpfC) == 0){
                return 1;
                //retorna 1 caso haja o cpf informado
            }

        }
        fclose(ptArq);

    }
    return 0;
}


void realizaCompra(cmpr **lst, prod **lstProdutos){
    //CRIA UMA NOVA CELULA DO TIPO COMPRA
    cmpr *novo;
    novo = (cmpr *)malloc(sizeof(cmpr));
    //LIMPA A TELA E COMECA O FORMULARIO
    system("cls");
    fflush(stdin);
    printf("\nDIGITE O CODIGO DO PRODUTO: ");
    scanf("%[^\n]s", &novo->codigo);

    int verificaCd = verificaCodigo(novo->codigo);
    //CASO O CODIGO NAO SEJA ENCONTRADO PELA FUNCAO VERIFICACODIGO ELE ENCERRA A FUNCAO
    if(verificaCd == 0){
        printf("COMPRA NAO EFETUADA, MOTIVO: CODIGO NAO ENCONTRADO\n");
        return;
    }

    fflush(stdin);
    printf("\nDIGITE O CPF: ");
    scanf("%[^\n]s", &novo->cpf);

    fflush(stdin);
    printf("\nDIGITE A QUANTIDADE: ");
    scanf("%d", &novo->quantidade);
    printf("--- %d ---", novo->quantidade);


    //FAZ O PROXIMO DA CELULA APONTAR PARA NADA, POIS ELE AINDA NAO ESTA NA LISTA
    novo->proximo = NULL;
    //VERIFICA SE O LIVRO INFORMADO EXISTE, CASO CONTRARIO ENCERRA A FUNCAO
    int verificaCl = verificaCpf(novo->cpf);
    if(verificaCl == 0){
        printf("COMPRA NAO EFETUADA, MOTIVO: CPF NAO ENCONTRADO\n");
        return;
    }
    else {
        prod *produtos;
        produtos = *lstProdutos;
        //ESSE WHILE RODA A LISTA DE TODOS OS PRODUTOS PROCURANDO UM LIVRO COM O MESMO ISSN, CASO ENCONTRE ELE VERIFICA SE QTD > 0
        //SE NAO FOR ELE ENCERRA A FUNCAO E PRINTA MENSAGEM PRO USUARIO, SE FOR ELE DIMINUI 1
        while(produtos != NULL){
            if(strcmp(novo->codigo,produtos->codigo) == 0){
                if(produtos->quantidade == 0){
                    printf("COMPRA NAO EFETUADA, MOTIVO: PRODUTO NAO DISPONIVEL\n");
                    return;
                } else {
                    if(produtos->quantidade < novo->quantidade){
                        printf("COMPRA NAO EFETUADA, MOTIVO: QUANTIDADE INDISPONIVEL\n");
                        return;
                    }
                    else{
                    produtos->quantidade = produtos->quantidade - novo->quantidade;
                    printf("COMPRA EFETUADA COM SUCESSO.\n\n");
                    //return;
                    }
                }
            }
            produtos = produtos->proximo;
        }
        //DAQUI ATE O FIM DA FUNCAO SAO VERIFICACOES PARA SABER EM QUE POSICAO DA LISTA A CELULA VAI ENTRAR
        if(*lst == NULL){
            *lst = novo;
        }else{
            cmpr *pt, *ptAux;
            pt = *lst;
            ptAux = NULL;

            while(pt!= NULL){
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

}

void pesquisaCpf(cmpr *lst){
    //CRIA UM APELIDO PRO COMEÇO DA LISTA
    cmpr *compras;
    compras = lst;
    char cpf[50];
    system("cls");
    printf("CPF DO CLIENTE QUE DESEJA PESQUISAR:");
    fflush(stdin);
    scanf("%[^\n]s", cpf);
    printf("\n----COMPRAS COM O CPF:-----\n\n");
    //ENQUANTO HOUVER CELULAS VAI PERCORRER A LISTA CHECANDO SE O RGA BATE E IMPRIMINDO TODOS QUE BATEREM
    while(compras!= NULL){
        if(strcmp(compras->cpf,cpf) == 0){
            printf("CODIGO: %s\nCPF: %s\nQUANTIDADE: %d\n",
                    compras->codigo, compras->cpf, compras->quantidade);
            printf("\n---------------------------------\n\n");
        }
        compras = compras->proximo;
    }


}

void pesquisaCodigo(cmpr *lst){
    //MESMA COISA QUE A FUNCAO ANTERIOR MAS PESQUISA PELO ISSN
    cmpr *compras;
    compras = lst;
    char codigo[50];
    system("cls");
    printf("CODIGO DO PRODUTO QUE DESEJA PESQUISAR:");
    fflush(stdin);
    scanf("%[^\n]s", codigo);
    printf("\n----COMPRAS COM O CODIGO:-----\n\n");
    while(compras!= NULL){
        if(strcmp(compras->codigo,codigo) == 0){
            printf("CPF: %s\nCODIGO: %s\nQUANTIDADE: %d\n\n",
                    compras->cpf, compras->codigo, compras->quantidade);
            printf("---------------------------------\n\n");
        }
        compras = compras->proximo;
    }


}
