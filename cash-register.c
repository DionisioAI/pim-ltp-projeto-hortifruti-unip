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
void consultaProdutos();

// Variáveis
int escolhaMenu;
int escolhaTipoDeBuscaProduto;
char nomeProdutoConsultaEspecifica[100];

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

    // access the JSON data 

    FILE *arquivoDeProdutos = fopen("produtos.json", "r"); // FILE *arquivoDeProdutos: Declares a file pointer "arquivoDeProdutos" of type FILE. This pointer will be used to manage the file operations
    if (arquivoDeProdutos == NULL) { 
        printf("Erro: nao foi possivel abrir o arquivo.\n"); 
        return 1; 
    } 

    // read the file contents into a string 

    char buffer[10000]; 
    int lengthProdutos = fread(buffer, 1, sizeof(buffer), arquivoDeProdutos); // lengthProdutos contains the number of bytes read 
    fclose(arquivoDeProdutos); 

    inicio:

    printf("\n\nCAIXA REGISTRADORA\n\n\n\n\n");
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

        printf("\n\nDeseja buscar um produto especifico (1) ou todos os produtos de nossa lista (2)? ");
        scanf("%i", &escolhaTipoDeBuscaProduto);
        
        if (escolhaTipoDeBuscaProduto == 1) {

            printf("\n\nQual e o nome do produto que deseja consultar? ");
            scanf("%s", nomeProdutoConsultaEspecifica);

            // parse the JSON data 
            // JSON parsing is the process of converting a JSON object in text format to a Javascript object that can be used inside a program

            cJSON *json = cJSON_Parse(buffer); // cJSON_Parse returns a pointer to a cJSON object.
            if (json == NULL) { 
            const char *error_ptr = cJSON_GetErrorPtr(); 
            if (error_ptr != NULL) { 
                printf("Erro: %s\n", error_ptr); 
            } 
            cJSON_Delete(json); 
            return 1; 

            // access the JSON data 
            cJSON *frutas = cJSON_GetObjectItem(json, "frutas");
            if (!cJSON_IsArray(frutas)) {
                printf("Error: 'frutas' is not an array.\n");
                cJSON_Delete(json);
                return 1;
            }

            char *ponteiroNomeProdutoConsultaEspecifica = nomeProdutoConsultaEspecifica;

            // Iterate through the array to find the fruit with the given name.
            cJSON *fruit = NULL;
            cJSON_ArrayForEach(fruit, frutas) {
            cJSON *nome = cJSON_GetObjectItem(fruit, "nome");
            if (cJSON_IsString(nome) && strcmp(nome->valuestring, ponteiroNomeProdutoConsultaEspecifica) == 0) {
                // If the name matches, get "precoPorQuilograma".
                cJSON *preco = cJSON_GetObjectItem(fruit, "precoPorQuilograma");
            if (cJSON_IsNumber(preco)) {
                printf("The price per kilogram for %s is: %d\n", ponteiroNomeProdutoConsultaEspecifica, preco->valueint);
            } else {
                    printf("Error: 'precoPorQuilograma' is not a number.\n");
            }
                break;
            }
            }
        
            // delete the JSON object
            cJSON_Delete(json);
            return 0;
            } 

        } else if (escolhaTipoDeBuscaProduto == 2) {
            
            printf("%s", buffer);

        }

        return 0;
    case 2: // Adicionar produto ao carrinho de compras
        digitarCodigo:
        printf("\n\nDigite o codigo do produto (ou digite 0 para consulta-lo): ");
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
        /* code */
        return 0;
    case 4:
        /* code */
        return 0;
    case 5:
        /* code */
        return 0;
    case 6:
        /* code */
        return 0;
    
    default:
        printf("Nao ha um servico correspondente ao caracter digitado. Tente novamente");
        return 0;
    }

    return 0;
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