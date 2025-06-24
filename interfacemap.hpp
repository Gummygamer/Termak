#include "mapa.hpp"

#ifndef INTERFACEMAP
#define INTERFACEMAP

#define MAX 1000
#define MIN -1000

#define DIMCASA 20

int modmonst;

inline void drawCell(const string& s){
    switch (s[0]){
    case '.':
        showBlock();
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

inline void nextLine(){
    glTranslatef(-xmapa*DIMCASA,0,DIMCASA);
}

inline void drawLine(const string& s){
    drawCell(s);
    nextLine();
}

/* Function in charge of refreshing the map */
inline void showMap(){
    int cont1,cont2;
    for(cont1=0; cont1<ymapa; ++cont1){
        for(cont2=0; cont2<xmapa; ++cont2){
            glPushMatrix();
            glRotatef(-90*gameMap[cont1][cont2].orientacao,0,1,0);
            glTranslatef(-(1-gameMap[cont1][cont2].interpolacao)*DIMCASA,0,0);
            switch(gameMap[cont1][cont2].rotulo){
            case TELEPORT:
            case VAZIO:
                drawCell(" ");
                break;
            case BLOCO:
                drawCell(".");
                break;
            case MONSTRO:
                interpolar(cont1,cont2);
                switch(gameMap[cont1][cont2].conteudo[0]){
                    case 'r': modmonst = MODRAT; break;
                    case 'g': modmonst = MODCAT; break;
                    case 'e': modmonst = MODSCORPION; break;
                }
                drawCell("*");
                break;
            case HEROI:
                interpolar(cont1,cont2);
                drawCell("h");
            }
        }
        nextLine();
    }
}

inline void show_map(){
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

    showMap();
    atualizamonsters();

    glutSwapBuffers();
}

inline void teclado_map(unsigned char tecla,int x,int y){
    x = y;
    switch (tecla){
    case 'a': alfax++; break;
    case 's': alfay++; break;
    case 'd': alfaz++; break;
    case 'z': alfax--; break;
    case 'x': alfay--; break;
    case 'c': alfaz--; break;
    case 'r': reseta();
    }
}

inline void setas_map(int seta,int x,int y){
    x = y;
    switch (seta){
    case GLUT_KEY_UP:    avaliamov(lhero,chero,CIMA); break;
    case GLUT_KEY_DOWN:  avaliamov(lhero,chero,BAIXO); break;
    case GLUT_KEY_LEFT:  avaliamov(lhero,chero,ESQ); break;
    case GLUT_KEY_RIGHT: avaliamov(lhero,chero,DIR); break;
    }
}

inline void mouse_map(int bot,int est,int x,int y){
    x = y = est;
    if(bot) yobs++; else yobs--;
}

#endif
