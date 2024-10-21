#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "SDC.c"
#include <direct.h>

int cadastra_cliente(void); int ler_arquivo(void);int main();int exclui_cadastro(void);     //Protótipos


//função principal void main
int main()
{    
    nome_dir = NULL;
    nome_pasta = NULL;       
    int inicia_funcao = 0;
    memset(cliente.cpf,0,sizeof(cliente.cpf));
    memset(nome_ficha,0,sizeof(nome_ficha));
    memset(aux,0,sizeof(aux));
    memset(aux2,0,sizeof(aux2)); 
    strcpy(mkd, mkd_original);

    system("cls");
  
    printf("==================SDC==================\n");
    printf("==========Sistema De Cadastro==========\n");
    printf("==========Escolha uma Funcao===========\n");
    printf("1 - Cadastrar de cliente\n2 - Ler|Editar cadastro\n3 - Excluir dados de cadastro\n\n");
    scanf("%d", &inicia_funcao);
    getchar();

    switch (inicia_funcao)
    {
    case 1:
        cadastra_cliente();
        break;
    
    case 2:
        system("cls");
        printf("=============================SDC==============================\n");
        printf("======================Sistema De Cadastro=======================\n");
        printf("\n1-Ler arquivo de cadastro\n2-editar arquivo de cadastro\n3-Retornar ao menu principal\n");
        scanf("%d", &escolha);
        getchar();
        if(escolha==1){
            ler_arquivo();
        }
        if (escolha==3)
        {
            main();
        }
        
        break;
    
    case 3:
        exclui_cadastro();
        break;

    default:
        break;
    }
    return 0;
}
//===============================================================================================================================================//

/*REQUISICOES A FAZER DO CODIGO:

- Voltar ao menu sempre que executar uma função, podendo fazer diversas operações em apenas um 'run'
- Conseguir ler um cliente específico (e não entregar todo o .txt inteiro)
- Aceitar acentuação (UTF-8)
- Deletar cliente
- Atualizar informações de cliente
- Lidar com produtos e fornecedores
- Simular caixas 
- Simular computadores de funcionários 
- Simular servidor 

PARA ALTERACAO E LEITURA DE DADOS/ARQUIVOS

- Criar uma funcao que le todas as linhas do arquivo txt e busca pelo parametro especifico que o usuario quer (e.x.: \n Rua: ) e fazer a mesma coisa para atualizar informacoes, nao so pra ler
*/