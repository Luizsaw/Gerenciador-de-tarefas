/*SISTEMA DE GERENCIAMENTO CHOVEU? ONDE ENCHEU?
SGCOE versao 0.1
22/09/2022 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// bliblioteca externa importado para o projeto para manipulacao de cores
#include <conio.c>

#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

// tamanho constante determinado
#define SIZE 300


const char login[SIZE]="Admin";// determina o login padrao do sistema
const char senha[SIZE]="admin";// determina a senha padrao do sistema

/*
* linha = indice do vetor que determina o numero de gerentes cadastrados
* linha2 = indice do vetor que determina o numero de colaboradores cadastrados
* linha3 = indice do vetor que determina o numero de clientes cadastrados
* identificarColab = armazena um numero inteiro responsavel por identificar o colaborador.
*/
static int linha,linha2,linha3,identificarColab;

static char caractere;//var global que armazena caracteres em todo programa

int op;// var global que armazena numero inteiros usados para opcao de menu
int loginSenha();// funcao responsavel por login e senha

// estrutura de dado de gerente, colaborador e tarefas
struct dados_1
{
    char nome[SIZE];// armazena nome
    char email[SIZE];// armazena email
    char login[SIZE];// armazena login
    char senha[SIZE];// armazena senha
    char ramal[SIZE];// armazena ramal
    char cargo[SIZE];// armazena o cargo
    char titulo[SIZE][SIZE];// vetor bidimensional, armazena titulo de tarefa
    char descricao[SIZE][SIZE]; // vetor bidimensional 0,1, armazena descricao de tarefa
    char prioridade[SIZE][SIZE];// vetor bidimensional 0,1, armazena prioridade de tarefa
    char comentario[SIZE][SIZE];// vetor bidimensional 0,1, armazena comentario de tarefa
    int idComentario[SIZE];// armazena numero de identificacao
    int data[3][SIZE];//armazena data: 0=dia,1=mes, 2=ano
    int dataConclusao[3][SIZE];//armazena data de conclusao da tarefa
    int hora[3][SIZE];//armazena hora:0=hora,1=minutos, 2=segundos
    int prazo[SIZE];//armazena prazo em dias
    int idTarefa[SIZE];// armazena numero de indentificacao de tarefa
    int id,quantTarefa,tarefasConcluida,tarefasPendente;//variaveis contadoras
    bool concluir[SIZE];//false/true para conclusao de tarefa
}gerente[SIZE],colaborador[SIZE];
struct dados_2
{
    //armazena dados do cliente
    char razaoSocial[SIZE];
    char cnpj[SIZE];
    char email[SIZE];
    char telefone[SIZE];
    char endereco[SIZE];
    char descricao[SIZE];
}cliente[SIZE];

void criptografia(int opcao)
{
    FILE *origem, *destino;
    if (opcao == 1)
    {
        system("cls");
        textcolor(10);
        printf("\t\t\t\t\t\t-RELATÓRIO-\n\n\n");
        textcolor(15);
        //fopen abri um arquivo ou gera um arquivo
        origem = fopen("relatorio.txt", "r");
        destino = fopen("relatorioCript.txt", "w");
        //verifica se o arquivo nao e nulo
        if(origem != NULL && destino != NULL)
        {
            char c;
            int contador = 0;
            int i = 0;

            while(( c = fgetc(origem)) != EOF)//verifica o final de arquivo
            {
                contador++;
                printf("%c", c);
                i = c;
                i = i * contador;
                fprintf(destino,"%i ", i);//grava no arquivo
            }
            //fecha arquivo
            fclose(origem);
            fclose(destino);
            remove("relatorio.txt");
        }
        else
        {
            puts("Erro de leitura/escrita nos arquivos...");
        }
    }
    else if(opcao == 2) // Se for descriptografia
    {
        system("cls");
        origem = fopen("relatorioCript.txt", "r");
        destino = fopen("relatorioDescript.txt", "w");

        if(origem != NULL && destino != NULL)
        {
            int contador = 0;
            char c[100];
            int i = 0;

            while(fscanf(origem, "%s", c) != EOF)
            {
                contador++;
                i = atoi(c);
                i /= contador;
                printf("%c", i);
                fprintf(destino,"%c", i);
            }
            fclose(origem);
            fclose(destino);
            remove("relatorioCript.txt");
            textcolor(10);
            printf("\n\t\t\t\t\a     RELATÓRIO DESCRIPTOGRAFADO COM SUCESSO!\n");
            textcolor(15);
            printf("\n\t\t\t\t     ");
            system("pause");
        }
        else
        {
            textcolor(12);
            printf("\n\t\t\t\t\t\a   SEM DADOS PARA DESCRIPTOGRAFAR!\n");
            textcolor(15);
            printf("\n\t\t\t\t     ");
            system("pause");
        }
    }
}// criptografar
void mostrarDadosTarefas(int i)
{
    textcolor(14);
    printf("\n\tDados do colaborador");
    textcolor(15);
    printf("\n\t------------------------------------------------------------------------------------------------------");
    printf("\n\tID: %d",colaborador[i].id);
    printf("\n\tNome: %s",colaborador[i].nome);
    printf("\n\tCargo: %s",colaborador[i].cargo);
    printf("\n\tEmail: %s",colaborador[i].email);
    textcolor(14);
    printf("\n\n\tTarefa(s)");
    textcolor(15);
    printf("\n\t------------------------------------------------------------------------------------------------------");
    printf("\n\tTarefas atribuidas <%d>",colaborador[i].quantTarefa);
    printf("\n\tTarefas pendente(s) <%d>",colaborador[i].tarefasPendente);
    printf("\n\tTarefas concluída(s) <%d>",colaborador[i].tarefasConcluida);
    textcolor(12);
    printf("\n\t------------------------------------------------------------------------------------------------------ ");
    textcolor(15);
}// fim mostrarDadosTarefas
void mostrarDados(int i,int x)
{
    if(x==1)
        {
            //Dados Gerente y = 1
            printf("\n\t.------------------------------------------------------------------------------------------------------.");
            printf("\n\t|ID: %d",gerente[i].id);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Nome: %s",gerente[i].nome);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Email: %s",gerente[i].email);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Ramal: %s",gerente[i].ramal);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Login: %s",gerente[i].login);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Senha: %s",gerente[i].senha);
            printf("\n\t.------------------------------------------------------------------------------------------------------.");
            textcolor(9);
            printf("\n\t ------------------------------------------------------------------------------------------------------ ");
            textcolor(15);
        }
        else if(x==2)
        {
           //Dados Colaborador y = 2
            printf("\n\t.------------------------------------------------------------------------------------------------------.");
            printf("\n\t|ID: %d",colaborador[i].id);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Nome: %s",colaborador[i].nome);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Cargo: %s",colaborador[i].cargo);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Email: %s",colaborador[i].email);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Login: %s",colaborador[i].login);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Senha: %s",colaborador[i].senha);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            textcolor(9);
            printf("\n\t.------------------------------------------------------------------------------------------------------.");
            textcolor(15);
        }
        else if(x==3)
        {
            //Dados Cliente y = 3
            printf("\n\t.------------------------------------------------------------------------------------------------------.");
            printf("\n\t|Razão social: %s",cliente[i].razaoSocial);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|CNPJ: %s",cliente[i].cnpj);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Telefone: %s",cliente[i].telefone);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Email: %s",cliente[i].email);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Endereço: %s",cliente[i].endereco);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            printf("\n\t|Descrição: %s",cliente[i].descricao);
            printf("\n\t|------------------------------------------------------------------------------------------------------|");
            textcolor(9);
            printf("\n\t.------------------------------------------------------------------------------------------------------.");
            textcolor(15);
        }
}// fim mostrarDados
void excluirDados(int i,int x)
{
    int a;
    printf("\n\t\t\t\t\t  .--------------");
    textcolor(10);
    printf("MENU");
    textcolor(15);
    printf("-------------.");
    printf("\n\t\t\t\t\t  .-------------------------------.");
    printf("\n\t\t\t\t\t  |     <");
    textcolor(10);
    printf("1");
    textcolor(15);
    printf(">");
    printf(" Excluir cadastro      |");
    printf("\n\t\t\t\t\t  .-------------------------------.");
    printf("\n\n\t\t Pressione <1> para excluir este cadastro ou pressione qualquer outra tecla para voltar:");
    caractere=getch();
    if(caractere=='1')
    {
        caractere='2';
        textcolor(12);
        printf("\n\n\t\t\t   <<ATENÇÃO ESTE CADASTRO SERÁ EXCLUÍDO PERMANENTEMENTE DO SISTEMA>>\n\t\t   <<Pressione <1> para confirmar ou pressione qualquer outra tecla para voltar>>");
        textcolor(15);
        caractere=getch();
    }
        switch(caractere)
        {
            case '1':
                if(x==1)
                    {
                        //limpando dados dos vetores
                        memset(gerente[i].nome, 0, SIZE);
                        memset(gerente[i].email, 0, SIZE);
                        memset(gerente[i].ramal, 0, SIZE);
                        memset(gerente[i].login, 0, SIZE);
                        memset(gerente[i].senha, 0, SIZE);
                        gerente[i].id=0;
                        do{
                            //limpando dados dos vetores
                            strcpy(gerente[i].nome,gerente[i+1].nome);
                            strcpy(gerente[i].email,gerente[i+1].email);
                            strcpy(gerente[i].ramal,gerente[i+1].ramal);
                            strcpy(gerente[i].login,gerente[i+1].login);
                            strcpy(gerente[i].senha,gerente[i+1].senha);
                            gerente[i].id=gerente[i+1].id;
                            i++;
                            }while(i<linha);
                        linha--;
                        system("cls");
                        textcolor(10);
                        printf("\n\n\t\t\t\t\t\a   CADASTRO EXCLUÍDO COM SUCESSO!");
                        textcolor(15);
                        printf("\n\t\t\t\t   ");
                        system("pause");
                    }
                    else if(x==2)
                    {
                        //limpando dados dos vetores
                        memset(colaborador[i].nome, 0, SIZE);
                        memset(colaborador[i].email, 0, SIZE);
                        memset(colaborador[i].ramal, 0, SIZE);
                        memset(colaborador[i].cargo, 0, SIZE);
                        memset(colaborador[i].login, 0, SIZE);
                        memset(colaborador[i].senha, 0, SIZE);
                        for(a=0;a<colaborador[i].quantTarefa;a++)
                        {
                            //limpando dados dos vetores
                            memset(colaborador[i].titulo[a], 0, SIZE);
                            memset(colaborador[i].comentario[a], 0, SIZE);
                            memset(colaborador[i].descricao[a], 0, SIZE);
                            memset(colaborador[i].prioridade[a], 0, SIZE);
                            memset(colaborador[i].idTarefa, 0, SIZE);
                            memset(colaborador[i].prazo, 0, SIZE);
                            memset(colaborador[i].idComentario, 0, SIZE);
                            memset(colaborador[i].concluir, false, SIZE);
                            memset(colaborador[i].data[0], 0, SIZE);
                            memset(colaborador[i].data[1], 0, SIZE);
                            memset(colaborador[i].data[2], 0, SIZE);
                            memset(colaborador[i].hora[0], 0, SIZE);
                            memset(colaborador[i].hora[1], 0, SIZE);
                            memset(colaborador[i].hora[2], 0, SIZE);
                            memset(colaborador[i].dataConclusao[0], 0, SIZE);
                            memset(colaborador[i].dataConclusao[1], 0, SIZE);
                            memset(colaborador[i].dataConclusao[2], 0, SIZE);
                        }
                        colaborador[i].id=0;
                        colaborador[i].tarefasConcluida=0;
                        colaborador[i].tarefasPendente=0;
                        colaborador[i].quantTarefa=0;
                        a=0;

                        do{
                            strcpy(colaborador[i].nome,colaborador[i+1].nome);
                            strcpy(colaborador[i].email,colaborador[i+1].email);
                            strcpy(colaborador[i].cargo,colaborador[i+1].cargo);
                            strcpy(colaborador[i].login,colaborador[i+1].login);
                            strcpy(colaborador[i].senha,colaborador[i+1].senha);
                            colaborador[i].quantTarefa=colaborador[i+1].quantTarefa;
                            for(a=0;a<colaborador[i].quantTarefa;a++)
                            {
                                //copia dados dos vetores do proximo indice no atual, realocando todos os dados
                                strcpy(colaborador[i].titulo[a],colaborador[i+1].titulo[a]);
                                strcpy(colaborador[i].comentario[a],colaborador[i+1].comentario[a]);
                                strcpy(colaborador[i].descricao[a],colaborador[i+1].descricao[a]);
                                strcpy(colaborador[i].prioridade[a],colaborador[i+1].prioridade[a]);
                                colaborador[i].concluir[a]=colaborador[i+1].concluir[a];
                                strcpy(colaborador[i].idTarefa,colaborador[i+1].idTarefa);
                                strcpy(colaborador[i].prazo,colaborador[i+1].prazo);
                                strcpy(colaborador[i].idComentario,colaborador[i+1].idComentario);
                                strcpy(colaborador[i].data[0],colaborador[i+1].data[0]);
                                strcpy(colaborador[i].data[1],colaborador[i+1].data[1]);
                                strcpy(colaborador[i].data[2],colaborador[i+1].data[2]);
                                strcpy(colaborador[i].hora[0],colaborador[i+1].hora[0]);
                                strcpy(colaborador[i].hora[1],colaborador[i+1].hora[1]);
                                strcpy(colaborador[i].hora[2],colaborador[i+1].hora[2]);
                                strcpy(colaborador[i].dataConclusao[0],colaborador[i+1].dataConclusao[0]);
                                strcpy(colaborador[i].dataConclusao[1],colaborador[i+1].dataConclusao[1]);
                                strcpy(colaborador[i].dataConclusao[2],colaborador[i+1].dataConclusao[2]);

                            }
                            colaborador[i].id=colaborador[i+1].id;
                            colaborador[i].tarefasConcluida=colaborador[i+1].tarefasConcluida;
                            colaborador[i].tarefasPendente=colaborador[i+1].tarefasPendente;
                            i++;
                            a=0;
                            }while(i<linha2);
                        i=0;
                        linha2--;
                        system("cls");
                        textcolor(10);
                        printf("\n\n\t\t\t\t\t\a   CADASTRO EXCLUÍDO COM SUCESSO!");
                        textcolor(15);
                        printf("\n\t\t\t\t   ");
                        system("pause");

                    }
                    else if(x==3)
                    {
                        //limpando dados dos vetores
                        memset(cliente[i].razaoSocial, 0, SIZE);
                        memset(cliente[i].email, 0, SIZE);
                        memset(cliente[i].telefone, 0, SIZE);
                        memset(cliente[i].cnpj, 0, SIZE);
                        memset(cliente[i].endereco, 0, SIZE);
                        memset(cliente[i].descricao, 0, SIZE);
                        do{
                            //copia dados dos vetores do proximo indice no atual
                            strcpy(cliente[i].razaoSocial,cliente[i+1].razaoSocial);
                            strcpy(cliente[i].email,cliente[i+1].email);
                            strcpy(cliente[i].telefone,cliente[i+1].telefone);
                            strcpy(cliente[i].endereco,cliente[i+1].endereco);
                            strcpy(cliente[i].cnpj,cliente[i+1].cnpj);
                            strcpy(cliente[i].descricao,cliente[i+1].descricao);
                            i++;
                        }while(i<linha3);
                        i=0;
                        linha3--;
                        system("cls");
                        textcolor(10);
                        printf("\n\n\t\t\t\t\t\a   CADASTRO EXCLUÍDO COM SUCESSO!");
                        textcolor(15);
                        printf("\n\t\t\t\t   ");
                        system("pause");
                    }
                break;
            default:
                break;
            }

}//fim excluirDados
int contarDias(int dia, int mes, int ano)
{
    //funcao que calcula os dias de acordo com o horario do windows
    int dias;
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    dias = (dia - tm.tm_mday)+30*(mes-(tm.tm_mon + 1))+(365*(ano-(tm.tm_year + 1900)));
    return dias;
}//fim data
int geradorId()
{
    // funcao responsavel por gerar um ID aleatorio
    int idGerado;
    srand( (unsigned)time(NULL) );
    idGerado = rand();// atribui um numero randomico
    return idGerado;
}//fim geradorId
char lerString(char palavra[SIZE])
{
    //funcao responsavel por ler caracteres digitados pelo usuario
    static char letra;
    static int i;

    do{
            letra=getch();
            if(isprint(letra))//Esta funcao e usada para verificar se o argumento contem algum caractere imprimivel
                {
                    palavra[i]=letra;
                    printf("%s",&letra);
                    i++;
                }
                else if(letra==8&&i) // apaga caractere, 8 = BackSpace na tabela ACSII
                {
                   palavra[i]='\0';
                   i--;
                   printf("\b \b");
                }
        }while(letra!=13); // 13 = ENTER na tabela ASCII, interromper o while quando o usuario digitar ENTER
        palavra[i]='\0';
        i=0;
        return palavra;
}//fim leString
void tarefa(int indetificador, bool mostrarTarConcluida)
{
    struct tm *hora_atual;
    time_t segundos,data_atual;
    data_atual = time(NULL);
    struct tm tm = *localtime(&data_atual);
    static int i,a,cont,cont2,idInt,verificar;
    char x;
    char acesso_id[SIZE],recebeData[SIZE],concluir[SIZE];
    if(indetificador==-1)
        {
            do
            {
                system("cls");
                textcolor(10);
                printf("\t\t\t\t\t\t-ATRIBUIR TAREFAS(S)-\n");
                textcolor(15);
                printf("\t\t\t  <<Após preencher o ID, pressione <ENTER> para encontrar um colaborador>>\n");
                printf("\n\t------------------------------------------------------------------------------------------------------");
                printf("\n\tID: ");
                lerString(acesso_id);
                idInt=atoi(acesso_id);
                if(linha2>0)
                {
                    for(i=0;i<linha2;i++)
                    {
                        if(colaborador[i].id==idInt)
                        {
                            system("cls");
                            textcolor(10);
                            printf("\t\t\t\t\t\t-ATRIBUIR TAREFAS(S)-\n");
                            textcolor(15);
                            printf("\t\t<<Após preencher o campo, pressione <ENTER> para seguir para o próximo campo>>\n");
                            mostrarDadosTarefas(i);
                            textcolor(14);
                            printf("\n\n\tAtribuindo Tarefa(s)");
                            textcolor(15);
                            printf("\n\t------------------------------------------------------------------------------------------------------");
                            printf("\n\tTitulo da tarefa: ");
                            lerString(colaborador[i].titulo[colaborador[i].quantTarefa]);
                            printf("\n\t------------------------------------------------------------------------------------------------------");
                            printf("\n\tDescriçao da tarefa: ");
                            lerString(colaborador[i].descricao[colaborador[i].quantTarefa]);
                            printf("\n\t------------------------------------------------------------------------------------------------------");
                            do{
                                textcolor(14);
                                printf("\n\n\tDefina o nível de prioridade desta tarefa");
                                textcolor(15);
                                printf("\n\t------------------------------------------------------------------------------------------------------");
                                textcolor(9);
                                printf("\n\t<1> ALTA Prioridade");
                                textcolor(15);
                                printf("\n\tTarefas de nível <1> o colaborador deverá finalizar a tarefa em curto prazo");
                                textcolor(2);
                                printf("\n\t<2> MEDIA Prioridade");
                                textcolor(15);
                                printf("\n\tTarefas de nível <2> o colaborador deverá finalizar a tarefa em médio prazo");
                                textcolor(6);
                                printf("\n\t<3> BAIXA Prioridade");
                                textcolor(15);
                                printf("\n\tTarefas de nível <3> o colaborador poderá finalizar a tarefa em longo prazo");
                                printf("\n\t------------------------------------------------------------------------------------------------------");
                                printf("\n\n\t\t\t\t        Digite a escolha correspondente:");
                                printf("\n\t------------------------------------------------------------------------------------------------------");
                                printf("\n\tNível de prioridade: ");
                                lerString(colaborador[i].prioridade[colaborador[i].quantTarefa]);
                                verificar=atoi(colaborador[i].prioridade[colaborador[i].quantTarefa]);
                                if((verificar==1)||(verificar==2)||(verificar==3))
                                {
                                    verificar=0;
                                    cont2=0;
                                }
                                else
                                {
                                    textcolor(12);
                                    printf("\n\n\t\t\t\t\t\t\aESCOLHA INVÁLIDA!\n");
                                    textcolor(15);
                                    cont2++;
                                }
                                if(cont2>=3)
                                {
                                    printf("\n\t------------------------------------------------------------------------------------------------------");
                                    textcolor(12);
                                    printf("\n\n\t\t\t\aMUITAS TENTATIVAS INVÁLIDAS, TENTE NOVAMENTE MAIS TARDE...\n");
                                    textcolor(15);
                                    break;
                                }
                            }while(cont2!=0);
                            //prazo
                            if(cont2==0)
                            {
                                do{
                                    textcolor(14);
                                    printf("\n\n\tData de entrega");
                                    textcolor(15);
                                    printf("\n\t------------------------------------------------------------------------------------------------------");
                                    printf("\n\t<Digite o <Dia> e pressione <ENTER> para continuar>\n\t<Digite o <Mês> e pressione <ENTER> para continuar>\n\t<Digite o <Ano> e pressione <ENTER> para definir Data>");
                                    textcolor(3);
                                    printf("\n\t<Exemplo de formato de data: Dia/Mês/Ano-01/04/1992>");
                                    textcolor(15);
                                    printf("\n\n\tData: ");
                                    lerString(recebeData);
                                    colaborador[i].data[0][colaborador[i].quantTarefa] = atoi(recebeData);
                                    printf("/");
                                    lerString(recebeData);
                                    colaborador[i].data[1][colaborador[i].quantTarefa] = atoi(recebeData);
                                    printf("/");
                                    lerString(recebeData);
                                    colaborador[i].data[2][colaborador[i].quantTarefa] = atoi(recebeData);
                                    textcolor(2);
                                    if((colaborador[i].data[0][colaborador[i].quantTarefa]<1)||
                                   (colaborador[i].data[0][colaborador[i].quantTarefa]>31)||
                                    (colaborador[i].data[1][colaborador[i].quantTarefa]<1)||
                                   (colaborador[i].data[1][colaborador[i].quantTarefa]>12)||
                                    (colaborador[i].data[2][colaborador[i].quantTarefa]<2022))
                                    {
                                        textcolor(12);
                                        printf("\n\n\t\t\t\t\t\t\aFORMATO DE DATA INVÁLIDO!\n");
                                        textcolor(15);
                                        cont2++;
                                    }
                                    else
                                    {
                                        colaborador[i].prazo[colaborador[i].quantTarefa]=contarDias(colaborador[i].data[0][colaborador[i].quantTarefa],
                                        colaborador[i].data[1][colaborador[i].quantTarefa],colaborador[i].data[2][colaborador[i].quantTarefa]);
                                        textcolor(10);
                                        if(colaborador[i].prazo[colaborador[i].quantTarefa]<0)
                                        {
                                            textcolor(12);
                                            printf("\n\n\t\t\t\t\t\t\aPRAZO INDEFINIDO!\n");
                                            textcolor(15);
                                            cont2++;
                                        }
                                        else
                                        {

                                            textcolor(15);
                                            printf("\n\t------------------------------------------------------------------------------------------------------");
                                            textcolor(10);
                                            printf("\n\n\t\t\t\t\t\a<TAREFA ATRIBUIDA COM SUCESSO!>");
                                            printf("\n\t\t   Data de entrega definda: %d/%d/%d, aproximadamente %d dias corridos\n",
                                            colaborador[i].data[0][colaborador[i].quantTarefa],colaborador[i].data[1][colaborador[i].quantTarefa],
                                            colaborador[i].data[2][colaborador[i].quantTarefa],colaborador[i].prazo[colaborador[i].quantTarefa]);
                                            textcolor(15);
                                            colaborador[i].idTarefa[colaborador[i].quantTarefa]=colaborador[i].quantTarefa;
                                            colaborador[i].quantTarefa++;
                                            colaborador[i].tarefasPendente++;
                                            cont2=0;
                                        }
                                    }
                                    if(cont2>=3)
                                    {
                                        printf("\n\t------------------------------------------------------------------------------------------------------");
                                        textcolor(12);
                                        printf("\n\n\t\t\t\a  MUITAS TENTATIVAS INVÁLIDAS, TENTE NOVAMENTE MAIS TARDE...\n");
                                        textcolor(15);
                                        break;
                                    }
                                }while(cont2!=0);
                            }
                            cont2=0;
                            cont=0;
                            i=0;
                            idInt=0;
                            break;
                        }else{cont=1;}
                }//fim for
            }else{cont=1;}
            if(cont==1)
            {
                printf("\n\t------------------------------------------------------------------------------------------------------");
                textcolor(12);
                printf("\n\n\t\t\t\t\t\a    CADASTRO NÃO ENCONTRADO!\n");
                textcolor(15);
                printf("\n\n\t\t\t\a    <<Consulte a lista de cadastro no menu principal>>\n");
                for(i=0;i<SIZE;i++)
                {
                    acesso_id[i]='\0';
                }
                i=0;
                cont=0;
                idInt=0;
            }
            printf("\n\n\t\t<<Pressione 1 para continuar ou pressione qualquer outra tecla para voltar>>\n\n");
            x=getch();
        }while(x=='1');
    }
    else if((indetificador<=SIZE)&&(mostrarTarConcluida==false))
    {
        do{
            idInt=colaborador[indetificador].id;
            for(i=0;i<linha2;i++)
            {
                if(colaborador[i].tarefasPendente>0)
                    {
                        if(colaborador[i].id==idInt)
                        {
                            system("cls");
                            textcolor(10);
                            printf("\t\t\t\t\t\t   -TAREFAS(S)-\n");
                            mostrarDadosTarefas(i);
                            for(a=0;a<colaborador[i].quantTarefa;a++)
                            {
                                if (colaborador[i].concluir[a]==false)
                                {
                                    textcolor(3);
                                    printf("\n\tTAREFA ID:%d",colaborador[i].idTarefa[a]+1);
                                    textcolor(15);
                                    verificar=atoi(colaborador[i].prioridade[a]);
                                    if(verificar==1)
                                    {
                                        textcolor(9);
                                        printf("\n\tNível de prioridade: <ALTA>");
                                    }
                                    else if(verificar==2)
                                        {
                                            textcolor(2);
                                            printf("\n\tNível de prioridade: <MEDIA>");
                                        }
                                        else if(verificar==3)
                                        {
                                            textcolor(6);
                                            printf("\n\tNível de prioridade: <BAIXA>");
                                        }
                                    textcolor(15);
                                    printf("\n\tTítulo da tarefa: %s",colaborador[i].titulo[a]);
                                    printf("\n\tDescrição da tarefa: %s",colaborador[i].descricao[a]);
                                    textcolor(10);
                                    printf("\n\tData de entrega: %d/%d/%d, aproximadamente %d dias corridos\n",
                                    colaborador[i].data[0][a],colaborador[i].data[1][a],
                                    colaborador[i].data[2][a],colaborador[i].prazo[a]);
                                    if(colaborador[i].idComentario[a]>0)
                                    {
                                        textcolor(14);
                                        printf("\n\n\tComentário:");
                                        textcolor(15);
                                        printf("\n\t------------------------------------------------------------------------------------------------------");
                                        printf("\n\tComentário do gerente: <%s>\n",colaborador[i].comentario[a]);
                                    }
                                    textcolor(9);
                                    printf("\n\t------------------------------------------------------------------------------------------------------");
                                }//fim if
                            }//fim for
                            verificar=0;
                            a=0;
                            idInt=0;
                            textcolor(15);
                            printf("\n\t\t\t\t   ");
                            system("pause");
                            printf("\n\t\t\t\t\t  .--------------");
                            textcolor(10);
                            printf("MENU");
                            textcolor(15);
                            printf("-------------.");
                            printf("\n\t\t\t\t\t  .-------------------------------.");
                            printf("\n\t\t\t\t\t  |     <");
                            textcolor(10);
                            printf("1");
                            textcolor(15);
                            printf(">");
                            printf(" Finalizar tarefa      |");
                            printf("\n\t\t\t\t\t  .-------------------------------.");
                            printf("\n\n\t\t   Pressione <1> para finalizar alguma tarefa ou pressione qualquer outra tecla para voltar:");
                            x=getch();
                            switch(x)
                            {
                                case '1':
                                    printf("\n\t------------------------------------------------------------------------------------------------------");
                                    printf("\n\tDigite o ID da tarefa: ");
                                    lerString(concluir);
                                    verificar=atoi(concluir);
                                    verificar--;
                                    if((verificar>=0) && (verificar<=colaborador[i].tarefasPendente))
                                    {
                                        for(a=0;a<colaborador[i].quantTarefa;a++)
                                        {
                                            if(verificar==colaborador[i].idTarefa[a]&&colaborador[i].concluir[a]==false)
                                            {
                                                colaborador[i].concluir[a]=true;
                                                //registra o horario de conclusao da tarefa
                                                time(&segundos);
                                                hora_atual = localtime(&segundos);
                                                colaborador[i].hora[0][a]=hora_atual->tm_hour;
                                                colaborador[i].hora[1][a]=hora_atual->tm_min;
                                                colaborador[i].hora[2][a]=hora_atual->tm_sec;
                                                //registra a data de conclusao da tarefa
                                                colaborador[i].dataConclusao[0][a]=tm.tm_mday;
                                                colaborador[i].dataConclusao[1][a]=tm.tm_mon+1;
                                                colaborador[i].dataConclusao[2][a]=tm.tm_year + 1900;
                                                printf("\n\t------------------------------------------------------------------------------------------------------");
                                                textcolor(10);
                                                printf("\n\t\t\t\t\t\aTarefa, ID: %d, CONCLUÍDA COM SUCESSO!\n",colaborador[i].idTarefa[a]+1);
                                                textcolor(15);
                                                printf("\n\t\t\t\t     ");
                                                system("pause");;
                                                colaborador[i].tarefasConcluida++;
                                                colaborador[i].tarefasPendente--;
                                                a=0;
                                                verificar=0;
                                                cont=0;
                                                break;
                                            }else{cont=1;}
                                        }
                                    }else{cont=1;}
                                    if(cont==1)
                                    {
                                        a=0;
                                        verificar=0;
                                        cont=0;
                                        printf("\n\t------------------------------------------------------------------------------------------------------");
                                        textcolor(12);
                                        printf("\n\n\t\t\t\t\t\a    TAREFA NÃO ENCONTRADA!\n");
                                        textcolor(15);
                                        printf("\n\t\t\t\t   ");
                                        system("pause");
                                    }
                                    break;
                            }//fim switch
                        }//fim if
                    }//fimse
            }//fim for
            if(colaborador[indetificador].tarefasPendente==0)
                {
                    system("cls");
                    textcolor(12);
                    printf("\n\t\t\t\t\t\t   SEM TAREFA(s) PENDENTE(s)\n");
                    textcolor(15);
                    printf("\n\t\t\t\t\t");
                    system("pause");
                    x='2';
                    i=0;
                    break;
                }
                else
                {
                    i=0;
                    x='2';
                }
        }while(x=='1');
    }//fim else if
    else if(mostrarTarConcluida==true)
    {
            do{
            idInt=colaborador[indetificador].id;
            for(i=0;i<linha2;i++)
            {
                if(colaborador[i].tarefasConcluida>0)
                    {
                        if(colaborador[i].id==idInt)
                        {
                            system("cls");
                            textcolor(10);
                            printf("\t\t\t\t\t\t   -TAREFAS(S) CONCLUÍDAS-\n");
                            mostrarDadosTarefas(i);
                            textcolor(14);
                            printf("\n\n\tTarefa(s)");
                            textcolor(9);
                            printf("\n\t------------------------------------------------------------------------------------------------------");
                            for(a=0;a<colaborador[i].quantTarefa;a++)
                            {
                                if (colaborador[i].concluir[a]==true)
                                {
                                    textcolor(3);
                                    printf("\n\tTAREFA ID:%d",colaborador[i].idTarefa[a]+1);
                                    textcolor(15);
                                    verificar=atoi(colaborador[i].prioridade[a]);
                                    if(verificar==1)
                                    {
                                        textcolor(9);
                                        printf("\n\tNível de prioridade: <ALTA>");
                                    }
                                    else if(verificar==2)
                                        {
                                            textcolor(2);
                                            printf("\n\tNível de prioridade: <MEDIA>");
                                        }
                                        else if(verificar==3)
                                        {
                                            textcolor(6);
                                            printf("\n\tNível de prioridade: <BAIXA>");
                                        }
                                    textcolor(15);
                                    printf("\n\tTítulo da tarefa: %s",colaborador[i].titulo[a]);
                                    printf("\n\tDescrição da tarefa: %s",colaborador[i].descricao[a]);
                                    textcolor(12);
                                    printf("\n\tData limite para entrega: %d/%d/%d\n",
                                    colaborador[i].data[0][a],colaborador[i].data[1][a],
                                    colaborador[i].data[2][a]);
                                    textcolor(10);
                                    printf("\n\tEntregue em: %d/%d/%d ás %d:%d:%d",
                                    colaborador[i].dataConclusao[0][a],colaborador[i].dataConclusao[1][a],
                                    colaborador[i].dataConclusao[2][a],colaborador[i].hora[0][a],
                                    colaborador[i].hora[1][a],colaborador[i].hora[2][a]);
                                    if(colaborador[i].idComentario[a]>0)
                                    {
                                        textcolor(14);
                                        printf("\n\n\tComentário:");
                                        textcolor(15);
                                        printf("\n\t------------------------------------------------------------------------------------------------------");
                                        printf("\n\tComentário do gerente: <%s>\n",colaborador[i].comentario[a]);
                                    }
                                    textcolor(9);
                                    printf("\n\t------------------------------------------------------------------------------------------------------");
                                }//fim if
                            }//fim for
                            textcolor(15);
                            printf("\n\t\t\t\t\t");
                            system("pause");
                            verificar=0;
                            a=0;
                            idInt=0;
                    }//fimse
                }//fim if
            }//fim for
            if(colaborador[indetificador].tarefasConcluida==0)
            {
                system("cls");
                textcolor(12);
                printf("\n\t\t\t\t\t\t  SEM TAREFA(s) CONCLUÍDAS(s)\n");
                textcolor(15);
                printf("\n\t\t\t\t\t");
                system("pause");
                x='2';
                i=0;
            }
            else
            {
                x='2';
                i=0;
            }
        }while(x=='1');

    }// fim else if
}// fim tarefa
void monitorarTarefas()
{
    static int i,a,cont,idInt,verificar; // var contadoras
    char x;
    char acesso_id[SIZE],acessarId[SIZE];// vetores que recebem dados digitados pelo o usuario
    do{
        system("cls");
        textcolor(10);
        printf("\t\t\t\t\t\t-MONITORAR TAREFA(S)-\n");
        textcolor(15);
        if(linha2>0)
            {
                for(i=0;i<linha2;i++)
                {
                    mostrarDadosTarefas(i);
                }
                printf("\n\t\t\t\t\t  .--------------");
                textcolor(10);
                printf("MENU");
                textcolor(15);
                printf("-------------.");
                printf("\n\t\t\t\t\t  .-------------------------------.");
                printf("\n\t\t\t\t\t  |  <");
                textcolor(10);
                printf("1");
                textcolor(15);
                printf(">");
                printf(" Informações sobre tarefa |");
                printf("\n\t\t\t\t\t  .-------------------------------.");
                printf("\n\n\t\t   Pressione <1> para acessar tarefas ou pressione qualquer outra tecla para voltar:");
                x=getch();
                switch(x)
                {
                    case '1':
                        textcolor(10);
                        printf("\n\n\t\t\t\t\t\t -PESQUISAR POR ID-\n");
                        textcolor(15);
                        printf("\t\t\t  <<Após preencher o campo, pressione <ENTER> para pesquisar>>\n");
                        printf("\n\t------------------------------------------------------------------------------------------------------");
                        printf("\n\tID: ");
                        lerString(acesso_id);
                        idInt=atoi(acesso_id);
                        for(i=0;i<linha2;i++)
                        {
                            if(colaborador[i].id==idInt)
                            {
                                do
                                {
                                    system("cls");
                                    textcolor(10);
                                    printf("\t\t\t\t\t\t-MONITORAR TAREFA(S)-\n");
                                    mostrarDadosTarefas(i);
                                    if(colaborador[i].quantTarefa>0)
                                    {
                                        for(a=0;a<colaborador[i].quantTarefa;a++)//repete de acordo com  quantidade de tarefas
                                        {
                                            verificar=atoi(colaborador[i].prioridade[a]);
                                            textcolor(3);
                                            printf("\n\tTAREFA ID:%d",colaborador[i].idTarefa[a]+1);
                                            textcolor(15);
                                            verificar=atoi(colaborador[i].prioridade[a]);
                                            if(verificar==1){printf("\n\tNível de prioridade: <ALTA>");}
                                            else if(verificar==2){printf("\n\tNível de prioridade: <MEDIA>");}
                                            else if(verificar==3){printf("\n\tNível de prioridade: <BAIXA>");}

                                            textcolor(15);
                                            printf("\n\tTítulo da tarefa: %s",colaborador[i].titulo[a]);
                                            printf("\n\tDescrição da tarefa: %s",colaborador[i].descricao[a]);
                                            textcolor(10);
                                            printf("\n\tData de entrega: %d/%d/%d, aproximadamente %d dias corridos\n",
                                            colaborador[i].data[0][a],colaborador[i].data[1][a],
                                            colaborador[i].data[2][a],colaborador[i].prazo[a]);
                                            textcolor(15);
                                            printf("\n\t------------------------------------------------------------------------------------------------------");
                                            if(colaborador[i].concluir[a]==false)
                                            {
                                                printf("\n\tStatus: ");
                                                textcolor(12);
                                                printf("<PENDENTE>");
                                                textcolor(15);
                                                printf("\n\t------------------------------------------------------------------------------------------------------");
                                            }
                                            else if(colaborador[i].concluir[a]==true)
                                            {
                                                printf("\n\tStatus: ");
                                                textcolor(10);
                                                printf("<CONCLUÍDO> em: %d/%d/%d ás %d:%d:%d",
                                                colaborador[i].dataConclusao[0][a],colaborador[i].dataConclusao[1][a],
                                                colaborador[i].dataConclusao[2][a],colaborador[i].hora[0][a],
                                                colaborador[i].hora[1][a],colaborador[i].hora[2][a]);
                                            }
                                            if(colaborador[i].idComentario[a]>0)
                                            {
                                                textcolor(14);
                                                printf("\n\n\tComentário:");
                                                textcolor(15);
                                                printf("\n\t------------------------------------------------------------------------------------------------------");
                                                printf("\n\tComentário do gerente: <%s>\n",colaborador[i].comentario[a]);
                                            }
                                            textcolor(9);
                                            printf("\n\t------------------------------------------------------------------------------------------------------");
                                        }//fim for
                                        textcolor(15);
                                        printf("\n\t\t\t\t\t  .--------------");
                                        textcolor(14);
                                        printf("MENU");
                                        textcolor(15);
                                        printf("-------------.");
                                        printf("\n\t\t\t\t\t  .-------------------------------.");
                                        printf("\n\t\t\t\t\t  | <");
                                        textcolor(14);
                                        printf("1");
                                        textcolor(15);
                                        printf(">");
                                        printf(" Add comentário            |");
                                        printf("\n\t\t\t\t\t  | <");
                                        textcolor(14);
                                        printf("2");
                                        textcolor(15);
                                        printf(">");
                                        printf(" Excluir tarefa            |");
                                        printf("\n\t\t\t\t\t  | <");
                                        textcolor(14);
                                        printf("3");
                                        textcolor(15);
                                        printf(">");
                                        printf(" Voltar                    |");
                                        printf("\n\t\t\t\t\t  .-------------------------------.");
                                        printf("\n\n\t\t\t\t\t   Digite a escolha correspondente:");
                                        x=getch();
                                        switch(x)
                                        {
                                            case '1':
                                                textcolor(10);
                                                printf("\n\n\t\t\t\t\t   -PESQUISAR POR ID DA TAREFA-\n");
                                                textcolor(15);
                                                printf("\t\t\t  <<Após preencher o campo, pressione <ENTER> para pesquisar>>\n");
                                                printf("\n\t------------------------------------------------------------------------------------------------------");
                                                printf("\n\tTAREFA ID: ");
                                                lerString(acessarId);
                                                verificar=atoi(acessarId);// converte o caractere em numero inteiro
                                                verificar--;
                                                if((verificar>=0))
                                                {
                                                    for(a=0;a<colaborador[i].quantTarefa;a++)
                                                    {
                                                        if(verificar==colaborador[i].idTarefa[a])
                                                        {
                                                            printf("\n\tComentário: ");
                                                            lerString(colaborador[i].comentario[colaborador[i].idTarefa[a]]);
                                                            colaborador[i].idComentario[a]=1;
                                                            printf("\n\t------------------------------------------------------------------------------------------------------");
                                                            textcolor(10);
                                                            printf("\n\t\t\t\t\t   \aCOMENTÁRIO FEITO COM SUCESSO!\n");
                                                            textcolor(15);
                                                            printf("\n\t\t\t\t     ");
                                                            system("pause");
                                                            verificar=0;
                                                            a=0;
                                                            cont=0;
                                                            break;
                                                        }
                                                        else{cont=1;}
                                                    }
                                                }
                                                else{cont=1;}
                                                if(cont==1)
                                                {
                                                    a=0;
                                                    verificar=0;
                                                    cont=0;
                                                    printf("\n\t------------------------------------------------------------------------------------------------------");
                                                    textcolor(12);
                                                    printf("\n\n\t\t\t\t\t\t\aTAREFA NÃO ENCONTRADA!\n");
                                                    textcolor(15);
                                                    printf("\n\t\t\t\t   ");
                                                    system("pause");
                                                }
                                                break;
                                            case '2':
                                                printf("\n\t------------------------------------------------------------------------------------------------------");
                                                printf("\n\tDigite o ID da tarefa:");
                                                lerString(acessarId);
                                                verificar=atoi(acessarId);
                                                verificar--;
                                                textcolor(12);
                                                printf("\n\n\t\t\t   <<ATENÇÃO ESTA TAREFA SERÁ EXCLUÍDA PERMANENTEMENTE DO SISTEMA>>\n\t\t   <<Pressione <1> para confirmar ou pressione qualquer outra tecla para voltar>>");
                                                textcolor(15);
                                                x=getch();

                                                if((verificar>=0)&&(x=='1'))
                                                {
                                                    for(a=0;a<colaborador[i].quantTarefa;a++)
                                                    {
                                                        if(verificar==colaborador[i].idTarefa[a])
                                                        {
                                                            if(colaborador[i].concluir[a]==true){colaborador[i].tarefasConcluida--;}
                                                            if(colaborador[i].concluir[a]==false){colaborador[i].tarefasPendente--;}
                                                            do{
                                                                //copia os dados da tarefa posterior e atribui a tarefa atual
                                                                strcpy(colaborador[i].titulo[a],colaborador[i].titulo[a+1]);
                                                                strcpy(colaborador[i].comentario[a],colaborador[i].comentario[a+1]);
                                                                strcpy(colaborador[i].descricao[a],colaborador[i].descricao[a+1]);
                                                                strcpy(colaborador[i].prioridade[a],colaborador[i].prioridade[a+1]);
                                                                colaborador[i].concluir[a]=colaborador[i].concluir[a+1];
                                                                colaborador[i].idTarefa[a]=colaborador[i].idTarefa[a+1];
                                                                colaborador[i].prazo[a]=colaborador[i].prazo[a+1];
                                                                colaborador[i].idComentario[a]=colaborador[i].idComentario[a+1];
                                                                colaborador[i].data[0][a]=colaborador[i].data[0][a+1];
                                                                colaborador[i].data[1][a]=colaborador[i].data[1][a+1];
                                                                colaborador[i].data[2][a]=colaborador[i].data[2][a+1];
                                                                colaborador[i].hora[0][a]=colaborador[i].hora[0][a+1];
                                                                colaborador[i].hora[1][a]=colaborador[i].hora[1][a+1];
                                                                colaborador[i].hora[2][a]=colaborador[i].hora[2][a+1];
                                                                colaborador[i].dataConclusao[0][a]=colaborador[i].dataConclusao[0][a+1];
                                                                colaborador[i].dataConclusao[1][a]=colaborador[i].dataConclusao[1][a+1];
                                                                colaborador[i].dataConclusao[2][a]=colaborador[i].dataConclusao[2][a+1];
                                                                a++;

                                                            }while(a<colaborador[i].quantTarefa);
                                                            colaborador[i].quantTarefa--;
                                                            printf("\n\t------------------------------------------------------------------------------------------------------");
                                                            textcolor(10);
                                                            printf("\n\n\t\t\t\t\t    \aTAREFA EXCLUÍDA COM SUCESSO!\n");
                                                            textcolor(15);
                                                            printf("\n\t\t\t\t     ");
                                                            system("pause");
                                                            break;
                                                        }else{cont=1;}

                                                    }
                                                    if(cont==1)
                                                    {
                                                        a=0;
                                                        verificar=0;
                                                        printf("\n\t------------------------------------------------------------------------------------------------------");
                                                        textcolor(12);
                                                        printf("\n\n\t\t\t\t\t\t\aTAREFA NÃO ENCONTRADA!\n");
                                                        textcolor(15);
                                                        printf("\n\t\t\t\t   ");
                                                        system("pause");
                                                    }

                                                }
                                                else
                                                {
                                                    printf("\n\t------------------------------------------------------------------------------------------------------");
                                                    textcolor(12);
                                                    printf("\n\n\t\t\t\t\t\t\aTAREFA NÃO EXCLUÍDA!\n");
                                                    textcolor(15);
                                                    printf("\n\t\t\t\t   ");
                                                    system("pause");
                                                }
                                                a=0;
                                                verificar=0;
                                                break;
                                            case '3':
                                                i=0;
                                                x='7';
                                                break;
                                            }
                                    }
                                    else
                                    {
                                        textcolor(10);
                                        printf("\n\t\t\t\t         %s, NAO POSSUI TAREFAS ATRIBUÍDAS\n",colaborador[i].nome);
                                        textcolor(15);
                                        printf("\n\t\t\t\t       ");
                                        system("pause");
                                        x='7';
                                    }
                                }while(x!='7');
                                break;
                            }//fim if idint
                        }//fim for linha2
                        if(colaborador[i].id!=idInt)
                        {
                            idInt=0;
                            i=0;
                            printf("\n\t------------------------------------------------------------------------------------------------------");
                            textcolor(12);
                            printf("\n\n\t\t\t\t\t\t\aTAREFA NÃO ENCONTRADA!\n");
                            textcolor(15);
                            printf("\n\t\t\t\t   ");
                            system("pause");
                        }
                        break;
                    default:
                        i=0;
                        x='7';
                        break;
                }//fim switch
        }
        else
        {
            textcolor(12);
            printf("\n\t\t\t\t\t\t      SEM DADOS\n");
            textcolor(15);
            printf("\n\t\t\t\t     ");
            system("pause");
            x='7';// forca o laco interromper
        }
    }while(x!='7');

}// fim monitorarTarefas
int perfilMaster()
{
       do
        {
            system("cls");
            textcolor(15);
            printf(" PERFIL LOGADO: ");
            textcolor(6);
            printf("<<MASTER>>");
            textcolor(15);
            printf("\n\n\n");
            printf("\n\t\t\t\t\t.--------------");
            textcolor(12);
            printf("MENU");
            textcolor(15);
            printf("-------------.");
            printf("\n\t\t\t\t\t.-------------------------------.");
            printf("\n\t\t\t\t\t| <");
            textcolor(12);
            printf("1");
            textcolor(15);
            printf(">");
            printf(" Cadastrar Gerente         |");
            printf("\n\t\t\t\t\t| <");
            textcolor(12);
            printf("2");
            textcolor(15);
            printf(">");
            printf(" Lista de Cadastro         |");
            printf("\n\t\t\t\t\t| <");
            textcolor(12);
            printf("3");
            textcolor(15);
            printf(">");
            printf(" Pesquisar                 |");
            printf("\n\t\t\t\t\t| <");
            textcolor(12);
            printf("4");
            textcolor(15);
            printf(">");
            printf(" Login                     |");
            printf("\n\t\t\t\t\t| <");
            textcolor(12);
            printf("5");
            textcolor(15);
            printf(">");
            printf(" Sair                      |");
            printf("\n\t\t\t\t\t.-------------------------------.");
            printf("\n\n\t\t\t\t         Digite a escolha correspondente:");
            caractere=getch();
            switch(caractere)
            {
                case '1':
                    cadastro(1);// 1 para ativar cadastro gerente ou 2 para ativar cadastro colaborador
                    break;
                case '2':
                    listaDados(1);
                    break;
                case '3':
                    pesquisa(1);
                    break;
                case '4':
                    system("cls"); // retorna 1 para voltar
                    return 1;
                    break;
                case '5':
                    return 4;// retorna 4 para sair
                    break;
                default:
                    textcolor(12);
                    printf("\n\n\t\t\t\t\t\t\aESCOLHA INVÁLIDA!\n");
                    textcolor(15);
                    printf("\n\t\t   Por favor digite um numero entre 1 e 5, pressione <ENTER> para tentar novamente...");
                    getchar();
                    break;
            }
        }while(caractere!='5');

}//fim perfil master
int perfilGerente()
{
    do
    {
        system("cls");
        textcolor(15);
        printf(" PERFIL LOGADO: ");
        textcolor(6);
        printf("<<GERENTE>>");
        textcolor(15);
        printf("\n\n\n");
        printf("\n\t\t\t\t\t.-----------------");
        textcolor(3);
        printf("MENU");
        textcolor(15);
        printf("----------------.");
        printf("\n\t\t\t\t\t.-------------------------------------.");
        printf("\n\t\t\t\t\t| <");
        textcolor(3);
        printf("0");
        textcolor(15);
        printf(">");
        printf(" Cadastrar Colaborador           |");
        printf("\n\t\t\t\t\t| <");
        textcolor(3);
        printf("1");
        textcolor(15);
        printf(">");
        printf(" Lista de Cadastro               |");
        printf("\n\t\t\t\t\t| <");
        textcolor(3);
        printf("2");
        textcolor(15);
        printf(">");
        printf(" Pesquisar                       |");
        printf("\n\t\t\t\t\t| <");
        textcolor(3);
        printf("3");
        textcolor(15);
        printf(">");
        printf(" Atribuir Tarefa(s)              |");
        printf("\n\t\t\t\t\t| <");
        textcolor(3);
        printf("4");
        textcolor(15);
        printf(">");
        printf(" Monitorar Tarefa(s)             |");
        printf("\n\t\t\t\t\t| <");
        textcolor(3);
        printf("5");
        textcolor(15);
        printf(">");
        printf(" Cliente                         |");
        printf("\n\t\t\t\t\t| <");
        textcolor(3);
        printf("6");
        textcolor(15);
        printf(">");
        printf(" Exportar Relatório(.txt)        |");
        printf("\n\t\t\t\t\t| <");
        textcolor(3);
        printf("7");
        textcolor(15);
        printf(">");
        printf(" Descriptografar Relatório(.txt) |");
        printf("\n\t\t\t\t\t| <");
        textcolor(3);
        printf("8");
        textcolor(15);
        printf(">");
        printf(" Voltar para tela de login       |");
        printf("\n\t\t\t\t\t| <");
        textcolor(12);
        printf("9");
        textcolor(15);
        printf(">");
        printf(" Sair                            |");
        printf("\n\t\t\t\t\t.-------------------------------------.");
        printf("\n\n\t\t\t\t           Digite a escolha correspondente:");
        caractere=getch();
            switch(caractere)
            {
                case '0':
                    cadastro(2);
                    break;
                case '1':
                    listaDados(2);
                    break;
                case '2':
                    pesquisa(2);
                    break;
                case '3':
                    tarefa(-1,false); //primeiro parametro: <-1> para atribuir tarefa, segundo parametro: false/true para mostrar tarefas concluidas
                    break;
                case '4':
                    monitorarTarefas();
                    break;
                case '5':
                    sistemaCliente();
                    break;
                case '6':
                    exportarDados();
                    break;
                case '7':
                    criptografia(2);
                    break;
                case '8':
                    system("cls");
                    return 1;
                    break;
                case '9':
                    return 4;
                    break;
                default:
                    textcolor(12);
                    printf("\n\n\t\t\t\t\t\t\a   ESCOLHA INVÁLIDA!\n");
                    textcolor(15);
                    printf("\n\t\t  Por favor digite um numero entre 0 e 9, pressione <ENTER> para tentar novamente...");
                    getchar();
                    break;
            }
        }while(caractere!='9');
}//fim perfilGerente
int perfilColaborador()
{
    do
    {
        system("cls");
        textcolor(15);
        printf(" PERFIL LOGADO: ");
        textcolor(6);
        printf("<<%s>>",colaborador[identificarColab].nome);
        textcolor(15);
        printf("\n\n\n");
        printf("\n\t\t\t\t\t.--------------");
        textcolor(10);
        printf("MENU");
        textcolor(15);
        printf("-------------.");
        printf("\n\t\t\t\t\t.-------------------------------.");
        printf("\n\t\t\t\t\t| <");
        textcolor(10);
        printf("1");
        textcolor(15);
        printf(">");
        printf(" Tarefas Pendentes         |");
        printf("\n\t\t\t\t\t| <");
        textcolor(10);
        printf("2");
        textcolor(15);
        printf(">");
        printf(" Tarefas Concluídas        |");
        printf("\n\t\t\t\t\t| <");
        textcolor(10);
        printf("3");
        textcolor(15);
        printf(">");
        printf(" Voltar para tela de login |");
        printf("\n\t\t\t\t\t| <");
        textcolor(10);
        printf("4");
        textcolor(15);
        printf(">");
        printf(" Sair                      |");
        printf("\n\t\t\t\t\t.-------------------------------.");
        printf("\n\n\t\t\t\t        Digite a escolha correspondente:");
        caractere=getch();
        switch(caractere)
        {
            case '1':
                tarefa(identificarColab,false);//false para tarefas pendentes
                break;
            case '2':
                tarefa(identificarColab,true);//true para tarefas concluidas
                break;
            case '3':
                system("cls");
                return 1;
                break;
            case '4':
                return 4;
                break;
            default:
                textcolor(12);
                printf("\n\n\t\t\t\t\t\t\aESCOLHA INVÁLIDA!\n");
                textcolor(15);
                printf("\n\t\t  Por favor digite um numero entre 1 e 4, pressione <ENTER> para tentar novamente...");
                getchar();
                break;
        }
    }while(caractere!='4');
}//fim perfilColaborador
void sistemaCliente()
{
    static int i,cont;
    char x;
    char acesso_nome[SIZE];
    do
    {
        system("cls");
        textcolor(15);
        printf(" PERFIL LOGADO: ");
        textcolor(6);
        printf("<<GERENTE>> <<CLIENTE>>");
        textcolor(15);
        printf("\n\n\n");
        printf("\n\t\t\t\t\t.-----------------");
        textcolor(9);
        printf("MENU");
        textcolor(15);
        printf("----------------.");
        printf("\n\t\t\t\t\t.------------------------------------.");
        printf("\n\t\t\t\t\t| <");
        textcolor(9);
        printf("1");
        textcolor(15);
        printf(">");
        printf(" Cadastrar cliente               |");
        printf("\n\t\t\t\t\t| <");
        textcolor(9);
        printf("2");
        textcolor(15);
        printf(">");
        printf(" Pesquisar                       |");
        printf("\n\t\t\t\t\t| <");
        textcolor(9);
        printf("3");
        textcolor(15);
        printf(">");
        printf(" Lista de clientes cadastrado(s) |");
        printf("\n\t\t\t\t\t| <");
        textcolor(9);
        printf("4");
        textcolor(15);
        printf(">");
        printf(" Voltar                          |");
        printf("\n\t\t\t\t\t.-------------------------------------.");
        printf("\n\n\t\t\t\t          Digite a escolha correspondente:");
        caractere=getch();
        switch(caractere)
        {
            case '1':
                cadastro(3); // 3 para chamar cadastro do cliente
                break;
            case '2':
                do
                {
                    system("cls");
                    textcolor(10);
                    printf("\t\t\t\t\t\t  -PESQUISAR CADASTRO-\n");
                    textcolor(15);
                    printf("\n\n\t\t\t\t\t      .-------");
                    textcolor(14);
                    printf("MENU");
                    textcolor(15);
                    printf("-------.");
                    printf("\n\t\t\t\t\t      .-------------------.");
                    printf("\n\t\t\t\t\t      | <");
                    textcolor(14);
                    printf("1");
                    textcolor(15);
                    printf(">");
                    printf(" Pesquisar     |");
                    printf("\n\t\t\t\t\t      | <");
                    textcolor(14);
                    printf("2");
                    textcolor(15);
                    printf(">");
                    printf(" Voltar        |");
                    printf("\n\t\t\t\t\t      .-------------------.");
                    printf("\n\n\t\t\t\t\tDigite a escolha correspondente:");
                    x=getch();
                    switch(x)
                    {
                        case '1':
                            system("cls");
                            textcolor(10);
                            printf("\t\t\t\t\t\t-PESQUISAR RAZÃO SOCIAL-\n");
                            textcolor(15);
                            printf("\t\t\t  <<Após preencher o campo, pressione <ENTER> para pesquisar>>\n");
                            printf("\n\t------------------------------------------------------------------------------------------------------");
                            printf("\n\tRazão social: ");
                            lerString(acesso_nome);
                            if(linha3>0)
                            {
                                for(i=0;i<linha3;i++)
                                {
                                    if(!strcmp(cliente[i].razaoSocial,acesso_nome))
                                    {
                                        msgcadastro();
                                        mostrarDados(i,3);
                                        excluirDados(i,3);
                                        cont=0;
                                        i=0;
                                        break;
                                    }else{cont=1;}
                                }
                            }else{cont=1;}
                            break;
                        case '2':
                            cont=0;
                            break;
                        default:
                            cont=0;
                            textcolor(12);
                            printf("\n\n\t\t\t\t\t\t\a      ESCOLHA INVÁLIDA!\n");
                            textcolor(15);
                            printf("\n\t\t     Por favor digite um numero entre 1 e 2, pressione <ENTER> para tentar novamente...");
                            getchar();
                            break;
                        }//fim switch
                    if(cont==1)
                    {
                        printf("\n\t------------------------------------------------------------------------------------------------------");
                        textcolor(12);
                        printf("\n\n\t\t\t\t\t\a    CADASTRO NÃO ENCONTRADO!\n");
                        textcolor(15);
                        printf("\n\n\t\t\t    \a<<Consulte a lista de cadastro no menu principal>>\n");
                        for(i=0;i<SIZE;i++){acesso_nome[i]='\0';}
                        i=0;
                        cont=0;
                        printf("\n\t\t\t\t ");
                        system("pause");
                    }
                }while(x!='2');
                break;
            case '3':
                listaDados(3);
                break;
            case '4':
                system("cls");
                return 1;
                break;
            default:
                textcolor(12);
                printf("\n\n\t\t\t\t\t\t\a  ESCOLHA INVÁLIDA!\n");
                textcolor(15);
                printf("\n\t\t    Por favor digite um numero entre 1 e 4, pressione <ENTER> para tentar novamente...");
                getchar();
                break;
        }
    }while(caractere!='4');
}//fim cliente
void cadastro(int y)
{
    static char x;//recebe a escolha do usuario
    static int i;// var contadora

    do
    {
        system("cls");
        textcolor(10);
        printf("\t\t\t\t\t\t-FORMULÁRIO DE CADASTRO-\n");
        textcolor(15);
        printf("\t\t\t<<Após preencher um campo, pressione <ENTER> para seguir para o próximo>>\n");
        //se y for diferente de 3 y==1 recebe nome do gerente, y==2 recebe nome do colaborador, se nao recebe razao social
        printf("\n\t------------------------------------------------------------------------------------------------------");
        if(y!=3)
        {
            printf("\n\tNome completo: ");
            if(y==1){lerString(gerente[linha].nome);}else
            if(y==2){lerString(colaborador[linha2].nome);}
        }
        else
        {
            printf("\n\tRazão social: ");
            lerString(cliente[linha3].razaoSocial);
        }
        //y==2 recebe cargo do colaborador, y==3 recebe CNPJ do cliente
        if(y==2)
        {
            printf("\n\t------------------------------------------------------------------------------------------------------");
            printf("\n\tCargo: ");
            lerString(colaborador[linha2].cargo);
        }
        else if(y==3)
        {
            printf("\n\t------------------------------------------------------------------------------------------------------");
            printf("\n\tCNPJ: ");
            lerString(cliente[linha3].cnpj);
        }
        //y==1 recebe email do gerente, y==2 recebe email do colaborador, y==3 recebe email do cliente
        printf("\n\t------------------------------------------------------------------------------------------------------");
        printf("\n\tEmail: ");
        if(y==1){lerString(gerente[linha].email);}else
        if(y==2){lerString(colaborador[linha2].email);}else
        if(y==3){lerString(cliente[linha3].email);}
        //y==1 recebe ramal do gerente, y==3 recebe telefone do cliente
        if(y==1)
        {
            printf("\n\t------------------------------------------------------------------------------------------------------");
            printf("\n\tRamal: ");
            lerString(gerente[linha].ramal);
        }
        else if(y==3)
        {
            printf("\n\t------------------------------------------------------------------------------------------------------");
            printf("\n\tTelefone: ");
            lerString(cliente[linha3].telefone);
        }
        //y== 1 gerente, y==2 colaborador, Gera um ID usando a funcao geradorId,
        if(y==1){gerente[linha].id = geradorId();}else
        if(y==2){colaborador[linha2].id = geradorId();}
        //endereco cliente
        if(y==3)
        {
            printf("\n\t------------------------------------------------------------------------------------------------------");
            printf("\n\tEndereço completo: ");
            lerString(cliente[linha3].endereco);
        }
        // Descricao da empresa do cliente
        if(y==3)
        {
            printf("\n\t------------------------------------------------------------------------------------------------------");
            printf("\n\tDescrição: ");
            lerString(cliente[linha3].descricao);
        }
        //Gera um login e senha para o gerente ou para colaborador
        if(y!=3)
        {
            printf("\n\t------------------------------------------------------------------------------------------------------");
            printf("\n\tCadastrar login: ");
            do{
                caractere=getch();
                if(isprint(caractere))//Esta funcao e usada para verificar se o argumento contem algum caractere imprimivel
                {
                    printf("%s",&caractere);
                    if (y==1){gerente[linha].login[i]=caractere;}else
                    if (y==2){colaborador[linha2].login[i]=caractere;}
                    if(caractere==32)// 32 = Space na tabela ASCII, para se o usuario apertar a tecla Space
                    {
                        break;
                    }else
                    {
                      i++;
                    }
                }
                else if(caractere==8&&i) // 8 = BackSpace na tabela ASCII, apaga um caractere
                {
                   if(y==1){gerente[linha].login[i]='\0';}else
                   if(y==2){colaborador[linha2].login[i]='\0';}
                   i--;
                   printf("\b \b");
                }
            }while(caractere!=13);// 13 = ENTER na tabela ASCII, interrompe o while quando digita ENTER e definie \0 como ultimo dado no vetor
            if(y==1){gerente[linha].login[i]='\0';}else
            if(y==2){colaborador[linha2].login[i]='\0';}
            i=0;
        }
        //Senha
        if(y!=3)
        {
            printf("\n\t------------------------------------------------------------------------------------------------------");
            if(caractere!=32)
            {
                printf("\n\tCadastrar senha: ");
                do{
                    caractere=getch();
                    if(isprint(caractere))
                    {
                        printf("%s",&caractere);
                        if (y==1){gerente[linha].senha[i]=caractere;}else
                        if (y==2){colaborador[linha2].senha[i]=caractere;}
                        if(caractere==32)
                        {
                            break;
                        }else{i++;}
                    }
                    else if(caractere==8&&i)
                    {
                        if(y==1){gerente[linha].senha[i]='\0';}else
                        if(y==2){colaborador[linha2].senha[i]='\0';}
                        i--;
                        printf("\b \b");
                    }
                }while(caractere!=13);
            }
            if(y==1){gerente[linha].senha[i]='\0';}else
            if(y==2){colaborador[linha2].senha[i]='\0';}
            i=0;
        }
        if(y==1)
            {
                if((caractere==32)||(gerente[linha].senha[i]=='\0')||(gerente[linha].login[i]=='\0'))
                {
                    printf("\n\t------------------------------------------------------------------------------------------------------");
                    textcolor(12);
                    printf("\n\n\t\t\t\t\a      LOGIN OU SENHA POSSUI CARACTERE INVÁLIDO!\n\t\t\t\t\t     <<Cadastro não realizado>>");
                    textcolor(15);
                }
                else
                {
                    linha++;
                    printf("\n\t------------------------------------------------------------------------------------------------------");
                    textcolor(10);
                    printf("\n\n\t\t\t\t\t\a      CADASTRO REALIZADO COM SUCESSO!\n");
                    textcolor(15);
                }
            }
            else if(y==2)
            {
                if((caractere==32)||(colaborador[linha2].senha[i]=='\0')||(colaborador[linha2].login[i]=='\0'))
                {
                    printf("\n\t------------------------------------------------------------------------------------------------------");
                    textcolor(12);
                    printf("\n\n\t\t\t\t\a      LOGIN OU SENHA POSSUI CARACTERE INVÁLIDO!\n\t\t\t\t\t     <<Cadastro não realizado>>");
                    textcolor(15);
                }
                else
                {
                    linha2++;
                    printf("\n\t------------------------------------------------------------------------------------------------------");
                    textcolor(10);
                    printf("\n\n\t\t\t\t\t\a      CADASTRO REALIZADO COM SUCESSO!\n");
                    textcolor(15);
                }
            }
            else if(y==3)
            {
                if((caractere==32)||(cliente[linha3].razaoSocial[i]=='\0')||
                   (cliente[linha3].email[i]=='\0')||(cliente[linha3].telefone[i]=='\0')||
                   (cliente[linha3].endereco[i]=='\0')||(cliente[linha3].cnpj[i]=='\0'))
                {
                    printf("\n\t------------------------------------------------------------------------------------------------------");
                    textcolor(12);
                    printf("\n\n\t\t\t\t\a      LOGIN OU SENHA POSSUI CARACTERE INVÁLIDO!\n\t\t\t\t\t     <<Cadastro não realizado>>");
                    textcolor(15);
                }
                else
                {
                    linha3++;
                    printf("\n\t------------------------------------------------------------------------------------------------------");
                    textcolor(10);
                    printf("\n\n\t\t\t\t\t\a      CADASTRO REALIZADO COM SUCESSO!\n");
                    textcolor(15);
                }
            }
        printf("\n\n\t\t\t\t\t      Deseja continuar cadastrando?\n\t\t\t<<Pressione <1> para continuar ou qualquer outra tecla para sair>>\n");
        x=getch();
    }while(x == '1');
}// fim cadastro
void pesquisa(int y)
{
    static int i,cont,idInt;//variaveis contadoras
    char x; // responsavel por receber a escolha do menu
    char acesso_nome[SIZE],acesso_id[SIZE];//vetores que armazena nome e id digitados pelo usuario
   do
   {
    system("cls");
    textcolor(10);
    printf("\t\t\t\t\t\t     -PESQUISAR CADASTRO-\n");
    textcolor(15);
    printf("\n\n\t\t\t\t\t      .--------------");
    textcolor(14);
    printf("MENU");
    textcolor(15);
    printf("-------------.");
    printf("\n\t\t\t\t\t      .-------------------------------.");
    printf("\n\t\t\t\t\t      | <");
    textcolor(14);
    printf("1");
    textcolor(15);
    printf(">");
    printf(" Pesquisar por 'NOME'      |");
    printf("\n\t\t\t\t\t      | <");
    textcolor(14);
    printf("2");
    textcolor(15);
    printf(">");
    printf(" Pesquisar por 'ID'        |");
    printf("\n\t\t\t\t\t      | <");
    textcolor(14);
    printf("3");
    textcolor(15);
    printf(">");
    printf(" Voltar                    |");
    printf("\n\t\t\t\t\t      .-------------------------------.");
    printf("\n\n\t\t\t\t\t      Digite a escolha correspondente:");
    x=getch();
     switch(x)
     {
        case '1':
            system("cls");
            textcolor(10);
            printf("\t\t\t\t\t\t-PESQUISA POR NOME-\n");
            textcolor(15);
            printf("\t\t\t  <<Após preencher o campo, pressione <ENTER> para pesquisar>>\n");
            printf("\n\t------------------------------------------------------------------------------------------------------");
            printf("\n\tNome completo: ");
            lerString(acesso_nome);


            if(y==1)
            {
                if(linha>0)
                {
                    for(i=0;i<linha;i++)
                    {
                        if(!strcmp(gerente[i].nome,acesso_nome))
                        {
                            msgcadastro();
                            mostrarDados(i,1);
                            excluirDados(i,1);
                            cont=0;
                            i=0;
                            break;
                        }else{cont=1;}
                    }
                }else{cont=1;}
            }else if(y==2)
                {
                    if(linha2>0)
                    {
                        for(i=0;i<linha2;i++)
                        {
                            if(!strcmp(colaborador[i].nome,acesso_nome))
                            {
                                msgcadastro();
                                mostrarDados(i,2);
                                excluirDados(i,2);
                                cont=0;
                                i=0;
                                break;
                            }
                        else{cont=1;}
                        }
                    }else{cont=1;}
                }
            break;

        case '2':
            system("cls");
            textcolor(10);
            printf("\t\t\t\t\t\t-PESQUISA POR ID-\n");
            textcolor(15);
            printf("\t\t\t  <<Após preencher o campo, pressione <ENTER> para pesquisar>>\n");
            printf("\n\t------------------------------------------------------------------------------------------------------");
            printf("\n\tID: ");
            lerString(acesso_id);
            idInt=atoi(acesso_id);
            if(y==1)
            {
                if(linha>0)
                {
                    for(i=0;i<linha;i++)
                    {
                        if(gerente[i].id==idInt)
                        {
                            msgcadastro();
                            mostrarDados(i,1);
                            excluirDados(i,1);
                            cont=0;
                            i=0;
                            idInt=0;
                            break;
                        }else{cont=1;}
                    }
                }else{cont=1;}
            }else if(y==2)
                {
                    if(linha2>0)
                    {
                        for(i=0;i<linha2;i++)
                        {
                            if(colaborador[i].id==idInt)
                            {
                                msgcadastro();
                                mostrarDados(i,2);
                                excluirDados(i,2);
                                cont=0;
                                i=0;
                                idInt=0;
                                break;
                            }else{cont=1;}
                        }
                    }else{cont=1;}
                }
            break;
        case '3':
            break;
        default:
            cont=0;
            textcolor(12);
            printf("\n\n\t\t\t\t\t\t\a      ESCOLHA INVÁLIDA!\n");
            textcolor(15);
            printf("\n\t\t     Por favor digite um numero entre 1 e 3, pressione <ENTER> para tentar novamente...");
            getchar();
            break;
     }//fim switch
        if(cont==1)
        {
            printf("\n\t------------------------------------------------------------------------------------------------------");
            textcolor(12);
            printf("\n\n\t\t\t\t\t\a    CADASTRO NÃO ENCONTRADO!\n");
            textcolor(15);
            printf("\n\n\t\t\t    \a<<Consulte a lista de cadastro no menu principal>>\n");
            for(i=0;i<SIZE;i++)
            {
                acesso_nome[i]='\0';
                acesso_id[i]='\0';
            }
            i=0;
            cont=0;
            idInt=0;
            printf("\n\t\t\t\t ");
            system("pause");
        }
    }while(x!='3');
}// fim pesquisa
void listaDados(int y)
{
    static int i;

    system("cls");
    textcolor(10);
    printf("\t\t\t\t\t\t-LISTA DE CADASTRO(S)-\n");
    textcolor(15);
    if((linha>0)&&(y==1))//y = 1 identifica gerente
        {
            for(i=0;i<linha;i++)//for que percorre o vetor de acordo com o numero de linhas criado
            {
                mostrarDados(i,1); // parametro 1 mostra dados do gerente
            }
        }
        else if((linha2>0)&&(y==2))//y = 2 identifica colaborador
            {
                for(i=0;i<linha2;i++)
                {
                    mostrarDados(i,2); // parametro 2 mostra dados do colaborador
                }
            }
            else if((linha3>0)&&(y==3))//y = 3 identifica cliente
                {
                    for(i=0;i<linha3;i++)
                    {
                        mostrarDados(i,3);// parametro 3 motra dados do cliente
                    }
                }
                else
                {
                    textcolor(12);
                    printf("\n\t\t\t\t\t\t      <<SEM DADOS>>\n");
                    textcolor(15);
                }

    printf("\n\t\t\t\t     ");
    system("pause");

}//fim lista dados
int loginSenha()
{
    int i=0;
    static int tentativas;
    char acesso_login[SIZE],acesso_senha[SIZE];
    do{
        textcolor(15);
        printf("\n\n\n\n\n\n\t\t>>>Pressione qualquer tecla para continuar ou digite 's' para fechar o programa<<<");
        textcolor(15);
        caractere=getch();
        if(caractere!='s')
        {
            system("cls");
            printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tTentativa:<%d>",tentativas+1);
            printf("\n\t\t\t\t-----------------------------------------------------");
            printf("\n\t\t\t\tEntre com o login: ");
            lerString(acesso_login);
            printf("\n\n\t\t\t\tEntre com a senha: ");
            do{
                caractere=getch();
                if(isprint(caractere))
                {
                    acesso_senha[i]=caractere;
                    i++;
                    printf("*");
                }
                else if(caractere==8&&i)
                    {
                        acesso_senha[i]='\0';
                        i--;
                        printf("\b \b");
                    }
                }while(caractere!=13);
                acesso_senha[i]='\0';
                i=0;
                if(!strcmp(login,acesso_login)&&!strcmp(senha,acesso_senha))
                {
                    tentativas=0;
                    msglogin();
                    return 1;
                }
                if(linha>0)
                {
                    for(i=0;i<linha;i++)
                    {
                        if(!strcmp(gerente[i].login,acesso_login)&&
                        !strcmp(gerente[i].senha,acesso_senha))
                        {
                            tentativas=0;
                            i=0;
                            msglogin();
                            return 2;
                            break;
                        }
                    }
                }
                if(linha2>0)
                {
                    for(i=0;i<linha2;i++)
                    {
                        if(!strcmp(colaborador[i].login,acesso_login)&&
                        !strcmp(colaborador[i].senha,acesso_senha))
                        {
                            identificarColab=i;
                            tentativas=0;
                            i=0;
                            msglogin();
                            return 3;
                            break;
                        }
                    }
                }
                if(tentativas<=3)
                {
                    tentativas++;
                    i=0;
                    textcolor(15);
                    printf("\n\t\t\t\t-----------------------------------------------------");
                    textcolor(12);
                    printf("\n\n\t\t\t\t\t\t\a >>ACESSO NEGADO<<");
                    textcolor(15);
                    printf("\n\t\t\t\t     Após 3 tentativas o programa encerrará.");
                    textcolor(15);
                }
            }else
                {
                    return 4;
                    break;
                }

    }while(tentativas!=3);
    if(tentativas==3)// apos 3 tentativas retorna o valor de 4 que encerra o programa
    {
        system("cls");
        textcolor(15);
        printf("\n\t\t\t\t-----------------------------------------------------");
        textcolor(12);
        printf("\n\t\t\t\tVocê errou <3> vezes consecutivas...");
        printf("\n\t\t\t\tEntre em contato com seu gestor para obter acesso.");
        textcolor(15);
        printf("\n\t\t\t\tPressione qualquer tecla para fechar o programa");
        getchar();
        return 4;
    }
}// fim loginSenha
void msglogin()
{
    //mostrar mensagem
    printf("\n\t\t\t\t-----------------------------------------------------");
    textcolor(10);
    printf("\n\n\t\t\t\t\t\a       >>LOGADO COM SUCESSO<<\n");
    textcolor(15);
    printf("\n\t\t\t\t    Pressione qualquer tecla para continuar...");
    getch();
}//fim msglogin
void msgcadastro()
{
    //mostrar mensagem
    system("cls");
    textcolor(10);
    printf("\t\t\t\t\t\t-CADASTRO ENCONTRADO-\n");
    textcolor(15);
}//fim msglogin
void exportarDados()
{
    FILE *arquivo; // cria variavel ponteiro para o arquivo
    int i,a,x,verificar;

  //abrindo o arquivo com tipo de abertura w
  arquivo = fopen("relatorio.txt", "w");

  //verifica se o arquivo foi realmente criado
    if(arquivo == NULL)
    {
        printf("\n\t\t\t\t\t\t  \aErro na abertura do arquivo!");
        printf("\n\t\t\t\t     ");
        system("pause");
    }
    else
    {
        //gravando dados
        for(x=0;x<linha;x++)
        {
            fputs("\nGERENTE RESPONSÁVEL: \n",arquivo);
            fputs("\nID: ",arquivo);
            fprintf(arquivo,"%d\n",gerente[x].id);
            fputs("\nNome: ",arquivo);
            fprintf(arquivo,"%s\n",gerente[x].nome);
            fputs("\nEmail: ",arquivo);
            fprintf(arquivo,"%s\n",gerente[x].email);
            fputs("\n",arquivo);
            for(i=0;i<linha2;i++)
            {
                fputs("EQUIPE: \n",arquivo);
                fputs("\nID: ",arquivo);
                fprintf(arquivo,"%d\n",colaborador[i].id);
                fputs("\nNome: ",arquivo);
                fprintf(arquivo,"%s\n",colaborador[i].nome);
                fputs("\nCargo: ",arquivo);
                fprintf(arquivo,"%s\n",colaborador[i].cargo);
                fputs("\nEmail: ",arquivo);
                fprintf(arquivo,"%s\n",colaborador[i].email);
                fputs("\nTotal de tarefas atribuídas: ",arquivo);
                fprintf(arquivo,"%d\n",colaborador[i].quantTarefa);
                fputs("\nTotal de tarefas pendente(s): ",arquivo);
                fprintf(arquivo,"%d\n",colaborador[i].tarefasPendente);
                fputs("\nTotal de tarefas concluída(s): ",arquivo);
                fprintf(arquivo,"%d\n",colaborador[i].tarefasConcluida);
                fputs("\nTAREFA(S):\n",arquivo);
                for(a=0;a<colaborador[i].quantTarefa;a++)
                {
                    fputs("\nTarefa Id: ",arquivo);
                    fprintf(arquivo,"%d\n",colaborador[i].idTarefa[a]+1);
                    verificar=atoi(colaborador[i].prioridade[a]);
                    if(verificar==1){fputs("\nNível de prioridade: <ALTA>",arquivo);}
                    else if(verificar==2){fputs("\nNível de prioridade: <MEDIA>",arquivo);}
                    else if(verificar==3){fputs("\nNível de prioridade: <BAIXA>",arquivo);}
                    fputs("\nTitulo da tarefa: ",arquivo);
                    fprintf(arquivo,"%s\n",colaborador[i].titulo[a]);
                    fputs("\nDescrição da tarefa: ",arquivo);
                    fprintf(arquivo,"%s\n",colaborador[i].descricao[a]);
                    fputs("\nData limite para entrega: ",arquivo);
                    fprintf(arquivo,"%d/",colaborador[i].data[0][a]);
                    fprintf(arquivo,"%d/",colaborador[i].data[1][a]);
                    fprintf(arquivo,"%d\n",colaborador[i].data[2][a]);
                    if(colaborador[i].concluir[a]==false)
                    {
                        fputs("\nStatus: <PENDENTE>\n",arquivo);
                    }
                    else if(colaborador[i].concluir[a]==true)
                    {
                        fputs("\nStatus: <CONCLUÍDO> em: ",arquivo);
                        fprintf(arquivo,"%d/",colaborador[i].dataConclusao[0][a]);
                        fprintf(arquivo,"%d/",colaborador[i].dataConclusao[1][a]);
                        fprintf(arquivo,"%d ás ",colaborador[i].dataConclusao[2][a]);
                        fprintf(arquivo,"%dh",colaborador[i].hora[0][a]);
                        fprintf(arquivo,"%dmin",colaborador[i].hora[1][a]);
                        fprintf(arquivo,"%ds\n",colaborador[i].hora[2][a]);
                    }
                    if(colaborador[i].idComentario[a]>0)
                    {
                        fputs("\nComentário do Gerente: ",arquivo);
                        fprintf(arquivo,"%s\n",colaborador[i].comentario[a]);
                    }
                }
            fputs("_____________________________________________________________________________________\n",arquivo);
            }
        }
        //fclose para fechar o arquivo
        fclose(arquivo);
        criptografia(1);
        textcolor(10);
        printf("\n\t\t\t\t\t\aRELATÓRIO EXPORTADO COM SUCESSO!\n");
        textcolor(15);
        printf("\n\t\t\t\t     ");
        system("pause");
    }
}//fim exportar dados
void sistemaPersonalizar()
{
    //cor do sistema
    system("color 0f");
    textcolor(15);
    //muda a linguagem para portuges, permite utilizar acentos
    setlocale (LC_ALL, "Portuguese");
    //emite som de bepp
    Beep(500,400);
    //logo SGCOE
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tVersao: ");
    textcolor(14);
    printf("SGCOEv0.1");
    textcolor(15);
    printf("\n\t\t\t\t    ._____________________________________________.\n");
     printf("\t\t\t\t    |@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|\n");
     printf("\t\t\t\t    |@@    @@@@@      @@@@     @@@@     @@@@    @@|\n");
     printf("\t\t\t\t    |@@ @@@@@@@@ @@@@@@@@@ @@@@@@@@ @@@ @@@@ @@@@@|\n");
     printf("\t\t\t\t    |@@    @@@@@ @@   @@@@ @@@@@@@@ @@@ @@@@   @@@|\n");
     printf("\t\t\t\t    |@@@@@ @@@@@ @@@  @@@@ @@@@@@@@ @@@ @@@@ @@@@@|\n");
     printf("\t\t\t\t    |@@    @@@@@      @@@@     @@@@     @@@@    @@|\n");
     printf("\t\t\t\t    |@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|\n");
     printf("\t\t\t\t    .____");
     textcolor(12);
     printf("SISTEMA DE GESTÃO CHOVEU? ONDE ENCHEU?");
     textcolor(15);
     printf("___.\n");
}// fim sistemaPersonalizar
void iniciarSistema()
{
    //funcao que inicia logo e linguagem em portugues
    sistemaPersonalizar();
    //Login
    do
    {
        //chama a funcao loginSenha que retorna um valor inteiro entre 1 e 4
        op = loginSenha();
        switch(op)
            {
                case 1:
                   op = perfilMaster();
                    break;
                case 2:
                    op = perfilGerente();
                    break;
                case 3:
                    op = perfilColaborador();
                    break;
                default:
                    system("exit");
                    break;
            }
    }while(op!=4);
}// fim iniciar sistema
int main(void)
{
    //funcao que inicia o programa
    iniciarSistema();
}//fim main
