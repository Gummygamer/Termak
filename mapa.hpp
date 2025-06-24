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

CASA **gameMap;
char *vetormapa;
int lhero,chero;
int xmapa,ymapa;
/* This function analises the string extracted from the map file, converts the map's line number into str and returns the characteres number in it. */
/* function that analyzes the map file string, places the number of lines in str and returns the digit count */
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

/* analogous to the previous function for the column count */

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



/* function that adds a reference to the file corresponding to element a of the sequence into gameMap[b][c] and stores its name size in *d */
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
    gameMap[b][c].conteudo=(char*) malloc(strlen(arquivo));
    strcpy(gameMap[b][c].conteudo,arquivo);
}

/* function that converts sequence element a into gameMap[b][c] */
int analisacharmapabruto(int a,int b,int c,int *d){
    int rot=0;
    switch (vetormapa[a]){
    case '.':
        rot=gameMap[b][c].rotulo=BLOCO;
        break;
    case 'v':
        rot=gameMap[b][c].rotulo=VAZIO;
        break;
    case 'h':
        rot=gameMap[b][c].rotulo=HEROI;
        lhero = b;
        chero = c;
        break;
    case '-':
        rot=gameMap[b][c].rotulo=TELEPORT;
        analisaconteudo(a,b,c,d);
        break;
    case '*':
        rot=gameMap[b][c].rotulo=MONSTRO;
        analisaconteudo(a,b,c,d);
    }
    return rot;
}

/* function responsible for allocating a map loaded from disk into RAM using the structure defined above */
void loadMap(string s)
{

    int cont,cont1,cont2,tamydomap,tamxdomap,inu=0,rot;
    string xdomap,ydomap,arquivo;
    //concatDirExt("mapas/",a,".map",&arquivo);

    arquivo = "mapas/" + s + ".map";

    vetormapa = loadFile(arquivo.c_str());

    //printf(".map ok\n");
    ydomap = extraidim1();
    xdomap = extraidim2();

    ymapa = stringToInt(ydomap);
    xmapa = stringToInt(xdomap);

    tamydomap = ydomap.size();
    tamxdomap = xdomap.size();

    /* this part converts the sequence loaded from file into gameMap cells */
    gameMap=(LINHA*) malloc(ymapa*sizeof(LINHA));
    for (cont=0;cont<ymapa;cont++)
        gameMap[cont]=(CASA*) malloc(xmapa*sizeof(CASA));

    cont=tamxdomap+tamydomap+2;
    /* essa parte traduz a seqüência carregada do arquivo em casas do mapa de jogo.*/
    for (cont1 = 0;cont1 < ymapa;++cont1) for (cont2 = 0;cont2 < xmapa;++cont2){
            rot=analisacharmapabruto(cont,cont1,cont2,&inu);
            if (rot==TELEPORT || rot==MONSTRO) cont+=inu;
            cont++;

            gameMap[cont1][cont2].interpolacao = 1;
            gameMap[cont1][cont2].orientacao = DIR;
        }
    free(vetormapa);
}

/* the following functions evaluate whether gameMap[a][b] contains a given element */

bool bloco(int a,int b){
    if (gameMap[a][b].rotulo==BLOCO) return true;
    return false;
}

bool hero(int a,int b){
    if (gameMap[a][b].rotulo==HEROI) return true;
    return false;
}
bool monster(int a,int b){
    if (gameMap[a][b].rotulo==MONSTRO) return true;
    return false;
}
bool tel(int a,int b){
    if (gameMap[a][b].rotulo==TELEPORT) return true;
    return false;
}
bool vazio(int a,int b){
    if (gameMap[a][b].rotulo==VAZIO) return true;
    return false;
}

void battle(char* a){
    reseta();

    /*if (a[0] == 'g'){
        monst = new Fighter(100,10,50,CAT);
    }
    else{
        monst = new Fighter(15,10,50,RAT);
    }*/

    switch(a[0])
    {
	case 'g': monst = new Fighter(100,10,50,10,CAT);
		  break;
	case 'r': monst = new Fighter(15,10,50,3,RAT);
                  break;
	case 'e': monst = new Fighter(15,20,50,4,SCORPION);
        default: break;
    }

    printf("HP = %f\n",her -> getHP());

    heroX = -50;
    heroY = 10;
    heroZ = -50;

    monsterX = 50;
    monsterY = 10;
    monsterZ = 50;

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

    if (gameMap[lin][col].interpolacao > 1-DELTA){

        if (hero(lin,col)){

            if (bloco(novalin,novacol)){
                gameMap[lin][col].orientacao = dir;
                return;
            }

            if (vazio(novalin,novacol)){
                gameMap[lin][col].rotulo = VAZIO;
                gameMap[novalin][novacol].rotulo = HEROI;
                gameMap[novalin][novacol].orientacao = dir;
                gameMap[novalin][novacol].interpolacao = 0;
                lhero = novalin;
                chero = novacol;
                return;
            }

            if (monster(novalin,novacol)){
                gameMap[lin][col].orientacao = dir;
                battle(gameMap[novalin][novacol].conteudo);
                gameMap[novalin][novacol].rotulo = VAZIO;
                return;
            }

            if (tel(novalin,novacol)){
                loadMap(gameMap[novalin][novacol].conteudo);
                gameMap[lhero][chero].orientacao = dir;
                return;
            }
        }

        if (monster(lin,col)){
            if (bloco(novalin,novacol)){
                gameMap[lin][col].orientacao = dir;
                return;
            }

            if (vazio(novalin,novacol)){
                gameMap[lin][col].rotulo = VAZIO;
                gameMap[novalin][novacol].rotulo = MONSTRO;
                gameMap[novalin][novacol].orientacao = dir;
                gameMap[novalin][novacol].conteudo = gameMap[lin][col].conteudo;
                gameMap[novalin][novacol].interpolacao = 0;
                return;
            }

            if (hero(novalin,novacol)){
                char* nome = gameMap[lin][col].conteudo;
                battle(nome);
                gameMap[lin][col].rotulo = VAZIO;
                return;
            }
        }
    }


}

/* function that makes the monster at gameMap[a][b] move */
void avaliamovmonster(int a,int b){
    int escolha=rand()%4;
    avaliamov(a,b,escolha);
}

/* function that updates monster positions on the map using gameMap */
void atualizamonsters(){
    int cont1,cont2;
    for (cont1=0;cont1<ymapa;cont1++) for (cont2=0;cont2<xmapa;cont2++)
            if (monster(cont1,cont2)) avaliamovmonster(cont1,cont2);
}

void interpolar(int lin,int col){
    if (gameMap[lin][col].interpolacao < 1){
        gameMap[lin][col].interpolacao+=DELTA;
    }
}


