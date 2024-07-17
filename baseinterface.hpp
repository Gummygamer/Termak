#ifndef BASE
#define BASE

#include "classes.hpp"


#define PI 3.141592653589
#define ANGLIM 0.999*PI/2

#define DISC 50

#define MAPA 0
#define BATALHA 1
#define MENU 3

#define MODHEROI 1
#define MODRATO 2
#define MODGATO 3
#define MODESCORPIAO 4

#define FATORGRAMA 2

#define ESCALA_BARRA 0.1

#define HP_GRANDE 20


double xobs = 0,yobs = 100,zobs = 0;

double alfax = 0;
double alfay = 0;
double alfaz = 0;

Corpo* corpoheroi;
Corpo* corporato;
Corpo* corpogato;
Corpo* corpoescorpiao;

int modo = MAPA;

void reseta(){
    alfax = 0;
    alfay = 0;
    alfaz = 0;
    yobs = 100;
}

void habzbuffer(){
    glEnable(GL_DEPTH_TEST);
}

void limpar(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void iluminacao(){
    glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    float amb[4] = {0,0,0,1};
    float dif[4] = {0.9,0.9,0.9,1};
    float pos[4] = {0,100,0,1};
    float att[1] = {0.001};

    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,dif);
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glLightfv(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,att);
    glEnable(GL_LIGHT0);
}

void mostratriang( double k ){
    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    glVertex2f(-k,-k);
    glVertex2f(k,-k);
    glVertex2f(0,k);
    glEnd();
}

void mostragrama( double k ){
    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    glVertex2f(-k,-k);
    glVertex2f(k,-k);
    glVertex2f(0,4*k);
    glEnd();
}


float* vetorpontoesfera(double raio,double alfa,double beta){
    float* vet = (float*) malloc(3*sizeof(float));
    vet[0] = raio*cos(alfa)*cos(beta);
    vet[1] = raio*cos(alfa)*sin(beta);
    vet[2] = raio*sin(alfa);
    return vet;
}

void pontoesfera(double raio,double alfa,double beta){
    float* v = vetorpontoesfera(raio,alfa,beta);
    glNormal3fv(v);
    glVertex3fv(v);
}

void mostraesfera(double raio,double div)
{
    double alfa,beta,delta;
    delta = 2*PI/div;
    for (alfa = -ANGLIM; alfa < ANGLIM; alfa+=delta){
        for (beta = -PI; beta < PI; beta+=delta){
            glBegin(GL_QUADS);
            pontoesfera(raio,alfa,beta);
            pontoesfera(raio,alfa+delta,beta);
            pontoesfera(raio,alfa+delta,beta+delta);
            pontoesfera(raio,alfa,beta+delta);
            glEnd();
        }
    }


    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,0,-raio);
    glVertex3f(0,0,-raio);
    for (beta = -PI; beta < PI; beta+=delta){
        pontoesfera(raio,-ANGLIM,beta);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,0,raio);
    glVertex3f(0,0,raio);
    for (beta = -PI; beta < PI; beta+=delta){
        pontoesfera(raio,ANGLIM,beta);
    }
    glEnd();
}

void mostraelipzoide(Elipzoide e)
{
    puts("vai mostrarelip");

    Cor difusa = e.difusa;
    Cor ambiente = e.ambiente;
    Cor especular = e.especular;

    puts("pegou cores");

    float fdifusa[4] = {(float)difusa.red, (float)difusa.green, (float)difusa.blue, 1.0f};
    float fambiente[4] = {(float) ambiente.red,(float) ambiente.green,(float) ambiente.blue,1};
    float fespecular[4] = {(float) especular.red,(float) especular.green,(float) especular.blue,1};
    float fbrilho[1] = {(float) e.brilho};

    glMaterialfv(GL_FRONT,GL_DIFFUSE,fdifusa);
    glMaterialfv(GL_FRONT,GL_AMBIENT,fambiente);
    glMaterialfv(GL_FRONT,GL_SPECULAR,fespecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,fbrilho);

    puts("opengl inicializou material");

    //Ponto* centro = e->getcentro();

    //Ponto* rotacao = e->getrotacao();

    //Ponto* distorcao = e->getdistorcao();


    glPushMatrix();

    glTranslatef(e.x,e.y,e.z);

    //glRotatef(e->getrx(),e->getry(),e->getrz());

    glRotatef(e.rx,1,0,0);
    glRotatef(e.ry,0,1,0);
    glRotatef(e.rz,0,0,1);

    glScalef(e.sx,e.sy,e.sz);

    mostraesfera(e.raio,DISC);

    glPopMatrix();
}

void mostracorpo(Corpo* c)
{
    int cont;
    //int tam = c->gettamanho();
    //vector<Elipzoide> vetor = c->getbolas();

    puts("pegou vetor");

    //printf("%d\n",vetor);

    //Elipzoide primeiro = vetor[0];

    puts("teste");

    for (cont = 0;cont < c->gettamanho()/*tam*/;cont++)
    {
        puts("vai chamar mostraelizoide");
        mostraelipzoide(c->getbolas().at(cont));
    }
}

void mostraplano( void ){
    glPushMatrix();
    glScalef(1,0.0001,1);

    float fdifusa[4] = {0.1,0.1,0.1,1};
    float fambiente[4] = {0,0,0,1};
    float fespecular[4] = {0.1,0.1,0.1,1};
    float fbrilho[1] = {0.5};

    glMaterialfv(GL_FRONT,GL_DIFFUSE,fdifusa);
    glMaterialfv(GL_FRONT,GL_AMBIENT,fambiente);
    glMaterialfv(GL_FRONT,GL_SPECULAR,fespecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,fbrilho);

    //glColor3f(0.2,0.7,0.2);
    //glColor3f(0.3,0.3,0.3);
    glutSolidCube(1000);
    glPopMatrix();
}

void mostrabloco( void ){
    glPushMatrix();
    float fdifusa[4] = {0.2,0.7,0.2,1};
    float fambiente[4] = {0.2,0.7,0.2,1};
    float fespecular[4] = {0.2,0.7,0.2,1};
    float fbrilho[1] = {1};

    glMaterialfv(GL_FRONT,GL_DIFFUSE,fdifusa);
    glMaterialfv(GL_FRONT,GL_AMBIENT,fambiente);
    glMaterialfv(GL_FRONT,GL_SPECULAR,fespecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,fbrilho);

    //glColor3f(0.2,0.7,0.2);
    glutSolidCube(20);

    glTranslatef(-5,5,-5);

    //glRotatef(90,0,1,0);

    /*int cont1,cont2;

    for (cont1 = 0;cont1 <= 10; cont1+=FATORGRAMA)
    {
        glPushMatrix();
        for (cont2 = 0;cont2 <= 10; cont2+=FATORGRAMA)
        {
            mostragrama(FATORGRAMA);
            glTranslatef(0,0,FATORGRAMA);
        }
        glPopMatrix();
        glTranslatef(FATORGRAMA,0,0);
    }*/

    //mostratriang(1);

    glPopMatrix();
}

void mostrabarraHP(double HP)
{
    glPushMatrix();

    double status = HP/HP_GRANDE;

    double comp = 1 - status;

    double extra = status - 1;

    float fdifusa[4] = {comp,status,extra,1};
    float fambiente[4] = {comp,status,extra,1};
    float fespecular[4] = {comp,status,extra,1};
    float fbrilho[1] = {0.6};

    glMaterialfv(GL_FRONT,GL_DIFFUSE,fdifusa);
    glMaterialfv(GL_FRONT,GL_AMBIENT,fambiente);
    glMaterialfv(GL_FRONT,GL_SPECULAR,fespecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,fbrilho);

    glScalef(ESCALA_BARRA,ESCALA_BARRA,HP*ESCALA_BARRA);

    //glColor3f(0.2,0.7,0.2);
    glutSolidCube(10);

    glPopMatrix();
}

/*void mostralutador(Lutador* l)
{
	mostracorpo(l->getmodelo());
}*/

void mostraheroi( void ){
    /* glPushMatrix();
    glColor3f(0,0,1);
    glScalef(0.74,0.74,0.74);
    mostraesfera(7,DISC);
    glTranslatef(0,7,0);
    glColor3f(1,1,0);
    mostraesfera(5,DISC);
    glColor3f(0,0,0);
    glTranslatef(4.5,1,-1);
    mostraesfera(1,DISC);
    glTranslatef(0,0,2);
    mostraesfera(1,DISC);
    glPopMatrix(); */
    corpoheroi->testaCorpo();
    mostracorpo(corpoheroi);
}

void mostrarato( void ){
    /*glPushMatrix();
    glColor3f(1,1,1);
    glScalef(0.74,0.74,0.74);
    mostraesfera(5,DISC);
    glTranslatef(5,0,0);
    glColor3f(0,0,0);
    mostraesfera(1,DISC);
    glTranslatef(-0.2,1,-1);
    glColor3f(1,0,0);
    mostraesfera(1,DISC);
    glTranslatef(0,0,2);
    mostraesfera(1,DISC);
    glColor3f(1,1,0);
    glTranslatef(-10,-1,-1);
    glScalef(2,0.1,0.1);
    mostraesfera(2,DISC);
    glPopMatrix(); */
    mostracorpo(corporato);
}

void mostragato( void ){
    /*glPushMatrix();
    glScalef(4,4,4);
    glColor3f(0,0,1);
    mostraesfera(5,DISC);
    glTranslatef(0,4,-1.1);
    glRotatef(90,0,1,0);
    glRotatef(60,0,0,1);
    mostratriang(3);
    glRotatef(-120,0,0,1);
    mostratriang(3);
    glRotatef(60,0,0,1);
    glRotatef(-90,0,1,0);
    glTranslatef(5,-4,0);
    glColor3f(1,0,0.2);
    mostraesfera(1,DISC);
    glTranslatef(-0.2,1,-1);
    glColor3f(0,1,0);
    mostraesfera(1,DISC);
    glTranslatef(0,0,2);
    mostraesfera(1,DISC);
    glColor3f(0,0,1);
    glTranslatef(-10,-1,-1);
    glScalef(2,0.1,0.1);
    mostraesfera(2,DISC);
    glPopMatrix();*/
    mostracorpo(corpogato);
}

Corpo* carregamodelo(string arq)
{
    string strcorpo;

    //colocaextedir((char*) "modelos/",c_arq,(char*) ".cor",&arq);
    arq = "modelos/" + arq + ".cor";

    const char* c_arq = arq.c_str();

    strcorpo = string(carregaarquivo(c_arq));

    printf("arq ok!\n");

    return new Corpo(strcorpo);
}

void inicializacoesdemodelos(){

    corpoheroi = carregamodelo("heroi");
    corporato = carregamodelo("rato");
    corpogato = carregamodelo("gato");
    corpoescorpiao = carregamodelo("escorpiao");

    puts("carregou");

    glNewList(MODHEROI,GL_COMPILE);
    puts("opengl vai fazer lista");
    mostraheroi();
    glEndList();

    puts("lista hero\n");

    glNewList(MODRATO,GL_COMPILE);
    mostrarato();
    glEndList();

    glNewList(MODGATO,GL_COMPILE);
    mostragato();
    glEndList();

    glNewList(MODESCORPIAO,GL_COMPILE);
    mostracorpo(corpoescorpiao);
    glEndList();

}

#endif

