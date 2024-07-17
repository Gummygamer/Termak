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

#define RATO 1
#define GATO 2
#define ESCORPIAO 3

double xheroi,yheroi,zheroi;
double xmonstro,ymonstro,zmonstro;

Lutador* her = new Lutador(15,10,10,5,666);
Lutador* monst;



void testefimdebat(){
    if (her -> getHP() <= 0){
        cout << "GAME OVER" << endl;
        exit(0);
    }

    if (monst -> getHP() <= 0){
        if (monst -> getid() == GATO){
            cout << "THE END" << endl;
            exit(0);
        }

        reseta();
        cout << "HP = " << her -> getHP() << endl;

        modo = MAPA;
        return;
    }
}

void mostrainimigo(){
    /*if (monst -> getid() == GATO){
        //glTranslatef(0,9.9,0);
        glCallList(MODGATO);
    }
    else glCallList(MODRATO);*/

    switch(monst -> getid())
    {
	case GATO: glCallList(MODGATO);
		   break;
	case RATO: glCallList(MODRATO);
		   break;
	case ESCORPIAO: glCallList(MODESCORPIAO);
    }
}


void movemonstro()
{
    int dir = rand() % 4;
    double novox = xmonstro;
    double novoz = zmonstro;
    double xalvo = xheroi;
    double zalvo = zheroi;
    double alcance = monst -> getalcance()*PASSO;

    //if (monst -> getid() == GATO) alcance = 10*PASSO;

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
        testefimdebat();
    }
    else
    {
        if (TESTELIM)
        {
            xmonstro = novox;
            zmonstro = novoz;
        }
    }
}

void mostra_bat()
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

    mostraplano();

    glPushMatrix();
    glTranslatef(xheroi,yheroi,zheroi);
    glCallList(MODHEROI);
    glTranslatef(15,10,15);
    //glScalef(ESCALA_BARRA,ESCALA_BARRA,her -> getHP()*ESCALA_BARRA);
    mostrabarraHP(her -> getHP());
    glPopMatrix();

    glPushMatrix();
    glTranslatef(xmonstro,ymonstro,zmonstro);
    mostrainimigo();
    glTranslatef(15,10,15);
    //if(monst -> getid() == GATO) glTranslatef(0,15,-15);
    //glScalef(ESCALA_BARRA,ESCALA_BARRA,monst -> getHP()*ESCALA_BARRA);
    mostrabarraHP(monst -> getHP());
    glPopMatrix();
    glutSwapBuffers();

    movemonstro();
}

void teclado_bat(unsigned char tecla,int x,int y)
{

    double xalvo = xmonstro;
    double zalvo = zmonstro;
    double novox = xheroi;
    double novoz = zheroi;
    double alcance = 2*monst->getalcance()*PASSO;

    x=y;

    //if (monst -> getid() == GATO) alcance = 15*PASSO;

    switch (tecla){
    case 'q':
        if (TESTEX && TESTEZ)
        {
            monst -> recebedano(her);
            testefimdebat();
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

void setas_bat(int seta,int x,int y)
{
    x = y;

    double xalvo = xmonstro;
    double zalvo = zmonstro;
    double novox = xheroi;
    double novoz = zheroi;
    double alcance = PASSO;

    if (monst -> getid() == GATO) alcance = 3*PASSO;

    if (!(TESTEX && TESTEZ))
    {
        switch (seta)
        {
        case GLUT_KEY_UP:
            xheroi += PASSO;
            break;
        case GLUT_KEY_DOWN:
            xheroi -= PASSO;
            break;
        case GLUT_KEY_RIGHT:
            zheroi += PASSO;
            break;
        case GLUT_KEY_LEFT:
            zheroi -= PASSO;
        }
    }
}

void mouse_bat(int bot,int est,int x,int y)
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
