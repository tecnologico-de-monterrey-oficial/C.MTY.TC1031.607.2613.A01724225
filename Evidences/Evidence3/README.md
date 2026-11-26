# Evidencia 3: Bitácora con Heap y BST

Programa en C++ que lee una bitácora de eventos en formato JSON, la ordena con Heap Sort (usando un heap hecho por mí) y cuenta las IPs con un árbol binario de búsqueda. No usa `priority_queue`, `sort`, `map`, `set` ni nada parecido de la STL; todas las estructuras están en `include/`.

## Estructura

```
Evidence3/
├── include/
│   ├── Heap.h        heap binario sobre un vector, con comparador (MaxHeap / MinHeap)
│   ├── HeapSort.h    heap sort usando el Heap
│   ├── BST.h         árbol binario de búsqueda con contador de apariciones por nodo
│   ├── IP.h          IP guardada como número para compararla bien, y su validación
│   └── Registro.h    lectura y validación de cada línea del JSON
├── src/
│   ├── main.cpp      programa principal con el menú
│   ├── pruebas.cpp   pruebas de las estructuras con casos de borde
│   └── experimento.cpp  altura del BST según el orden en que se insertan las IPs
├── data/
│   └── log607-3.json
├── build/            aquí van los ejecutables (no se suben al repo)
└── out/              aquí se generan los archivos ordenados
```

## Cómo compilar

Necesitas `g++` con soporte para C++17. Desde la carpeta `Evidence3`:

**Windows (cmd)**

```
mkdir build
g++ -std=c++17 -static src/main.cpp -o build/main
g++ -std=c++17 -static src/pruebas.cpp -o build/pruebas
g++ -std=c++17 -static src/experimento.cpp -o build/experimento
```

El `-static` es importante en Windows. Sin él, si tienes Git instalado, el programa puede agarrar una librería de C++ que no es la de tu compilador y cerrarse sin mostrar nada.

**Linux / Mac**

```
mkdir -p build
g++ -std=c++17 src/main.cpp -o build/main
g++ -std=c++17 src/pruebas.cpp -o build/pruebas
g++ -std=c++17 src/experimento.cpp -o build/experimento
```

## Cómo correrlo

Siempre desde la carpeta `Evidence3`, para que encuentre `data/` y escriba en `out/`.

```
build\main        (Windows)
./build/main      (Linux / Mac)
```

Primero pide el archivo. Si das Enter sin escribir nada, carga `log607-3.json`. Las líneas con errores (fecha que no existe, hora fuera de rango, IP mal escrita, campos que faltan o mensaje vacío) se muestran con su número de línea y el motivo, y se saltan.

Después aparece el menú:

Las opciones 1 y 2 ordenan primero por IP (como número), luego por fecha y hora, y si todo eso empata, por mensaje.

1. **Ordenar de mayor a menor (MaxHeap).** Pide una predicción de cómo crecerían las comparaciones con el doble de registros, ordena y muestra el tiempo, las comparaciones, la altura del heap y si la predicción se cumplió. Genera `out/output608-1.out`.
2. **Ordenar de menor a mayor (MinHeap).** Lo mismo, pero con MinHeap. Genera `out/output608-2.out`.
3. **Top 10 de IPs.** Toma el conteo del BST, lo mete a un MaxHeap y saca los 10 primeros. Si hay empate, va primero la IP menor, y si el empate cae justo en el lugar 10, lo avisa.
4. **Buscar una IP.** Dice cuántas veces aparece, cuántas comparaciones hizo la búsqueda y la altura del BST comparada con ⌈log₂ n⌉.
5. **Salir.**

Los archivos de salida tienen un registro por línea, así:

```
Nov 13 2024 04:46:01 10.14.14.131 SQL Injection Attempt
```

## Pruebas

```
build\pruebas
```

Prueba el heap, el heap sort, la validación de IPs y el BST con casos de borde: estructuras vacías, un solo elemento, valores repetidos, IPs que no existen y un árbol degenerado. Cada caso muestra el resultado esperado y el obtenido, y al final dice cuántas pasaron.

## Experimento del BST

```
build\experimento
```

Mete las mismas IPs al BST en tres órdenes distintos (como vienen en el archivo, ordenadas de menor a mayor y de mayor a menor) y compara la altura y las comparaciones de búsqueda. Sirve para ver que, si las IPs llegan ordenadas, el árbol se vuelve una lista.

## Video explicativo

[[Ver video explicativo](https://drive.google.com/file/d/1G_EF5gOmczSP6_uQJm9e6Yh7NvYrLt49/view?usp=sharing)]

## Uso de IA

La IA se utilizó como apoyo para encontrar bugs, hacer pruebas y redactar este README.
