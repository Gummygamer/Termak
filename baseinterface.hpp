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
#define MODRAT 2
#define MODCAT 3
#define MODSCORPION 4

#define FATORGRAMA 2

#define ESCALA_BARRA 0.1

#define HP_GRANDE 20


double xobs = 0,yobs = 100,zobs = 0;

double alfax = 0;
double alfay = 0;
double alfaz = 0;

Body* heroBody;
Body* ratBody;
Body* catBody;
Body* scorpionBody;

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

void showTriangle( double k ){
    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,1);
    glVertex2f(-k,-k);
    glVertex2f(k,-k);
    glVertex2f(0,k);
    glEnd();
}

void showGram( double k ){
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

void showSphere(double raio,double div)
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

void showEllipsoid(Ellipsoid e)
{
    puts("displayEllipsoid");

    Color difusa = e.difusa;
    Color ambiente = e.ambiente;
    Color especular = e.especular;

    puts("got colors");

    float fdifusa[4] = {(float)difusa.red, (float)difusa.green, (float)difusa.blue, 1.0f};
    float fambiente[4] = {(float) ambiente.red,(float) ambiente.green,(float) ambiente.blue,1};
    float fespecular[4] = {(float) especular.red,(float) especular.green,(float) especular.blue,1};
    float fbrilho[1] = {(float) e.brilho};

    glMaterialfv(GL_FRONT,GL_DIFFUSE,fdifusa);
    glMaterialfv(GL_FRONT,GL_AMBIENT,fambiente);
    glMaterialfv(GL_FRONT,GL_SPECULAR,fespecular);
    glMaterialfv(GL_FRONT,GL_SHININESS,fbrilho);

    puts("OpenGL material initialized");

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

    showSphere(e.raio,DISC);

    glPopMatrix();
}

void showBody(Body* c)
{
    int cont;
    //int tam = c->gettamanho();
    //vector<Ellipsoid> vetor = c->getbolas();

    puts("got vector");

    //printf("%d\n",vetor);

    //Ellipsoid primeiro = vetor[0];

    puts("test");

    for (cont = 0;cont < c->gettamanho()/*tam*/;cont++)
    {
        puts("calling displayEllipsoid");
        showEllipsoid(c->getbolas().at(cont));
    }
}

void showPlane( void ){
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

void showBlock( void ){
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
            showGram(FATORGRAMA);
            glTranslatef(0,0,FATORGRAMA);
        }
        glPopMatrix();
        glTranslatef(FATORGRAMA,0,0);
    }*/

    //showTriangle(1);

    glPopMatrix();
}

void showHPBar(double HP)
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

/*void mostralutador(Fighter* l)
{
	showBody(l->getmodelo());
}*/

void showHero( void ){
    /* glPushMatrix();
    glColor3f(0,0,1);
    glScalef(0.74,0.74,0.74);
    showSphere(7,DISC);
    glTranslatef(0,7,0);
    glColor3f(1,1,0);
    showSphere(5,DISC);
    glColor3f(0,0,0);
    glTranslatef(4.5,1,-1);
    showSphere(1,DISC);
    glTranslatef(0,0,2);
    showSphere(1,DISC);
    glPopMatrix(); */
    heroBody->testaBody();
    showBody(heroBody);
}

void showRat( void ){
    /*glPushMatrix();
    glColor3f(1,1,1);
    glScalef(0.74,0.74,0.74);
    showSphere(5,DISC);
    glTranslatef(5,0,0);
    glColor3f(0,0,0);
    showSphere(1,DISC);
    glTranslatef(-0.2,1,-1);
    glColor3f(1,0,0);
    showSphere(1,DISC);
    glTranslatef(0,0,2);
    showSphere(1,DISC);
    glColor3f(1,1,0);
    glTranslatef(-10,-1,-1);
    glScalef(2,0.1,0.1);
    showSphere(2,DISC);
    glPopMatrix(); */
    showBody(ratBody);
}

void showCat( void ){
    /*glPushMatrix();
    glScalef(4,4,4);
    glColor3f(0,0,1);
    showSphere(5,DISC);
    glTranslatef(0,4,-1.1);
    glRotatef(90,0,1,0);
    glRotatef(60,0,0,1);
    showTriangle(3);
    glRotatef(-120,0,0,1);
    showTriangle(3);
    glRotatef(60,0,0,1);
    glRotatef(-90,0,1,0);
    glTranslatef(5,-4,0);
    glColor3f(1,0,0.2);
    showSphere(1,DISC);
    glTranslatef(-0.2,1,-1);
    glColor3f(0,1,0);
    showSphere(1,DISC);
    glTranslatef(0,0,2);
    showSphere(1,DISC);
    glColor3f(0,0,1);
    glTranslatef(-10,-1,-1);
    glScalef(2,0.1,0.1);
    showSphere(2,DISC);
    glPopMatrix();*/
    showBody(catBody);
}

Body* loadModel(string arq)
{
    string strcorpo;

    //concatDirExt((char*) "modelos/",c_arq,(char*) ".cor",&arq);
    arq = "modelos/" + arq + ".cor";

    const char* c_arq = arq.c_str();

    strcorpo = string(loadFile(c_arq));

    printf("arq ok!\n");

    return new Body(strcorpo);
}

void initializeModels(){

    heroBody = loadModel("hero");
    ratBody = loadModel("rato");
    catBody = loadModel("gato");
    scorpionBody = loadModel("escorpiao");

    puts("carregou");

    glNewList(MODHEROI,GL_COMPILE);
    puts("opengl vai fazer lista");
    showHero();
    glEndList();

    puts("lista hero\n");

    glNewList(MODRAT,GL_COMPILE);
    showRat();
    glEndList();

    glNewList(MODCAT,GL_COMPILE);
    showCat();
    glEndList();

    glNewList(MODSCORPION,GL_COMPILE);
    showBody(scorpionBody);
    glEndList();

}

#endif

