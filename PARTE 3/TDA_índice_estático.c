#include "TDA_índice_estático.h"

#include<stdio.h>
#include<stdlib.h>

void ind_crear(t_indice *ind)
{
    ind->tope=0;
    ind->hay_cola=0;
}

int ind_insertar(t_indice *ind,const t_reg_indice *reg_ind)
{
    if(ind->tope==TAM)
        return INDICE_LLENO;

    if(ind->tope!=0)
    {
        t_reg_indice aux1,aux2;

        unsigned pos=0;
        while(pos<ind->tope&&ind->registro[pos].dni<reg_ind->dni)
            pos++;

        if(pos<ind->tope&&ind->registro[pos].dni==reg_ind->dni)
            return DUPLICADO;

        aux1=ind->registro[pos];
        ind->registro[pos]=*reg_ind;
        pos++;

        while(pos < ind->tope)
        {
            aux2=ind->registro[pos];
            ind->registro[pos]=aux1;
            aux1=aux2;

            pos++;
        }

        ind->registro[pos]=aux1;
    }
    else
        ind->registro[ind->tope]=*reg_ind;

    ind->tope++;
    return OK;
}

int ind_eliminar(t_indice *ind,t_reg_indice *reg_ind)
{
    unsigned pos=0;

    if(ind->tope==0)
        return INDICE_VACIO;

    while(pos<ind->tope&&ind->registro[pos].dni<reg_ind->dni)
        pos++;

     if(pos==ind->tope||(pos<ind->tope&&ind->registro[pos].dni!= reg_ind->dni))
        return NO_ENCONTRADO;

    while(pos<ind->tope)
    {
        ind->registro[pos]=ind->registro[pos+1];
        pos++;
    }

    ind->tope--;
    return OK;
}

int ind_buscar(const t_indice *ind,t_reg_indice *reg_ind)
{
    unsigned pos=0;

    if(ind->tope==0)
        return INDICE_VACIO;

    while(pos<ind->tope&&ind->registro[pos].dni<reg_ind->dni )
        pos++;

    if(pos==ind->tope||(pos<ind->tope&&ind->registro[pos].dni!=reg_ind->dni))
        return NO_ENCONTRADO;

    *reg_ind = ind->registro[pos];
    return OK;
}

int ind_cargar(t_indice *ind,const char *path)
{
    FILE *pf;
    unsigned pos=0;

    pf=fopen(path,"rb");
    if(!pf)
        return ARCHIVO_CORRUPTO;

    fread(&ind->registro[pos],sizeof(t_reg_indice),1,pf);
    while(!feof(pf))
    {
        pos++;
        fread(&ind->registro[pos],sizeof(t_reg_indice),1,pf);
    }

    fclose(pf);
    ind->tope=pos;
    return OK;
}

int ind_grabar(const t_indice *ind,const char *path)
{
    FILE *pf;
    unsigned pos=0;

    if(ind->tope==0)
        return INDICE_VACIO;

    pf=fopen(path,"wb");
    if(!pf)
        return ARCHIVO_CORRUPTO;

    while(pos<ind->tope)
    {
        fwrite(&ind->registro[pos],sizeof(t_reg_indice),1,pf);
        pos++;
    }

    fclose(pf);
    return OK;
}

void ind_vaciar(t_indice *ind)
{
    ind->tope=0;
    ind->hay_cola=0;
}

int ind_primero(t_indice *ind,t_reg_indice *reg_ind)
{
    int i=0;

    if(ind->tope==0)
        return INDICE_VACIO;

    if(ind->hay_cola==1)
        vaciar_cola(&ind->cola);

    crear_cola(&ind->cola);
    ind->hay_cola=1;

    while(i<ind->tope)
    {
        if(cola_llena(&ind->cola))
            return COLA_LLENA;

        acolar(&ind->cola,(t_dato*)&ind->registro[i]);
        i++;
    }

    desacolar(&ind->cola,(t_dato*)reg_ind);
    return OK;
}

int ind_siguiente(t_indice *ind,t_reg_indice *reg_ind)
{
    if(ind->tope==0)
        return INDICE_VACIO;

    if(ind->hay_cola==0)
        return COLA_VACIA;

    desacolar(&ind->cola,(t_dato*)reg_ind);

    if(cola_vacia(&ind->cola))
        ind->hay_cola=0;

    return OK;
}

int ind_fin(t_indice *ind)
{
    if(ind->tope==0)
        return INDICE_VACIO;

    if(ind->hay_cola==1)
        return COLA_LLENA;

    return OK;
}

void ind_liberar(t_indice *indice)
{
    ///Esta primitiva no aplica a la implementación estática del TDA índice
}
