#include "registro.h"
#include "primitivas_cola_estática.h"

#define         INDICE_VACIO            0
#define         INDICE_LLENO            0
#define         DUPLICADO               0
#define         NO_ENCONTRADO           0
#define         ARCHIVO_CORRUPTO        0
#define         OK                      1

typedef struct
{
    t_cola cola;
    unsigned hay_cola;
    t_reg_indice registro[TAM];
    unsigned tope;//primera posición libre
} t_indice;

void ind_crear(t_indice*);
int ind_insertar(t_indice*,const t_reg_indice*);
int ind_eliminar(t_indice*,t_reg_indice*);
int ind_buscar(const t_indice*,t_reg_indice*);
int ind_cargar(t_indice*,const char*);
int ind_grabar(const t_indice*,const char*);
void ind_vaciar(t_indice*);
int ind_primero(t_indice*,t_reg_indice*);
int ind_siguiente(t_indice*,t_reg_indice*);
int ind_fin(t_indice*);
void ind_liberar(t_indice*);
