#include <stdio.h> 
#include "produccion.h" 

int main() {
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    int demandas[MAX_PRODUCTOS];
    float tiemposUnidad[MAX_PRODUCTOS];
    float recursosUnidad[MAX_PRODUCTOS];

    int numProductosActual = 0;
    int opcion = -1;

    printf("=====================================================\n");
    printf("  Sistema de Optimizacion de Produccion (v1.0)\n");
    printf("=====================================================\n");

    do {
        mostrarMenuProduccion();
        printf("Ingrese su opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Error: Entrada invalida. Por favor ingrese un numero.\n");
            limpiarBufferEntradaStdin(); 
            opcion = -1; 
            printf("\nPresione Enter para continuar...");
            getchar(); 
            continue;
        }
        limpiarBufferEntradaStdin(); 

        switch (opcion) {
            case 1:
                ingresarDatosProductos(nombres, demandas, tiemposUnidad, recursosUnidad, &numProductosActual);
                break;
            case 2:
                mostrarDatosProductos(nombres, demandas, tiemposUnidad, recursosUnidad, numProductosActual);
                break;
            case 3:
                if (numProductosActual > 0) {
                    printf("\nCalculando Tiempo Total...\n");
                    float tiempoTotal = calcularTiempoTotal(demandas, tiemposUnidad, numProductosActual);
                    printf("El tiempo total de fabricacion requerido es: %.2f unidades de tiempo.\n", tiempoTotal);
                } else {
                    printf("No hay productos ingresados para calcular el tiempo total.\n");
                }
                break;
            case 4:
                 if (numProductosActual > 0) {
                    printf("\nCalculando Recursos Totales...\n");
                    float recursosTotales = calcularRecursosTotales(demandas, recursosUnidad, numProductosActual);
                    printf("La cantidad total de recursos necesarios es: %.2f unidades de recursos.\n", recursosTotales);
                } else {
                    printf("No hay productos ingresados para calcular los recursos totales.\n");
                }
                break;
            case 5:
                 verificarViabilidadProduccion(demandas, tiemposUnidad, recursosUnidad, numProductosActual);
                 break;
            case 6:
                 editarProducto(nombres, demandas, tiemposUnidad, recursosUnidad, numProductosActual);
                 break;
            case 7:
                 eliminarProducto(nombres, demandas, tiemposUnidad, recursosUnidad, &numProductosActual);
                 break;
            case 8:
                 mostrarConsideraciones();
                 break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }

        if (opcion != 0) {
            printf("\nPresione Enter para continuar...");
            getchar();
        }

    } while (opcion != 0);

    printf("Programa finalizado. ¡Hasta luego!\n");
    return 0;
}