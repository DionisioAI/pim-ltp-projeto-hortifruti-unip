#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include "cJSON.c"
#include "cJSON.h"
#include <ctype.h>

// Funções
int main();

// Variáveis
int escolhaMenu;

typedef struct  { // Estrutura dos itens que irão ser armazenados no array do carrinho
    char nome[100];
    double preco;
    int quantidade;
    int codigo;
} itensCarrinho;

itensCarrinho carrinhoComItens[100]; // Array do carrinho de compras

int codigoProduto;
int unidadesProduto;

int main() {

    // Access the JSON data 

    FILE *arquivoDeProdutos = fopen("produtos.json", "r"); // FILE *arquivoDeProdutos: declares a file pointer "arquivoDeProdutos" of type FILE. This pointer will be used to manage the file operations
    if (arquivoDeProdutos == NULL) { 
        printf("Erro: nao foi possivel abrir o arquivo.\n"); 
        return 1; 
    } 

    // Read the file contents into a string 

    char buffer[10000]; 
    int lengthProdutos = fread(buffer, 1, sizeof(buffer), arquivoDeProdutos); // lengthProdutos contains the number of bytes read 
    fclose(arquivoDeProdutos); 

    inicio:

    printf("\n\n\nCAIXA REGISTRADORA\n\n\n");
    printf("Digite o numero de acordo com o servico desejado:\n\n");
    printf("1. Consultar informacoes de produtos\n");
    printf("2. Adicionar produto ao carrinho de compras\n");
    printf("3. Excluir itens do carrinho de compras\n");
    printf("4. Consultar carrinho de compras\n");
    printf("5. Finalizar compra\n");
    printf("6. Administrar estoque\n\n");
    scanf("%d", &escolhaMenu);

    switch (escolhaMenu)
    {
    case 1: // Consultar informacoes de produtos

        printf("%s", buffer);
        goto inicio;

    case 2: // Adicionar produto ao carrinho de compras

        printf("\n\nDigite o codigo do produto: ");
        scanf("%i", &codigoProduto);

        if (codigoProduto == 0) {

            printf("%s", buffer);
            goto digitarCodigo;
            
        } else {
            printf("\nQuantas unidades deseja comprar? ");
            scanf("%i", &unidadesProduto);
        }

        goto inicio;
        return 0;
    case 3:
        printf("\n\nAinda nao, corno");
        return 0;
    case 4:
        printf("\n\nAinda nao, corno");
        return 0;
    case 5:
        printf("\n\nAinda nao, corno");
        return 0;
    case 6:
        printf("\n\nAinda nao, corno");
        return 0;
    default:
        printf("Nao ha um servico correspondente ao caracter digitado. Tente novamente");
        return 0;

    return 0;

    }

}
    
int adicionarItem(itensCarrinho carrinhoComItens[100], int *numItens, ItensCarrinho novoItem) {

    if (*numItens >= MAX_ITEMS) {
        printf("Carrinho cheio! Não é possível adicionar mais itens.\n");
        return -1; // Carrinho cheio
    }
    
    // Adiciona o novo item ao carrinho
    carrinho[*numItens] = novoItem;
    (*numItens)++; // Incrementa o número de itens
    return 0; // Sucesso

    
}



/*REQUISITOS

@ Poder consultar preço de produtos a partir de arquivo .txt
- Processar compras (como um carrinho)
- Excluir frutas do carrinho em quantidades especificas
- Consultar condição atual do carrinho (ver produtos)
- Função finalizar compra para retornar o total
- Consultar todas as frutas disponiveis para compra
- Poder consultar codigo do produtos a partir do seu nome
- Controle de estoque
*/