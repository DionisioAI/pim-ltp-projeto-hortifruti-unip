#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Funções
int adicionar_produto();

// Variáveis
int escolhaMenu;
int codigoProduto;
int unidadesProduto;

typedef struct { // Estrutura dos itens que irão ser armazenados no array do carrinho
    char nome[100];
    double preco;
    int quantidade;
    int codigo;
} itens_carrinho;

itens_carrinho carrinho_com_itens[100]; // Array do carrinho de compras

int main() {

    FILE* arquivo__produtosprodutos = fopen("produtos.txt", "r");

    if (arquivo__produtosprodutos == NULL) {
    printf("Nao foi possivel iniciar a execucao do programa");
    return 1;
    }

    system("cls");

    printf("CAIXA REGISTRADORA\n\n\n");
    printf("Digite o numero de acordo com o servico desejado:\n\n");
    printf("1. Consultar informacoes de produtos\n");
    printf("2. Adicionar produto ao carrinho de compras\n");
    printf("3. Excluir itens do carrinho de compras\n");
    printf("4. Consultar carrinho de compras\n");
    printf("5. Finalizar compra\n");
    printf("6. Administrar estoque\n\n");
    scanf("%d", &escolhaMenu);
    getchar(); // Limpa o buffer após o scanf

    switch (escolhaMenu) {
    case 1: // Consultar informacoes de produtos
        printf("\n\nEssa funcionalidade ainda nao esta disponivel");
        break;
    case 2: // Adicionar produto ao carrinho de compras
        adicionar_produto();
        break;
    case 3:
        printf("\n\nEssa funcionalidade ainda nao esta disponivel");
        break;
    case 4:
        printf("\n\nEssa funcionalidade ainda nao esta disponivel");
        break;
    case 5:
        printf("\n\nEssa funcionalidade ainda nao esta disponivel");
        break;
    case 6:
        printf("\n\nEssa funcionalidade ainda nao esta disponivel");
        break;
    default:
        printf("Nao ha um servico correspondente ao caracter digitado. Tente novamente\n");
        break;
    }

    return 0;
}

int adicionar_produto() {

    FILE* arquivo_produtos = fopen("produtos.txt", "r");

    if (arquivo_produtos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char produto[100];
    int quantidade;
    double preco_por_quilograma;
    long int codigo;
    long int estoque;

    char linha[100];
    int numero_linhas;
    int resultado_busca = 0;
    char* endpointer;

    printf("\n\nQual produto quer adicionar? ");
    scanf("%s", produto);

    printf("Quantas unidades? ");
    scanf("%i", &quantidade);

    while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) {
        // Procura o nome do item
        if (strstr(linha, produto) != NULL) {
            resultado_busca = 1;

            // Lê e exibe as próximas 6 linhas (Codigo, preço, e quantidade)
            for (int i = 0; i < 6; i++) {
                fgets(linha, sizeof(linha), arquivo_produtos);
                strcpy(produto, linha);
                
                if (strstr(linha, "Codigo") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    codigo = strtol(linha, &endpointer, 10);
                    printf("\nCodigo: %li", codigo);
                }
                
                if (strstr(linha, "Preco por quilograma") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    preco_por_quilograma = strtod(linha, &endpointer);
                    printf("\nPreco por quilograma: R$ %.2f", preco_por_quilograma);
                }
                
                if (strstr(linha, "Quantidade no estoque") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    estoque = strtol(linha, &endpointer, 10);
                    printf("\nQuantidade no estoque: %li\n", estoque);
                }
            }
            break;
        }
    }

    strcpy(carrinho_com_itens[0].nome, produto);
    carrinho_com_itens[0].preco = preco_por_quilograma;
    carrinho_com_itens[0].quantidade = quantidade;
    carrinho_com_itens[0].codigo = codigo;

    if (!resultado_busca) {
        printf("Item '%s' nao encontrado.\n", produto);
        main();
    }

    fclose(arquivo_produtos);

    Sleep(2000);
    printf("\n\nItem adicionado ao carrinho");
    Sleep(2500);
    system("cls");
    
    main();
}

int consultar_carrinho() {


}


/*REQUISITOS

@ Poder consultar Preco de produtos a partir de arquivo_produtos .txt
- Processar compras (como um carrinho)
- Excluir frutas do carrinho em quantidades especificas
- Consultar condição atual do carrinho (ver produtos)
- Função finalizar compra para retornar o total
- Consultar todas as frutas disponiveis para compra
- Poder consultar codigo do produtos a partir do seu nome
- Controle de estoque
*/