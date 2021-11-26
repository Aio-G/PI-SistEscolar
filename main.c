#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define QALUN 20 // Limite 99 || Quantidade Maxima de Alunos
#define QCURS 15 // Limite 99 || Quantidade Maxima de Cursos
#define QMATERIAS 8 // Padrao 8|| Quantidade de Materias
#define QUANTNOTAS 6// Padrao 6|| Quantidade de Notas
#define CMDLIMP() system("@cls||clear")
#define lt() fflush(stdin)
#define sleep() system("powershell Start-Sleep 2")
//Variaveis globais de contagem

int gCCurs = 0;
int gCAlun = 0;
//Funcoes declaradas
int gerenAlu();int listAlun();int addAluno();int pesqAlun();int listarAlnRemv();int editAlun(unsigned int RA);
int gerenCurs();int addCurso();int listarCursos();int remvCurs();int listarRemovidos();int editCurs();int pesqCurso();
int gerenNotas();int alunosCurso(int aCurso);int setqNotas();_Bool checarRA(unsigned int RA);_Bool checarCurso(int IDcurso);
int editMat(int ID);int setEndr(int IDAluno);int RAtoID(unsigned int RA);char *printG(char *texto);int scanfint(bool permitirNegativo);

unsigned int gerarRA(int nAlun,int idCurso);

//Facilitacao e padronizacao de selecao de horarios
char  periodos[4][13]= {"Nao definido","Manha","Tarde","Noite"};
// Informacoes do aluno (Endereco)
struct sEndereco
{
    char rua[50];
    unsigned int numero;
    char estado[40];
    char cidade[40];
    char bairro[40];
    char complemento[50];
};
// Informacoes do aluno
struct cadastro
{
    bool ativo;
    char nome[256];
    char cpf[15];
    char email[50];
    char telefone[15];
    struct sEndereco endereco;
    unsigned short int idCurso;
    unsigned int RA;
};
//Informacoes do Curso
struct curso
{
    bool ativo;
    unsigned short int id;
    char nome[50];
    short int periodo;
    char tipo[20];
    char materias[QMATERIAS][40];
    unsigned short int qNotas[QMATERIAS];
    short int quantMat;
    short int totalAlunos;
    short int alunosAtivos;
};

struct sNotas
{
    unsigned int RA;
    float notas[QMATERIAS][QUANTNOTAS];
    float media[QMATERIAS];
};



// Inicializacao da struct
struct sNotas notas[QALUN];
struct curso curso[QCURS];
struct cadastro aluno[QALUN];
int main()
{
    int primOpt = -1;
    do
    {
        lt();
        CMDLIMP();
        printf("[ 1 ] Gerenciar Cursos\n[ 2 ] Gerenciar Alunos\n[ 3 ] Gerenciar notas\n[ 0 ] Sair\n");
        printf("Digite a opcao: ");
        primOpt = scanfint(false);
        printf("\n");
        switch(primOpt)
        {
        case 0:
            printf("Deseja Sair ? [S/n] ");
            lt();
            switch(getchar())
            {
            case 'y':
            case 'Y':
            case 's':
            case 'S':
                primOpt = 0;
                break;
            case 'n':
            case 'N':
                primOpt = -1;
                break;
            default:
                primOpt = -1;
            }
            break;
        case 1:
            gerenCurs();
            break;
        case 2:
            gerenAlu();
            break;
        case 3:
            gerenNotas();
            break;

        default:
            printf("Erro: Opcao incorreta/inexistente");
            sleep();
        }
    }
    while(primOpt != 0);
}

int gerenCurs()
{
    int edit = 0;
    int opt = -1;
    while(opt != 0)
    {
        CMDLIMP();
        printf("[ 1 ] Adicionar Curso\n[ 2 ] Editar Curso\n[ 3 ] Listar Cursos\n[ 4 ] Remover Curso\n[ 5 ] Informacoes do Curso\n[ 6 ] Definir quantidade de notas\n[ 0 ] Voltar\nDigite a opcao: ");
        lt();
        scanf(" %d", &opt);
        switch(opt)
        {
        case 0:
            printf("\nRetornando...\n");
            break;
        case 1:
            addCurso();
            break;
        case 2:
            listarCursos();
            if(!gCCurs == 0)
            {
                printf("Digite o ID do curso desejado: ");
                scanf(" %d",&edit);
                editCurs(edit);
            }
            else
            {
                sleep();
            }
            break;
        case 3:
            listarCursos();
            system("pause");
            break;
        case 4:
            if(!gCCurs == 0)
            {
                remvCurs();
            }
            else
            {
                listarCursos();
                system("pause");
            }
            break;
        case 5:
            if(!gCCurs == 0)
            {
                pesqCurso();
                sleep();
                system("pause");
            }
            else
            {
                listarCursos();
                system("pause");
            }
            break;
        case 6:
            setqNotas();
            break;
        default:
            printf("Erro: Opcao incorreta ou inexistente\n");
            sleep();
        }
    }
    return 0;
}

int gerenAlu()
{
    int opt = -1,rra;
    if(gCCurs < 1)
    {
        printf("Por favor adicione ao menos um curso antes de fazer isso\n");
        lt();
        system("pause");
        return 0;
    }
    do
    {
        CMDLIMP();
        printf("[ 1 ] Adicionar Aluno\n[ 2 ] Listar Alunos\n[ 3 ] Modificar Aluno\n[ 4 ] Pesquisar Aluno\n[ 5 ] Desativar/Reativar aluno\n[ 0 ] Voltar\nDigite uma opcao: ");
        scanf(" %d", &opt);
        switch(opt)
        {
        case 0:

            break;
        case 1://Adicionar Alunos
            addAluno();
            break;
        case 2://Listar Alunos
            listAlun();
            system("pause");
            break;
        case 3:
            printf("Digite o RA do aluno: ");
            scanf(" %d",&rra);
            editAlun(rra);
            break;
        case 4://Pesquisar aluno
            pesqAlun();
            system("pause");
            break;

        case 5://Remover/Readicionar Aluno
            printf("[ 1 ] Desativar\n[ 2 ] Reativar\nDigite a opcao: ");
            opt = -1;
            lt();
            scanf(" %d",&opt);
            switch(opt)
            {
            case 1:
                printf("Removendo aluno...\n");
                listAlun();
                printf("Digite o RA do aluno: ");
                scanf(" %d",&rra);
                aluno[RAtoID(rra)].ativo = false;
                break;

            case 2:
                printf("Reativando aluno...\n");
                listarAlnRemv();
                printf("Digite o RA do aluno: ");
                scanf(" %d",&rra);
                aluno[RAtoID(rra)].ativo = true;
                break;

            }
            break;

        default:
            printf("Erro: Opcao incorreta");
            sleep();
        }
    }
    while(opt != 0);
    return 0;
}

unsigned int gerarRA(int nAlun,int idCurso )
{
    if(idCurso < 0)
    {
        idCurso = QCURS-1;
    }
    if (nAlun > 99)
    {
        printf("Erro: Limite de alunos atingido\n");
        system("pause");
        return 0;
    }
    if (idCurso > 99)
    {
        printf("Erro: Limite de cursos atingido\n");
        system("pause");
        return 0;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int raAno = (tm.tm_year + 1900)*10000;
    int raCurs = idCurso * 100;
    int RA = raAno + raCurs + nAlun;
    if(RA < 20210000)
    {
        return 0;
    }
    return RA;
}

int addAluno()
{
    int confirma = -1,opt = -1;
    bool RAGen = false;
    int nAluno = gCAlun;
    int RA = 0;
    char notDef[50] = "Nao definido";
    do
    {
        CMDLIMP();
        if(!RAGen)
        {
            printf("O RA sera gerado ao selecionar algum curso\n");
        }
        else
        {
            strcpy(notDef,curso[aluno[nAluno].idCurso].nome);
        }

        printf("Adicionar dados:\n      RA : %d \n[ 1 ] Nome: %s\n[ 2 ] CPF: %s\n[ 3 ] Email: %s\n[ 4 ] Curso: %s\n[ 5 ] Telefone: %s\n[ 6 ] Endereco\n[ 9 ] Cancelar\n[ 0 ] Salvar e Sair\nSelecione a opcao: ",aluno[nAluno].RA,printG(aluno[nAluno].nome),printG(aluno[nAluno].cpf),printG(aluno[nAluno].email),printG(notDef),printG(aluno[nAluno].telefone));
        lt();
        scanf(" %d",&opt);
        switch(opt)
        {
        case 0:
            if(strlen(aluno[nAluno].nome) < 3)
            {
                opt = -1;
                printf("Erro: E necessario digitar um nome");
                sleep();
                break;

            }
            else if(RAGen && RA != 0 && RA < 20210000)
            {
                opt = -1;
                printf("Erro: Escolha um curso para o aluno");
                sleep();
                break;
            }
            printf("Salvo\n");
            aluno[nAluno].ativo = true;
            gCAlun += 1;
            lt();
            break;


        case 1:
            printf("Digite o nome: ");
            lt();
            fgets(aluno[nAluno].nome,255,stdin);
            //aluno[nAluno].nome = remNL(aluno[nAluno].nome);

            break;

        case 2:
            printf("Digite o CPF (Sem Pontuacao): ");
            lt();
            fgets(aluno[nAluno].cpf,15,stdin);
            break;

        case 3:
            printf("Digite o Email: ");
            lt();
            fgets(aluno[nAluno].email,50,stdin);
            break;

        case 4:
            printf("Cursos:\n");
            listarCursos();
            printf("Digite o ID do curso selecionado: ");
            lt();
            confirma = scanfint(false);
            if(!curso[confirma].ativo)
            {
                printf("Erro: Curso Inexistente/Inativo");
                sleep();
            }


            aluno[nAluno].idCurso = confirma;
            RAGen = true;
            aluno[nAluno].RA = gerarRA(nAluno,aluno[nAluno].idCurso);

            break;

        case 5:
            printf("Digite o telefone: ");
            lt();
            fgets(aluno[nAluno].telefone,15,stdin);
            break;

        case 6:
            setEndr(nAluno);
            break;

        case 9:
            return 0;
            break;

        }
    }
    while(opt !=0);
    system("pause");
    return confirma;
}

int addCurso()
{
    int addMat(int x);
    int opt = -1;
    curso[gCCurs].quantMat = 0;
    curso[gCCurs].id = gCCurs;
    do
    {
        CMDLIMP();

        printf("Adicionando curso\nID do curso: %02d\n\n[ 1 ] Nome: %s\n",gCCurs,printG(curso[gCCurs].nome));
        printf("[ 2 ] Tipo: %s\n[ 3 ] Periodo: %s\n",printG(curso[gCCurs].tipo),periodos[curso[gCCurs].periodo]);
        printf("[ 4 ] Materias\n[ 0 ] Salvar e Sair\n[ 9 ] Cancelar\nSelecione a opcao que deseja adicionar: ");
        lt();
        scanf(" %d",&opt);
        switch (opt)
        {
        case 0:

            if(strlen(curso[gCCurs].nome) < 3)
            {
                opt = -1;
                printf("Erro: E necessario digitar um nome para o curso");
                sleep();
            }
            else
            {
                curso[gCCurs].ativo = true;
                for(int y=0; y<QMATERIAS ; y++)
                {
                    curso[gCCurs].qNotas[y] = 4;
                }
                curso[gCCurs].id = gCCurs;
                gCCurs += 1;
            }

            break;

        case 1:
            printf("Digite o nome do curso: ");
            lt();
            fgets(curso[gCCurs].nome,50,stdin);
            break;
        case 2:
            printf("Qual o tipo do curso?: ");
            lt();
            fgets(curso[gCCurs].tipo,20,stdin);
            break;
        case 3:
            for(int i = 1; i < 4; i++)
            {
                printf("[ %d ] %s\n",i,periodos[i]);
            }
            printf("Qual periodo?: ");
            lt();
            scanf(" %hd",&curso[gCCurs].periodo);
            break;
        case 4:
            addMat(gCCurs);
            break;
        case 9:
            return 0;
            break;
        }
    }
    while(opt != 0);
    return 0;
}

int remvCurs()
{

    int temp = -1;
    listarCursos();

    printf("Digite o ID do curso a ser removido: ");
    scanf(" %d", &temp);
    if(temp > gCCurs || temp < 0)
    {
        printf("Erro: Curso inexistente\n");
        system("pause");
        return 0;
    }
    curso[temp].ativo = false;
    printf("O Curso %s foi removido\n",printG(curso[temp].nome));
    system("pause");
    return 0;
}

int editCurs(int ID)
{
    int opt;
    if(checarCurso(ID))
    {
        printf("Erro: ID de curso nao existe ou esta desativado");
        sleep();
        return 0;
    }



    do
    {
        lt();
        CMDLIMP();
        printf("Editando curso...\nID: %02d\n[ 1 ] Nome: %s\n[ 2 ] Tipo",ID,curso[ID].nome);
        printf("\n[ 3 ] Periodo %s\n[ 4 ] Materias\n[ 0 ] Salvar e Sair\nSelecione a opcao que deseja adicionar: ",periodos[curso[ID].periodo]);
        scanf(" %d",&opt);
        switch(opt)
        {
        case 1:
            printf("Digite o novo nome do curso: ");
            lt();
            fgets(curso[ID].nome,50,stdin);
            break;
        case 2:
            printf("Digite o novo tipo do curso: ");
            lt();
            fgets(curso[ID].tipo,20,stdin);
            break;
        case 3:
            printf("Selecione o novo periodo do curso\nAtual: %s\n",periodos[curso[ID].periodo]);
            for(int temp = 1; temp < 4; temp++)
            {
                printf("[ %02d ] %s\n",temp,periodos[temp]);
            }
            printf("Escolha o novo periodo: ");
            scanf(" %hd",&curso[ID].periodo);

            break;
        case 4:
            editMat(ID);
            break;
        }
    }
    while(opt !=0);

    return 0;
}


int addMat(int x)
{
    short unsigned int opt;
    do
    {
        CMDLIMP();
        printf("Limite: %d | Atual : %d\n[ 1 ] Adicionar materia\n[ 2 ] Remover ultima materia\n[ 0 ] Concluir\n",QMATERIAS,curso[x].quantMat);
        if(curso[x].quantMat != 0)
        {
            printf("Materias:\n");
            for(int y = 0; y < curso[x].quantMat; y++)
            {
                printf("ID: %02d - Nome : %s\n",y,printG(curso[x].materias[y]));
            }
        }
        printf("Digite uma opcao: ");
        scanf(" %hu",&opt);
        lt();
        switch(opt)
        {
        case 0:
            printf("Salvo...");
            break;
        case 1:
            if(curso[x].quantMat == QMATERIAS)
            {
                printf("Erro: Limite de materias atingido\n");
                sleep();
                continue;
            }
            printf("Digite o nome da Materia: ");
            lt();
            while(strlen(curso[x].materias[curso[x].quantMat]) < 3){
            fgets(curso[x].materias[curso[x].quantMat],50,stdin);
            if(strlen(curso[x].materias[curso[x].quantMat]) < 3){printf("Erro: O nome da materia deve possuir mais de 3 caracteres");sleep();
            }}
            curso[x].quantMat += 1;
            break;

        case 2:
            if(curso[x].quantMat > 0)
            {
                curso[x].quantMat -= 1;
                printf("Removendo: %s\n",curso[x].materias[curso[x].quantMat]);
            }
            else
            {
                printf("Nao ha materias para serem removidas");
            }
            sleep();
            break;
        }

    }
    while(opt != 0);
    return 0;
}

int listarCursos()
{

    if(gCCurs == 0)
    {
        printf("Ainda nao ha cursos adicionados\n");
        return 0;
    }

    for(int k = 0; k < gCCurs; k++)
    {
        curso[k].alunosAtivos = 0;
        for(int q = 0; q < gCAlun; q++)
        {
            if(aluno[k].ativo)
            {
                if(aluno[q].idCurso == k)
                {
                    curso[k].alunosAtivos += 1;
                }
            }
        }
    }

    printf("*AR -> Numero de alunos registrados no curso*\n");
    for(int x = 0; x < gCCurs; x++)
    {
        if(curso[x].ativo)
        {
            printf("ID: %02d || AR: %02d || ",curso[x].id,curso[x].alunosAtivos);//ID do Curso e Quantidade de alunos ativos
            printf("Nome: %s\n",printG(curso[x].nome));
        }
    }
    return 0;
}

int listarRemovidos()
{
    printf("Cursos removidos:");
    for(int x = 0; x < gCCurs; x++)
    {
        if(!(curso[x].ativo))
        {
            printf("ID: %02d || AR: %02d",curso[x].id,curso[x].alunosAtivos);//ID do Curso e Quantidade de alunos ativos
            printf("Nome: %s\n",curso[x].nome);
        }
    }
    return 0;
}

int editMat(int ID)
{
    addMat(ID);
    return 0;
}


int listAlun()
{
    if(gCAlun == 0)
    {
        printf("Ainda nao ha alunos registrados\n");
        return 0;
    }
    for(int x= 0; x < gCAlun; x++)
    {
        if(aluno[x].ativo)
        {
            printf("RA: %d | Nome: %s | Curso: %s\n",aluno[x].RA,printG(aluno[x].nome),printG(curso[aluno[x].idCurso].nome));
        }
    }
    return 0;
}


int setEndr(int IDAluno)
{
    int opt= -1;
    do
    {
        lt();
        CMDLIMP();
        printf("[ 1 ] Cidade: %s\n[ 2 ] Estado: %s\n[ 3 ] Bairro: %s\n[ 4 ] Rua: %s\n[ 5 ] Numero: %u\n[ 6 ] Complemento: %s\n[ 0 ] Salvar e Sair\nEscolha uma opcao: ",printG(aluno[IDAluno].endereco.cidade),printG(aluno[IDAluno].endereco.estado),printG(aluno[IDAluno].endereco.bairro),printG(aluno[IDAluno].endereco.rua),aluno[IDAluno].endereco.numero,printG(aluno[IDAluno].endereco.complemento));
        scanf(" %d",&opt);

        switch(opt)
        {
        case 0:
            break;
        case 1:
            printf("Cidade: ");
            lt();
            fgets(aluno[IDAluno].endereco.cidade,40,stdin);
            break;
        case 2:
            printf("Estado: ");
            lt();
            fgets(aluno[IDAluno].endereco.estado,40,stdin);
            break;
        case 3:
            printf("Bairro: ");
            lt();
            fgets(aluno[IDAluno].endereco.bairro,40,stdin);
            break;
        case 4:
            printf("Rua: ");
            lt();
            fgets(aluno[IDAluno].endereco.rua,50,stdin);
            break;
        case 5:
            printf("Numero: ");
            lt();
            aluno[IDAluno].endereco.numero = scanfint(false);
            break;
        case 6:
            printf("Complemento: ");
            lt();
            fgets(aluno[IDAluno].endereco.complemento,50,stdin);
            break;
        default:
            printf("Opcao incorreta");
            sleep();

        }
    }
    while(opt != 0);
    return 0;
}

int pesqAlun()
{
    lt();
    unsigned int sRA = 0;
    printf("Digite o RA do aluno: ");
    scanf(" %u",&sRA);
    if(!checarRA(sRA))
    {
        printf("Erro: RA nao existente\n");
        return 0;
    }


    for(int x = 0; x < gCAlun; x++)
    {
        if(sRA == aluno[x].RA )
        {
            printf("\nAluno:\nNome: %s\n",printG(aluno[x].nome));
            printf("RA: %d\n",aluno[x].RA);

            if(!aluno[x].ativo)
            {
                printf("Situacao: Inativo/Removido\n");
            }
            else
            {
                printf("Situacao: Regular/Ativo\n");
            }

            printf("CPF: %s\n",printG(aluno[x].cpf));
            printf("Email: %s\n",printG(aluno[x].email));
            printf("Telefone: %s\n",printG(aluno[x].telefone));
            printf("Curso: %s\n",printG(curso[aluno[x].idCurso].nome));

            printf("Rua: %s\n",printG(aluno[x].endereco.rua));
            printf("Numero: %d\n",aluno[x].endereco.numero);
            printf("Complemento: %s\n",printG(aluno[x].endereco.complemento));
            printf("Bairro: %s\n",printG(aluno[x].endereco.bairro));
            printf("Cidade: %s\n",printG(aluno[x].endereco.cidade));
            printf("Estado: %s\n",printG(aluno[x].endereco.estado));


        }
    }
    return 0;
}


int     pesqCurso()
{
    int printMaterias(int sID);
    int sID;
    printf("Digite o ID do curso a ser pesquisado: ");
    lt();
    scanf(" %d",&sID);


    for(int x = 0; x< gCCurs; x++)
    {
        if(sID == curso[x].id)
        {
            printf("ID: %02d\n",curso[sID].id);
            printf("Nome: %s\n",printG(curso[sID].nome));
            printf("Tipo: %s\n",printG(curso[sID].tipo));
            printf("Periodo: %s\n",periodos[curso[sID].periodo]);
            printMaterias(sID);
        }

    }
    return 0;
}
int printMaterias(int sID)
{
    printf("Materias: \n");
    for(int x=0; x < curso[sID].quantMat; x++)
    {
        printf(" - %s\n",printG(curso[sID].materias[x]));
    }
    return 0;
}

int listarAlnRemv()
{
    for(int x = 0; x < gCAlun; x++)
    {
        if(!aluno[x].ativo)
        {
            printf("RA: %d | Nome: %sCurso: %s\n",aluno[x].RA,printG(aluno[x].nome),printG(curso[aluno[x].idCurso].nome));
        }
    }
    return 0;
}

int gerenNotas()
{
    if(gCCurs == 0)
    {
        printf("Erro: Nao ha cursos registrados\n");
        system("pause");
        return 0;
    }

    if(gCAlun == 0)
    {
        printf("Erro: Nao ha alunos registrados\n");
        system("pause");
        return 0;
    }

    int csID,RAluno,opt,opt2,alID;
    float nota,divMed=0;

    CMDLIMP();
    lt();
    CMDLIMP();
    listarCursos();
    printf("Digite o ID do curso: ");
    lt();
    csID = scanfint(false);
    if(!curso[csID].ativo)
    {
        printf("Erro: Curso Inexistente/Inativo");
        sleep();
        return 0;
    }
    alunosCurso(csID);
    printf("Digite o RA aluno: ");
    lt();
    RAluno = scanfint(false);
    if(!checarRA(RAluno))
    {
        printf("Erro: Aluno Inexistente/Inativo");
        sleep();
        return 0;
    }
    alID = RAtoID(RAluno);
    notas[alID].RA = RAluno;
    do{
        lt();
        CMDLIMP();
        printf("Materias:\n");
        for(int x=0; x < curso[csID].quantMat; x++)
        {
            printf("[ %d ] %s \n",(x+1),curso[csID].materias[x] );
        }
        printf("[ 0 ] Sair");
        printf("\nSelecione: ");
        scanf(" %d",&opt2);
        if(opt2 < 0 || opt2 > curso[csID].quantMat){
            printf("Erro: Materia inexistente\n");
            sleep();
            continue;
        }
        opt2 -=1;
        if(opt2 == -1){
            break;
        }
        do{
            CMDLIMP();
            divMed =0;
            for(int z=0;z < curso[csID].qNotas[opt2];z++){
                divMed += notas[alID].notas[opt2][z];
            }
            divMed /= curso[csID].qNotas[opt2];
            notas[alID].media[opt2] = divMed;
            printf("Materia: %s\n",curso[csID].materias[opt2]);
            for(int y=0; y < curso[csID].qNotas[opt2]; y++)
            {
                printf("[Nota %d] %0.2f \n",(y+1),notas[alID].notas[opt2][y]);;
            }
            printf("[ Media: %0.2f ]",notas[alID].media[opt2]);
            printf("\n[ 0 ] Sair\n");
            printf("Digite o numero da nota: ");
            scanf(" %d",&opt);
            if(opt < 0 || opt > curso[csID].qNotas[opt2])
            {
                printf("Erro: Nota Inexistente");
                lt();
                sleep();
                continue;
            }
            opt -=1;
            if(opt == -1)
            {
                break;
            }
            printf("Digite o valor da nota: ");
            scanf(" %f",&nota);
            if(nota < 0 || nota > 10)
            {
                printf("Erro: Nota invalida");
                lt();
                sleep();
                continue;
            }
            notas[alID].notas[opt2][opt] = nota;
            /*
            notas[alID].notas[opt2][opt] = nota;
            divMed =0;
            for(int z=0;z < curso[csID].qNotas[opt2];z++){
                divMed += notas[alID].notas[opt2][z];
            }
            divMed /= curso[csID].qNotas[opt2];
            notas[alID].media[opt2] = divMed;
*/
        }
        while(opt != -1);
    }
    while(opt2 !=-1);


    return 0;
}

int RAtoID(unsigned int RA)
{
    for(int x = 0; x < gCAlun; x++)
    {
        if(aluno[x].RA == RA)
        {
            return x;
        }
    }
    return QALUN;
}

int editAlun(unsigned int RA)
{
    if(RA < 20210000)
    {
        printf("Erro: RA Invalido");
        sleep();
        return 0;
    }
    if(!checarRA(RA))
    {
        printf("Erro: RA Invalido");
        sleep();
        return 0;
    }
    int opt = -1;
    int nAluno = RAtoID(RA);
    do
    {
        CMDLIMP();
        printf("Editando dados:\n\n[ 1 ] Nome: %s\n[ 2 ] CPF: %s\n[ 3 ] Email: %s\n[ 4 ] Curso: %s\n[ 5 ] Telefone: %s\n[ 6 ] Endereco\n[ 0 ] Salvar e Sair\nSelecione a opcao: ",printG(aluno[nAluno].nome),printG(aluno[nAluno].cpf),printG(aluno[nAluno].email),printG(curso[aluno[nAluno].idCurso].nome),printG(aluno[nAluno].telefone));
        lt();
        scanf(" %d",&opt);
        switch(opt)
        {
        case 0:
            if(strlen(aluno[nAluno].nome) < 3)
            {
                printf("Erro: Nome do Aluno invalido");
                sleep();
                opt = -1;
            }
            printf("Salvo...\n");
            break;
        case 1:
            printf("Digite o nome: ");
            lt();
            fgets(aluno[nAluno].nome,255,stdin);
            break;

        case 2:
            printf("Digite o CPF (Sem Pontuacao): ");
            lt();
            fgets(aluno[nAluno].cpf,15,stdin);
            break;

        case 3:
            printf("Digite o Email: ");
            lt();
            fgets(aluno[nAluno].email,50,stdin);
            break;

        case 4:
            printf("Cursos:\n");
            listarCursos();
            printf("Digite o ID do curso selecionado: ");
            lt();
            aluno[nAluno].idCurso = scanfint(false);
            break;

        case 5:
            printf("Digite o telefone: ");
            lt();
            fgets(aluno[nAluno].telefone,15,stdin);
            break;

        case 6:
            setEndr(nAluno);
            break;

        }
    }
    while(opt !=0);
    return 0;
}

int alunosCurso(int aCurso)
{
    printf("Alunos do curso de : %s\n",printG(curso[0].nome));
    for(int x = 0; x < gCAlun; x++)
    {
        if(aluno[x].ativo && aluno[x].idCurso == aCurso)
        {
            printf("RA: %d || Nome: %s\n",aluno[x].RA,printG(aluno[x].nome));
        }

    }
    return 0;
}


int setqNotas()
{
    int cID,opt,quant;
    printf("Selecione o Curso:\n");
    listarCursos();
    printf("Digite o ID: ");
    scanf("%d",&cID);
    do
    {
        CMDLIMP();
        lt();
        for(int x = 0; x < curso[cID].quantMat; x++)
        {
            printf("[ %d ] %s | Quantidade Atual: %hu\n",(x+1),printG(curso[cID].materias[x]),curso[cID].qNotas[x]);
        }

        printf("[ 0 ] Sair\nSelecione a materia: ");
        lt();
        scanf(" %d",&opt);
        if(opt == 0)
        {
            return 0;
        }
        if(opt < 0 || opt > curso[cID].quantMat)
        {
            printf("Erro: Materia Inexistente");
            return 0;
        }


        printf("Maximo de notas: %d\nDigite o numero de notas: ",QUANTNOTAS);
        lt();
        scanf(" %d",&quant);
        if(quant == 0 || quant > QUANTNOTAS )
        {
            printf("Erro: Numero invalido\n");
            system("pause");
        }
        else
        {
            curso[cID].qNotas[opt-1] = quant;
        }

    }
    while(opt != 0);
    return 0;
}


_Bool checarRA(unsigned int RA)
{
    int x = RAtoID(RA);
    if(aluno[x].ativo && aluno[x].RA == RA)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}


_Bool checarCurso(int IDcurso)
{
    if(curso[IDcurso].ativo && strlen(curso[IDcurso].nome) < 3)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

char *printG(char *texto)
{
    long long unsigned int x=0;
    while( x < (strlen(texto)))
    {
        if(texto[x] == '\n')
        {
            texto[x]='\0';
        }
        x++;
    }
    return texto;
}


int scanfint(bool permitirNegativo)
{
    char scanfi[64];
    char* convert;
    while (1)
    {
        fgets(scanfi, 64, stdin);
        int numero = strtol(scanfi, &convert, 0);
        if(permitirNegativo)
        {
            if ((numero == 0 && convert == scanfi)|| *convert != '\n')
            {
                printf("Numero invalido. Digite novamente: ");
                continue;
            }
            else
            {
                return numero;
            }
        }
        else
        {
            if ((numero == 0 && convert == scanfi)|| *convert != '\n' || numero < 0)
            {
                printf("Numero invalido. Digite novamente: ");
                continue;
            }
            else
            {
                return numero;
            }
        }

    }
    return 0;
}

