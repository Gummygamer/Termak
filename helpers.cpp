#include "helpers.hpp"


vector<string> explode(string s,char c)
{
    vector<string> v;

    size_t index1 = 0;
    size_t index2 = 0;

    while ((index2 = s.find_first_of(c, index1)) != string::npos)
    {
        int tam = index2 - index1;
        v.push_back(s.substr(index1,tam));
        index1 = index2 + 1;
    }

    v.push_back(s.substr(index1));
    return v;
}

// fun��o que lembra a pr�pria strcat
void concatDirExt(char* dir,char* arq,char* ext,char** alvo){
    *alvo = (char*) malloc((strlen(dir)+strlen(arq)+strlen(ext) + 1)*sizeof(char));
    printf("aloca��o ext ok\n");
    sprintf(*alvo, "%s%s%s", dir, arq, ext);
    printf("strcat ok\n %s\n",*alvo);
}


/* fun��o que carrega o arquivo de nome arq e coloca seu conte�do em *alvo retornando seu
tamanho */
char* loadFile(const char* arq){
    int cont = 0;

    printf("%s\n", arq);

    FILE* arqu = fopen(arq, "r");
    if (!arqu) {
        fprintf(stderr, "Failed to open %s\n", arq);
        return NULL;
    }

    printf("fopen ok\n");

    char buffer[LIM];

    printf("buffer aloc\n");

    int c;
    while ((c = fgetc(arqu)) != EOF && cont < LIM - 1) {
        buffer[cont++] = (char)c;
    }

    buffer[cont] = '\0';

    fclose(arqu);

    char* ret = (char*) malloc((cont + 1) * sizeof(char));
    if (!ret) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    strcpy(ret, buffer);

    return ret;
}

void writeToFile(char* arq,char* conteudo)
{
    FILE* arqu = fopen(arq,"w");
    fprintf(arqu, "%s", conteudo);
}
/* fun��o que converte uma string para int,em caso de char inv�lido retorna -1 */
int stringToInt(string s)
{
    istringstream stream(s);
    int ret;

    stream >> ret;

    return ret;
}




