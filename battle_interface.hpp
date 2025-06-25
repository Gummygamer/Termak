#include "base_interface.hpp"

#ifndef INTERFACEBAT

#define INTERFACEBAT

#include <math.h>
#include <cctype>
#include <string>

#define LIML 0
#define LIMU 75
#define STEP 3
#define BATTLE_CENTER ((LIML + LIMU) / 2.0)
#define BATTLE_CAM_HEIGHT 80
#define TESTEX (fabs(xalvo - novox) <= rangeVar)
#define TESTEZ (fabs(zalvo - novoz) <= rangeVar)
#define TESTELIM ((novox >= LIML) && (novox <= LIMU) && (novoz >= LIML) && (novoz <= LIMU))

#define RAT 1
#define CAT 2
#define SCORPION 3

double heroX,heroY,heroZ;
double monsterX,monsterY,monsterZ;

Fighter* her = new Fighter(15,10,10,5,666);
Fighter* monst = nullptr;



void checkBattleEnd(){
    if (her -> getHP() <= 0){
        cout << "GAME OVER" << endl;
        exit(0);
    }

    if (monst && monst->getHP() <= 0){
        if (monst->getid() == CAT){
            cout << "THE END" << endl;
            exit(0);
        }

        resetCamera();
        cout << "HP = " << her -> getHP() << endl;
        modo = MAP;
        delete monst;
        monst = nullptr;
        return;
    }
}

void showEnemy(){
    /*if (monst -> getid() == CAT){
        //glTranslatef(0,9.9,0);
        glCallList(MOD_CAT);
    }
    else glCallList(MOD_RAT);*/

    if (!monst) return;
    switch(monst->getid())
    {
        case CAT: glCallList(MOD_CAT);
                   break;
        case RAT: glCallList(MOD_RAT);
                   break;
        case SCORPION: glCallList(MOD_SCORPION);
                   break;
        default: break;
    }
}


void moveMonster()
{
    if (!monst) return;

    int dir = rand() % 4;
    double novox = monsterX;
    double novoz = monsterZ;
    double xalvo = heroX;
    double zalvo = heroZ;
    double rangeVar = monst->getRange()*STEP;

    //if (monst -> getid() == CAT) rangeVar = 10*STEP;

    switch (dir)
    {
    case 0:
        novox += STEP;
        break;
    case 1:
        novox -= STEP;
        break;
    case 2:
        novoz += STEP;
        break;
    case 3:
        novoz -= STEP;
    }

    if (TESTEX && TESTEZ)
    {
        her -> takeDamage(monst);
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
    /* top-down camera centered on the battle field */
    gluLookAt(BATTLE_CENTER, BATTLE_CAM_HEIGHT + yobs, BATTLE_CENTER,
              BATTLE_CENTER, 0, BATTLE_CENTER,
              0, 0, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /* disable camera rotations during battle for a fixed view */

    showPlane();

    glPushMatrix();
    glTranslatef(heroX,heroY,heroZ);
    glCallList(MOD_HERO);
    glTranslatef(15,10,15);
    //glScalef(ESCALA_BARRA,ESCALA_BARRA,her -> getHP()*ESCALA_BARRA);
    showHPBar(her -> getHP());
    glPopMatrix();

    if (monst){
        glPushMatrix();
        glTranslatef(monsterX,monsterY,monsterZ);
        showEnemy();
        glTranslatef(15,10,15);
        //if(monst -> getid() == CAT) glTranslatef(0,15,-15);
        //glScalef(ESCALA_BARRA,ESCALA_BARRA,monst -> getHP()*ESCALA_BARRA);
        showHPBar(monst->getHP());
        glPopMatrix();
    }
    glutSwapBuffers();

    moveMonster();
}

void keyboard_battle(unsigned char tecla,int x,int y)
{

    if (!monst) return;

    double xalvo = monsterX;
    double zalvo = monsterZ;
    double novox = heroX;
    double novoz = heroZ;
    double rangeVar = 2*monst->getRange()*STEP;

    x=y;

    //if (monst -> getid() == CAT) rangeVar = 15*STEP;

    switch (tecla){
    case 'q':
        if (TESTEX && TESTEZ)
        {
            monst -> takeDamage(her);
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
        resetCamera();
        break;
    }
}

void arrows_battle(int seta,int x,int y)
{
    x = y;

    if (!monst) return;

    double xalvo = monsterX;
    double zalvo = monsterZ;
    double novox = heroX;
    double novoz = heroZ;
    double rangeVar = STEP;

    if (monst->getid() == CAT) rangeVar = 3*STEP;

    if (!(TESTEX && TESTEZ))
    {
        switch (seta)
        {
        case GLUT_KEY_UP:
            heroX += STEP;
            break;
        case GLUT_KEY_DOWN:
            heroX -= STEP;
            break;
        case GLUT_KEY_RIGHT:
            heroZ += STEP;
            break;
        case GLUT_KEY_LEFT:
            heroZ -= STEP;
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
