#include <time.h>

#define CIMA 3
#define BAIXO 1
#define ESQ 2
#define DIR 0

#define VAZIO 0
#define HEROI 1
#define TELEPORT 2
#define MONSTRO 3
#define BLOCO 4

#define DELTA 0.05

typedef struct{
    int rotulo;
    char *conteudo;
    int orientacao;
    double interpolacao;
}CASA;

typedef CASA* LINHA;

CASA **mapadejogo;
char *vetormapa;
int lheroi,cheroi;
int xmapa,ymapa;
/* This function analises the string extracted from the map file, converts the map's line number into str and returns the characteres number in it. */
/* função que analisa a string extraída do arquivo de mapa, coloca o número de linhas do mapa em str e retorna o  		número de dígitos */
string extraidim1()
{
    char atual;
    int cont = 0;
    string ret;

    //str = (char*) malloc(5*sizeof(char));

    while (1){
        atual = vetormapa[cont];
        if (atual == 'x') break;
        ret += atual;
        cont++;
    }

    //(*str)[cont] = '\0';

    return ret;
}

/* análoga à anterior para o número de colunas */

string extraidim2(){
    char atual = 'o';
    int cont = 0;

    string ret;

    while (atual != 'x'){
        atual = vetormapa[cont];
        cont++;
    }

    while (1){
        atual = vetormapa[cont];
        if (atual == 'x') break;
        ret += atual;
        cont++;
    }

    return ret;
}



/* função que coloca a referência a arquivo correspondente ao elemento a da seq. em
mapadejogo[b][c] ela coloca em *d o tamanho desse nome de arq. + 1 */
void analisaconteudo(int a,int b,int c,int *d){
    int cont=a+1;
    char arquivo[100];
    char atual;
    *d=0;
    while (1){
        atual = vetormapa[cont];
        if (atual=='"') break;
        arquivo[*d] = atual;
        cont++;
        *d=*d+1;
    }
    arquivo[*d] = '\0';
    *d=*d+1;
    mapadejogo[b][c].conteudo=(char*) malloc(strlen(arquivo));
    strcpy(mapadejogo[b][c].conteudo,arquivo);
}

/* função que traduz o elemento a da seq. para mapadejogo[b][c] */
int analisacharmapabruto(int a,int b,int c,int *d){
    int rot=0;
    switch (vetormapa[a]){
    case '.':
        rot=mapadejogo[b][c].rotulo=BLOCO;
        break;
    case 'v':
        rot=mapadejogo[b][c].rotulo=VAZIO;
        break;
    case 'h':
        rot=mapadejogo[b][c].rotulo=HEROI;
        lheroi = b;
        cheroi = c;
        break;
    case '-':
        rot=mapadejogo[b][c].rotulo=TELEPORT;
        analisaconteudo(a,b,c,d);
        break;
    case '*':
        rot=mapadejogo[b][c].rotulo=MONSTRO;
        analisaconteudo(a,b,c,d);
    }
    return rot;
}

/* função encarregada de alocar um mapa carregado de arquivos do HD na RAM segundo a estrutura
	de casas declarada no início do código*/
void carregamapa(string s)
{

    int cont,cont1,cont2,tamydomap,tamxdomap,inu=0,rot;
    string xdomap,ydomap,arquivo;
    //colocaextedir("mapas/",a,".map",&arquivo);

    arquivo = "mapas/" + s + ".map";

    vetormapa = carregaarquivo(arquivo.c_str());

    //printf(".map ok\n");
    ydomap = extraidim1();
    xdomap = extraidim2();

    ymapa = paraint(ydomap);
    xmapa = paraint(xdomap);

    tamydomap = ydomap.size();
    tamxdomap = xdomap.size();

    /* se aloca o mapa de jogo atual, o tipo LINHA se fez necessária para isso */
    mapadejogo=(LINHA*) malloc(ymapa*sizeof(LINHA));
    for (cont=0;cont<ymapa;cont++)
        mapadejogo[cont]=(CASA*) malloc(xmapa*sizeof(CASA));

    cont=tamxdomap+tamydomap+2;
    /* essa parte traduz a seqüência carregada do arquivo em casas do mapa de jogo.*/
    for (cont1 = 0;cont1 < ymapa;++cont1) for (cont2 = 0;cont2 < xmapa;++cont2){
            rot=analisacharmapabruto(cont,cont1,cont2,&inu);
            if (rot==TELEPORT || rot==MONSTRO) cont+=inu;
            cont++;

            mapadejogo[cont1][cont2].interpolacao = 1;
            mapadejogo[cont1][cont2].orientacao = DIR;
        }
    free(vetormapa);
}

/* as funções a seguir avaliam se há determinado elemento em
mapadejogo[a][b] */

bool bloco(int a,int b){
    if (mapadejogo[a][b].rotulo==BLOCO) return true;
    return false;
}

bool heroi(int a,int b){
    if (mapadejogo[a][b].rotulo==HEROI) return true;
    return false;
}
bool monstro(int a,int b){
    if (mapadejogo[a][b].rotulo==MONSTRO) return true;
    return false;
}
bool tel(int a,int b){
    if (mapadejogo[a][b].rotulo==TELEPORT) return true;
    return false;
}
bool vazio(int a,int b){
    if (mapadejogo[a][b].rotulo==VAZIO) return true;
    return false;
}

void batalha(char* a){
    reseta();

    /*if (a[0] == 'g'){
        monst = new Lutador(100,10,50,GATO);
    }
    else{
        monst = new Lutador(15,10,50,RATO);
    }*/

    switch(a[0])
    {
	case 'g': monst = new Lutador(100,10,50,10,GATO);
		  break;
	case 'r': monst = new Lutador(15,10,50,3,RATO);
                  break;
	case 'e': monst = new Lutador(15,20,50,4,ESCORPIAO);
        default: break;
    }

    printf("HP = %f\n",her -> getHP());

    xheroi = -50;
    yheroi = 10;
    zheroi = -50;

    xmonstro = 50;
    ymonstro = 10;
    zmonstro = 50;

    modo = BATALHA;

}

void avaliamov(int lin,int col,int dir){
    int novalin = lin,novacol = col;

    switch (dir){
    case CIMA:
        if (lin > 0) novalin--;
        break;
    case BAIXO:
        if (lin < ymapa - 1) novalin++;
        break;
    case ESQ:
        if (col > 0) novacol--;
        break;
    case DIR:
        if (col < xmapa - 1) novacol++;
        break;
    }

    if (mapadejogo[lin][col].interpolacao > 1-DELTA){

        if (heroi(lin,col)){

            if (bloco(novalin,novacol)){
                mapadejogo[lin][col].orientacao = dir;
                return;
            }

            if (vazio(novalin,novacol)){
                mapadejogo[lin][col].rotulo = VAZIO;
                mapadejogo[novalin][novacol].rotulo = HEROI;
                mapadejogo[novalin][novacol].orientacao = dir;
                mapadejogo[novalin][novacol].interpolacao = 0;
                lheroi = novalin;
                cheroi = novacol;
                return;
            }

            if (monstro(novalin,novacol)){
                mapadejogo[lin][col].orientacao = dir;
                batalha(mapadejogo[novalin][novacol].conteudo);
                mapadejogo[novalin][novacol].rotulo = VAZIO;
                return;
            }

            if (tel(novalin,novacol)){
                carregamapa(mapadejogo[novalin][novacol].conteudo);
                mapadejogo[lheroi][cheroi].orientacao = dir;
                return;
            }
        }

        if (monstro(lin,col)){
            if (bloco(novalin,novacol)){
                mapadejogo[lin][col].orientacao = dir;
                return;
            }

            if (vazio(novalin,novacol)){
                mapadejogo[lin][col].rotulo = VAZIO;
                mapadejogo[novalin][novacol].rotulo = MONSTRO;
                mapadejogo[novalin][novacol].orientacao = dir;
                mapadejogo[novalin][novacol].conteudo = mapadejogo[lin][col].conteudo;
                mapadejogo[novalin][novacol].interpolacao = 0;
                return;
            }

            if (heroi(novalin,novacol)){
                char* nome = mapadejogo[lin][col].conteudo;
                batalha(nome);
                mapadejogo[lin][col].rotulo = VAZIO;
                return;
            }
        }
    }


}

/* função que faz o monstro em mapadejogo[a][b] se mover */
void avaliamovmonstro(int a,int b){
    int escolha=rand()%4;
    avaliamov(a,b,escolha);
}

/* função que atualiza a posição dos monstros no mapa alterando a var mapadejogo */
void atualizamonstros(){
    int cont1,cont2;
    for (cont1=0;cont1<ymapa;cont1++) for (cont2=0;cont2<xmapa;cont2++)
            if (monstro(cont1,cont2)) avaliamovmonstro(cont1,cont2);
}

void interpolar(int lin,int col){
    if (mapadejogo[lin][col].interpolacao < 1){
        mapadejogo[lin][col].interpolacao+=DELTA;
    }
}


