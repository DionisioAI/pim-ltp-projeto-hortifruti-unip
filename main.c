#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>


// Declaração de funções

void exit();
void menuPrincipal();
void escreverArquivo();
void lerArquivo();
void atualizarArquivo();
void deletarArquivo();

// Função principal

int main(){
    
    int escolha = 0; // Inicializa a variável escolha pela primeira vez

    menuPrincipal();



    switch(escolha) {
            case 1:
                escreverArquivo();
                printf("\n\nCliente adicionado com sucesso!\n\n");
                menuPrincipal();
                break;
            case 2:
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nINFORMACOES SOBRE CLIENTES\n\n\n");
                lerArquivo();
                menuPrincipal();
                break;
            case 5:
                printf("\n\n\n\n\n\n\n\n\n\n                          _/`.-'`.\n");
                printf("                _      _/` .  _.'\n");
                printf("       ..:::::.(_)   /` _.'_./\n");
                printf("     .oooooooooo\\ \\o/.-'__.'o.\n");
                printf("    .ooooooooo`._\\_|_.'`oooooob.\n");
                printf("  .ooooooooooooooooooooo&&oooooob.\n");
                printf(" .oooooooooooooooooooo&@@@@@@oooob.\n");
                printf(".ooooooooooooooooooooooo&&@@@@@ooob.\n");
                printf("doooooooooooooooooooooooooo&@@@@ooob\n");
                printf("doooooooooooooooooooooooooo&@@@oooob\n");
                printf("dooooooooooooooooooooooooo&@@@ooooob\n");
                printf("dooooooooooooooooooooooooo&@@oooooob\n");
                printf("`dooooooooooooooooooooooooo&@ooooob'\n");
                printf(" `doooooooooooooooooooooooooooooob'\n");
                printf("  `doooooooooooooooooooooooooooob'\n");
                printf("   `doooooooooooooooooooooooooob'\n");
                printf("    `doooooooooooooooooooooooob'\n");
                printf("     `doooooooooooooooooooooob'\n");
                printf("      `dooooooooobodoooooooob'\n");
                printf("       `doooooooob dooooooob'\n");
                printf("         `\"""""""' `""""""'\n");
                printf("");
                printf("");

                break;
            default:
                printf("O programa ainda nao reconhece este comando");
                break;
        }


    

}

void escreverArquivo() {

    struct fichaCliente{ // Estrutura de dado para a ficha do cliente
        char nome [100];
        char endereco[100];
        char cpf[100];
        char telefone[100];
    };

    struct fichaCliente cliente; // Declarando a variável 'cliente' no formato/estrutura 'fichaCliente' logo acima

    printf("\nDigite o nome do cliente: \n\n");
    scanf("%c", (char *) stdin); // O que essa linha faz? Não sei, mas funciona
    fgets(cliente.nome, 100, stdin);

    printf("\nDigite o endereco do cliente: \n\n");
    fgets(cliente.endereco, 100, stdin);

    printf("\nDigite o CPF do cliente: \n\n");
    fgets(cliente.cpf, 100, stdin);

    printf("\nDigite o telefone do cliente: \n\n");
    fgets(cliente.telefone, 100, stdin);

    // Adicionar os inputs do usuário do programa para um arquivo '.txt'

    FILE *file;
    file = fopen("cliente.txt","a");
    fprintf(file, "\nNome do cliente: %s \nEndereco do cliente: %s \nCPF do cliente: %s \nTelefone do cliente: %s------------------------------------------------------------", cliente.nome, cliente.endereco, cliente.cpf, cliente.telefone);
    
    fclose(file);

}

void lerArquivo() {

    FILE *file = fopen("cliente.txt", "r");
    char ch;
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);
    
    fclose(file);
}

void menuPrincipal() {

    int escolha = 0;

    printf("\n\n\nMENU DE CADASTRO DO HORTIFRUTI\n\n");
    printf("Digite '1' para: Cadastrar um novo cliente\n");
    printf("Digite '2' para: Consultar informacoes de um cliente\n");
    printf("Digite '3' para: Atualizar informacoes de um cliente\n");
    printf("Digite '4' para: Deletar cliente\n");
    printf("Digite '5' para: Sair do programa\n\n\n");
    printf("Favor, digitar servico desejado: \n");

    scanf("%i", &escolha); // Pede para o usuário escolher qual função chamar

    switch(escolha) {
            case 1:
                escreverArquivo();
                printf("\n\nCliente adicionado com sucesso!\n\n");
                menuPrincipal();
                break;
            case 2:
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nINFORMACOES SOBRE CLIENTES\n\n\n");
                lerArquivo();
                menuPrincipal();
                break;
            case 5:
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                          _/`.-'`.\n");
                printf("                _      _/` .  _.'\n");
                printf("       ..:::::.(_)   /` _.'_./\n");
                printf("     .oooooooooo\\ \\o/.-'__.'o.\n");
                printf("    .ooooooooo`._\\_|_.'`oooooob.\n");
                printf("  .ooooooooooooooooooooo&&oooooob.\n");
                printf(" .oooooooooooooooooooo&@@@@@@oooob.\n");
                printf(".ooooooooooooooooooooooo&&@@@@@ooob.\n");
                printf("doooooooooooooooooooooooooo&@@@@ooob\n");
                printf("doooooooooooooooooooooooooo&@@@oooob\n");
                printf("dooooooooooooooooooooooooo&@@@ooooob\n");
                printf("dooooooooooooooooooooooooo&@@oooooob\n");
                printf("`dooooooooooooooooooooooooo&@ooooob'\n");
                printf(" `doooooooooooooooooooooooooooooob'\n");
                printf("  `doooooooooooooooooooooooooooob'\n");
                printf("   `doooooooooooooooooooooooooob'\n");
                printf("    `doooooooooooooooooooooooob'\n");
                printf("     `doooooooooooooooooooooob'\n");
                printf("      `dooooooooobodoooooooob'\n");
                printf("       `doooooooob dooooooob'\n");
                printf("         `\"""""""' `""""""'\n");
                printf("");
                printf("");

                exit(0);
                break;
                
                
            default:
                printf("O programa ainda nao reconhece este comando");
        }
        

}

/*Esse código ainda precisa:

- Voltar ao menu sempre que executar uma função, podendo fazer diversas operações em apenas um 'run'
- Conseguir ler um cliente específico (e não entregar todo o .txt inteiro)
- Aceitar acentuação (UTF-8)
- Deletar cliente
- Atualizar informações de cliente
- Lidar com produtos e fornecedores
- Simular caixas
- Simular computadores de funcionários
- Simular servidor



ARTIGO PARA MANIPULAR DADOS COM ARQUIVOS JSON EM C:
https://www.geeksforgeeks.org/cjson-json-file-write-read-modify-in-c/
*/