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

void carregaClientes (clnt **lst);

void salvaClientes (clnt **lst);

void cadastraCliente (clnt **lst);

void pesquisaNome (clnt *lst);
