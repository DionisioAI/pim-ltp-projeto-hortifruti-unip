#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>


// funções
int adicionar_produto();
int consultar_carrinho();
void exibir_informacao(char mensagem[50]);
int consultar_produtos();
int excluir_produtos();
int finalizar_compra();

// variáveis
int escolha_menu;
int codigo_produto;
int unidades_produto;
int numero_de_produtos_no_carrinho = 0;

// variáveis especiais
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

    printf("\n\nCAIXA REGISTRADORA\n\n\n");
    printf("Digite o número de acordo com o serviço desejado:\n\n");
    printf("1. Consultar informações de produtos\n");
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
        exibir_informacao("continuar");
        break;
    case 5:
        finalizar_compra();
        break;
    case 6:
        printf("\n\nEssa funcionalidade ainda não está disponível\n");
        break;
    default:
        printf("Não há um serviço correspondente ao caracter digitado. Tente novamente\n");
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
                    printf("\nCódigo: %li", codigo);
                }
                
                if (strstr(linha, "Preco por quilograma") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    preco_por_quilograma = strtod(linha, &endpointer);
                    printf("\nPreço por quilograma: R$ %.2f", preco_por_quilograma);
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
        printf("Item '%s' não encontrado.\n", produto);
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
        printf("Você ainda não tem nenhum produto adicionado");
        exibir_informacao("padrao");
        return 0;
    } else {

    printf("Carrinho de compras\n\n\n");
    
    for (int i = 0; i < numero_de_produtos_no_carrinho; i++) {
        printf("Produto %d: \n\n", i + 1);
        printf("Nome: %s", carrinho_com_itens[i].nome);
        printf("\nPreço por quilograma: R$ %.2f\n", carrinho_com_itens[i].preco);
        printf("Quantidade (em gramas) no carrinho: %d\n", carrinho_com_itens[i].quantidade);
        printf("Código: %d\n\n", carrinho_com_itens[i].codigo);
    }

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
        printf("\nNao é possível realizar %i consultas de uma vez. O número máximo de consultas é 10", quantidade_de_consultas);
        printf("\n\nPressione Enter para tentar novamente...");
        fflush(stdin);
        getchar();
        goto pergunta;
    } else if (quantidade_de_consultas <= 0) {
        printf("\n\"%i\" não é um número válido", quantidade_de_consultas);
        printf("\n\nPressione Enter para tentar novamente...");
        fflush(stdin);
        getchar();
        goto pergunta;
    }

    printf("Escreva o nome do(s) produto(s): \n\n");

    for (int i = 0; i < quantidade_de_consultas; i++) {
        scanf("%s", produtos[i]);
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
                    printf("\nCódigo: %li", codigo);
                }
                
                if (strstr(linha, "Preco por quilograma") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    preco_por_quilograma = strtod(linha, &endpointer);
                    printf("\nPreço por quilograma: R$ %.2f", preco_por_quilograma);
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

int finalizar_compra() {

    double total = 0;
    int i = 0;
    double valor_de_compra_produto;
    double quilogramas;
    int gramas;

    system("cls");

    printf("Número de itens: %d\n", numero_de_produtos_no_carrinho);
    fflush(stdout);

    while (i < numero_de_produtos_no_carrinho) {

        valor_de_compra_produto = carrinho_com_itens[i].preco * carrinho_com_itens[i].quantidade / 1000;
        quilogramas = (double) carrinho_com_itens[i].quantidade / 1000;
        gramas = carrinho_com_itens[i].quantidade;
        fflush(stdout);

        if (quilogramas >= 1) {
            printf("\n%.0f quilos de %-30s R$%8.2f\n", quilogramas, carrinho_com_itens[i].nome, valor_de_compra_produto);
        } else {
            printf("\n%.0f gramas de %-30s R$%8.2f\n", gramas, carrinho_com_itens[i].nome, valor_de_compra_produto);
        }

        fflush(stdout);


        total += (carrinho_com_itens[i].preco * carrinho_com_itens[i].quantidade / 1000);
        i++;

    }

    printf("\n-----------------------\n");
    printf("Total: %.2f", total);
    printf("\n-----------------------\n");

    return 0;

}



/*REQUISITOS

@ Poder consultar Preco de produtos a partir de arquivo_produtos .txt
@ Processar compras (como um carrinho)
- Excluir frutas do carrinho em quantidades especificas
@ Consultar condição atual do carrinho (ver produtos)
- Função finalizar compra para retornar o total
- Consultar todas as frutas disponíveis para compra
@ Poder consultar codigo do produtos a partir do seu nome
- Controle de estoque

AINDA TEM QUE FAZER

- Consertar função de consultar produtos para printar uma mensagem caso o produto não tiver sido achado
- Deixar o .txt bonito, cheio de produtos (falta melão)
- Bug que adiciona o produto ao carrinho mesmo que a função não tenha achado
- Suportar input de quilogramas quando o usuário adicionar produto ao carrinho
- Fazer duas adições ou mais ao carrinho do mesmo produto se somarem e contarem apenas como um item no carrinho
- Erro na função 'adicionar_produto': mesmo que você digite o nome de um produto meio certo (ex.: "Per", ao invés de "Pera") o programa o procura, e salva o nome que o usuário escreveu no carrinho com nome escrito de forma incorreta
- Diminuir a quantidade do produto armazenado no estoque após a função finalizar compra (já que o cliente comprou, o estoque diminuiu)


*/

