struct compra{
    char codigo[50];
    char cpf[20];
    int quantidade;
    struct compra *proximo;
};

typedef struct compra cmpr;

void carregaCompras (cmpr **lst);

void salvaCompras (cmpr **lst);

void realizaCompra (cmpr **lst, prod **lstProdutos);

void pesquisaCpf (cmpr *lst);

void pesquisaCodigo (cmpr *lst);
