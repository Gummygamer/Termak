#include "auxiliares.hpp"
#include "structs.hpp"


class Lutador{
private:
    double HP;
    double ataque;
    double defesa;
    int alcance;
    int id;
    //Corpo* modelo;
public:
    Lutador(double HP,int atq,int def,int alcance,int id/*,Corpo* */);
    void recebedano(Lutador*);
    void evolui(Lutador*);
    double getHP();
    //Corpo* getmodelo();
    int getid();
    int getalcance();
};

/* class SetofLutadores{
	private:
	 Lutador** lutadores;
	 int tamanho;
	 int atual;
	public:
	 SetofLutadores(Lutador**,int);
	 int gettamanho(void);
	 Lutador* getprox(void);
}; */


class Corpo{
private:
    vector<Elipzoide> bolas;
    int tamanho;
public:
    Corpo(vector<Elipzoide>,int);
    Corpo(string);
    void testaCorpo();
    vector<Elipzoide> getbolas();
    int gettamanho();

    Elipzoide elip(string);
    Cor cor(string);
    //Corpo* carregar(FILE*);
};
