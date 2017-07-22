#include "header.h"

int main()
{
    t_fecha fecha_proceso;
    char nombre[31],path_txt[35],path_bin[35];

    FILE *pf_escritura;
    FILE *pf_lectura;
    FILE *pf_errores;

    setlocale(LC_CTYPE,"Spanish");
    system("COLOR 70");

    printf("\n ************************************");
    printf("\n * GENERACION DE ARCHIVO DE ALUMNOS * \a\a");
    printf("\n ************************************ \n\n");

    printf("\n FECHA DE PROCESO \n");
    ingresa_fecha(&fecha_proceso);

    printf("\n Para generar el archivo binario de alumnos, tomaremos los datos \n de un archivo de texto ya existente \n");
    printf("\n\n Ingrese el nombre del archivo de texto (NO el path. Nombre SIN extension): \n\n\t\a\a");
    fflush(stdin);
    gets(nombre);

    //genero los paths de los archivos de lectura y escritura, a partir del nombre del archivo

    str_cat(str_cpy(path_txt,nombre),".txt");
    str_cat(str_cpy(path_bin,nombre),".dat");

    //abro el archivo de texto --> de este archivo tomaré los registros

    pf_lectura=fopen(path_txt,"rt");
    if(!pf_lectura)
    {
        printf("\n\n No se ha podido leer el archivo de texto. \n\n Programa evacuado \n\n\a\a");
        exit(EXIT_FAILURE);
    }

    //creo el archivo binario --> en este archivo pondré los registros válidos

    pf_escritura=fopen(path_bin,"wb");
    if(!pf_escritura)
    {
        printf("\n\n No se ha podido crear el archivo binario. \n\n Programa evacuado \n\n\a\a");
        fclose(pf_lectura);
        exit(EXIT_FAILURE);
    }

    //creo el archivo de errores --> en este archivo pondré los registros inválidos

    pf_errores=fopen("errores.txt","wt");
    if(!pf_errores)
    {
        printf("\n\n No se ha podido crear el archivo de texto para ERRORES. \n\n Programa evacuado \n\n\a\a");
        fclose(pf_lectura);
        fclose(pf_lectura);
        remove(path_txt);
        exit(EXIT_FAILURE);
    }

    generar_archivo_de_alumnos(pf_lectura,pf_escritura,pf_errores,&fecha_proceso);

    fclose(pf_lectura);
    fclose(pf_escritura);
    fclose(pf_errores);

    printf("\n\n El archivo de ALUMNOS fue generado exitosamente...");
    printf("\n\n También se ha generado un archivo de ERRORES, donde aparecen los registros \
    \n que traían errores desde el archivo de texto por lo que fueron ignorados. \n");

    printf("\n\n \t\t\t\t\t Fin del programa... \n\n\a\a");
    getch();
    return 0;
}
