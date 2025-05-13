#include <stdio.h>  // Para printf, fgets, sscanf, getchar, EOF
#include <string.h> // Para strcmp, strcpy, strcspn, strlen, strchr (opcional)
#include "produccion.h"

// --- Implementación de Funciones de Utilidad y Validación ---

void limpiarBufferEntradaStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int leerCadenaValida(char mensaje[], char destino[], int longitudMax) {
    printf("%s", mensaje);
    if (fgets(destino, longitudMax, stdin) != NULL) {
        destino[strcspn(destino, "\n")] = '\0';
        if (strlen(destino) == 0) {
            printf("Error: La entrada no puede estar vacia.\n");
            return 0;
        }
         // Opcional: Detectar si se llenó el buffer sin encontrar '\n'
         // if (strchr(destino, '\n') == NULL && strlen(destino) == longitudMax - 1) {
         //     limpiarBufferEntradaStdin(); // Limpiar el resto si es necesario
         // }
        return 1;
    } else {
        printf("Error al leer la entrada.\n");
        return 0;
    }
}

int leerEnteroPositivo(char mensaje[]) {
    char buffer[100];
    int valor;
    int resultadoScan;
    char extra; // Para verificar caracteres extra

    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            resultadoScan = sscanf(buffer, "%d %c", &valor, &extra); // Intenta leer número y algo más
            if (resultadoScan == 1) { // Éxito: Solo se leyó un entero
                if (valor > 0) {
                    return valor; // Válido y positivo
                } else {
                    printf("Error: El numero debe ser mayor que 0.\n");
                }
            } else if (resultadoScan == 2) { // Se leyó número pero había algo más después
                 printf("Error: Entrada invalida. Ingrese solo un numero entero sin caracteres adicionales.\n");
            }
            else { // No se pudo leer ni un entero (ej: "abc")
                printf("Error: Entrada invalida. Ingrese un numero entero valido.\n");
            }
        } else {
            printf("Error fatal al leer la entrada.\n");
            return -1; // Indicar error fatal
        }
    }
}


float leerFlotantePositivo(char mensaje[]) {
    char buffer[100];
    float valor;
    int resultadoScan;
    char extra; // Para verificar caracteres extra

    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            resultadoScan = sscanf(buffer, "%f %c", &valor, &extra); // Intenta leer flotante y algo más
            if (resultadoScan == 1) { // Éxito: Solo se leyó un flotante
                if (valor > 0.0f) {
                    return valor; // Válido y positivo
                } else {
                    printf("Error: El valor debe ser mayor que 0.0.\n");
                }
             } else if (resultadoScan == 2) { // Se leyó flotante pero había algo más
                 printf("Error: Entrada invalida. Ingrese solo un numero decimal valido (ej: 10.5) sin caracteres adicionales.\n");
            } else { // No se pudo leer ni un flotante
                printf("Error: Entrada invalida. Ingrese un numero decimal valido (ej: 10.5).\n");
            }
        } else {
            printf("Error fatal al leer la entrada.\n");
            return -1.0f; // Indicar error fatal
        }
    }
}

// ... (El resto de las implementaciones de funciones se mantienen igual que antes) ...
// ... (mostrarMenuProduccion, existeProducto, buscarProductoIndice, ...)
// ... (ingresarDatosProductos, mostrarDatosProductos, calcularTiempoTotal, ...)
// ... (calcularRecursosTotales, verificarViabilidadProduccion, editarProducto, ...)
// ... (eliminarProducto, mostrarConsideraciones) ...

// --- Pegar aquí el resto de las implementaciones de la respuesta anterior ---

void mostrarMenuProduccion() {
    printf("\n--- MENU OPTIMIZACION DE PRODUCCION ---\n");
    printf("1. Ingresar/Completar Datos de Productos (%d max)\n", MAX_PRODUCTOS);
    printf("2. Mostrar Datos de Productos Ingresados\n");
    printf("3. Calcular Tiempo Total de Fabricacion\n");
    printf("4. Calcular Recursos Totales Necesarios\n");
    printf("5. Verificar Viabilidad de Produccion (con limites)\n");
    printf("6. Editar Datos de un Producto\n");
    printf("7. Eliminar un Producto\n");
    printf("8. Mostrar Consideraciones del Proyecto\n");
    printf("0. Salir\n");
}

int existeProducto(char nombres[][MAX_NOMBRE], int numProductosActual, const char nombreNuevo[]) {
    for (int i = 0; i < numProductosActual; i++) {
        if (strcmp(nombres[i], nombreNuevo) == 0) {
            return 1;
        }
    }
    return 0;
}

int buscarProductoIndice(char nombres[][MAX_NOMBRE], int numProductosActual, const char nombreBuscado[]) {
     for (int i = 0; i < numProductosActual; i++) {
        if (strcmp(nombres[i], nombreBuscado) == 0) {
            return i;
        }
    }
    return -1;
}

void ingresarDatosProductos(char nombres[][MAX_NOMBRE], int demandas[], float tiemposUnidad[], float recursosUnidad[], int *numProductosActual) {
    if (*numProductosActual >= MAX_PRODUCTOS) {
        printf("Error: Ya se han ingresado los datos para los %d productos.\n", MAX_PRODUCTOS);
        return;
    }

    printf("--- Ingreso de Datos de Productos ---\n");
    printf("Actualmente hay %d productos ingresados. Puede ingresar %d mas.\n", *numProductosActual, MAX_PRODUCTOS - *numProductosActual);

    while (*numProductosActual < MAX_PRODUCTOS) {
        int indiceActual = *numProductosActual;
        printf("\n--- Producto %d ---\n", indiceActual + 1);

        char nombreTemporal[MAX_NOMBRE];
        while (1) {
            if (!leerCadenaValida("Ingrese nombre del producto: ", nombreTemporal, MAX_NOMBRE)) {
                 printf("Lectura de nombre fallida. Cancelando ingreso de este producto.\n");
                 return;
            }
            if (!existeProducto(nombres, *numProductosActual, nombreTemporal)) {
                break;
            } else {
                printf("Error: El producto '%s' ya existe. Ingrese un nombre diferente.\n", nombreTemporal);
            }
        }
        strcpy(nombres[indiceActual], nombreTemporal);

        demandas[indiceActual] = leerEnteroPositivo("Ingrese demanda (unidades): ");
        if (demandas[indiceActual] == -1) {
             printf("Ingreso de demanda cancelado.\n");
             return;
        }


        tiemposUnidad[indiceActual] = leerFlotantePositivo("Ingrese tiempo de fabricacion por unidad (ej: 0.5): ");
         if (tiemposUnidad[indiceActual] < 0) {
             printf("Ingreso de tiempo cancelado.\n");
             return;
         }

        recursosUnidad[indiceActual] = leerFlotantePositivo("Ingrese recursos necesarios por unidad (ej: 2.3): ");
         if (recursosUnidad[indiceActual] < 0) {
             printf("Ingreso de recursos cancelado.\n");
             return;
         }

        (*numProductosActual)++;
        printf("Producto '%s' agregado correctamente.\n", nombres[indiceActual]);

        if (*numProductosActual < MAX_PRODUCTOS) {
            char continuar[10];
            // Usar leerCadenaValida para leer la respuesta s/n de forma segura
            while(1) {
                if(leerCadenaValida("¿Desea ingresar otro producto? (s/n): ", continuar, 10)) {
                    if (strcmp(continuar, "s") == 0 || strcmp(continuar, "S") == 0 || strcmp(continuar, "n") == 0 || strcmp(continuar, "N") == 0) {
                        break; // Entrada válida (s o n)
                    } else {
                        printf("Respuesta invalida. Ingrese 's' o 'n'.\n");
                    }
                } else {
                    // Si leerCadenaValida falla aquí, es un problema mayor
                    printf("Error leyendo respuesta. Asumiendo 'no'.\n");
                    strcpy(continuar, "n"); // Salir por seguridad
                    break;
                }
            }

            if (strcmp(continuar, "n") == 0 || strcmp(continuar, "N") == 0) {
                break;
            }
        } else {
             printf("Se ha alcanzado el maximo de %d productos.\n", MAX_PRODUCTOS);
        }
    }
}


void mostrarDatosProductos(const char nombres[][MAX_NOMBRE], const int demandas[], const float tiemposUnidad[], const float recursosUnidad[], int numProductosActual) {
    if (numProductosActual == 0) {
        printf("No hay productos ingresados para mostrar.\n");
        return;
    }

    printf("\n--- DATOS DE PRODUCCION ACTUALES (%d productos) ---\n", numProductosActual);
    printf("----------------------------------------------------------------------------\n");
    printf("%-*s | %-10s | %-15s | %-15s\n", MAX_NOMBRE -1 , "Nombre Producto", "Demanda", "Tiempo/Unidad", "Recursos/Unidad");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < numProductosActual; i++) {
        printf("%-*s | %-10d | %-15.2f | %-15.2f\n",
               MAX_NOMBRE - 1,
               nombres[i],
               demandas[i],
               tiemposUnidad[i],
               recursosUnidad[i]);
    }
     printf("----------------------------------------------------------------------------\n");
}

float calcularTiempoTotal(const int demandas[], const float tiemposUnidad[], int numProductosActual) {
    float total = 0.0f;
    for (int i = 0; i < numProductosActual; i++) {
        total += (float)demandas[i] * tiemposUnidad[i];
    }
    return total;
}

float calcularRecursosTotales(const int demandas[], const float recursosUnidad[], int numProductosActual) {
    float total = 0.0f;
    for (int i = 0; i < numProductosActual; i++) {
        total += (float)demandas[i] * recursosUnidad[i];
    }
    return total;
}

void verificarViabilidadProduccion(const int demandas[], const float tiemposUnidad[], const float recursosUnidad[], int numProductosActual) {
     if (numProductosActual == 0) {
        printf("No hay productos ingresados para verificar viabilidad.\n");
        return;
    }
     if (numProductosActual < MAX_PRODUCTOS) {
         printf("Advertencia: Aun no se han ingresado los datos de los %d productos.\n", MAX_PRODUCTOS);
         printf("La verificacion se hara con los %d productos actuales.\n", numProductosActual);
     }

    printf("\n--- Verificacion de Viabilidad ---\n");
    float tiempoLimite = leerFlotantePositivo("Ingrese el tiempo total de produccion disponible: ");
     if (tiempoLimite < 0) return;

    float recursosLimite = leerFlotantePositivo("Ingrese la cantidad total de recursos disponibles: ");
     if (recursosLimite < 0) return;

    float tiempoRequerido = calcularTiempoTotal(demandas, tiemposUnidad, numProductosActual);
    float recursosRequeridos = calcularRecursosTotales(demandas, recursosUnidad, numProductosActual);

    printf("\n--- Resultados ---\n");
    printf("Tiempo Total Requerido: %.2f\n", tiempoRequerido);
    printf("Recursos Totales Requeridos: %.2f\n", recursosRequeridos);
    printf("Tiempo Disponible: %.2f\n", tiempoLimite);
    printf("Recursos Disponibles: %.2f\n", recursosLimite);

    int tiempoOk = (tiempoRequerido <= tiempoLimite);
    int recursosOk = (recursosRequeridos <= recursosLimite);

    if (tiempoOk && recursosOk) {
        printf("\nConclusion: La produccion ES VIABLE con los limites dados.\n");
    } else {
        printf("\nConclusion: La produccion NO ES VIABLE con los limites dados.\n");
        if (!tiempoOk) {
            printf("  - Se excede el tiempo disponible en %.2f unidades de tiempo.\n", tiempoRequerido - tiempoLimite);
        }
        if (!recursosOk) {
            printf("  - Se exceden los recursos disponibles en %.2f unidades de recursos.\n", recursosRequeridos - recursosLimite);
        }
    }
}

void editarProducto(char nombres[][MAX_NOMBRE], int demandas[], float tiemposUnidad[], float recursosUnidad[], int numProductosActual) {
    if (numProductosActual == 0) {
        printf("No hay productos para editar.\n");
        return;
    }

    char nombreBuscado[MAX_NOMBRE];
    printf("\n--- Editar Producto ---\n");
    mostrarDatosProductos(nombres, demandas, tiemposUnidad, recursosUnidad, numProductosActual);

    if (!leerCadenaValida("Ingrese el nombre EXACTO del producto a editar: ", nombreBuscado, MAX_NOMBRE)) {
        return;
    }

    int indice = buscarProductoIndice(nombres, numProductosActual, nombreBuscado);

    if (indice == -1) {
        printf("Producto '%s' no encontrado.\n", nombreBuscado);
        return;
    }

    printf("Editando datos para el producto '%s'. Deje en blanco y presione Enter para no cambiar un campo.\n", nombres[indice]);

    char nuevoNombre[MAX_NOMBRE];
    int demandaNueva;
    float tiempoNuevo, recursosNuevos;
    char buffer[100]; // Buffer auxiliar para leer entradas opcionales

    // Editar Nombre
    printf("Nombre actual: %s\n", nombres[indice]);
    printf("Nuevo nombre (o Enter para mantener): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
         if (strlen(buffer) > 0) { // Si se ingresó algo
            // Verificar que el nuevo nombre no exista ya (a menos que sea el mismo producto)
            int otroIndice = buscarProductoIndice(nombres, numProductosActual, buffer);
            if (otroIndice != -1 && otroIndice != indice) {
                printf("Error: Ya existe otro producto con el nombre '%s'. No se cambio el nombre.\n", buffer);
            } else {
                 strcpy(nombres[indice], buffer);
                 printf("Nombre actualizado.\n");
            }
         } else {
             printf("Nombre no modificado.\n");
         }
    } else {
         printf("Error leyendo entrada para nombre. No se modifico.\n");
    }


    // Editar Demanda
    printf("Demanda actual: %d\n", demandas[indice]);
    printf("Nueva demanda (numero > 0, o Enter para mantener): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) > 0) {
            char extra;
            if (sscanf(buffer, "%d %c", &demandaNueva, &extra) == 1 && demandaNueva > 0) {
                 demandas[indice] = demandaNueva;
                 printf("Demanda actualizada.\n");
            } else {
                printf("Entrada invalida para demanda (debe ser numero > 0 sin extras). No se modifico.\n");
            }
        } else {
             printf("Demanda no modificada.\n");
        }
    } else {
         printf("Error leyendo entrada para demanda. No se modifico.\n");
    }


    // Editar Tiempo
    printf("Tiempo/Unidad actual: %.2f\n", tiemposUnidad[indice]);
     printf("Nuevo tiempo/unidad (numero > 0.0, o Enter para mantener): ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
         if (strlen(buffer) > 0) {
             char extra;
            if (sscanf(buffer, "%f %c", &tiempoNuevo, &extra) == 1 && tiempoNuevo > 0.0f) {
                 tiemposUnidad[indice] = tiempoNuevo;
                 printf("Tiempo/Unidad actualizado.\n");
            } else {
                printf("Entrada invalida para tiempo (debe ser numero > 0.0 sin extras). No se modifico.\n");
            }
         } else {
              printf("Tiempo/Unidad no modificado.\n");
         }
    } else {
        printf("Error leyendo entrada para tiempo. No se modifico.\n");
    }

    // Editar Recursos
    printf("Recursos/Unidad actual: %.2f\n", recursosUnidad[indice]);
     printf("Nuevos recursos/unidad (numero > 0.0, o Enter para mantener): ");
     if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
         buffer[strcspn(buffer, "\n")] = '\0';
         if (strlen(buffer) > 0) {
             char extra;
             if (sscanf(buffer, "%f %c", &recursosNuevos, &extra) == 1 && recursosNuevos > 0.0f) {
                 recursosUnidad[indice] = recursosNuevos;
                 printf("Recursos/Unidad actualizados.\n");
             } else {
                 printf("Entrada invalida para recursos (debe ser numero > 0.0 sin extras). No se modifico.\n");
             }
         } else {
            printf("Recursos/Unidad no modificados.\n");
         }
    } else {
         printf("Error leyendo entrada para recursos. No se modifico.\n");
    }

     printf("Edicion finalizada para el producto '%s'.\n", nombres[indice]); // Muestra el nombre final

}

void eliminarProducto(char nombres[][MAX_NOMBRE], int demandas[], float tiemposUnidad[], float recursosUnidad[], int *numProductosActual) {
     if (*numProductosActual == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }

    char nombreAEliminar[MAX_NOMBRE];
    printf("\n--- Eliminar Producto ---\n");
    mostrarDatosProductos(nombres, demandas, tiemposUnidad, recursosUnidad, *numProductosActual);

    if (!leerCadenaValida("Ingrese el nombre EXACTO del producto a eliminar: ", nombreAEliminar, MAX_NOMBRE)) {
        return;
    }

    int indice = buscarProductoIndice(nombres, *numProductosActual, nombreAEliminar);

    if (indice == -1) {
        printf("Producto '%s' no encontrado.\n", nombreAEliminar);
        return;
    }

    for (int j = indice; j < *numProductosActual - 1; j++) {
        strcpy(nombres[j], nombres[j + 1]);
        demandas[j] = demandas[j + 1];
        tiemposUnidad[j] = tiemposUnidad[j + 1];
        recursosUnidad[j] = recursosUnidad[j + 1];
    }

    (*numProductosActual)--;

    printf("Producto '%s' eliminado exitosamente.\n", nombreAEliminar);
}

void mostrarConsideraciones() {
    printf("\n--- CONSIDERACIONES DEL PROYECTO ---\n");
    printf("Consideraciones Externas (Ejemplos):\n");
    printf(" * Cumplimiento de normativas de seguridad electrica (ej: UL, CE).\n");
    printf(" * Regulaciones ambientales para componentes (ej: RoHS).\n");
    printf(" * Impuestos aplicables a la importacion de materiales o exportacion de productos.\n");
    printf(" * Acuerdos de nivel de servicio (SLA) con clientes sobre tiempos de entrega.\n");
    printf(" * Disponibilidad y costo de materias primas en el mercado global.\n");
    printf("\n");
    printf("Consideraciones Internas (Ejemplos):\n");
    printf(" * Lenguaje de Programacion: C (estandar C99 o posterior).\n");
    printf(" * Almacenamiento de Datos: Arreglos paralelos en memoria (sin persistencia en disco).\n");
    printf(" * Limitaciones de la Linea: Tiempo maximo de operacion diario/semanal, numero de operarios.\n");
    printf(" * Capacidad de Almacenamiento Interno: Espacio para materias primas y producto terminado.\n");
    printf(" * Mantenimiento de Maquinaria: Tiempos muertos planificados o no planificados.\n");
    printf(" * Control de Calidad: Porcentaje esperado de defectos, tiempo para pruebas.\n");
     printf(" * Interfaz de Usuario: Basada en consola de texto.\n");
}