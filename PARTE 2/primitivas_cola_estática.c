#include "primitivas_cola_estática.h"

void crear_cola(t_cola *c)
{
    c->pri=0;
    c->ult=-1;
}

int cola_llena(const t_cola *c)
{
    return (c->ult+1)%TAM==c->pri&&c->ult!=-1;
}

int acolar(t_cola *c,const t_dato *d)
{
    if((c->ult+1)%TAM==c->pri&&c->ult!=-1)
        return COLA_LLENA;

    c->ult=(c->ult+1)%TAM;
    c->cola[c->ult]=*d;

    return OK;
}

int cola_vacia(const t_cola *c)
{
    return c->ult==-1;
}

int desacolar(t_cola *c,t_dato *d)
{
    if(c->ult==-1)
        return COLA_VACIA;

    *d=c->cola[c->pri];

    if(c->pri==c->ult)
    {
        c->pri=0;
        c->ult=-1;
    }
    else
        c->pri=(c->pri+1)%TAM;

    return OK;
}

int ver_primero_en_cola(const t_cola *c,t_dato *d)
{
    if(c->ult==-1)
        return COLA_VACIA;

    *d=c->cola[c->pri];
    return OK;
}

int ver_ultimo_en_cola(const t_cola *c,t_dato *d)
{
    if(c->ult==-1)
        return COLA_VACIA;

    *d=c->cola[c->ult];
    return OK;
}

void vaciar_cola(t_cola *c)
{
    c->pri=0;
    c->ult=-1;
}
