#include <stdio.h>
#include "produccion.h"

// Función auxiliar privada (solo se usa dentro de este .c) para comparar texto sin <string.h>
int compararCadenas(char *cad1, char *cad2) {
    int i = 0;
    while (cad1[i] != '\0' && cad2[i] != '\0') {
        if (cad1[i] != cad2[i]) {
            return 0; // Son diferentes
        }
        i++;
    }
    // Retorna 1 solo si ambas cadenas terminaron exactamente en la misma posición
    return (cad1[i] == '\0' && cad2[i] == '\0');
}

// Función auxiliar privada para leer textos con espacios de forma segura
void leerTexto(char *buffer, int tam) {
    fgets(buffer, tam, stdin);
    int i = 0;
    while (buffer[i] != '\0') {
        if (buffer[i] == '\n') {
            buffer[i] = '\0'; // Elimina el salto de línea del Enter
            break;
        }
        i++;
    }
}

// Búsqueda secuencial propia: devuelve el índice (0 a 4) o -1 si no existe
int buscarProducto(char nombres[][MAX_LEN], int total, char *nombreBuscado) {
    for (int i = 0; i < total; i++) {
        if (compararCadenas(nombres[i], nombreBuscado)) {
            return i;
        }
    }
    return -1;
}

void ingresarProducto(char nombres[][MAX_LEN], float *tiempos, int *recursos, int *cantidades, int *total) {
    if (*total >= MAX_PROD) {
        printf("\n[ERROR] Capacidad maxima alcanzada (%d productos).\n", MAX_PROD);
        return;
    }

    int idx = *total; // Usamos el valor al que apunta el puntero
    char tempNombre[MAX_LEN];

    printf("\n--- INGRESAR PRODUCTO %d ---\n", idx + 1);
    printf("Nombre del componente: ");
    leerTexto(tempNombre, MAX_LEN);

    // Validamos que no exista ya ese nombre
    if (buscarProducto(nombres, *total, tempNombre) != -1) {
        printf("[AVISO] Ese producto ya esta registrado. Use la opcion de editar.\n");
        return;
    }

    // Copiamos el nombre manualmente al arreglo principal
    int j = 0;
    while (tempNombre[j] != '\0') {
        nombres[idx][j] = tempNombre[j];
        j++;
    }
    nombres[idx][j] = '\0';

    do {
        printf("Tiempo de fabricacion por unidad (horas): ");
        scanf("%f", (tiempos + idx)); // Aritmética de punteros equivalente a &tiempos[idx]
    } while (*(tiempos + idx) <= 0);

    do {
        printf("Recursos necesarios por unidad: ");
        scanf("%d", (recursos + idx));
    } while (*(recursos + idx) <= 0);

    do {
        printf("Cantidad demandada: ");
        scanf("%d", (cantidades + idx));
    } while (*(cantidades + idx) < 0);

    while (getchar() != '\n'); // Limpiar el buffer del teclado

    (*total)++; // Incrementamos la variable original en el main
    printf("[OK] Producto registrado con exito.\n");
}

void mostrarProductos(char nombres[][MAX_LEN], float *tiempos, int *recursos, int *cantidades, int total) {
    if (total == 0) {
        printf("\n[AVISO] No hay productos registrados todavia.\n");
        return;
    }

    printf("\n====================================================================\n");
    printf("%-4s | %-20s | %-10s | %-10s | %-10s\n", "No.", "Producto", "T.Unit(h)", "Rec.Unit", "Demanda");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-4d | %-20s | %-10.2f | %-10d | %-10d\n", 
               i + 1, nombres[i], *(tiempos + i), *(recursos + i), *(cantidades + i));
    }
    printf("====================================================================\n");
}

void editarProducto(char nombres[][MAX_LEN], float *tiempos, int *recursos, int *cantidades, int total) {
    if (total == 0) {
        printf("\n[AVISO] No hay productos para editar.\n");
        return;
    }

    char buscado[MAX_LEN];
    printf("\nIngrese el nombre exacto del producto a editar: ");
    leerTexto(buscado, MAX_LEN);

    int idx = buscarProducto(nombres, total, buscado);
    if (idx == -1) {
        printf("[ERROR] Producto '%s' no encontrado.\n", buscado);
        return;
    }

    printf("\nEditando '%s':\n", nombres[idx]);
    printf("Nuevo nombre: ");
    leerTexto(nombres[idx], MAX_LEN);

    do {
        printf("Nuevo tiempo de fabricacion por unidad (horas): ");
        scanf("%f", (tiempos + idx));
    } while (*(tiempos + idx) <= 0);

    do {
        printf("Nuevos recursos necesarios por unidad: ");
        scanf("%d", (recursos + idx));
    } while (*(recursos + idx) <= 0);

    do {
        printf("Nueva cantidad demandada: ");
        scanf("%d", (cantidades + idx));
    } while (*(cantidades + idx) < 0);

    while (getchar() != '\n');
    printf("[OK] Producto actualizado correctamente.\n");
}

void eliminarProducto(char nombres[][MAX_LEN], float *tiempos, int *recursos, int *cantidades, int *total) {
    if (*total == 0) {
        printf("\n[AVISO] No hay productos para eliminar.\n");
        return;
    }

    char buscado[MAX_LEN];
    printf("\nIngrese el nombre exacto del producto a eliminar: ");
    leerTexto(buscado, MAX_LEN);

    int idx = buscarProducto(nombres, *total, buscado);
    if (idx == -1) {
        printf("[ERROR] Producto '%s' no encontrado.\n", buscado);
        return;
    }

    // Desplazamos todos los elementos posteriores una posición hacia la izquierda
    for (int i = idx; i < (*total) - 1; i++) {
        // Copiar nombre[i+1] hacia nombre[i]
        int j = 0;
        while (nombres[i + 1][j] != '\0') {
            nombres[i][j] = nombres[i + 1][j];
            j++;
        }
        nombres[i][j] = '\0';

        // Desplazar los arreglos numéricos
        *(tiempos + i) = *(tiempos + i + 1);
        *(recursos + i) = *(recursos + i + 1);
        *(cantidades + i) = *(cantidades + i + 1);
    }

    (*total)--; // Reducimos el contador global
    printf("[OK] Producto '%s' eliminado del sistema.\n", buscado);
}

void evaluarProduccion(float *tiempos, int *recursos, int *cantidades, int total, float tiempoDisp, int recursosDisp) {
    if (total == 0) {
        printf("\n[AVISO] Ingrese al menos un producto para calcular la produccion.\n");
        return;
    }

    float tiempoTotalReq = 0.0;
    int recursosTotalReq = 0;

    for (int i = 0; i < total; i++) {
        tiempoTotalReq += (*(tiempos + i)) * (*(cantidades + i));
        recursosTotalReq += (*(recursos + i)) * (*(cantidades + i));
    }

    printf("\n================ REPORTE DE OPTIMIZACION ================\n");
    printf("Tiempo total requerido   : %.2f horas (Disponible: %.2f h)\n", tiempoTotalReq, tiempoDisp);
    printf("Recursos totales req.    : %d unidades (Disponible: %d u)\n", recursosTotalReq, recursosDisp);
    printf("---------------------------------------------------------\n");

    if (tiempoTotalReq <= tiempoDisp && recursosTotalReq <= recursosDisp) {
        printf("RESULTADO: VIABLE. La fabrica PUEDE cumplir con toda la demanda.\n");
        printf("Sobrante -> Tiempo: %.2f h | Recursos: %d u\n", 
               tiempoDisp - tiempoTotalReq, recursosDisp - recursosTotalReq);
    } else {
        printf("RESULTADO: NO VIABLE. Capacidad insuficiente en la linea.\n");
        if (tiempoTotalReq > tiempoDisp) {
            printf(" -> Deficit de tiempo: faltan %.2f horas.\n", tiempoTotalReq - tiempoDisp);
        }
        if (recursosTotalReq > recursosDisp) {
            printf(" -> Deficit de recursos: faltan %d unidades.\n", recursosTotalReq - recursosDisp);
        }
    }
    printf("=========================================================\n");
}