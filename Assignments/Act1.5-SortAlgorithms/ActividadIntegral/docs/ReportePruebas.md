# Reporte de pruebas

## Qué se probó

Ejecuté los siete algoritmos con los dos archivos. En total se hicieron 14 pruebas.

En cada prueba revisamos que:

- El programa leyera los 6,818 registros.
- Los registros quedaran ordenados por fecha y hora.
- Se creara `output608.txt`.
- Un rango sin registros produjera un `range607.txt` vacío.

También usamos una fecha duplicada como inicio y fin para comprobar que el programa incluyera todos los registros con esa fecha una sola vez.

## Capturas de las pruebas

### Archivo desordenado

- [Swap Sort](evidencias_pruebas/log1_swap.png)
- [Bubble Sort](evidencias_pruebas/log1_bubble.png)
- [Selection Sort](evidencias_pruebas/log1_selection.png)
- [Insertion Sort](evidencias_pruebas/log1_insertion.png)
- [Merge Sort](evidencias_pruebas/log1_merge.png)
- [Quick Sort](evidencias_pruebas/log1_quick.png)
- [Shell Sort](evidencias_pruebas/log1_shell.png)

### Archivo casi ordenado

- [Swap Sort](evidencias_pruebas/log2_swap.png)
- [Bubble Sort](evidencias_pruebas/log2_bubble.png)
- [Selection Sort](evidencias_pruebas/log2_selection.png)
- [Insertion Sort](evidencias_pruebas/log2_insertion.png)
- [Merge Sort](evidencias_pruebas/log2_merge.png)
- [Quick Sort](evidencias_pruebas/log2_quick.png)
- [Shell Sort](evidencias_pruebas/log2_shell.png)

## Qué se observó

- Insertion Sort y Bubble Sort fueron mucho más rápidos con el archivo casi ordenado.
- Selection Sort tardó casi lo mismo con ambos archivos.
- Merge Sort tuvo tiempos parecidos porque normalmente trabaja de forma similar sin importar el orden inicial.
- Quick Sort fue más lento con el archivo casi ordenado. Esto ocurrió porque usa el primer registro como pivote y puede crear divisiones poco equilibradas.
- Shell Sort también mejoró con el archivo casi ordenado.

## Prueba de fechas duplicadas

Usé esta misma fecha como inicio y fin:

```text
Oct 02 2024 23:04:24
```

El programa encontró dos registros. Cada uno apareció una sola vez.

[Ver captura de la prueba](evidencias_pruebas/prueba_timestamps_duplicados.png)

## Conclusión

Insertion Sort fue la mejor opción para el archivo casi ordenado. Merge Sort fue una opción estable para el archivo desordenado. Selection Sort no aprovechó que el segundo archivo estuviera casi ordenado.

La búsqueda binaria encontró correctamente los rangos y conservó todos los registros que tenían fechas duplicadas.
