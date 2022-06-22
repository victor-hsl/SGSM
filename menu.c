#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#ifndef _WIN32
    #include "getch.h"
#endif

int menu_principal(){
    char op;
    system("cls");
    printf("\n  1 - PRODUTOS\n  2 - CLIENTES\n  3 - COMPRAS \nESC - SAIR \n\n\nOPCAO:");
    op = getch();
    return op;
}

int submenu1(int id){
    char op;
    if(id != 1)system("cls");
    printf("\n  1 - PESQUISAR POR DESCRIÇÃO \n  2 - PESQUISAR POR FORNECEDOR \n  3 - CADASTRAR PRODUTO \n  0 - Voltar \n\n\nOPCAO:");
    op = getch();
    return op;
}

int submenu2(int id){
    char op;
    if(id != 1)system("cls");
    printf("\n  1 - PESQUISAR POR NOME \n  2 - CADASTRAR CLIENTE \n  0 - Voltar \n\n\n\nOPCAO:");
    op = getch();
    return op;
}

int submenu3(int id){
    char op;
    if(id != 1)system("cls");
    printf("\n  1 - PESQUISAR COMPRAS PELO CPF DO CLIENTE \n  2 - PESQUISAR COMPRAS PELO CODIGO DO PRODUTO \n  3 - REALIZAR COMPRA \n  0 - Voltar \n\nOPCAO:");
    op = getch();
    return op;
}

