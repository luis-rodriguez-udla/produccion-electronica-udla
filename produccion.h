#ifndef PRODUCCION_H
#define PRODUCCION_H

#define MAX_PROD 5
#define MAX_LEN 50

// Prototipos de funciones usando arreglos paralelos y punteros
void ingresarProducto(char nombres[][MAX_LEN], float *tiempos, int *recursos, int *cantidades, int *total);
int buscarProducto(char nombres[][MAX_LEN], int total, char *nombreBuscado);
void editarProducto(char nombres[][MAX_LEN], float *tiempos, int *recursos, int *cantidades, int total);
void eliminarProducto(char nombres[][MAX_LEN], float *tiempos, int *recursos, int *cantidades, int *total);
void mostrarProductos(char nombres[][MAX_LEN], float *tiempos, int *recursos, int *cantidades, int total);
void evaluarProduccion(float *tiempos, int *recursos, int *cantidades, int total, float tiempoDisp, int recursosDisp);

#endif