#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>


// fun��es
int adicionar_produto();
int consultar_carrinho();
void exibir_informacao(char mensagem[50]);
int consultar_produtos();
int excluir_produtos();
int finalizar_compra();
int administrar_estoque();

// vari�veis
int escolha_menu;
int codigo_produto;
int unidades_produto;
int numero_de_produtos_no_carrinho = 0;

// vari�veis especiais
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
    printf("Digite o n�mero de acordo com o servi�o desejado:\n\n");
    printf("1. Consultar informa��es de produtos\n");
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
        administrar_estoque();
        break;
    default:
        printf("N�o h� um servi�o correspondente ao caracter digitado. Tente novamente\n");
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

    char quilos_ou_gramas;
    float entrada_quantidade;

    quilos_ou_gramas:
    printf("Quilos ou gramas (q/g)? ");
    fflush(stdin);
    scanf("%c", &quilos_ou_gramas);

    if (quilos_ou_gramas == 'q') {
        printf("Quantos quilos? ");
        scanf("%f", &entrada_quantidade);
        quantidade = (int)(entrada_quantidade * 1000);
    } else if (quilos_ou_gramas == 'g') {
        printf("Quantas gramas? ");
        scanf("%i", &quantidade);  
    } else {
        printf("\nEsta n�o � uma op��o v�lida, tente novamente");
        fflush(stdin);
        getchar();
        goto quilos_ou_gramas;
    }


    while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) { // procura o produto e printa as informacoes do .txt
        if (strstr(linha, produto) != NULL) {
            resultado_busca = 1;

            for (int i = 0; i < 6; i++) {
                fgets(linha, sizeof(linha), arquivo_produtos);
                
                if (strstr(linha, "Codigo") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    codigo = strtol(linha, &endpointer, 10);
                    printf("\nC�digo: %li", codigo);
                }
                
                if (strstr(linha, "Preco por quilograma") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    preco_por_quilograma = strtod(linha, &endpointer);
                    printf("\nPre�o por quilograma: R$ %.2f", preco_por_quilograma);
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
        printf("Item '%s' n�o encontrado.\n", produto);
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
        printf("Voc� n�o tem nenhum produto adicionado ao carrinho");
        exibir_informacao("padrao");
        return 0;
    } else {

    printf("Carrinho de compras\n\n\n");
    
    for (int i = 0; i < numero_de_produtos_no_carrinho; i++) {
        printf("Produto %d: \n\n", i + 1);
        printf("Nome: %s", carrinho_com_itens[i].nome);
        printf("\nPre�o por quilograma: R$ %.2f\n", carrinho_com_itens[i].preco);
        printf("Quantidade (em gramas) no carrinho: %d\n", carrinho_com_itens[i].quantidade);
        printf("C�digo: %d\n\n", carrinho_com_itens[i].codigo);
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
        printf("\nNao � poss�vel realizar %i consultas de uma vez. O n�mero m�ximo de consultas � 10", quantidade_de_consultas);
        printf("\n\nPressione Enter para tentar novamente...");
        fflush(stdin);
        getchar();
        goto pergunta;
    } else if (quantidade_de_consultas <= 0) {
        printf("\n\"%i\" n�o � um n�mero v�lido", quantidade_de_consultas);
        printf("\n\nPressione Enter para tentar novamente...");
        fflush(stdin);
        getchar();
        goto pergunta;
    }

    printf("Escreva o nome do(s) produto(s): \n\n");

    for (int i = 0; i < quantidade_de_consultas; i++) {
        scanf("%s", produtos[i]);
    }

    // o "for" serve para procurar cada produto separadamente, enquanto o "while" procura apenas um �ndice espec�fico do array de produtos
    
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
                    printf("\nC�digo: %li", codigo);
                }
                
                if (strstr(linha, "Preco por quilograma") != NULL) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                    preco_por_quilograma = strtod(linha, &endpointer);
                    printf("\nPre�o por quilograma: R$ %.2f", preco_por_quilograma);
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
        printf("Voc� ainda n�o tem produtos para excluir\n\n");
        exibir_informacao("padrao");
        return 0;
    } else {
        int produtos_a_deletar, codigo_do_produto_indesejado; 
        system("cls");
        consultar_carrinho();
        printf("Qual o c�digo do produto que deseja excluir? ");
        scanf("%d",&codigo_do_produto_indesejado);
        
        // loop para encontrar o produto com o c�digo e exclu�-lo
        for(int i = 0;i < numero_de_produtos_no_carrinho; i++) {
            for (int j = 0; j < produtos_a_deletar; j++) {
                if (carrinho_com_itens[i].codigo == codigo_do_produto_indesejado) {
                    // desloca a posi��o dos outros itens para deletar o item desejado
                    for (int k = i; k < numero_de_produtos_no_carrinho - 1; k++) {
                        carrinho_com_itens[k] = carrinho_com_itens[k + 1];
                    }
                    numero_de_produtos_no_carrinho--;
                    i--;
                    break;
                }
            }
        }

        printf("\nProduto exclu�do com sucesso!\n");
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

    printf("N�mero de itens: %d\n", numero_de_produtos_no_carrinho);

    while (i < numero_de_produtos_no_carrinho) {

        valor_de_compra_produto = carrinho_com_itens[i].preco * carrinho_com_itens[i].quantidade / 1000;
        quilogramas = (double) carrinho_com_itens[i].quantidade / 1000;
        gramas = carrinho_com_itens[i].quantidade;

       if (quilogramas < 1) {
        printf("\n%i gramas de %-30s R$%8.2f\n", gramas, carrinho_com_itens[i].nome, valor_de_compra_produto);
       } else if (quilogramas < 2) {
        printf("\n%.1f quilo de %-30s R$%10.2f\n", quilogramas, carrinho_com_itens[i].nome, valor_de_compra_produto);
       } else {
        printf("\n%.1f quilos de %-30s R$%8.2f\n", quilogramas, carrinho_com_itens[i].nome, valor_de_compra_produto);
       }



        total += (carrinho_com_itens[i].preco * carrinho_com_itens[i].quantidade / 1000);
        i++;

    }

    printf("\n-----------------------\n");
    printf("Total: %.2f", total);
    printf("\n-----------------------\n");

    printf("\n\nDeseja finalizar a compra? (s/n)");
    char finalizar;
    scanf("%c", finalizar);

    finalizar:

    if (finalizar == 's') {

    } else if (finalizar == 'n') {
        return 0;
    } else {
        printf("\nEsta n�o � uma op��o v�lida, tente novamente");
        fflush(stdin);
        getchar();
        goto finalizar;
    }

    return 0;

}

int administrar_estoque() { // fun��o para editar quantidade de produto no estoque e adicionar um novo produto no .txt

    char linha[100];
    char escolha;
    char produto_editar[100];
    unsigned int opcao_editar;
    char palavra_chave[25];

    opcao:
    
    system("cls");
    printf("Quer editar informa��o de algum produto ou adicionar um novo produto (e/a)? ");
    scanf("%c", &escolha);

    switch (escolha)
    {
    case 'e':

        ;
        FILE* arquivo_produtos = fopen("produtos.txt", "r+");

        if (arquivo_produtos == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        printf("\nQual produto quer editar? ");
        scanf("%s", produto_editar);



        editar:

        printf("\nO que quer editar? \n1. Nome\n2. C�digo\n3. Pre�o\n4. Quantidade no estoque\n");
        scanf("%i", &opcao_editar);

        switch (opcao_editar) 
        {
            case 1:
                ;
                strcpy(palavra_chave, "Nome");
                break;
            case 2:
                ;
                strcpy(palavra_chave, "Codigo");
                break;
            case 3:
                ;
                strcpy(palavra_chave, "Preco");
                break;
            case 4:
                ;
                strcpy(palavra_chave, "Quantidade no estoque");
                break;
            default:
                printf("Esta n�o � uma op��o v�lida. Tente novamente");
                fflush(stdin);
                getchar();
                goto editar;
                break;
            
        }

        while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) { // itera dentro do arquivo testando a condicional abaixo
            if (strstr(linha, produto_editar) != NULL) { // procura pelo nome do produto que o usu�rio escolheu editar
                while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) {
                    if (strstr(linha, palavra_chave) != NULL) { // procura pela informa��o espec�fica do produto
                        fgets(linha, sizeof(linha), arquivo_produtos);
                        long int linha_length = strlen(linha);
                        printf("\n\nValor da linha ao procurar pela palavra-chave (ex.: Nome, Qtdd. no estoque): %s", linha);
                        printf("\n%s atual do produto:\n%s", palavra_chave, linha);
                        palavra_chave[0] = tolower(palavra_chave[0]); // converte a string "palavra_chave" para caracteres min�sculos
                        printf("\nQual novo valor voc� deseja atribuir ao campo \"%s\"? ", palavra_chave);
                        char valor_novo[100];
                        scanf("%s", valor_novo);
                        fseek(arquivo_produtos, linha_length, SEEK_CUR);
                        fputs(valor_novo, arquivo_produtos);
                    }
                }
            }
        }

        break;
    case 'a':

        break;
    default:
        printf("Esta n�o � uma op��o v�lida. Tente novamente");
        fflush(stdin);
        getchar();
        goto opcao;
        break;
    }


}

/*REQUISITOS

@ Poder consultar Preco de produtos a partir de arquivo_produtos .txt
@ Processar compras (como um carrinho)
- Excluir frutas do carrinho em quantidades especificas #####
@ Consultar condi��o atual do carrinho (ver produtos)
@ Fun��o finalizar compra para retornar o total
@ Poder consultar codigo do produtos a partir do seu nome
- Controle de estoque ########

AINDA TEM QUE FAZER

- Consertar fun��o de consultar produtos para printar uma mensagem caso o produto n�o tiver sido achado
- Deixar o .txt bonito, cheio de produtos (falta mel�o)
- Bug que adiciona o produto ao carrinho mesmo que a fun��o n�o tenha achado
- Fazer duas adi��es ou mais ao carrinho do mesmo produto se somarem e contarem apenas como um item no carrinho
- Erro na fun��o 'adicionar_produto': mesmo que voc� digite o nome de um produto meio certo (ex.: "Per", ao inv�s de "Pera") o programa o procura, e salva o nome que o usu�rio escreveu no carrinho com nome escrito de forma incorreta
- Diminuir a quantidade do produto armazenado no estoque ap�s a fun��o finalizar compra (j� que o cliente comprou, o estoque diminuiu)
- Erro na fun��o consultar produtos: se o item que o usu�rio digitou n�o existe no .txt, o programa apenas d� output no que o usu�rio digitou. Deveria haver alguma mensagem de erro para o usu�rio tentar digitar de novo
- Fazer as fun��es de procura/leitura do .txt funcionar com encoding Portugu�s (acentos e caracteres n�o inclusos no ASCII), sem dar falso positivo
- Fun��o administrar estoque (editar informacao de produto): Mostrar informacoes do produto depois do usuario digitar o nome (produto_editar) para facilitar visualiza��o

IDEIAS

- Alguma das coisas que ainda tem que fazer 
*/

