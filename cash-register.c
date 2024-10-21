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

int escolhaMenu;
int escolhaTipoDeBuscaProduto;
char nomeProdutoConsultaEspecifica[100];

int main() {

    printf("CAIXA REGISTRADORA\n\n\n\n\n");
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
    case 1:

        printf("\n\nDeseja buscar um produto especifico (1) ou todos os produtos de nossa lista (2)? ");
        scanf("%i", &escolhaTipoDeBuscaProduto);
        
        // access the JSON data 

            FILE *arquivoDeProdutos = fopen("produtos.json", "r"); // FILE *arquivoDeProdutos: Declares a file pointer "arquivoDeProdutos" of type FILE. This pointer will be used to manage the file operations
            if (arquivoDeProdutos == NULL) { 
                printf("Error: Unable to open the file.\n"); 
                return 1; 
            } 

        // read the file contents into a string 
            char buffer[10000]; 
            int len = fread(buffer, 1, sizeof(buffer), arquivoDeProdutos); // len contains the number of bytes read 
            fclose(arquivoDeProdutos); 
        
        if (escolhaTipoDeBuscaProduto == 1) {

            printf("\n\nQual e o nome do produto que deseja consultar? ");
            scanf("%s", nomeProdutoConsultaEspecifica);

            // parse the JSON data 
            // JSON parsing is the process of converting a JSON object in text format to a Javascript object that can be used inside a program

            cJSON *json = cJSON_Parse(buffer); // cJSON_Parse returns a pointer to a cJSON object.
            if (json == NULL) { 
            const char *error_ptr = cJSON_GetErrorPtr(); 
            if (error_ptr != NULL) { 
                printf("Error: %s\n", error_ptr); 
            } 
            cJSON_Delete(json); 
            return 1; 

            // access the JSON data 
            cJSON *precoProduto = cJSON_GetObjectItemCaseSensitive(json, "frutas"); 
            if (cJSON_IsString(precoProduto) && (precoProduto->valuestring != NULL)) { 
                printf("Preço: %s\n", precoProduto->valuestring); 
            } 
        
            // delete the JSON object 
            cJSON_Delete(json); 
            return 0;
            } 

        } else if (escolhaTipoDeBuscaProduto == 2) {
            
            printf("%s", buffer);

        }

        return 0;
    case 2:
        /* code */
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