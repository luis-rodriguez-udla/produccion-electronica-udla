#include <stdio.h>
#include "produccion.h"

int main() {
    // Arreglos paralelos (sin struct, cumpliendo restricciones)
    char nombres[MAX_PROD][MAX_LEN];
    float tiempos[MAX_PROD];
    int recursos[MAX_PROD];
    int cantidades[MAX_PROD];
    
    int totalProductos = 0;
    float tiempoDisponible = 0.0;
    int recursosDisponibles = 0;
    int opcion = 0;

    printf("=== SISTEMA DE OPTIMIZACION DE PRODUCCION ELECTRONICA ===\n");
    
    // Configuración inicial de las limitaciones de la planta
    do {
        printf("Ingrese el tiempo maximo de produccion disponible (horas): ");
        scanf("%f", &tiempoDisponible);
    } while (tiempoDisponible <= 0);

    do {
        printf("Ingrese la cantidad maxima de recursos disponibles: ");
        scanf("%d", &recursosDisponibles);
    } while (recursosDisponibles <= 0);

    while (getchar() != '\n'); // Limpiar salto de línea del buffer

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Ingresar producto (%d/%d registrados)\n", totalProductos, MAX_PROD);
        printf("2. Mostrar lista de productos\n");
        printf("3. Editar un producto (por busqueda)\n");
        printf("4. Eliminar un producto (por busqueda)\n");
        printf("5. Calcular tiempos, recursos y viabilidad\n");
        printf("6. Actualizar limites de tiempo/recursos de la fabrica\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n'); // Evitar bugs con fgets

        switch (opcion) {
            case 1:
                ingresarProducto(nombres, tiempos, recursos, cantidades, &totalProductos);
                break;
            case 2:
                mostrarProductos(nombres, tiempos, recursos, cantidades, totalProductos);
                break;
            case 3:
                editarProducto(nombres, tiempos, recursos, cantidades, totalProductos);
                break;
            case 4:
                eliminarProducto(nombres, tiempos, recursos, cantidades, &totalProductos);
                break;
            case 5:
                evaluarProduccion(tiempos, recursos, cantidades, totalProductos, tiempoDisponible, recursosDisponibles);
                break;
            case 6:
                do {
                    printf("Nuevo tiempo disponible (horas): ");
                    scanf("%f", &tiempoDisponible);
                } while (tiempoDisponible <= 0);
                do {
                    printf("Nuevos recursos disponibles: ");
                    scanf("%d", &recursosDisponibles);
                } while (recursosDisponibles <= 0);
                while (getchar() != '\n');
                printf("[OK] Limites de planta actualizados.\n");
                break;
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("[ERROR] Opcion invalida.\n");
        }
    } while (opcion != 0);

    return 0;
}