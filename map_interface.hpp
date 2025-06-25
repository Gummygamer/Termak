#include "map_logic.hpp"

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
        if (!firstPerson)
            glCallList(MOD_HERO);
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
            case EMPTY:
                drawCell(" ");
                break;
            case BLOCK:
                drawCell(".");
                break;
            case MONSTER:
                interpolar(cont1,cont2);
                switch(gameMap[cont1][cont2].conteudo[0]){
                    case 'r': modmonst = MOD_RAT; break;
                    case 'g': modmonst = MOD_CAT; break;
                    case 'e': modmonst = MOD_SCORPION; break;
                }
                drawCell("*");
                break;
            case HERO:
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

    double hx = chero * DIMCASA;
    double hz = lhero * DIMCASA;
    double hy = yobs;

    double tx = hx;
    double ty = hy;
    double tz = hz;

    switch(gameMap[lhero][chero].orientacao){
        case RIGHT: tx += DIMCASA; break;
        case LEFT:  tx -= DIMCASA; break;
        case UP:    tz -= DIMCASA; break;
        case DOWN:  tz += DIMCASA; break;
    }

    gluPerspective(80,1,0.05,200);
    gluLookAt(hx,hy,hz,tx,ty,tz,0,1,0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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
    case 'r': resetCamera();
    case 'p': toggleFirstPerson();
    }
}

inline void setas_map(int seta,int x,int y){
    x = y;
    switch (seta){
    case GLUT_KEY_UP:    avaliamov(lhero,chero,UP); break;
    case GLUT_KEY_DOWN:  avaliamov(lhero,chero,DOWN); break;
    case GLUT_KEY_LEFT:  avaliamov(lhero,chero,LEFT); break;
    case GLUT_KEY_RIGHT: avaliamov(lhero,chero,RIGHT); break;
    }
}

inline void mouse_map(int bot,int est,int x,int y){
    x = y = est;
    if(bot) yobs++; else yobs--;
}

#endif
