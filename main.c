#include <stdio.h>
#include "menu.h"
#include "produto.h"
#include "cliente.h"
#include "compra.h"

#define MAX_SIZE 30

int main(){
    char op, subop;
    prod *listaProdutos = NULL;
    clnt *listaClientes = NULL;
    cmpr *listaCompras = NULL;
    carregaProdutos(&listaProdutos);
    carregaClientes(&listaClientes);
    carregaCompras(&listaCompras);
    op = menu_principal();


    while (op != 27 && op != 'S' && op != 's'){
        switch(op){
            case '1':
                subop = submenu1(0);

                while (subop != '0'){
                    switch(subop){
                        //PESQUISAR POR DESCRICAO
                        case '1':
                            pesquisaDescricao(listaProdutos);
                            submenu1(1);
                        break;
                        //PESQUISAR POR FORNECEDOR
                        case '2':
                            pesquisaFornecedor(listaProdutos);
                            submenu1(1);
                        break;
                        /* CADASTRAR PRODUTO */
                        case '3':
                            cadastraProduto(&listaProdutos);
                        break;

                        default:
                        break;
                    }
                    subop = submenu1(0);
                }
            break;

            case '2':
                subop = submenu2(0);

                while (subop != '0'){
                    switch(subop){
                        case '1':
                            pesquisaNome(listaClientes);
                            submenu2(1);
                        break;
                        case '2':
                            cadastraCliente(&listaClientes);
                        break;
                        default:
                        break;
                    }
                    subop = submenu2(0);
                }
            break;

            case '3':
                subop = submenu3(0);

                while (subop != '0'){
                    switch(subop){
                        case '1':
                            //PESQUISAR COMPRAS PELO CPF DO CLIENTE
                            pesquisaCpf(listaCompras);
                            submenu3(1);
                        break;
                        case '2':
                            //PESQUISAR COMPRAS PELO CODIGO DO PRODUTO
                            pesquisaCodigo(listaCompras);
                            submenu3(1);
                        break;
                        case '3':
                            //REALIZAR COMPRA
                            //Bug nao estava deixando criar emprestimo pq nao encotnrava academico antes de fechar o programa
                            salvaClientes(&listaClientes);
                            salvaProdutos(&listaProdutos);
                            realizaCompra(&listaCompras, &listaProdutos);
                            salvaProdutos(&listaProdutos);
                        break;
                        default:
                        break;
                    }
                    subop = submenu3(0);
                }
            break;

            default:
            break;
        }
        op = menu_principal();
    }
    system("cls");
    salvaProdutos(&listaProdutos);
    printf("...Produtos Salvos!\n.\n");
    salvaClientes(&listaClientes);
    printf("...Clientes Salvos!\n.\n");
    salvaCompras(&listaCompras);
    printf("...Compras Salvos!\n");

    return 0;
}
