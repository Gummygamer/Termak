#include "helpers.hpp"
#include "structs.hpp"


class Fighter{
private:
    double HP;
    double attack;
    double defense;
    int range;
    int id;
    //Body* modelo;
public:
    Fighter(double HP,int atk,int defenseVal,int range,int id/*,Body* */);
    void takeDamage(Fighter*);
    void evolve(Fighter*);
    double getHP();
    //Body* getmodelo();
    int getid();
    int getRange();
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
