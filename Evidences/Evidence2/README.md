# Evidencia 2: Bitácora con estructuras de datos propias

Programa en C++ que carga una bitácora de eventos, la ordena por fecha y hora con Merge Sort sobre una lista doblemente ligada, y permite buscar por día y ver estadísticas.

## Archivos

| Archivo | Qué es |
|---|---|
| `main.cpp` | Programa principal (menú de la bitácora) |
| `pruebas.cpp` | Programa de pruebas de las estructuras (lista, pila, fila, lista doble) |
| `estructuras.h` | Lista ligada, Pila, Fila y Lista doblemente ligada (con Merge Sort) |
| `registro.h` | Registro de la bitácora y validación de cada línea |
| `log607-1.txt`, `log607-2.txt` | Archivos de datos de ejemplo |
| `Documento_Evidencia.md` | Documento de evidencia |

## Requisitos

- Un compilador de C++ con soporte para C++17 (`g++` 7 o superior, o `clang++`).
- No se necesitan librerías externas.

En Ubuntu/Debian, si no tienes `g++`: `sudo apt install g++`.

## Compilar

Desde la carpeta de este proyecto:

```bash
g++ -std=c++17 main.cpp -o main
g++ -std=c++17 pruebas.cpp -o pruebas
```

Opcional, para ver advertencias: agrega `-Wall -Wextra` a los comandos.

## Ejecutar

### Programa principal

```bash
./main
```

1. Escribe el nombre del archivo a cargar (por ejemplo `log607-2.txt`). El archivo debe estar en la carpeta desde donde ejecutas el programa, o escribe su ruta. Si no existe o lo dejas vacío, el programa vuelve a preguntar.
2. Al terminar de cargar, muestra cuántos registros se cargaron y cuántas líneas se omitieron (con número de línea y motivo de cada una).
3. Usa el menú:

```
1) Ordenar por fecha y hora
2) Buscar logs por dia
3) Mostrar logs por dia en orden descendente
4) Estadisticas del archivo
5) Salir
```

- **Opción 1:** pide tu predicción de crecimiento (n log n o n²), ordena y muestra algoritmo, archivo, tamaño, tiempo, comparaciones, profundidad máxima y si tu predicción coincidió. Genera `output608.out` con los datos ordenados. Si ya estaba ordenada, lo avisa.
- **Opción 2:** pide un día con el formato `Mes dd yyyy` (por ejemplo `Sep 08 2024`) y muestra sus registros con el total. Requiere haber ordenado antes (opción 1).
- **Opción 3:** muestra los registros de un día en orden descendente usando una Pila. Reutiliza el día de la última búsqueda, o lo pide si no hay una. Requiere haber ordenado antes.
- **Opción 4:** total de registros, día con más incidentes, tipo de evento más frecuente e IP más repetida. Si hay empates, muestra todos.
- **Opción 5:** salir.

Los meses se escriben en inglés abreviado: `Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec`.

### Formato esperado del archivo de datos

Una línea por registro:

```
Sep 29 2024 14:37:38 10.14.19.188 Unauthorized Access Attempts
```

Es decir: mes, día, año, hora (`hh:mm:ss`), dirección IP y descripción. Las líneas que no cumplan el formato se reportan y se omiten sin detener el programa.

### Programa de pruebas

```bash
./pruebas
```

Prueba cada estructura con estructura vacía, un solo elemento y operaciones en los extremos. Al final imprime `Todas las pruebas pasaron` si todo está bien.

## Archivo de salida

La opción 1 crea (o sobrescribe) `output608.out` en la carpeta desde donde ejecutaste el programa, con los registros ordenados y en el mismo formato del archivo original.

## Ejemplo rápido

```bash
g++ -std=c++17 main.cpp -o main
./main
# Archivo a cargar: log607-2.txt
# Opcion: 1   (ordenar)  -> Tu prediccion: 1
# Opcion: 2   (buscar)   -> Dia: Sep 08 2024
# Opcion: 5   (salir)
```
