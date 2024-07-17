typedef struct
{
    double red,green,blue;
}Cor;

typedef struct
{
    float x,y,z,sx,sy,sz,rx,ry,rz;

    Cor ambiente,difusa,especular;

    double brilho;

    double raio;

}Elipzoide;
