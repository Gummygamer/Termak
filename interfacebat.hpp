#include "baseinterface.hpp"

#ifndef INTERFACEBAT

#define INTERFACEBAT

#include <math.h>

#define LIML 0
#define LIMU 75
#define PASSO 3
#define TESTEX (fabs(xalvo - novox) <= alcance)
#define TESTEZ (fabs(zalvo - novoz) <= alcance)
#define TESTELIM ((novox >= LIML) && (novox <= LIMU) && (novoz >= LIML) && (novoz <= LIMU))

#define RAT 1
#define CAT 2
#define SCORPION 3

double heroX,heroY,heroZ;
double monsterX,monsterY,monsterZ;

Fighter* her = new Fighter(15,10,10,5,666);
Fighter* monst;



void checkBattleEnd(){
    if (her -> getHP() <= 0){
        cout << "GAME OVER" << endl;
        exit(0);
    }

    if (monst -> getHP() <= 0){
        if (monst -> getid() == CAT){
            cout << "THE END" << endl;
            exit(0);
        }

        reseta();
        cout << "HP = " << her -> getHP() << endl;

        modo = MAPA;
        return;
    }
}

void showEnemy(){
    /*if (monst -> getid() == CAT){
        //glTranslatef(0,9.9,0);
        glCallList(MODCAT);
    }
    else glCallList(MODRAT);*/

    switch(monst -> getid())
    {
	case CAT: glCallList(MODCAT);
		   break;
	case RAT: glCallList(MODRAT);
		   break;
	case SCORPION: glCallList(MODSCORPION);
    }
}


void moveMonster()
{
    int dir = rand() % 4;
    double novox = monsterX;
    double novoz = monsterZ;
    double xalvo = heroX;
    double zalvo = heroZ;
    double alcance = monst -> getalcance()*PASSO;

    //if (monst -> getid() == CAT) alcance = 10*PASSO;

    switch (dir)
    {
    case 0:
        novox += PASSO;
        break;
    case 1:
        novox -= PASSO;
        break;
    case 2:
        novoz += PASSO;
        break;
    case 3:
        novoz -= PASSO;
    }

    if (TESTEX && TESTEZ)
    {
        her -> recebedano(monst);
        checkBattleEnd();
    }
    else
    {
        if (TESTELIM)
        {
            monsterX = novox;
            monsterZ = novoz;
        }
    }
}

void show_battle()
{

    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,1,0.05,200);
    gluLookAt(xobs,yobs,zobs,0,0,0,1,0,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(alfax,1,0,0);
    glRotatef(alfay,0,1,0);
    glRotatef(alfaz,0,0,1);

    showPlane();

    glPushMatrix();
    glTranslatef(heroX,heroY,heroZ);
    glCallList(MODHEROI);
    glTranslatef(15,10,15);
    //glScalef(ESCALA_BARRA,ESCALA_BARRA,her -> getHP()*ESCALA_BARRA);
    showHPBar(her -> getHP());
    glPopMatrix();

    glPushMatrix();
    glTranslatef(monsterX,monsterY,monsterZ);
    showEnemy();
    glTranslatef(15,10,15);
    //if(monst -> getid() == CAT) glTranslatef(0,15,-15);
    //glScalef(ESCALA_BARRA,ESCALA_BARRA,monst -> getHP()*ESCALA_BARRA);
    showHPBar(monst -> getHP());
    glPopMatrix();
    glutSwapBuffers();

    moveMonster();
}

void keyboard_battle(unsigned char tecla,int x,int y)
{

    double xalvo = monsterX;
    double zalvo = monsterZ;
    double novox = heroX;
    double novoz = heroZ;
    double alcance = 2*monst->getalcance()*PASSO;

    x=y;

    //if (monst -> getid() == CAT) alcance = 15*PASSO;

    switch (tecla){
    case 'q':
        if (TESTEX && TESTEZ)
        {
            monst -> recebedano(her);
            checkBattleEnd();
        }
        break;
    case 'a':
        alfax++;
        break;
    case 's':
        alfay++;
        break;
    case 'd':
        alfaz++;
        break;
    case 'z':
        alfax--;
        break;
    case 'x':
        alfay--;
        break;
    case 'c':
        alfaz--;
        break;
    case 'r':
        reseta();
    }
}

void arrows_battle(int seta,int x,int y)
{
    x = y;

    double xalvo = monsterX;
    double zalvo = monsterZ;
    double novox = heroX;
    double novoz = heroZ;
    double alcance = PASSO;

    if (monst -> getid() == CAT) alcance = 3*PASSO;

    if (!(TESTEX && TESTEZ))
    {
        switch (seta)
        {
        case GLUT_KEY_UP:
            heroX += PASSO;
            break;
        case GLUT_KEY_DOWN:
            heroX -= PASSO;
            break;
        case GLUT_KEY_RIGHT:
            heroZ += PASSO;
            break;
        case GLUT_KEY_LEFT:
            heroZ -= PASSO;
        }
    }
}

void mouse_battle(int bot,int est,int x,int y)
{
    est = x = y;

    if (bot)
    {
        yobs++;
    }
    else
    {
        yobs--;
    }
}

#endif
