typedef struct
{
    double red,green,blue;
}Color;

typedef struct
{
    float x,y,z,sx,sy,sz,rx,ry,rz;

    Color ambiente,difusa,especular;

    double brilho;

    double raio;

}Ellipsoid;
