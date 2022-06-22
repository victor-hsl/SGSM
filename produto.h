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

void carregaProdutos (prod **lst);

void salvaProdutos (prod **lst);

void cadastraProduto (prod **lst);

void pesquisaDescricao (prod *lst);

void pesquisaFornecedor (prod *lst);

int verificaProdutos(prod *lst, prod *novo);
