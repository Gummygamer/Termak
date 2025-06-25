#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <math.h>

#include "battle_interface.hpp"
#include "map_interface.hpp"

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
        case MAP:
            show_map();
            break;
        case BATTLE:
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

void keyboard(unsigned char tecla,int x,int y){
    switch (modo)
    {
    case MAP:
        teclado_map(tecla,x,y);
        break;
    case BATTLE:
        keyboard_battle(tecla,x,y);
    }
}

void arrows(int seta,int x,int y)
{
    switch (modo)
    {
    case MAP:
        setas_map(seta,x,y);
        break;
    case BATTLE:
        arrows_battle(seta,x,y);
    }
}

void mouse(int bot,int est,int x,int y)
{
    switch (modo)
    {
    case MAP:
        mouse_map(bot,est,x,y);
        break;
    case BATTLE:
        mouse_battle(bot,est,x,y);
    }
}

void joystick(unsigned int bot, int x, int y, int z)
{
    /* simple threshold based mapping for analog sticks */
    const int thr = 200;
    if (x > thr) arrows(GLUT_KEY_RIGHT, 0, 0);
    if (x < -thr) arrows(GLUT_KEY_LEFT, 0, 0);
    if (y > thr) arrows(GLUT_KEY_UP, 0, 0);
    if (y < -thr) arrows(GLUT_KEY_DOWN, 0, 0);

    if (bot & GLUT_JOYSTICK_BUTTON_A)
        keyboard('q', 0, 0);
    if (bot & GLUT_JOYSTICK_BUTTON_B)
        keyboard('r', 0, 0);
}

void initGlut(int* a,char** b)
{
    glutInit(a,b);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0,0);
    int width = glutGet(GLUT_SCREEN_WIDTH);
    int height = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowSize(width, height);
    glutCreateWindow("Termak 3D");
    glutFullScreen();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutSpecialFunc(arrows);
    glutJoystickFunc(joystick, 50);
    glutIdleFunc(display);
}

/* function called when starting the game without saved progress */
void initialize()
{
    loadMap("map0");
}

/* function to load the game from saved progress - not implemented */
void loadGame()
{
}

int main(int a,char** b)
{
    srand(time(0));
    initGlut(&a,b);
    initializeModels();
    initialize();
    glutMainLoop();
    return 0;
}






