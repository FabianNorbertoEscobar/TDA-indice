#include "header.h"

int fecha_valida(t_fecha *f)
{
    return (f->a>=1600&&f->m>=1&&f->m<=12&&f->d>=1&&f->d<=cant_dias_mes(f->m,f->a))?1:0;
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

char *str_chr(char *s,int c)
{
    while(*s&&*s!=c)
        s++;

    return (*s)?s:NULL;
}

char *str_tok(char *s, const char *sep)
{
    static char *sig;
    char *aux;

    if(s)
        sig=s;

    while(*sig&&str_chr((char*)sep,*sig))
        sig++;

    aux=sig;

    while(*sig&&!str_chr((char*)sep,*sig))
        sig++;

    if(*sig)
        *sig++='\0';

    return (*aux)?aux:NULL;
}

void menu(FILE *pf,t_indice *indice,t_fecha *fecha_proceso)
{
    //estructuras de tipos alumno y registro de índice
    t_alumno registro;
    t_reg_indice registro_indice;

    //opción ingresada y bandera
    int op,bandera;

    //cadena y puntero a utilizar para tratar la fecha de aprobación de última materia
    char cadena[11],*aux=cadena;

    //fecha usada para una de las validaciones
    t_fecha fecha_aux=*fecha_proceso;
    fecha_aux.a-=10;

    //muestro las opciones del menu y obtengo una opción válida
    fflush(stdin);
    op=opcion_del_menu();

    while(op)
    {
        switch(op)
        {
        case 1:
            system("cls");
            fflush(stdin);
            op=opcion_del_submenu();

            while(op)
            {
                system("cls");
                switch(op)
                {
                case 1:
                    printf("\n\n ALTA de un registro \n\a\a");

                    //ingreso del registro completo
                    printf("\n Ingrese todos los datos del registro a dar de alta:");

                    printf("\n\n DNI: \t\t");
                    scanf("%ld",&registro.dni);

                    //verifico que el dni (CLAVE) no esté en el índice
                    registro_indice.dni=registro.dni;
                    if(ind_buscar(indice,&registro_indice))
                    {
                        printf("\n\n El DNI ingresado ya figura en el índice cargado en memoria \n\n Alta cancelada \n \a\a");
                        break;
                    }

                    printf("\n\n Apellido, Nombre/s: \n\n\t");
                    fflush(stdin);
                    gets(registro.apellido_nombre);

                    printf("\n\n Fecha de nacimiento: \n");
                    printf("\n Ingrese la fecha en formato dd/mm/aaaa: \t");
                    scanf("%d/%d/%d",&registro.f_nacimiento.d,&registro.f_nacimiento.m,&registro.f_nacimiento.a);

                    printf("\n\n Sexo (F ó M): \t\t");
                    fflush(stdin);
                    registro.sexo=getchar();

                    printf("\n\n Fecha de ingreso: \n");
                    printf("\n Ingrese la fecha en formato dd/mm/aaaa: \t");
                    scanf("%d/%d/%d",&registro.f_ingreso.d,&registro.f_ingreso.m,&registro.f_ingreso.a);

                    printf("\n\n Carrera (INF, ELE, IND, ECO, DER, ADM, MED, EDF, FIL): \n\n\t");
                    fflush(stdin);
                    gets(registro.carrera);

                    printf("\n\n Cantidad de materias aprobadas: \t\t");
                    scanf("%d",&registro.materias_aprob);

                    printf("\n\n Fecha de aprobación de última materia: \n");
                    printf("\n Ingrese la fecha en formato dd/mm/aaaa: \t");
                    fflush(stdin);
                    gets(cadena);

                    //validación del registro

                    //si alguno de los campos del registro levantado no es válido, se ignora el registro y se da por cancelada la operación

                    if(!DATO_VALIDO(registro.dni,10001,99999999))
                    {
                        printf("\n\n El registro ingresado presenta errores. \n\n Alta cancelada \n \a\a");
                        break;
                    }

                    //este campo no lo valido --->>> solo lo normalizo
                    normalizar_apellido_nombre(registro.apellido_nombre);

                    if(!fecha_valida(&registro.f_nacimiento)||comparacion_de_fechas(&registro.f_nacimiento,&fecha_aux)>=0)
                    {
                        printf("\n\n El registro ingresado presenta errores. \n\n Alta cancelada \n \a\a");
                        break;
                    }

                    if(registro.sexo!='F'&&registro.sexo!='M')
                    {
                        printf("\n\n El registro ingresado presenta errores. \n\n Alta cancelada \n \a\a");
                        break;
                    }

                    if(!fecha_valida(&registro.f_ingreso)||comparacion_de_fechas(&registro.f_ingreso,fecha_proceso)>0||\
                            comparacion_de_fechas(&registro.f_ingreso,&registro.f_nacimiento)<=0)
                    {
                        printf("\n\n El registro ingresado presenta errores. \n\n Alta cancelada \n \a\a");
                        break;
                    }

                    if(str_cmp(registro.carrera,"INF")!=0&&str_cmp(registro.carrera,"ELE")!=0&&str_cmp(registro.carrera,"IND")!=0&&\
                            str_cmp(registro.carrera,"ECO")!=0&&str_cmp(registro.carrera,"DER")!=0&&str_cmp(registro.carrera,"ADM")!=0&&\
                            str_cmp(registro.carrera,"MED")!=0&&str_cmp(registro.carrera,"EDF")!=0&&str_cmp(registro.carrera,"FIL")!=0)
                    {
                        printf("\n\n El registro ingresado presenta errores. \n\n Alta cancelada \n \a\a");
                        break;
                    }

                    if(registro.materias_aprob<0)
                    {
                        printf("\n\n El registro ingresado presenta errores. \n\n Alta cancelada \n \a\a");
                        break;
                    }

                    if(*cadena!='\0')
                    {
                        while(*aux&&ES_BLANCO(*aux))
                            aux++;
                        if(*aux)
                        {
                            sscanf(cadena,"%d/%d/%d",&registro.f_ult_mat_aprob.d,&registro.f_ult_mat_aprob.m,&registro.f_ult_mat_aprob.a);
                            if(!fecha_valida(&registro.f_ult_mat_aprob)||comparacion_de_fechas(&registro.f_ult_mat_aprob,&registro.f_ingreso)<=0||\
                                    comparacion_de_fechas(&registro.f_ult_mat_aprob,fecha_proceso)>0)
                            {
                                printf("\n\n El registro ingresado presenta errores. \n\n Alta cancelada \n \a\a");
                                break;
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

                    //posiciono el puntero del archivo al final para contar la cantidad de registros y de allí deducir el número de registro del nuevo alumno
                    fseek(pf,0L,SEEK_END);
                    registro_indice.nro_reg=ftell(pf)/sizeof(t_alumno);

                    //inserto el registro en el índice
                    if(!ind_insertar(indice,&registro_indice))
                    {
                        printf("\n\n No hay lugar para insertar un nuevo registro en el índice \n\t\t Alta cancelada \n\n\a\a");
                        break;
                    }

                    //grabo el registro al final del archivo binario
                    fseek(pf,0L,SEEK_END);
                    fwrite(&registro,sizeof(t_alumno),1,pf);

                    printf("\n\n El registro fue dado de alta exitosamente \n\n\a\a");
                    break;

                case 2:
                    printf("\n\n BAJA de un registro \n\a\a");

                    //ingreso de la clave que se quiere dar de baja
                    printf("\n\n Ingrese el DNI del registro que desea dar de baja: \n\n\t");
                    scanf("%ld",&registro_indice.dni);

                    //verifico que la clave figure en el índice
                    if(!ind_buscar(indice,&registro_indice))
                    {
                        printf("\n\n El registro con el DNI ingresado no fue encontrado en el índice. \n\n Baja cancelada \n\n\a\a");
                        break;
                    }

                    //me coloco en la posición del archivo que contiene el registro deseado y lo leo
                    //avanzo el número de registro, ya que dicho campo, se hizo comenzar de cero en la carga -> no se debe restar uno
                    fseek(pf,registro_indice.nro_reg*sizeof(t_alumno),SEEK_SET);
                    fread(&registro,sizeof(t_alumno),1,pf);

                    //si corresponde, lo doy de baja
                    if(registro.estado=='B')
                    {
                        printf("\n\n El registro no se puede dar de baja porque ya está dado de baja. Baja cancelada \n\n\a\a");
                        break;
                    }
                    registro.estado='B';

                    //la fecha de baja será la fecha de proceso
                    registro.f_baja=*fecha_proceso;

                    //retrocedo el puntero del archivo, ya que luego de la lectura se movió y grabo el registro actualizado
                    fseek(pf,-sizeof(t_alumno),SEEK_CUR);
                    fwrite(&registro,sizeof(t_alumno),1,pf);

                    //y elimino el registro del índice
                    ind_eliminar(indice,&registro_indice);

                    printf("\n\n El registro fue dado de baja exitosamente \n\n\a\a");
                    break;
                }

                getch();
                fflush(stdin);
                op=opcion_del_submenu();
            }
            break;

        case 2:

            system("cls");
            //rebobino el archivo binario
            rewind(pf);

            //con esta bandera, informaré cuando no hay registros que se hayan dado de baja
            bandera=0;

            printf("\n\n LISTA DE DADOS DE BAJA \n");

            //debo utilizar el archivo ya que necesito mostrar los registros en el orden en que allí se encuentran
            //y además de ello, es el único lugar en el que puedo ver quiénes son los registros que están dados de baja

            //lectura del archivo
            fread(&registro,sizeof(t_alumno),1,pf);

            while(!feof(pf))
            {
                //si el registro levantado está dado de baja, lo muestro
                if(registro.estado=='B')
                {
                    mostrar_registro(&registro);
                    bandera=1;
                }

                //leo otro registro del archivo
                fread(&registro,sizeof(t_alumno),1,pf);
            }

            //si no mostré nada, entonces aclaro que no hay registros dados de baja
            if(bandera==0)
                printf("\n\n No hay registros que se hayan dado de baja \n\n\a\a");

            getch();
            break;

        case 3: //rebobino el archivo binario

            system("cls");

            printf("\n\n LISTA EN ORDEN (sin los dados de baja) \n");

            //aquí puedo utilizar las primitivas primero, siguiente y fin del TDA índice
            // ya que en el índice, los registros están ordenados por dni y además están activos

            //veo al primero del índice
            ind_primero(indice,&registro_indice);

            //me muevo a su posición en el archivo (no tengo que restar 1 ya que el número de registro se hizo comenzar desde cero en la carga)
            fseek(pf,registro_indice.nro_reg*sizeof(t_alumno),SEEK_SET);
            fread(&registro,sizeof(t_alumno),1,pf);

            //muestro el registro
            mostrar_registro(&registro);

            while(!ind_fin(indice))     //mientras no llegue al fin del índice
            {
                //veo al siguiente del índice
                ind_siguiente(indice,&registro_indice);

                //me muevo a su posición en el archivo (no tengo que restar 1 ya que el número de registro se hizo comenzar desde cero en la carga)
                fseek(pf,registro_indice.nro_reg*sizeof(t_alumno),SEEK_SET);
                fread(&registro,sizeof(t_alumno),1,pf);

                //muestro el registro
                mostrar_registro(&registro);
            }

            getch();
            break;
        }

        fflush(stdin);
        op=opcion_del_menu();
    }
}

int opcion_del_menu(void)
{
    int op,bandera=0;

    do
    {
        if(bandera==1)
        {
            printf("\n\n La opción ingresada no existe \n\a\a");
            getch();
        }

        system("cls");
        printf("\n\n \t\t\t ***** MENU ***** \n\a\a");
        printf("\n\n Elija una de las siguientes opciones: \n");
        printf("\n 1- Efectuar mantenimiento \n");
        printf("\n 2- Listar los dados de baja \n");
        printf("\n 3- Listarlos en orden (sin los dados de baja) \n");
        printf("\n\n 0- SALIR \n");

        printf("\n\n\t\t\t Opción: \t");
        fflush(stdin);
        scanf("%d",&op);
        bandera=1;
    }
    while(!DATO_VALIDO(op,0,3));

    return op;
}

int opcion_del_submenu(void)
{
    int op,bandera=0;

    do
    {
        if(bandera==1)
        {
            printf("\n\n La opción ingresada no existe \n\a\a");
            getch();
        }

        system("cls");
        printf("\n\n\t\t ***** SUBMENU - EFECTUAR MANTENIMIENTO ***** \n\a\a");
        printf("\n\n Elija una de las siguientes opciones: \n");
        printf("\n 1- Alta \n");
        printf("\n 2- Baja \n");
        printf("\n\n 0- RETORNAR AL MENU PRINCIPAL \n");

        printf("\n\n\t\t\t Opción: \t");
        fflush(stdin);
        scanf("%d",&op);
        bandera=1;
    }
    while(!DATO_VALIDO(op,0,2));

    return op;
}

void mostrar_registro(t_dato *d)
{
    printf("\n\n REGISTRO \n");
    printf("\n DNI: \t\t\t\t\t\t %ld",d->dni);
    printf("\n Apellido y nombre/s: \t\t\t\t %s",d->apellido_nombre);
    printf("\n Fecha de nacimiento: \t\t\t\t %d/%d/%d",d->f_nacimiento.d,d->f_nacimiento.m,d->f_nacimiento.a);
    printf("\n Sexo: \t\t\t\t\t\t %c",d->sexo);
    printf("\n Fecha de ingreso: \t\t\t\t %d/%d/%d",d->f_ingreso.d,d->f_ingreso.m,d->f_ingreso.a);
    printf("\n Carrera: \t\t\t\t\t %s",d->carrera);
    printf("\n Cantidad de materias aprobadas: \t\t %d",d->materias_aprob);
    printf("\n Fecha de aprobación de última materia: \t %d/%d/%d",d->f_ult_mat_aprob.d,d->f_ult_mat_aprob.m,d->f_ult_mat_aprob.a);
    printf("\n Estado: \t\t\t\t\t %c",d->estado);
    printf("\n Fecha de baja: \t\t\t\t %d/%d/%d",d->f_baja.d,d->f_baja.m,d->f_baja.a);
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

int comparar_alumnos_por_dni(const void *v1,const void *v2)
{
    t_dato *e1=(t_dato*)v1,*e2=(t_dato*)v2;
    return e1->dni-e2->dni;
}
