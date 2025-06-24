#include "classes.hpp"


#define QUEBRA_ALEAT 1000


void Body::testaBody() {
    /* if(this->bolas[0]->getraio());
    if(this->tamanho); */
}

double aleat(double inf,double sup)
{
    return inf + ( rand() % QUEBRA_ALEAT ) * ( (sup - inf) / QUEBRA_ALEAT );
}

Fighter::Fighter(double HP,int atq,int def,int alc,int id/*,Body* modelo */){
    this -> HP = HP;
    this -> ataque = atq;
    this -> defesa = def;
    this -> alcance = alc;
    this -> id = id;
    //this -> modelo = modelo;
}

void Fighter::recebedano(Fighter* inimigo){
    inimigo -> evolui(this);
    this -> HP -= inimigo -> ataque/this -> defesa*aleat(0,inimigo -> ataque);
    printf("%d HP = %f\n",id,HP);
    printf("%d HP = %f\n",inimigo -> id,inimigo -> HP);
}

void Fighter::evolui(Fighter* inimigo){
    HP += (inimigo -> HP) / 100;
    ataque += (inimigo -> defesa) / 100;
    defesa += (inimigo -> ataque) / 100;
}

double Fighter::getHP(void){
    return HP;
}

int Fighter::getid(void){
    return id;
}

int Fighter::getalcance(void){
    return alcance;
}

/*Body* Fighter::getmodelo(void)
{
	return modelo;
} */

/* SetofFighteres::SetofFighteres(Fighter** lutadores,int tam){
	this -> tamanho = tam;
	this -> lutadores = lutadores;
	atual = 0;
}

Fighter* SetofFighteres::getprox(void){
	if(atual == tamanho){
		atual = 0;
		return 0;
	}

	atual++;
	return lutadores[atual - 1];
} */


Body::Body(vector<Ellipsoid> bolas,int tam)
{
    //puts("bolas\n");
    this -> bolas = bolas;
    this -> tamanho = tam;
    //puts("const corp\n");
}

Body::Body(string s)
{
    //char* strcorpo;
    //char* strtam;
    size_t tam;
    int cont;

    //cout << s << endl;

    //concatDirExt("modelos/",arq,".cor",&arq);
    //loadFile(arq,&strcorpo);

    //strtam = strtok(s,"\n");

    //tam = stringToInt(strtam);

    vector<Ellipsoid> elipz;

    vector<string> str = explode(s,'\n');

    tam = stringToInt(str[0]);

    cout << "tam =" << tam << endl;

    for (cont = tam ;cont >= 1;cont--)
    {

        cout << str.at(cont) << endl;

        elipz.push_back(elip(str.at(cont)));

        puts("e");
    }

    puts("elips ok\n");

    //Body(elip,tam);
    this->bolas = elipz;
    this->tamanho = tam;
}


vector<Ellipsoid> Body::getbolas()
{
    return bolas;
}

int Body::gettamanho(){
    return bolas.size();
}

Color Body::cor(string s)
{
    Color ret;

    vector<string> v = explode(s,',');

    ret.red = ((double) stringToInt(v[0].c_str()))/100;
    ret.green = ((double) stringToInt(v[1].c_str()))/100;
    ret.blue = ((double) stringToInt(v[2].c_str()))/100;

    return ret;
}

Ellipsoid Body::elip(string s)
{
    Ellipsoid ret;

    puts("comec elip");

    vector<string> v = explode(s,';');

    puts("explodiu");

    vector<string> pos = explode(v[0],',');

    //string o = pos[0];

    //ret.z = 2;

    puts("explodiu");

    ret.x = (float) stringToInt(pos[0]);
    ret.y = (float) stringToInt(pos[1]);

    //puts(s.c_str());

    ret.z = (float) stringToInt(pos[2]);

    puts("pos");

    vector<string> sc = explode(v[1],',');

    ret.sx = (float) stringToInt(sc[0]);
    ret.sy = (float) stringToInt(sc[1]);
    ret.sz = (float) stringToInt(sc[2]);

    puts("sc");

    vector<string> rot = explode(v[2],',');

    ret.rx = (float) stringToInt(rot[0]);
    ret.ry = (float) stringToInt(rot[1]);
    ret.rz = (float) stringToInt(rot[2]);

    puts("rx");

    vector<string> mat = explode(v[3],'-');

    ret.ambiente = cor(mat[0]);

    ret.difusa = cor(mat[1]);

    ret.especular = cor(mat[2]);

    ret.brilho = ((double) stringToInt(mat[3]))/100;

    puts("mat");

    ret.raio = (double) stringToInt(v[4]);

    return ret;
}
