#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>

#include "interfacebat.hpp"
#include "interfacemap.hpp"

#define FPS 60

clock_t tempoquadro = 0;
clock_t tempocalc = 0;
int framecount = 0;
int fpscalc = FPS;
int fpssum = 0;
int fpsavg = 0;
int recalcount = 0;

void display()
{
    clock_t tempoatual = clock();
    habzbuffer();
    limpar();
    iluminacao();

    int ratio = 0;

    if (ratio == 0)
    {
        switch (modo)
        {
        case MAPA:
            show_map();
            break;
        case BATALHA:
            show_battle();
        }
    }

    clock_t tempofps = clock();
    clock_t max_clocks_per_fs = CLOCKS_PER_SEC/FPS;

    while (tempofps - tempoatual < max_clocks_per_fs)
    {
        tempofps = clock();
    }
}

void teclado(unsigned char tecla,int x,int y){
    switch (modo)
    {
    case MAPA:
        teclado_map(tecla,x,y);
        break;
    case BATALHA:
        keyboard_battle(tecla,x,y);
    }
}

void setas(int seta,int x,int y)
{
    switch (modo)
    {
    case MAPA:
        setas_map(seta,x,y);
        break;
    case BATALHA:
        arrows_battle(seta,x,y);
    }
}

void mouse(int bot,int est,int x,int y)
{
    switch (modo)
    {
    case MAPA:
        mouse_map(bot,est,x,y);
        break;
    case BATALHA:
        mouse_battle(bot,est,x,y);
    }
}

void initGlut(int* a,char** b)
{
    glutInit(a,b);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Termak 3D");
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);
    glutSpecialFunc(setas);
    glutIdleFunc(display);
}

void initialize()
    loadMap("map0");
{
    initGlut(&a,b);
    initializeModels();
    initialize();

/* função a construir imaginada para iniciar o jogo a partir de um progresso salvo.*/
void carrega()
{
}

int main(int a,char** b)
{
    srand(time(0));
    inicializacoesglut(&a,b);
    inicializacoesdemodelos();
    inicializa();
    glutMainLoop();
    return 0;
}






