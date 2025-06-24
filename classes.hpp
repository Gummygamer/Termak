#include "auxiliares.hpp"
#include "structs.hpp"


class Fighter{
private:
    double HP;
    double ataque;
    double defesa;
    int alcance;
    int id;
    //Body* modelo;
public:
    Fighter(double HP,int atq,int def,int alcance,int id/*,Body* */);
    void recebedano(Fighter*);
    void evolui(Fighter*);
    double getHP();
    //Body* getmodelo();
    int getid();
    int getalcance();
};

/* class SetofFighteres{
	private:
	 Fighter** lutadores;
	 int tamanho;
	 int atual;
	public:
	 SetofFighteres(Fighter**,int);
	 int gettamanho(void);
	 Fighter* getprox(void);
}; */


class Body{
private:
    vector<Ellipsoid> bolas;
    int tamanho;
public:
    Body(vector<Ellipsoid>,int);
    Body(string);
    void testaBody();
    vector<Ellipsoid> getbolas();
    int gettamanho();

    Ellipsoid elip(string);
    Color cor(string);
    //Body* carregar(FILE*);
};
