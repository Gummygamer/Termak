#ifndef AUXILIARES

#define AUXILIARES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <vector>
#include <string>
#include <sstream>
#include <iostream>


using namespace std;

#define LIM 1000000

vector<string> explode(string s,char c);
void colocaextedir(char* dir,char* arq,char* ext,char** alvo);
char* carregaarquivo(const char* arq);
void escreveemarquivo(char* arq,char* conteudo);
int paraint(string s);

#endif
