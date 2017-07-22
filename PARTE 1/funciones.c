#include "header.h"

int fecha_valida(t_fecha *f)
{
    return ((f->a >= 1600) && (f->m >= 1) && (f->m <= 12) && (f->d >= 1) && (f->d <= cant_dias_mes(f->m,f->a)))?1:0;
}

int cant_dias_mes(int m,int a)
{
    int dias[]= {31,28,31,30,31,30,31,31,30,31,30,31};
    return (m==2)?28+bisiesto(a):dias[m-1];
}

int bisiesto(int a)
{
    return ((a%4==0&&a%100!=0)||a%400==0)?1:0;
}

void ingresa_fecha(t_fecha *f)
{
    int bandera=0;

    printf("\n Ingrese la fecha en formato dd/mm/aaaa: \t");

    do
    {
        if(bandera==1)
            printf("\n La fecha ingresada no existe. Reingrésela: \t\a\a");

        scanf("%d/%d/%d",&f->d,&f->m,&f->a);
        bandera=1;
    }
    while(!fecha_valida(f));
}

char *str_cpy(char *destino,const char *origen)
{
    char *s=destino;

    while(*origen)
    {
        *destino=*origen;
        destino++;
        origen++;
    }

    *destino='\0';
    return s;
}

char *str_cat(char *destino,const char *origen)
{
    char *s=destino;

    while(*destino)
        destino++;

    while(*origen)
    {
        *destino=*origen;
        destino++;
        origen++;
    }

    *destino='\0';
    return s;
}

int str_cmp(const char *s1,const char *s2)
{
    while(*s1==*s2&&*s1&&*s2)
    {
        s1++;
        s2++;
    }

    return *s1-*s2;
}

void generar_archivo_de_alumnos(FILE *pf_lectura,FILE *pf_escritura,FILE *pf_errores,t_fecha *fecha_proceso)
{
    t_alumno registro;

    //cadena y puntero a utilizar para tratar la fecha aprobación de última materia
    char cadena[11],*aux=cadena;

    //fecha usada para una de las validaciones
    t_fecha fecha_aux=*fecha_proceso;
    fecha_aux.a-=10;

    //rebobino los archivos por si alguno hubiese llegado a esta función con el puntero en otro lugar que no sea el principio
    //--> de todas formas, este no es el caso
    rewind(pf_lectura);
    rewind(pf_escritura);
    rewind(pf_errores);

    //lectura de los registros

    while(fscanf(pf_lectura,"%ld|%[^|]|%d/%d/%d|%c|%d/%d/%d|%[^|]|%d|%[^\n]",&registro.dni,registro.apellido_nombre,\
            &registro.f_nacimiento.d,&registro.f_nacimiento.m,&registro.f_nacimiento.a,&registro.sexo,\
            &registro.f_ingreso.d,&registro.f_ingreso.m,&registro.f_ingreso.a,registro.carrera,&registro.materias_aprob,cadena)!=EOF)
    {
        //validación de los registros
        //si alguno de los campos del registro levantado no es válido, grabo el registro en el archivo de errores
        //y luego salto hacia atrás, al inicio del bucle --> leeré el siguiente registro

        if(!DATO_VALIDO(registro.dni,10001,99999999))
        {
            //normalizar_apellido_nombre(registro.apellido_nombre);//lo aguegue para que el archivo de error este normalizado
            grabar_registro_en_errores(&registro,pf_errores);
            continue;
        }

        //este campo no lo valido --->>> solo lo normalizo
        normalizar_apellido_nombre(registro.apellido_nombre);

        if(!fecha_valida(&registro.f_nacimiento)||comparacion_de_fechas(&registro.f_nacimiento,&fecha_aux)>=0)
        {
            grabar_registro_en_errores(&registro,pf_errores);
            continue;
        }

        if(registro.sexo!='F'&&registro.sexo!='M')
        {
            grabar_registro_en_errores(&registro,pf_errores);
            continue;
        }

        if(!fecha_valida(&registro.f_ingreso)||comparacion_de_fechas(&registro.f_ingreso,fecha_proceso)>0||\
                comparacion_de_fechas(&registro.f_ingreso,&registro.f_nacimiento)<=0)
        {
            grabar_registro_en_errores(&registro,pf_errores);
            continue;
        }

        if(str_cmp(registro.carrera,"INF")!=0&&str_cmp(registro.carrera,"ELE")!=0&&str_cmp(registro.carrera,"IND")!=0&&\
                str_cmp(registro.carrera,"ECO")!=0&&str_cmp(registro.carrera,"DER")!=0&&str_cmp(registro.carrera,"ADM")!=0&&\
                str_cmp(registro.carrera,"MED")!=0&&str_cmp(registro.carrera,"EDF")!=0&&str_cmp(registro.carrera,"FIL")!=0)
        {
            grabar_registro_en_errores(&registro,pf_errores);
            continue;
        }

        if(registro.materias_aprob<0)
        {
            grabar_registro_en_errores(&registro,pf_errores);
            continue;
        }

        if(*cadena!='\0')
        {
            while(*aux && ES_BLANCO(*aux))
                aux++;

            if(*aux) //
            {
                sscanf(cadena,"%d/%d/%d",&registro.f_ult_mat_aprob.d,&registro.f_ult_mat_aprob.m,&registro.f_ult_mat_aprob.a);

                if(!fecha_valida(&registro.f_ult_mat_aprob)||comparacion_de_fechas(&registro.f_ult_mat_aprob,&registro.f_ingreso)<=0||\
                        comparacion_de_fechas(&registro.f_ult_mat_aprob,fecha_proceso)>0)
                {
                    grabar_registro_en_errores(&registro,pf_errores);
                    continue;
                }
            }
            else
                registro.f_ult_mat_aprob=registro.f_ingreso;
        }

        //una vez realizadas todas las validaciones, si el registro no tiene errores, doy de alta a los últimos dos campos
        registro.estado='R';

        registro.f_baja.d=31;
        registro.f_baja.m=12;
        registro.f_baja.a=9999;

        //finalmente grabo el registro en el archivo de alumnos

        fwrite(&registro,sizeof(t_alumno),1,pf_escritura);
    }
}

void grabar_registro_en_errores(t_alumno *registro,FILE *pf)
{
    fprintf(pf,"%ld|%s|%d/%d/%d|%c|%d/%d/%d|%s|%d|%d/%d/%d\n",\
            registro->dni,registro->apellido_nombre,registro->f_nacimiento.d,registro->f_nacimiento.m,registro->f_nacimiento.a,\
            registro->sexo,registro->f_ingreso.d,registro->f_ingreso.m,registro->f_ingreso.a,\
            registro->carrera,registro->materias_aprob,registro->f_ult_mat_aprob.d,registro->f_ult_mat_aprob.m,registro->f_ult_mat_aprob.a);
}

void normalizar_apellido_nombre(char *s)
{
    char cadena[40],*aux=cadena,*inicio_s=s;

    while(ES_BLANCO(*s))
        s++;

    *aux=A_MAYUSCULA(*s);
    aux++;
    s++;

    while(ES_LETRA(*s))
    {
        *aux=A_MINUSCULA(*s);
        aux++;
        s++;
    }

    while(!ES_LETRA(*s))
        s++;

    *aux=',';
    aux++;

    while(*s)
    {
        *aux=' ';
        aux++;

        *aux=A_MAYUSCULA(*s);
        aux++;
        s++;

        while(ES_LETRA(*s))
        {
            *aux=A_MINUSCULA(*s);
            aux++;
            s++;
        }

        while(*s && ES_BLANCO(*s))
            s++;
    }

    *aux='\0';

    s=inicio_s;
    str_cpy(s,cadena);
}

int comparacion_de_fechas(t_fecha *fecha1,t_fecha *fecha2)
{
    int comparador;

    if((comparador=fecha1->a-fecha2->a)==0)
        if((comparador=fecha1->m-fecha2->m)==0)
            if((comparador=fecha1->d-fecha2->d)==0)
                return IGUAL;

    return comparador;
}
