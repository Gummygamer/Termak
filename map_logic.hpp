#include <time.h>
#include <string>
#include <cstring>
#include <cctype>

#define UP 3
#define DOWN 1
#define LEFT 2
#define RIGHT 0

#define EMPTY 0
#define HERO 1
#define TELEPORT 2
#define MONSTER 3
#define BLOCK 4

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
string extractDim1()
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

string extractDim2(){
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
void analyzeContent(int a,int b,int c,int *d){
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
    gameMap[b][c].conteudo=(char*) malloc(strlen(arquivo) + 1);
    strcpy(gameMap[b][c].conteudo,arquivo);
}

/* function that converts sequence element a into gameMap[b][c] */
int analyzeRawMapChar(int a,int b,int c,int *d){
    int rot=0;
    switch (vetormapa[a]){
    case '.':
        rot=gameMap[b][c].rotulo=BLOCK;
        break;
    case 'v':
        rot=gameMap[b][c].rotulo=EMPTY;
        break;
    case 'h':
        rot=gameMap[b][c].rotulo=HERO;
        lhero = b;
        chero = c;
        break;
    case '-':
        rot=gameMap[b][c].rotulo=TELEPORT;
        analyzeContent(a,b,c,d);
        break;
    case '*':
        rot=gameMap[b][c].rotulo=MONSTER;
        analyzeContent(a,b,c,d);
    }
    return rot;
}

/* function responsible for procedurally generating a map when the game loads */
void loadMap(string s)
{
    int cont, cont1, cont2;

    /* create a pseudo random seed based on the map name */
    unsigned seed = 0;
    for(char c : s) seed = seed * 131 + c;
    srand(time(0) + seed);

    /* generate random dimensions */
    ymapa = 8 + rand() % 5;
    xmapa = 8 + rand() % 5;

    gameMap = (LINHA*) malloc(ymapa * sizeof(LINHA));
    for (cont = 0; cont < ymapa; ++cont)
        gameMap[cont] = (CASA*) malloc(xmapa * sizeof(CASA));

    /* initialise the grid */
    for (cont1 = 0; cont1 < ymapa; ++cont1) for (cont2 = 0; cont2 < xmapa; ++cont2){
            gameMap[cont1][cont2].rotulo = EMPTY;
            gameMap[cont1][cont2].conteudo = NULL;
            gameMap[cont1][cont2].interpolacao = 1;
            gameMap[cont1][cont2].orientacao = RIGHT;
        }

    /* place the hero */
    lhero = rand() % ymapa;
    chero = rand() % xmapa;
    gameMap[lhero][chero].rotulo = HERO;

    /* randomly add blocks */
    for (cont1 = 0; cont1 < ymapa; ++cont1) for (cont2 = 0; cont2 < xmapa; ++cont2)
            if (gameMap[cont1][cont2].rotulo == EMPTY && rand() % 100 < 20)
                gameMap[cont1][cont2].rotulo = BLOCK;

    /* add teleports to other maps */
    int teleCount = 1 + rand() % 2;
    for (cont = 0; cont < teleCount; ++cont){
        int r1 = rand() % ymapa, r2 = rand() % xmapa;
        if (gameMap[r1][r2].rotulo != EMPTY){ --cont; continue; }
        gameMap[r1][r2].rotulo = TELEPORT;
        string dest = "map" + to_string(rand() % 3);
        gameMap[r1][r2].conteudo = (char*) malloc(dest.size() + 1);
        strcpy(gameMap[r1][r2].conteudo, dest.c_str());
    }

    /* add a few monsters */
    const char* monsters[] = {"rat", "cat", "scorpion"};
    int monsterCount = (ymapa * xmapa) / 20;
    for (cont = 0; cont < monsterCount; ++cont){
        int r1 = rand() % ymapa, r2 = rand() % xmapa;
        if (gameMap[r1][r2].rotulo != EMPTY){ --cont; continue; }
        gameMap[r1][r2].rotulo = MONSTER;
        const char* name = monsters[rand() % 3];
        gameMap[r1][r2].conteudo = (char*) malloc(strlen(name) + 1);
        strcpy(gameMap[r1][r2].conteudo, name);
    }
}

/* the following functions evaluate whether gameMap[a][b] contains a given element */

bool isBlock(int a,int b){
    if (gameMap[a][b].rotulo==BLOCK) return true;
    return false;
}

bool isHero(int a,int b){
    if (gameMap[a][b].rotulo==HERO) return true;
    return false;
}
bool isMonster(int a,int b){
    if (gameMap[a][b].rotulo==MONSTER) return true;
    return false;
}
bool isTeleport(int a,int b){
    if (gameMap[a][b].rotulo==TELEPORT) return true;
    return false;
}
bool isEmpty(int a,int b){
    if (gameMap[a][b].rotulo==EMPTY) return true;
    return false;
}

void battle(char* a){
    resetCamera();

    /*if (a[0] == 'g'){
        monst = new Fighter(100,10,50,CAT);
    }
    else{
        monst = new Fighter(15,10,50,RAT);
    }*/

    if (monst){
        delete monst;
        monst = nullptr;
    }

    std::string name = a ? std::string(a) : "";
    if (!name.empty()) name[0] = std::tolower(name[0]);

    if (name.size() && (name[0] == 'c' || name[0] == 'g')){
        monst = new Fighter(100,10,50,10,CAT);
    } else if (name.size() && name[0] == 'r'){
        monst = new Fighter(15,10,50,3,RAT);
    } else if (name.size() && (name[0] == 's' || name[0] == 'e')){
        monst = new Fighter(15,20,50,4,SCORPION);
    } else {
        fprintf(stderr, "Unknown monster '%s', defaulting to rat\n", a);
        monst = new Fighter(15,10,50,3,RAT);
    }

    printf("HP = %f\n",her -> getHP());

    heroX = -50;
    heroY = 10;
    heroZ = -50;

    monsterX = 50;
    monsterY = 10;
    monsterZ = 50;

    modo = BATTLE;

}

void avaliamov(int lin,int col,int dir){
    int novalin = lin,novacol = col;

    switch (dir){
    case UP:
        if (lin > 0) novalin--;
        break;
    case DOWN:
        if (lin < ymapa - 1) novalin++;
        break;
    case LEFT:
        if (col > 0) novacol--;
        break;
    case RIGHT:
        if (col < xmapa - 1) novacol++;
        break;
    }

    if (gameMap[lin][col].interpolacao > 1-DELTA){

        if (isHero(lin,col)){

            if (isBlock(novalin,novacol)){
                gameMap[lin][col].orientacao = dir;
                return;
            }

            if (isEmpty(novalin,novacol)){
                gameMap[lin][col].rotulo = EMPTY;
                gameMap[novalin][novacol].rotulo = HERO;
                gameMap[novalin][novacol].orientacao = dir;
                gameMap[novalin][novacol].interpolacao = 0;
                lhero = novalin;
                chero = novacol;
                return;
            }

            if (isMonster(novalin,novacol)){
                gameMap[lin][col].orientacao = dir;
                battle(gameMap[novalin][novacol].conteudo);
                gameMap[novalin][novacol].rotulo = EMPTY;
                return;
            }

            if (isTeleport(novalin,novacol)){
                loadMap(gameMap[novalin][novacol].conteudo);
                gameMap[lhero][chero].orientacao = dir;
                return;
            }
        }

        if (isMonster(lin,col)){
            if (isBlock(novalin,novacol)){
                gameMap[lin][col].orientacao = dir;
                return;
            }

            if (isEmpty(novalin,novacol)){
                gameMap[lin][col].rotulo = EMPTY;
                gameMap[novalin][novacol].rotulo = MONSTER;
                gameMap[novalin][novacol].orientacao = dir;
                gameMap[novalin][novacol].conteudo = gameMap[lin][col].conteudo;
                gameMap[novalin][novacol].interpolacao = 0;
                return;
            }

            if (isHero(novalin,novacol)){
                char* nome = gameMap[lin][col].conteudo;
                battle(nome);
                gameMap[lin][col].rotulo = EMPTY;
                return;
            }
        }
    }


}

/* function that makes the isMonster at gameMap[a][b] move */
void avaliamovmonster(int a,int b){
    int escolha=rand()%4;
    avaliamov(a,b,escolha);
}

/* function that updates isMonster positions on the map using gameMap */
void atualizamonsters(){
    int cont1,cont2;
    for (cont1=0;cont1<ymapa;cont1++) for (cont2=0;cont2<xmapa;cont2++)
            if (isMonster(cont1,cont2)) avaliamovmonster(cont1,cont2);
}

void interpolar(int lin,int col){
    if (gameMap[lin][col].interpolacao < 1){
        gameMap[lin][col].interpolacao+=DELTA;
    }
}


