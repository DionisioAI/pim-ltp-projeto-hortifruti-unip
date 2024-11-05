#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>


// funcï¿½es
int adicionar_produto();
int consultar_carrinho();
void exibir_informacao(char mensagem[50]);
int consultar_produtos();
int excluir_produtos();

// variï¿½veis
int escolha_menu;
int codigo_produto;
int unidades_produto;
int numero_de_produtos_no_carrinho = 0;

// variï¿½veis especiais
FILE* arquivo_produtos;
typedef struct {
    char nome[100];
    double preco;
    int quantidade;
    int codigo;
} item_carrinho;
item_carrinho carrinho_com_itens[100]; // array do carrinho de compras

int main() {

    setlocale(LC_ALL, "Portuguese");

    int menu = 1;

    while (menu) {

    FILE* arquivo_produtos = fopen("produtos.txt", "r");

    if (arquivo_produtos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // system("cls");

    printf("CAIXA REGISTRADORA\n\n\n");
    printf("Digite o nï¿½mero de acordo com o serviï¿½o desejado:\n\n");
    printf("1. Consultar informaï¿½ï¿½es de produtos\n");
    printf("2. Adicionar produto ao carrinho de compras\n");
    printf("3. Excluir itens do carrinho de compras\n");
    printf("4. Consultar carrinho de compras\n");
    printf("5. Finalizar compra\n");
    printf("6. Administrar estoque\n\n");
    scanf("%d", &escolha_menu);
    getchar();

    switch (escolha_menu) {
    case 1:
        consultar_produtos();
        break;
    case 2:
        adicionar_produto();
        break;
    case 3:
        excluir_produtos();
        break;
    case 4:
        consultar_carrinho();
        break;
    case 5:
        printf("\n\nEssa funcionalidade ainda nï¿½o estï¿½ disponï¿½vel\n");
        break;
    case 6:
        printf("\n\nEssa funcionalidade ainda nï¿½o estï¿½ disponï¿½vel\n");
        break;
    default:
        printf("Nï¿½o hï¿½ um serviï¿½o correspondente ao caracter digitado. Tente novamente\n");
        break;
    }

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

    printf("\nQual produto quer adicionar? ");
    scanf("%s", produto);

    printf("Quantas gramas? ");
    scanf("%i", &quantidade);

    while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) { // procura o produto e printa as informacoes do .txt
        if (strstr(linha, produto) != NULL) {
            resultado_busca = 1;

            for (int i = 0; i < 6; i++) {
                fgets(linha, sizeof(linha), arquivo_produtos);
                
                if (strstr(linha, "Codigo") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    codigo = strtol(linha, &endpointer, 10);
                    printf("\nCï¿½digo: %li", codigo);
                }
                
                if (strstr(linha, "Preco por quilograma") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    preco_por_quilograma = strtod(linha, &endpointer);
                    printf("\nPreï¿½o por quilograma: R$ %.2f", preco_por_quilograma);
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

    // atualiza o array do carrinho com o item adicionado

    strcpy(carrinho_com_itens[numero_de_produtos_no_carrinho].nome, produto);
    carrinho_com_itens[numero_de_produtos_no_carrinho].preco = preco_por_quilograma;
    carrinho_com_itens[numero_de_produtos_no_carrinho].quantidade = quantidade;
    carrinho_com_itens[numero_de_produtos_no_carrinho].codigo = codigo;
    numero_de_produtos_no_carrinho++;

    if (!resultado_busca) {
        system("cls");
        printf("Item '%s' nï¿½o encontrado.\n", produto);
        exibir_informacao("padrao");
    } else {
        printf("\nItem adicionado ao carrinho");
        exibir_informacao("padrao");
        system("cls");
    }

    fclose(arquivo_produtos);
    return 0;
    
}

int consultar_carrinho() {

    system("cls");

    if (numero_de_produtos_no_carrinho == 0) {
        printf("Vocï¿½ ainda nï¿½o tem nenhum produto adicionado");
        exibir_informacao("padrao");
        return 0;
    } else {

    printf("Carrinho de compras\n\n\n");
    
    for (int i = 0; i < numero_de_produtos_no_carrinho; i++) {
        printf("Produto %d: \n\n", i + 1);
        printf("Nome: %s", carrinho_com_itens[i].nome);
        printf("\nPreï¿½o por quilograma: R$ %.2f\n", carrinho_com_itens[i].preco);
        printf("Quantidade (em gramas) no carrinho: %d\n", carrinho_com_itens[i].quantidade);
        printf("Cï¿½digo: %d\n\n", carrinho_com_itens[i].codigo);
    }

    exibir_informacao("continuar");

    }

    return 0;

}

void exibir_informacao(char mensagem[50]) {

    if (mensagem == "padrao") {
        printf("\nPressione Enter para voltar ao menu...");
        fflush(stdin);
        getchar();

    } else if (mensagem == "continuar") {
        printf("\nPressione Enter para continuar...");
        fflush(stdin);
        getchar();        
    }
}

int consultar_produtos() {

    FILE* arquivo_produtos = fopen("produtos.txt", "r");

    if (arquivo_produtos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int quantidade_de_consultas;
    char produtos[11][100];
    int buscas_pendentes;
    char linha[100];
    char* endpointer;

    char nome[100];
    double preco_por_quilograma;
    int codigo;
    long int estoque;

    pergunta:

    printf("\nQuer consultar quantos produtos? ");
    scanf("%i", &quantidade_de_consultas);

    buscas_pendentes = quantidade_de_consultas;

    if (quantidade_de_consultas > 10) {
        printf("\nNao ï¿½ possï¿½vel realizar %i consultas de uma vez. O nï¿½mero mï¿½ximo de consultas ï¿½ 10", quantidade_de_consultas);
        printf("\n\nPressione Enter para tentar novamente...");
        fflush(stdin);
        getchar();
        goto pergunta;
    } else if (quantidade_de_consultas <= 0) {
        printf("\n\"%i\" nï¿½o ï¿½ um nï¿½mero vï¿½lido", quantidade_de_consultas);
        printf("\n\nPressione Enter para tentar novamente...");
        fflush(stdin);
        getchar();
        goto pergunta;
    }

    printf("Escreva o nome do(s) produto(s): \n\n");

    for (int i = 0; i < quantidade_de_consultas; i++) {
        scanf("%s", produtos[i]); // Armazena em produtos[i]
    }

    // o "for" serve para procurar cada produto separadamente, enquanto o "while" procura apenas um Ã­ndice especÃ­fico do array de produtos
    
    for (size_t j = 0; j < buscas_pendentes; j++)
    {
        printf("\n%s", produtos[j]);
        rewind(arquivo_produtos);

        while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) { // procura os produtos e printa as informacoes do .txt
        if (strstr(linha, produtos[j]) != NULL) {
            strcpy(nome, produtos[j]);

            for (int i = 0; i < 6; i++) {
                fgets(linha, sizeof(linha), arquivo_produtos);
                
                if (strstr(linha, "Codigo") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    codigo = strtol(linha, &endpointer, 10);
                    printf("\nCï¿½digo: %li", codigo);
                }
                
                if (strstr(linha, "Preco por quilograma") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    preco_por_quilograma = strtod(linha, &endpointer);
                    printf("\nPreï¿½o por quilograma: R$ %.2f", preco_por_quilograma);
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

        rewind(arquivo_produtos);

    }
    
    exibir_informacao("padrao");
    fclose(arquivo_produtos);
    return 0;

}

int excluir_produtos(){

    if (numero_de_produtos_no_carrinho <= 0) {
        system("cls");
        printf("Você ainda não tem produtos para excluir\n\n");
        exibir_informacao("padrao");
        return 0;
    } else {
        int produtos_a_deletar, codigo_do_produto_indesejado; 
        system("cls");
        consultar_carrinho();
        printf("Qual o código do produto que deseja excluir? ");
        scanf("%d",&codigo_do_produto_indesejado);
        
        // loop para encontrar o produto com o código e excluí-lo
        for(int i = 0;i < numero_de_produtos_no_carrinho; i++) {
            for (int j = 0; j < produtos_a_deletar; j++) {
                if (carrinho_com_itens[i].codigo == codigo_do_produto_indesejado) {
                    // desloca a posição dos outros itens para deletar o item desejado
                    for (int k = i; k < numero_de_produtos_no_carrinho - 1; k++) {
                        carrinho_com_itens[k] = carrinho_com_itens[k + 1];
                    }
                    numero_de_produtos_no_carrinho--;
                    i--;
                    break;
                }
            }
        }

        printf("\nProduto excluído com sucesso!\n");
        return 0;
        }
    
}





/*REQUISITOS

@ Poder consultar Preco de produtos a partir de arquivo_produtos .txt
- Processar compras (como um carrinho)
- Excluir frutas do carrinho em quantidades especificas
- Consultar condiÃ§Ã£o atual do carrinho (ver produtos)
- FunÃ§Ã£o finalizar compra para retornar o total
- Consultar todas as frutas disponiveis para compra
- Poder consultar codigo do produtos a partir do seu nome
- Controle de estoque

AINDA TEM QUE FAZER

- Consertar funcao de consultar produtos para printar uma mensagem caso o produto nao tiver sido achado
- Deixar o txt bonito, cheio de produtos (falta MelÃ£o)
- Bug que adiciona o produto ao carrinho mesmo que a funcao nao tenha achado

*/

