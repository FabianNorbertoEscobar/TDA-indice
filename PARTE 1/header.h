#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#define     IGUAL       0

#define     DATO_VALIDO(x,li,ls)    ((x)>=(li)&&(x)<=(ls))
#define     ES_BLANCO(x)            ((x)==' ')
#define     ES_COMA(x)              ((x)==',')
#define     ES_LETRA(x)             (((x)>='A'&&(x)<='Z')||((x)>='a'&&(x)<='z'))
#define     ES_MAYUSCULA(x)         ((x)>='A'&&(x)<='Z')
#define     ES_MINUSCULA(x)         ((x)>='a'&&(x)<='z')
#define     A_MAYUSCULA(x)          (((x)>='a'&&(x)<='z')?((x)-32):(x))
#define     A_MINUSCULA(x)          (((x)>='A'&&(x)<='Z')?((x)+32):(x))

typedef struct
{
    int d,
        m,
        a;
} t_fecha;

typedef struct
{
    long dni;
    char apellido_nombre[40];
    t_fecha f_nacimiento;
    char sexo;
    t_fecha f_ingreso;
    char carrera[4];
    int materias_aprob;
    t_fecha f_ult_mat_aprob;
    char estado;
    t_fecha f_baja;
} t_alumno;

int fecha_valida(t_fecha*);
int cant_dias_mes(int,int);
int bisiesto(int);
void ingresa_fecha(t_fecha*);

char* str_cpy(char*,const char*);
char* str_cat(char*,const char*);
int str_cmp(const char*,const char*);

void generar_archivo_de_alumnos(FILE*,FILE*,FILE*,t_fecha*);
void grabar_registro_en_errores(t_alumno*,FILE*);

void normalizar_apellido_nombre(char*);
int comparacion_de_fechas(t_fecha*,t_fecha*);

void leerarchbin(FILE *);
