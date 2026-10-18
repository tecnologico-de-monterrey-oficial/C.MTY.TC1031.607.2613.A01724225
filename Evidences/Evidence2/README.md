# Evidencia 2: Bitácora con estructuras de datos propias
 * Utilizé IA en este archivo

Programa en C++ que carga una bitácora de eventos, la ordena por fecha y hora con Merge Sort sobre una lista doblemente ligada, y permite buscar por día y ver estadísticas.

## Estructura del proyecto

```
.
├── data/      log607-1.txt, log607-2.txt (archivos de datos)
├── src/       main.cpp (programa principal), pruebas.cpp (pruebas de las estructuras)
├── include/   Node.h, LinkedList.h, Stack.h, Queue.h, DoublyLinkedList.h, Registro.h
├── docs/      Evidencia2.docx (documento de evidencia)
├── out/       output607.out (lo genera el programa)
├── build/     ejecutables compilados
└── README.md
```

| Archivo | Qué es |
|---|---|
| `src/main.cpp` | Programa principal (menú de la bitácora) |
| `src/pruebas.cpp` | Programa de pruebas de las estructuras |
| `include/Node.h` | Nodo de la lista ligada simple |
| `include/LinkedList.h` | Lista ligada simple con head y tail |
| `include/Stack.h` | Pila construida sobre la lista ligada |
| `include/Queue.h` | Fila construida sobre la lista ligada |
| `include/DoublyLinkedList.h` | Lista doblemente ligada (con Merge Sort) |
| `include/Registro.h` | Registro de la bitácora y validación de cada línea |

## Requisitos

- Un compilador de C++ con soporte para C++17 (`g++` 8 o superior, o `clang++`).
- No se necesitan librerías externas.

En Ubuntu/Debian, si no tienes `g++`: `sudo apt install g++`.

## Compilar

Desde la carpeta de este proyecto (donde está este README):

```bash
mkdir -p build
g++ -std=c++17 src/main.cpp -o build/main
g++ -std=c++17 src/pruebas.cpp -o build/pruebas
```

Opcional, para ver advertencias: agrega `-Wall -Wextra` a los comandos.

## Ejecutar

Ejecuta siempre desde la carpeta del proyecto, para que encuentre `data/` y escriba en `out/`.

### Programa principal

```bash
./build/main
```

1. Escribe el nombre del archivo a cargar (por ejemplo `log607-2.txt`). El programa lo busca tal como lo escribes y, si no lo encuentra, también dentro de `data/`. Si no existe o lo dejas vacío, vuelve a preguntar.
2. Al terminar de cargar, muestra cuántos registros se cargaron y cuántas líneas se omitieron (con número de línea y motivo de cada una).
3. Usa el menú:

```
1) Ordenar por fecha y hora
2) Buscar logs por dia
3) Mostrar logs por dia en orden descendente
4) Estadisticas del archivo
5) Salir
```

- **Opción 1:** pide tu predicción de crecimiento (n log n o n²), ordena y muestra algoritmo, archivo, tamaño, tiempo, comparaciones, profundidad máxima y si tu predicción coincidió. Genera `out/output607.out` con los datos ordenados. Si ya estaba ordenada, lo avisa.
- **Opción 2:** pide un día con el formato `Mes dd yyyy` (por ejemplo `Sep 08 2024`) y muestra sus registros con el total. Requiere haber ordenado antes (opción 1).
- **Opción 3:** muestra los registros de un día en orden descendente usando una Pila. Reutiliza el día de la última búsqueda, o lo pide si no hay una. Requiere haber ordenado antes.
- **Opción 4:** total de registros, día con más incidentes, tipo de evento más frecuente e IP más repetida. Si hay empates, muestra todos.
- **Opción 5:** salir.

### Formato esperado de fechas y del archivo de datos

Los días se escriben como `Mes dd yyyy`, con el mes en inglés abreviado: `Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec`. Ejemplo: `Sep 14 2024`.

El archivo de datos tiene una línea por registro:

```
Sep 29 2024 14:37:38 10.14.19.188 Unauthorized Access Attempts
```

Es decir: mes, día, año, hora (`hh:mm:ss`), dirección IP y descripción. Las líneas que no cumplan el formato se reportan y se omiten sin detener el programa.

### Programa de pruebas

```bash
./build/pruebas
```

Prueba cada estructura con estructura vacía, un solo elemento y operaciones en los extremos. Al final imprime `Todas las pruebas pasaron` si todo está bien.

## Archivo de salida

La opción 1 crea (o sobrescribe) `out/output607.out`, con los registros ordenados y en el mismo formato del archivo original.

## Ejemplo rápido

```bash
mkdir -p build
g++ -std=c++17 src/main.cpp -o build/main
./build/main
# Archivo a cargar: log607-2.txt
# Opcion: 1   (ordenar)  -> Tu prediccion: 1
# Opcion: 2   (buscar)   -> Dia: Sep 08 2024
# Opcion: 5   (salir)
```

## Video explicativo

[Ver video explicativo](https://drive.google.com/file/d/19AWcDi85zq2EIyaPuQnTmeTzaB8zyti_/view?usp=sharing)

## Política de uso de IA

La IA se utilizó para encontrar bugs, hacer testing, ordenar archivos y para el README.
