# TDA Índice — Trabajo Práctico Integrador

Repositorio de prácticas en lenguaje C organizado en tres partes progresivas. El proyecto modela la carga, validación, almacenamiento y mantenimiento de registros de alumnos mediante archivos binarios, un índice por DNI y estructuras de datos abstractas.

> El enunciado original se incluye en `TRABAJO PRÁCTICO INTEGRADOR.doc`. Este README resume el funcionamiento observado en el código y en los archivos de datos incluidos.

## Contenido

- [Descripción general](#descripción-general)
- [Stack tecnológico](#stack-tecnológico)
- [Evolución del práctico](#evolución-del-práctico)
- [Funcionalidades](#funcionalidades)
- [Modelo de datos](#modelo-de-datos)
- [Estructura del repositorio](#estructura-del-repositorio)
- [Cómo ejecutar](#cómo-ejecutar)
- [Formatos de archivo](#formatos-de-archivo)
- [Prácticas y conceptos aplicados](#prácticas-y-conceptos-aplicados)
- [Notas técnicas](#notas-técnicas)

## Descripción general

El sistema trabaja con alumnos identificados por DNI y permite:

- convertir un archivo de texto con datos maestros en un archivo binario;
- separar registros válidos e inválidos;
- crear y mantener un índice estático ordenado por DNI;
- realizar altas y bajas lógicas;
- recorrer y listar alumnos activos o dados de baja;
- persistir el índice actualizado junto con los datos.

El proyecto fue desarrollado como práctica académica, por lo que prioriza la comprensión de archivos, TDA, arreglos, colas y memoria binaria sobre la abstracción de un framework moderno.

## Stack tecnológico

| Componente | Tecnología |
|---|---|
| Lenguaje | C |
| IDE recomendado | Code::Blocks |
| Compilador | GCC / MinGW |
| Archivos maestros | Texto plano delimitado por `\|` |
| Base de datos práctica | Archivo binario `.dat` |
| Indización | Archivo binario `.idx` |
| Entrada y salida | `stdio.h` |
| Herramientas específicas de Windows | `conio.h`, `system("cls")`, `system("COLOR 70")` |
| Proyecto | Archivos `.cbp` de Code::Blocks |

No utiliza bibliotecas externas ni dependencias gestionadas por un paquete.

## Evolución del práctico

### Parte 1 — Generación y validación

La primera etapa lee un archivo de texto, valida cada alumno y genera:

- un archivo binario `.dat` con los registros válidos;
- un archivo `errores.txt` con los registros rechazados.

También normaliza nombres y apellidos y completa los campos de estado y baja del nuevo registro.

### Parte 2 — Índice estático

La segunda etapa incorpora el TDA índice. Durante la generación:

- cada DNI válido se vincula con su número de registro;
- las entradas se mantienen ordenadas por DNI;
- el índice completo se guarda en un archivo `.idx`;
- se reutiliza una cola estática como soporte de recorrido.

El índice tiene una capacidad máxima de `100` entradas.

### Parte 3 — Mantenimiento

La tercera etapa carga el archivo binario y el índice, y ofrece un menú para:

- dar de alta nuevos alumnos;
- dar de baja alumnos existentes;
- listar los registros dados de baja;
- listar los registros activos en orden de DNI;
- persistir el índice actualizado al salir.

Las bajas son lógicas: el registro permanece en el `.dat`, cambia su estado a `B` y registra la fecha de proceso.

## Funcionalidades

- entrada interactiva de la fecha de proceso;
- validación de fechas reales, incluyendo años bisiestos;
- validación del DNI dentro del rango establecido;
- validación de sexo y carreras admitidas;
- validación de fechas de nacimiento, ingreso y última materia aprobada;
- normalización de nombres y apellidos;
- control de DNI duplicado;
- baja lógica sin eliminar físicamente el registro;
- acceso directo a registros mediante `nro_reg`;
- búsqueda e inserción ordenada en el índice;
- recorrido del índice mediante una cola estática;
- manejo de archivos binarios con `fread`, `fwrite`, `fseek` y `rewind`;
- separación de datos válidos y registros con errores.

## Modelo de datos

### Alumno

Cada alumno contiene:

| Campo | Tipo conceptual | Uso |
|---|---|---|
| DNI | `long` | clave de identificación |
| Apellido y nombres | `char[40]` | datos personales |
| Fecha de nacimiento | `t_fecha` | validación y datos históricos |
| Sexo | `char` | `F` o `M` |
| Fecha de ingreso | `t_fecha` | fecha académica |
| Carrera | `char[4]` | código de carrera |
| Materias aprobadas | `int` | progreso académico |
| Última materia aprobada | `t_fecha` | fecha académica |
| Estado | `char` | `R` activo o `B` dado de baja |
| Fecha de baja | `t_fecha` | fecha del proceso de baja |

Carreras admitidas:

`INF`, `ELE`, `IND`, `ECO`, `DER`, `ADM`, `MED`, `EDF`, `FIL`.

### Entrada de índice

La entrada de índice relaciona la clave con la ubicación física:

```c
typedef struct
{
    long dni;
    unsigned nro_reg;
} t_reg_indice;
```

Esto permite obtener el número de registro del alumno y posicionar el puntero directamente dentro del archivo `.dat`.

## Estructura del repositorio

```text
.
├── PARTE 1/
│   ├── main.c
│   ├── funciones.c
│   ├── header.h
│   ├── alumnos.txt
│   ├── alumnos.dat
│   ├── errores.txt
│   └── PARTE 1.cbp
├── PARTE 2/
│   ├── main.c
│   ├── funciones.c
│   ├── TDA_índice_estático.{c,h}
│   ├── primitivas_cola_estática.{c,h}
│   ├── dato.h
│   ├── registro.h
│   ├── alumnos.dat
│   ├── alumnos.idx
│   └── PARTE 2.cbp
├── PARTE 3/
│   ├── main.c
│   ├── funciones.c
│   ├── TDA_índice_estático.{c,h}
│   ├── primitivas_cola_estática.{c,h}
│   ├── dato.h
│   ├── registro.h
│   ├── alumnos.dat
│   ├── alumnos.idx
│   └── PARTE 3.cbp
└── TRABAJO PRÁCTICO INTEGRADOR.doc
```

Cada carpeta incluye el proyecto de Code::Blocks correspondiente, además de archivos binarios y objetos generados durante una compilación de práctica.

## Cómo ejecutar

### Con Code::Blocks

1. Instala Code::Blocks con el compilador GCC/MinGW.
2. Abre `PARTE 1/PARTE 1.cbp`, `PARTE 2/PARTE 2.cbp` o `PARTE 3/PARTE 3.cbp`.
3. Ejecuta **Build and run**.
4. Ejecuta la parte correspondiente desde su carpeta, ya que allí están los nombres de archivo utilizados por el programa.

### Desde MinGW/GCC

El proyecto está preparado para Windows. Desde una terminal de MinGW, por ejemplo:

```bat
cd "PARTE 1"
gcc -Wall main.c funciones.c -o "PARTE 1.exe"
"PARTE 1.exe"
```

Para la parte 2:

```bat
cd "PARTE 2"
gcc -Wall main.c funciones.c "TDA_índice_estático.c" "primitivas_cola_estática.c" -o "PARTE 2.exe"
"PARTE 2.exe"
```

Para la parte 3:

```bat
cd "PARTE 3"
gcc -Wall main.c funciones.c "TDA_índice_estático.c" "primitivas_cola_estática.c" -o "PARTE 3.exe"
"PARTE 3.exe"
```

## Formatos de archivo

### Archivo de texto

Los registros de entrada usan el separador `|`:

```text
DNI|Apellido, Nombre|fecha_nacimiento|sexo|fecha_ingreso|carrera|materias|fecha_ultima_materia
```

Ejemplo:

```text
36879541|Peralta, Joaquin Horacio|19/7/1992|M|12/2/2011|FIL|16|2/7/2015
```

### Archivo binario `.dat`

Contiene estructuras `t_alumno` escritas secuencialmente con `fwrite`. No es texto plano y puede incluir cadenas de longitud fija y campos numéricos binarios.

### Archivo de índice `.idx`

Contiene estructuras `t_reg_indice` escritas con el DNI y la posición relativa del registro dentro del archivo `.dat`. Permite búsquedas por clave sin recorrer todos los alumnos.

### Archivo de errores

Conserva los registros rechazados durante la carga. Las razones pueden incluir DNI fuera de rango, fecha imposible, sexo inválido, carrera inexistente, materias negativas o fechas académicas inconsistentes.

## Prácticas y conceptos aplicados

- Tipos abstractos de datos y modularización;
- implementación separada de interfaz y primitivas;
- arreglos como almacenamiento estático;
- cola circular estática;
- recorrido de estructuras;
- validación de datos de entrada;
- normalización de cadenas;
- archivos secuenciales y acceso directo;
- almacenamiento binario y persistencia;
- registros con clave primaria;
- índice secundario en memoria;
- búsquedas, altas y bajas;
- baja lógica y actualización de estado;
- funciones con punteros y paso por referencia;
- administración manual de punteros de archivo;
- manejo básico de errores de apertura y escritura;
- uso de `typedef`, estructuras, macros y funciones de comparación.

## Notas técnicas

- El código utiliza funciones antiguas como `gets` y `fflush(stdin)`; en proyectos modernos conviene reemplazarlas por funciones seguras como `fgets` y limpiar el búfer de entrada de forma explícita.
- Los nombres de archivos con caracteres acentuados pueden depender de la configuración regional y del sistema operativo.
- Los ejecutables, archivos `.o` y archivos `.layout` incluidos son artefactos de compilaciones previas y pueden regenerarse.
- La consola usa comportamientos específicos de Windows mediante `conio.h`, `cls` y `COLOR`.
- El TDA índice está limitado a `TAM` entradas, definido actualmente como `100`.
