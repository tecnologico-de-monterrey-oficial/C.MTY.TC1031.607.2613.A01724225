# Actividad integral de ordenamiento y búsqueda

## Estructura

```text
data/       Archivos de entrada
src/        Código fuente
include/    Espacio para archivos de cabecera
docs/       Documentación, evidencias y video
build/      Ejecutable compilado
out/        Archivos generados por el programa
```

## Compilación

Ejecutar desde la carpeta `ActividadIntegral`:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic src/main.cpp -o build/main.exe
```

## Ejecución

```bash
./build/main.exe
```

El programa permite seleccionar `log607-1.txt` o `log607-2.txt`, escoger un algoritmo de ordenamiento, registrar una predicción y realizar una búsqueda por rango.

## Formato de fechas

Las fechas de búsqueda deben escribirse con el mes en inglés:

```text
Sep 08 2024 14:37:38
```

El rango incluye las fechas inicial y final. Cuando existen timestamps duplicados en uno de los límites, se incluyen todos exactamente una vez.

## Salidas

- `out/output608.txt`: registros ordenados de la corrida más reciente.
- `out/range607.txt`: registros encontrados en la búsqueda más reciente.

## Documentación

- [Reflexión](docs/ReflexEvidencia1.pdf)
- [Reporte de pruebas](docs/ReportePruebas.md)
- [Video explicativo](https://drive.google.com/file/d/1FD4tcYVBVVRULb87KR80AFO0e06o5DlQ/view?usp=sharing)

## Uso de inteligencia artificial

Más que nada la utilizé para revisar un problema que tuve con el algoritmo de quick sort. No permití que se metiera con otras partes del código, también me ayudó a crear este README. 

## Casos de pruebas

En la carpeta docs/, hay dos archivos diferentes, está Casos de pruebas.pdf, en este se ven algunas pruebas generales y las pruebas a la búsqueda binaria, al igual de explicaciones. Además, está el archivo ReportePruebas.md, que se apoya con la carpeta evidencias_pruebas. En este se encuentran los 14 casos de algoritmos probados (dos archivos por cada uno de los 7 algoritmos) en imágenes y en el archvio ReportePruebas.md un reporte de lo que observé. Esto lo hice para ordenar mejor y no tener un archivo con 14 imágenes, que no se ve tan bien como este directorio con las imaǵenes. 