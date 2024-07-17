#include "classes.hpp"


#define QUEBRA_ALEAT 1000


void Corpo::testaCorpo() {
    /* if(this->bolas[0]->getraio());
    if(this->tamanho); */
}

double aleat(double inf,double sup)
{
    return inf + ( rand() % QUEBRA_ALEAT ) * ( (sup - inf) / QUEBRA_ALEAT );
}

Lutador::Lutador(double HP,int atq,int def,int alc,int id/*,Corpo* modelo */){
    this -> HP = HP;
    this -> ataque = atq;
    this -> defesa = def;
    this -> alcance = alc;
    this -> id = id;
    //this -> modelo = modelo;
}

void Lutador::recebedano(Lutador* inimigo){
    inimigo -> evolui(this);
    this -> HP -= inimigo -> ataque/this -> defesa*aleat(0,inimigo -> ataque);
    printf("%d HP = %f\n",id,HP);
    printf("%d HP = %f\n",inimigo -> id,inimigo -> HP);
}

void Lutador::evolui(Lutador* inimigo){
    HP += (inimigo -> HP) / 100;
    ataque += (inimigo -> defesa) / 100;
    defesa += (inimigo -> ataque) / 100;
}

double Lutador::getHP(void){
    return HP;
}

int Lutador::getid(void){
    return id;
}

int Lutador::getalcance(void){
    return alcance;
}

/*Corpo* Lutador::getmodelo(void)
{
	return modelo;
} */

/* SetofLutadores::SetofLutadores(Lutador** lutadores,int tam){
	this -> tamanho = tam;
	this -> lutadores = lutadores;
	atual = 0;
}

Lutador* SetofLutadores::getprox(void){
	if(atual == tamanho){
		atual = 0;
		return 0;
	}

	atual++;
	return lutadores[atual - 1];
} */


Corpo::Corpo(vector<Elipzoide> bolas,int tam)
{
    //puts("bolas\n");
    this -> bolas = bolas;
    this -> tamanho = tam;
    //puts("const corp\n");
}

Corpo::Corpo(string s)
{
    //char* strcorpo;
    //char* strtam;
    size_t tam;
    int cont;

    //cout << s << endl;

    //colocaextedir("modelos/",arq,".cor",&arq);
    //carregaarquivo(arq,&strcorpo);

    //strtam = strtok(s,"\n");

    //tam = paraint(strtam);

    vector<Elipzoide> elipz;

    vector<string> str = explode(s,'\n');

    tam = paraint(str[0]);

    cout << "tam =" << tam << endl;

    for (cont = tam ;cont >= 1;cont--)
    {

        cout << str.at(cont) << endl;

        elipz.push_back(elip(str.at(cont)));

        puts("e");
    }

    puts("elips ok\n");

    //Corpo(elip,tam);
    this->bolas = elipz;
    this->tamanho = tam;
}


vector<Elipzoide> Corpo::getbolas()
{
    return bolas;
}

int Corpo::gettamanho(){
    return bolas.size();
}

Cor Corpo::cor(string s)
{
    Cor ret;

    vector<string> v = explode(s,',');

    ret.red = ((double) paraint(v[0].c_str()))/100;
    ret.green = ((double) paraint(v[1].c_str()))/100;
    ret.blue = ((double) paraint(v[2].c_str()))/100;

    return ret;
}

Elipzoide Corpo::elip(string s)
{
    Elipzoide ret;

    puts("comec elip");

    vector<string> v = explode(s,';');

    puts("explodiu");

    vector<string> pos = explode(v[0],',');

    //string o = pos[0];

    //ret.z = 2;

    puts("explodiu");

    ret.x = (float) paraint(pos[0]);
    ret.y = (float) paraint(pos[1]);

    //puts(s.c_str());

    ret.z = (float) paraint(pos[2]);

    puts("pos");

    vector<string> sc = explode(v[1],',');

    ret.sx = (float) paraint(sc[0]);
    ret.sy = (float) paraint(sc[1]);
    ret.sz = (float) paraint(sc[2]);

    puts("sc");

    vector<string> rot = explode(v[2],',');

    ret.rx = (float) paraint(rot[0]);
    ret.ry = (float) paraint(rot[1]);
    ret.rz = (float) paraint(rot[2]);

    puts("rx");

    vector<string> mat = explode(v[3],'-');

    ret.ambiente = cor(mat[0]);

    ret.difusa = cor(mat[1]);

    ret.especular = cor(mat[2]);

    ret.brilho = ((double) paraint(mat[3]))/100;

    puts("mat");

    ret.raio = (double) paraint(v[4]);

    return ret;
}
