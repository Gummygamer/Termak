#include "mapa.hpp"
//#include "baseinterface.hpp"

#ifndef INTERFACEMAP

#define INTERFACEMAP

#define MAX 1000
#define MIN -1000

#define DIMCASA 20

int modmonst;

void imprime(string s){
    switch (s[0]){
    case '.':
        mostrabloco();
        break;

    case '*':
        glCallList(modmonst);
        break;
    case 'h':
        glCallList(MODHEROI);

    }
    glPopMatrix();
    glTranslatef(DIMCASA,0,0);
}

void ln(void){
    glTranslatef(-xmapa*DIMCASA,0,DIMCASA);
}

void imprimeln(string s){
    imprime(s);
    ln();
}
/* Function in charge of refreshing the map */
/* função encarregada de atualizar o mapa */
void mostramapa(){
    int cont1,cont2;
    for (cont1=0; cont1< ymapa;++cont1){
        for (cont2=0;cont2 < xmapa;++cont2){
            glPushMatrix();
            glRotatef(-90*mapadejogo[cont1][cont2].orientacao,0,1,0);
            glTranslatef(-(1-mapadejogo[cont1][cont2].interpolacao)*DIMCASA,0,0);
            switch (mapadejogo[cont1][cont2].rotulo){
            case TELEPORT:
            case VAZIO:
                imprime(" ");
                break;
            case BLOCO:
                imprime(".");
                break;
            case MONSTRO:
                interpolar(cont1,cont2);
		switch(mapadejogo[cont1][cont2].conteudo[0])
		{
			case 'r': modmonst = MODRATO;
				  break;
			case 'g': modmonst = MODGATO;
				  break;
			case 'e': modmonst = MODESCORPIAO;
		}
		//puts(mapadejogo[cont1][cont2].conteudo[0]);
                imprime("*");
                break;
            case HEROI:
                interpolar(cont1,cont2);
                imprime("h");
            }
        }
        ln();
    }
}

void mostra_map(){
    glClearColor(0,0,0.5,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80,1,0.05,200);
    gluLookAt(xobs,yobs,zobs,0,0,0,1,0,0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glRotatef(-90,0,1,0);
    glRotatef(alfax,1,0,0);
    glRotatef(alfay,0,1,0);
    glRotatef(alfaz,0,0,1);

    mostramapa();
    atualizamonstros();

    glutSwapBuffers();
}

void teclado_map(unsigned char tecla,int x,int y){
    x = y;

    switch (tecla){
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

void setas_map(int seta,int x,int y){

    x = y;

    switch (seta){
    case GLUT_KEY_UP:
        avaliamov(lheroi,cheroi,CIMA);
        break;
    case GLUT_KEY_DOWN:
        avaliamov(lheroi,cheroi,BAIXO);
        break;
    case GLUT_KEY_LEFT:
        avaliamov(lheroi,cheroi,ESQ);
        break;
    case GLUT_KEY_RIGHT:
        avaliamov(lheroi,cheroi,DIR);
    }
}

void mouse_map(int bot,int est,int x,int y){

    x = y = est;

    if (bot){
        yobs++;
    }
    else{
        yobs--;
    }
}

#endif
