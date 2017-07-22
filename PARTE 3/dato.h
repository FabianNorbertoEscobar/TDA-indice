#define     TAM     100

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

typedef t_alumno t_dato;
