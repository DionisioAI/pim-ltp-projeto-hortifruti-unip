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
FILE* arquivo_produtos; // arquivo .txt que vai ser utilizado para armazenar informa��es de produtos
typedef struct { // structure usada para armazenar produtos no carrinho
    char nome[100];
    double preco;
    int quantidade;
    int codigo;
} item_carrinho;
item_carrinho carrinho_com_itens[100]; // array do carrinho de compras
int menu = 1; // vari�vel para controlar o loop do menu

int main() {

    setlocale(LC_ALL, "Portuguese"); // chamada da fun��o para compatibilidade com portugu�s

    menu = 1;

    while (menu) {

    FILE* arquivo_produtos = fopen("produtos.txt", "r"); // abrir arquivo no modo "read"

    if (arquivo_produtos == NULL) { // imprime erro caso arquivo n�o abra
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    system("cls"); // limpa o terminal

    // menu principal
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
        break;
    case 5:
        finalizar_compra();
        break;
    case 6:
        administrar_estoque();
        break;
    default:
        printf("N�o h� um servi�o correspondente ao caracter digitado. Tente novamente\n");
        exibir_informacao("padrao");
        break;
    }

    }

    return 0;

}

// para adicionar produto no carrinho de compras
int adicionar_produto() {

    FILE* arquivo_produtos = fopen("produtos.txt", "r");

    if (arquivo_produtos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // vari�veis que armazenam valores do produto 
    char produto[100];
    int quantidade;
    double preco_por_quilograma;
    long int codigo;
    long int estoque;

    // vari�veis para controlar fluxo de procura no arquivo
    char linha[100];
    int resultado_busca = 0;
    char* endpointer;

    printf("\nQual produto quer adicionar? ");
    scanf("%s", produto);

    char quilos_ou_gramas;
    float entrada_quantidade;

    quilos_ou_gramas:
    printf("Quilos ou gramas (q/g)? "); // permite o usu�rio escolher se ele quer fazer input da quantidade em gramas ou quilos
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


    while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) { // procura as informa��es do produto e guarda elas em vari�veis
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

    // atualiza o array do carrinho com as informa��es do produto escolhido

    strcpy(carrinho_com_itens[numero_de_produtos_no_carrinho].nome, produto);
    carrinho_com_itens[numero_de_produtos_no_carrinho].preco = preco_por_quilograma;
    carrinho_com_itens[numero_de_produtos_no_carrinho].quantidade = quantidade;
    carrinho_com_itens[numero_de_produtos_no_carrinho].codigo = codigo;
    numero_de_produtos_no_carrinho++;

    if (!resultado_busca) { // caso n�o haja nenhum produto com o nome do produto que o usu�rio quis procurar, imprime mensagem de erro
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

    if (numero_de_produtos_no_carrinho == 0) { // caso o usu�rio n�o tenha adicionado nenhum produto ou adicionou e excluiu todos, informa que n�o existem produtos no carrinho
        printf("Voc� n�o tem nenhum produto adicionado ao carrinho");
        exibir_informacao("padrao");
        return 0;
    } else {

    printf("Carrinho de compras\n\n\n"); // exibe todos produtos no carrinho
    
    for (int i = 0; i < numero_de_produtos_no_carrinho; i++) {
        printf("Produto %d: \n\n", i + 1);
        printf("Nome: %s", carrinho_com_itens[i].nome);
        printf("\nPre�o por quilograma: R$ %.2f\n", carrinho_com_itens[i].preco);
        printf("Quantidade (em gramas) no carrinho: %d\n", carrinho_com_itens[i].quantidade);
        printf("C�digo: %d\n\n", carrinho_com_itens[i].codigo);
    }

    }

    exibir_informacao("padrao");

    return 0;

}

void exibir_informacao(char mensagem[50]) { // fun��o simples para pausar execu��o do programa quando alguma informa��o relevante aparecer no terminal

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

int consultar_produtos() { // fun��o para consultar informa��es dos produtos a partir do .txt

    FILE* arquivo_produtos = fopen("produtos.txt", "r");

    if (arquivo_produtos == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // vari�veis de controle e de armazenamento tempor�rio
    int quantidade_de_consultas;
    char produtos[11][100];
    int buscas_pendentes;
    char linha[100];
    char* endpointer;
    int sucesso_busca = 0;

    char nome[100];
    double preco_por_quilograma;
    int codigo;
    long int estoque;

    pergunta:

    printf("\nQuer consultar quantos produtos? ");
    scanf("%i", &quantidade_de_consultas);

    buscas_pendentes = quantidade_de_consultas;

    if (quantidade_de_consultas > 10) {
        printf("\nNao � poss�vel realizar %i consultas de uma vez. O n�mero m�ximo de consultas � 10", quantidade_de_consultas); // limita a consulta em at� 10 produtos de uma vez
        printf("\n\nPressione Enter para tentar novamente...");
        fflush(stdin);
        getchar();
        goto pergunta;
    } else if (quantidade_de_consultas <= 0) { // corrige usu�rio caso haja erro de digita��o
        printf("\n\"%i\" n�o � um n�mero v�lido", quantidade_de_consultas);
        printf("\n\nPressione Enter para tentar novamente...");
        fflush(stdin);
        getchar();
        goto pergunta;
    }

    

    if (quantidade_de_consultas == 1) { // muda output se houver plural (mais de um produto requerido na consulta)
        printf("Escreva o nome do produto: \n"); 
    } else {
        printf("Escreva o nome dos produtos: \n");
    }

    for (int i = 0; i < quantidade_de_consultas; i++) {
        scanf("%s", produtos[i]);
    }

    // o "for" serve para procurar cada produto separadamente, enquanto o "while" procura apenas um �ndice espec�fico do array de produtos
    
    for (size_t j = 0; j < buscas_pendentes; j++)
    {
        rewind(arquivo_produtos);

        while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) { // procura os produtos e printa as informacoes do .txt
            if (strstr(linha, produtos[j]) != NULL) {
                strcpy(nome, linha);
                printf("\n%s", nome);

                for (int i = 0; i < 6; i++) {
                    fgets(linha, sizeof(linha), arquivo_produtos);
                
                    if (strstr(linha, "Codigo") != NULL) {
                        fgets(linha, sizeof(linha), arquivo_produtos);
                        codigo = strtol(linha, &endpointer, 10);
                        printf("C�digo: %li", codigo);
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

int excluir_produtos() { // fun��o para excluir produtos do carrinho

    if (numero_de_produtos_no_carrinho <= 0) { // caso o usu�rio n�o tenha adicionado nenhum produto ou adicionou e excluiu todos, informa que n�o existem produtos no carrinho
        system("cls");
        printf("Voc� ainda n�o tem produtos para excluir\n\n");
        exibir_informacao("padrao");
        return 0;
    } else {
        int produtos_a_deletar, codigo_do_produto_indesejado; 
        system("cls");
        consultar_carrinho();
        printf("Qual o c�digo do produto que deseja excluir? "); // exclui com base no c�digo do produto
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

int finalizar_compra() { // fun��o de c�lculo do total e finaliza��o da execu��o do programa

    double total = 0;
    int i = 0;
    double valor_de_compra_produto;
    double quilogramas;
    int gramas;

    system("cls");

    printf("N�mero de itens: %d\n", numero_de_produtos_no_carrinho);

    while (i < numero_de_produtos_no_carrinho) { // calcula o pre�o a se pagar com base na quantidade que o usu�rio escolheu

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



        total += (carrinho_com_itens[i].preco * carrinho_com_itens[i].quantidade / 1000); // acumula todos os valores na vari�vel "total"
        i++;

    }

    printf("\n-----------------------\n");
    printf("Total: %.2f", total); // exibe o valor a pagar
    printf("\n-----------------------\n");

    printf("\n\nDeseja finalizar a compra (s/n)? "); // d� a op��o do usu�rio apenas vizualizar as informa��es e voltar � compra
    char finalizar;
    scanf(" %c", &finalizar);

    finalizar:

    if (finalizar == 's') {
        printf("\nCompra finalizada com sucesso!"); // encerra a execu��o
        menu = 0;
        return 1;
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
    char valor_novo[100];
    long posicao_atual_ponteiro;

    opcao:
    
    system("cls");
    printf("Quer editar informa��o de algum produto ou adicionar um novo produto (e/a)? ");
    scanf("%c", &escolha);

    switch (escolha)
    {
    case 'e': // op��o de (e)ditar informa��es

        ;
        arquivo_produtos = fopen("produtos.txt", "r+"); // abre no modo de ler e escrever no arquivo, pois "editar", na l�gica interna, � sobrescrever

        if (arquivo_produtos == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        printf("\nQual produto quer editar? "); // define qual produto ser� editado
        scanf("%s", produto_editar);

        editar:

        printf("\nO que quer editar? \n1. Nome\n2. C�digo\n3. Pre�o\n4. Quantidade no estoque\n"); // define qual valor ser� editado
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
                strcpy(palavra_chave, "Preco por quilograma");
                break;
            case 4:
                ;
                strcpy(palavra_chave, "Quantidade no estoque");
                break;
            default:
                printf("Esta n�o � uma op��o v�lida. Aperte Enter para tentar novamente");
                fflush(stdin);
                getchar();
                goto editar;
                break;
            
        }

        while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) { // l� linhas do arquivo em loop
            if (strstr(linha, produto_editar) != NULL) { // procura pelo nome do produto
                if (opcao_editar == 1) { // se o usu�rio quiser editar o nome
                    int length_linha = strlen(linha); // guarda o tamanho da string do nome do produto
                    posicao_atual_ponteiro = ftell(arquivo_produtos); // guarda posi��o do ponteiro (in�cio do nome do produto)
                    printf("\nValor atual de \"%s\":\n%s", palavra_chave, linha);
                    printf("\nQual novo valor voc� deseja atribuir ao campo \"%s\"? ", palavra_chave);
                    scanf(" %[^\n]", valor_novo); // l� o valores com espa�os
                    fseek(arquivo_produtos, posicao_atual_ponteiro - (length_linha + 1), SEEK_SET);
                    long outra_posicao = ftell(arquivo_produtos);
                    fprintf(arquivo_produtos, "%s", valor_novo);
                    fseek(arquivo_produtos, outra_posicao + strlen(valor_novo), SEEK_SET);
                    fprintf(arquivo_produtos, "                         "); // permite escrever nomes menores (em caracteres) que o nome antigo sobrescrevendo eles com espa�os em branco
                    fclose(arquivo_produtos);
                    break;

                } else {
                // encontrou o produto, agora busca a chave espec�fica (nome, c�digo, etc.)
                while (fgets(linha, sizeof(linha), arquivo_produtos) != NULL) {
                    if (strstr(linha, palavra_chave) != NULL) { // encontrou a chave desejada
                        // move para a pr�xima linha, onde est� o valor a ser editado
                        posicao_atual_ponteiro = ftell(arquivo_produtos); // salva a posi��o atual
                        fgets(linha, sizeof(linha), arquivo_produtos); // l� o valor atual
                        // mostra o valor atual ao usu�rio
                        printf("\nValor atual de \"%s\":\n%s", palavra_chave, linha);
                        // solicita o novo valor ao usu�rio
                        printf("\nQual novo valor voc� deseja atribuir ao campo \"%s\"? ", palavra_chave);
                        scanf(" %[^\n]", valor_novo); // l� o valor com espa�os
                        // retorna ao in�cio da linha onde o valor ser� substitu�do
                        fseek(arquivo_produtos, posicao_atual_ponteiro, SEEK_SET);
                        // substitui o valor antigo pelo novo (sobrescrevendo)
                        fprintf(arquivo_produtos, "%s", valor_novo);
                        // garante que os dados sejam gravados no arquivo
                        fflush(arquivo_produtos);
                        // sai do loop ap�s fazer a substitui��o
                        break;
                    }
                }
                }

                // sai do loop ap�s encontrar e substituir a informa��o do produto
                break;
            }
        }

        fclose(arquivo_produtos);

        break;
    case 'a': // op��o de (a)dicionar produtos novos

        fflush(stdin);
        arquivo_produtos = fopen("produtos.txt", "a");

        if (arquivo_produtos == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        struct estrutura_produto {
            char nome[100];
            char codigo[100];
            char preco[100];
            char quantidade[100];
        };

        struct estrutura_produto produto_novo; // cria uma structure apenas para esta fun��o

        inserir_informacoes:

        printf("\nQual o nome do produto? ");
        gets(produto_novo.nome);

        printf("\nQual o c�digo do produto? ");
        scanf("%s", produto_novo.codigo);

        printf("\nQual o pre�o por quilograma do produto? ");
        scanf("%s", produto_novo.preco);

        printf("\nQuanto h� no estoque deste produto (em quilos)? "); // consertar para aceitar valores em quilos e valores decimais
        scanf("%s", produto_novo.quantidade);

        // exibe o produto novo para o usu�rio

        printf("\n\nINFORMA��ES DO NOVO PRODUTO");
        printf("\n\nNome");
        printf("\n%s", produto_novo.nome);
        printf("\nC�digo");
        printf("\n%s", produto_novo.codigo);
        printf("\nPre�o");
        printf("\n%s", produto_novo.preco);
        printf("\nQuantidade no estoque");
        printf("\n%s\n\n", produto_novo.quantidade);

        confirmacao:

        printf("As informa��es est�o corretas (s/n)? "); // permite o usu�rio visualizar e confirmar o que escreveu, permitindo alterar caso haja erro
        fflush(stdin);
        char confirmacao;
        scanf("%c", &confirmacao);

        if (confirmacao == 's') {
            fprintf(arquivo_produtos, "\n\nNome");
            fprintf(arquivo_produtos, "\n%s", produto_novo.nome);
            fprintf(arquivo_produtos, "\nCodigo");
            fprintf(arquivo_produtos, "\n%s", produto_novo.codigo);
            fprintf(arquivo_produtos, "\nPreco por quilograma");
            fprintf(arquivo_produtos, "\n%s", produto_novo.preco);
            fprintf(arquivo_produtos, "\nQuantidade no estoque");
            fprintf(arquivo_produtos, "\n%s", produto_novo.quantidade);
            fclose(arquivo_produtos);
            printf("\nProduto adicionado com sucesso!");
            exibir_informacao("padrao");
            break;
        } else if (confirmacao == 'n') {
            printf("Voc� voltar� para inserir as informa��es do produto novamente ao pressionar Enter...\n");
            fflush(stdin);
            getchar();
            goto inserir_informacoes;
        } else {
            printf("\nEsta n�o � uma op��o v�lida. Aperte Enter para retornar � confirma��o");
            fflush(stdin);
            getchar();
            goto confirmacao;
        }

        break;
    default:
        printf("Esta n�o � uma op��o v�lida. Pressione Enter para tentar novamente");
        fflush(stdin);
        getchar();
        goto opcao;
        break;
    }



}



