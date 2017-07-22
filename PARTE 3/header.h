#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

#include "TDA_índice_estático.h"

#define     IGUAL                   0

#define     DATO_VALIDO(x,li,ls)    ((x)>=(li)&&(x)<=(ls))

#define     ES_BLANCO(x)            ((x)==32)
#define     ES_COMA(x)              ((x)==',')
#define     ES_LETRA(x)             (((x)>='A'&&(x)<='Z')||((x)>='a'&&(x)<='z'))
#define     ES_MAYUSCULA(x)         ((x)>='A'&&(x)<='Z')
#define     ES_MINUSCULA(x)         ((x)>='a'&&(x)<='z')
#define     A_MAYUSCULA(x)          (((x)>='a'&&(x)<='z')?((x)-32):(x))
#define     A_MINUSCULA(x)          (((x)>='A'&&(x)<='Z')?((x)+32):(x))

typedef int(*t_cmp)(const void*,const void*);

int fecha_valida(t_fecha*);
int cant_dias_mes(int,int);
int bisiesto(int);
void ingresa_fecha(t_fecha*);

char *str_cpy(char*,const char*);
char *str_cat(char*,const char*);
int str_cmp(const char*,const char*);
char *str_chr(char*,int);
char *str_tok(char*,const char*);

void menu(FILE*,t_indice*,t_fecha*);
int opcion_del_menu(void);
int opcion_del_submenu(void);
void mostrar_registro(t_dato*);

void normalizar_apellido_nombre(char*);
int comparacion_de_fechas(t_fecha*,t_fecha*);
int comparar_alumnos_por_dni(const void*,const void*);
