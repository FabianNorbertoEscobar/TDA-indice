#include "header.h"

int main()
{
    char path_bin[35],path_idx[35];
    FILE *pf;

    t_indice indice;

    t_fecha fecha_proceso;

    setlocale(LC_CTYPE,"Spanish");
    system("COLOR 70");

    printf("\n\t\t\t *****************");
    printf("\n\t\t\t * MANTENIMIENTO * \a\a");
    printf("\n\t\t\t ***************** \n\n");

    printf("\n Para comenzar con el mantenimiento, necesitamos los datos \n de un archivo binario ya existente \n");
    printf("\n Para dicho archivo debe haber sido generado un archivo de �ndice, previamente \n");
    printf("\n\n Ingrese el path (nombre y extensi�n) del archivo binario : \n\n\t");
    fflush(stdin);
    gets(path_bin);
    fflush(stdin);

    //abro el archivo binario --> de aqu� sacar� los registros con los que trabajaremos

    //primero, verifico la existencia del archivo, por lo que debo abrirlo en modo lectura

    pf=fopen(path_bin,"rb");
    if(!pf)
    {
        printf("\n\n No se ha podido leer el archivo binario. \n\n Programa evacuado \n\n\a\a");
        exit(EXIT_FAILURE);
    }

    //si el archivo existe, lo cierro y reabro de esta forma para poder actualizarlo
    fclose(pf);
    pf=fopen(path_bin,"r+b");            // o bien podr�a haber usado la funci�n freopen
    if(!pf)
    {
        printf("\n\n No se ha podido reabrir el archivo binario. \n\n Programa evacuado \n\n\a\a");
        exit(EXIT_FAILURE);
    }

    //genero el path del archivo del �ndice, a partir del nombre del archivo
    str_cat(str_cpy(path_idx,str_tok(path_bin,".")),".idx");

    //creo un �ndice y lo cargo a partir del archivo cuyo path acabo de generar

    ind_crear(&indice);
    if(!ind_cargar(&indice,path_idx))
    {
        printf("\n\n No se ha podido cargar el �ndice en memoria. \n\n\t\t Programa evacuado \n\n\a\a");
        exit(EXIT_FAILURE);
    }

    printf("\n FECHA DE PROCESO \n");
    ingresa_fecha(&fecha_proceso);

    //todo el proceso de mantenimiento se llevar� a cabo en el siguiente men�
    menu(pf,&indice,&fecha_proceso);

    fclose(pf);
    printf("\n\n Se ha cerrado exitosamente el archivo binario actualizado \n");

    //finalmente, grabamos el �ndice actualizado en un archivo binario
    ind_grabar(&indice,path_idx);
    printf("\n\n Se ha grabado en el archivo \"%s\" el �ndice actualizado \n\n",path_idx);

    //esto solo lo escribo porque el enunciado solicitaba que se libere la memoria del �ndice cuando ya no se lo ulilizaba
    //aqu� no cumple ninguna funci�n ya que esta primitiva no corresponde a la implementaci�n est�tica del TDA
    ind_liberar(&indice);
    printf("\n\n La memoria del �ndice ha sido liberada \n");

    printf("\n\n \t\t\t\t\t Fin del programa... \n\n\a\a");
    getch();
    return 0;
}
