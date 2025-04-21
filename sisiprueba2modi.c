#include <stdio.h>
#include <string.h>

// --- Constantes ---
#define MAX_PRODUCTOS 10
#define MAX_ID_LEN 30
#define MAX_NOMBRE_LEN 30
#define MAX_VENTAS 100

// --- Variables Globales ---
// Información de productos
char ids[MAX_PRODUCTOS][MAX_ID_LEN];
char nombres[MAX_PRODUCTOS][MAX_NOMBRE_LEN];
int stocks[MAX_PRODUCTOS];
float precios[MAX_PRODUCTOS];
float ventasPorProducto[MAX_PRODUCTOS]; // NUEVO: Array para acumular ventas por producto
int numProductos = 0;

// Ganancias globales y detalle
float total_ganancias = 0;
float ganancias[MAX_VENTAS];
int contadorVentas = 0;

// --- Prototipos de Funciones ---
int mostrarMenuYObtenerOpcion();
void registrarProducto();
void venderProducto();
void reabastecerProducto();
void mostrarInfoProductos();
void eliminarProducto();
void mostrarGanancias();
void mostrarVentasMaxMinPorProducto(); // NUEVO: Prototipo para reporte max/min
void limpiarBufferEntrada();
int buscarProductoPorID(const char* id_buscar);

// --- Función Principal (Orquestador) ---
int main() {
    int opcion_menu;

    do {
        opcion_menu = mostrarMenuYObtenerOpcion();

        switch(opcion_menu) {
            case 1:
                registrarProducto();
                break;
            case 2:
                if (numProductos == 0) {
                     printf("\tError: No hay productos registrados para vender.\n");
                } else {
                    venderProducto();
                }
                break;
            case 3:
                 if (numProductos == 0) {
                    printf("\tError: No hay productos registrados para reabastecer.\n");
                } else {
                    reabastecerProducto();
                }
                break;
            case 4:
                mostrarInfoProductos();
                break;
            case 5:
                 eliminarProducto();
                 break;
            case 6:
                 mostrarVentasMaxMinPorProducto(); // NUEVO: Llamada a la función
                 break;
            case 7:
                mostrarGanancias(); // Ganancias globales ahora es opción 7
                break;
            case 8:
                printf("\tSaliendo del programa...\n"); // Salir ahora es opción 8
                break;
        }

    } while (opcion_menu != 8); // Ajustar condición de salida

    return 0;
}

// --- Implementación de Funciones ---

void limpiarBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int buscarProductoPorID(const char* id_buscar) {
    for (int i = 0; i < numProductos; i++) {
        if (strcmp(ids[i], id_buscar) == 0) {
            return i;
        }
    }
    return -1;
}

int mostrarMenuYObtenerOpcion() {
    int opcion_local = 0;
    int resultado_scanf;
    int max_opcion = 8; // Ajustar al número total de opciones (ahora 8)

    do {
        printf("\n\tMenú de Opciones:\n");
        printf("\t1. Registrar nuevo producto\n");
        printf("\t2. Vender producto\n");
        printf("\t3. Reabastecer producto\n");
        printf("\t4. Mostrar información de todos los productos\n");
        printf("\t5. Eliminar producto\n");
        printf("\t6. Mostrar producto con más/menos ventas\n"); // NUEVO: Texto de opción
        printf("\t7. Mostrar total de ganancias globales\n"); // Opción ajustada
        printf("\t8. Salir\n"); // Opción ajustada
        printf("\tSeleccione una opción: ");

        resultado_scanf = scanf("%d", &opcion_local);
        limpiarBufferEntrada();

        if (resultado_scanf != 1) {
            printf("\tError: Entrada inválida. Por favor ingrese un número.\n");
            opcion_local = 0;
        } else if (opcion_local < 1 || opcion_local > max_opcion) {
            printf("\tOpción inválida. Intente nuevamente (1-%d).\n", max_opcion);
        }

    } while (opcion_local < 1 || opcion_local > max_opcion);

    return opcion_local;
}

void registrarProducto() {
    // ... (código interior de registrarProducto sin cambios, excepto la inicialización) ...

    if (numProductos >= MAX_PRODUCTOS) {
        printf("\tError: Se ha alcanzado el límite máximo de productos (%d).\n", MAX_PRODUCTOS);
        return;
    }

    // ...(resto del código para pedir id, nombre, stock, precio)...
    char id_nuevo[MAX_ID_LEN];
    char nombre_nuevo[MAX_NOMBRE_LEN];
    int stock_nuevo = 0;
    float precio_nuevo = 0.0f;
    int resultado_scanf;

    printf("\n\t--- Registrar Nuevo Producto ---\n");

    // Ingresar ID y validar duplicados
    while (1) {
        printf("\tIngrese el ID del nuevo producto: ");
        fgets(id_nuevo, sizeof(id_nuevo), stdin);
        id_nuevo[strcspn(id_nuevo, "\n")] = '\0';

        if (strlen(id_nuevo) == 0) {
            printf("\tError: El ID no puede estar vacío.\n");
            continue;
        }
        if (buscarProductoPorID(id_nuevo) != -1) {
            printf("\tError: Ya existe un producto con el ID '%s'.\n", id_nuevo);
            continue;
        }
        break; // ID válido y no duplicado
    }

    // Ingresar Nombre
    do {
        printf("\tIngrese el nombre del nuevo producto: ");
        fgets(nombre_nuevo, sizeof(nombre_nuevo), stdin);
        nombre_nuevo[strcspn(nombre_nuevo, "\n")] = '\0';
        if (strlen(nombre_nuevo) == 0) {
            printf("\tError: El nombre no puede estar vacío.\n");
        }
    } while (strlen(nombre_nuevo) == 0);

    // Ingresar Stock
    do {
        printf("\tIngrese la cantidad inicial en stock: ");
        resultado_scanf = scanf("%d", &stock_nuevo);
        limpiarBufferEntrada();
        if (resultado_scanf != 1) {
            printf("\tError: Entrada inválida (no es un número entero).\n");
            stock_nuevo = -1;
        } else if (stock_nuevo < 0) { // Permitimos stock 0 inicial, pero no negativo
            printf("\tError, el stock no puede ser negativo. Intente nuevamente.\n");
        }
    } while (stock_nuevo < 0);

    // Ingresar Precio
    do {
        printf("\tIngrese el precio unitario del producto: ");
        resultado_scanf = scanf("%f", &precio_nuevo);
        limpiarBufferEntrada();
         if (resultado_scanf != 1) {
            printf("\tError: Entrada inválida (no es un número).\n");
            precio_nuevo = -1.0f;
        } else if (precio_nuevo <= 0) {
            printf("\tError, ingrese un precio válido mayor que 0.\n");
        }
    } while (precio_nuevo <= 0);


    // Añadir producto a los arrays
    strcpy(ids[numProductos], id_nuevo);
    strcpy(nombres[numProductos], nombre_nuevo);
    stocks[numProductos] = stock_nuevo;
    precios[numProductos] = precio_nuevo;
    ventasPorProducto[numProductos] = 0.0f; // NUEVO: Inicializar ventas acumuladas para este producto
    numProductos++;

    printf("\tProducto '%s' registrado con éxito!\n", nombre_nuevo);
}

void venderProducto() {
    // ... (declaraciones iniciales de venderProducto) ...
    char id_venta[MAX_ID_LEN];
    int indice_producto;
    int cantidad_local;
    float venta_actual, venta_sin_desc, desc_aplicado, porcentaje_desc;
    int resultado_scanf;

    printf("\n\t--- Vender Producto ---\n");

    printf("\tIngrese el ID del producto a vender: ");
    fgets(id_venta, sizeof(id_venta), stdin);
    id_venta[strcspn(id_venta, "\n")] = '\0';
    indice_producto = buscarProductoPorID(id_venta);

    if (indice_producto == -1) {
        printf("\tError: Producto con ID '%s' no encontrado.\n", id_venta);
        return;
    }
     printf("\tProducto seleccionado: %s (Stock: %d, Precio: $%.2f)\n",
           nombres[indice_producto], stocks[indice_producto], precios[indice_producto]);

    if (stocks[indice_producto] == 0) {
        printf("\tNo hay stock disponible para '%s'. Reabastezca primero.\n", nombres[indice_producto]);
        return;
    }
    // ... (código para pedir cantidad) ...
     do {
        printf("\tIngrese la cantidad a vender: ");
        resultado_scanf = scanf("%d", &cantidad_local);
        limpiarBufferEntrada();

        if (resultado_scanf != 1) {
            printf("\tError: Entrada inválida (no es un número entero).\n");
            cantidad_local = -1;
        } else if (cantidad_local < 1 || cantidad_local > stocks[indice_producto]) {
            printf("\tCantidad inválida. Intente nuevamente (Stock disponible: %d).\n", stocks[indice_producto]);
        }
    } while (cantidad_local < 1 || cantidad_local > stocks[indice_producto]);

    // ... (cálculo de venta_sin_desc, porcentaje_desc, desc_aplicado, venta_actual) ...
     venta_sin_desc = cantidad_local * precios[indice_producto];
    porcentaje_desc = 0.0f;
     if (cantidad_local > 20) {
        porcentaje_desc = 5.0f;
        printf("\tAplicando descuento automático del 5%% por comprar más de 20 unidades.\n");
    }
    desc_aplicado = venta_sin_desc * (porcentaje_desc / 100.0f);
    venta_actual = venta_sin_desc - desc_aplicado;

    // ... (impresión de detalles de venta) ...
    printf("\t----------------------------------\n");
    printf("\tVenta sin descuento: $%.2f\n", venta_sin_desc);
    if (porcentaje_desc > 0) {
      printf("\tDescuento aplicado (%.1f%%): $%.2f\n", porcentaje_desc, desc_aplicado);
    }
    printf("\tTotal de la venta: $%.2f\n", venta_actual);
    printf("\t----------------------------------\n");


    // Actualizar globales
    total_ganancias += venta_actual;
    ventasPorProducto[indice_producto] += venta_actual; // NUEVO: Acumular venta para este producto
    if (contadorVentas < MAX_VENTAS) {
        ganancias[contadorVentas++] = venta_actual;
    } else {
        printf("\tAdvertencia: Límite de registro de ventas individuales alcanzado.\n");
    }
    stocks[indice_producto] -= cantidad_local;

    // ... (mensaje de stock cero y éxito) ...
     if (stocks[indice_producto] == 0) {
        printf("\t¡Se ha vendido todo el stock de '%s'!\n", nombres[indice_producto]);
    }
    printf("\tVenta registrada con éxito.\n");
}

void reabastecerProducto() {
    // ... (sin cambios internos, ya opera sobre el índice correcto) ...
     char id_reabastecer[MAX_ID_LEN];
    int indice_producto;
    int cantidad_local;
    int resultado_scanf;

    printf("\n\t--- Reabastecer Producto ---\n");

    printf("\tIngrese el ID del producto a reabastecer: ");
    fgets(id_reabastecer, sizeof(id_reabastecer), stdin);
    id_reabastecer[strcspn(id_reabastecer, "\n")] = '\0';
    indice_producto = buscarProductoPorID(id_reabastecer);

    if (indice_producto == -1) {
        printf("\tError: Producto con ID '%s' no encontrado.\n", id_reabastecer);
        return;
    }
     printf("\tProducto seleccionado: %s (Stock actual: %d)\n",
           nombres[indice_producto], stocks[indice_producto]);

    do {
        printf("\tIngrese la cantidad a agregar al stock: ");
        resultado_scanf = scanf("%d", &cantidad_local);
        limpiarBufferEntrada();

        if (resultado_scanf != 1) {
            printf("\tError: Entrada inválida (no es un número entero).\n");
            cantidad_local = -1;
        } else if (cantidad_local < 1) {
            printf("\tError, la cantidad a agregar debe ser al menos 1.\n");
        }
    } while (cantidad_local < 1);

    stocks[indice_producto] += cantidad_local;
    printf("\tStock agregado con éxito. Nuevo stock para '%s': %d\n",
           nombres[indice_producto], stocks[indice_producto]);
}

void mostrarInfoProductos() {
    // ... (sin cambios) ...
     printf("\n\t--- Información de Productos Registrados ---\n");
     if (numProductos == 0) {
         printf("\tNo hay productos registrados.\n");
         return;
     }
     printf("\t---------------------------------------------------------------------\n");
     printf("\t| %-15s | %-25s | %-10s | %-12s |\n", "ID", "Nombre", "Stock", "Precio Unit.");
     printf("\t---------------------------------------------------------------------\n");
     for (int i = 0; i < numProductos; i++) {
         printf("\t| %-15s | %-25s | %-10d | $% -11.2f |\n",
                ids[i], nombres[i], stocks[i], precios[i]);
     }
     printf("\t---------------------------------------------------------------------\n");
}

void eliminarProducto() {
    // ... (código interior de eliminarProducto sin cambios, excepto el array de ventas) ...
     char id_eliminar[MAX_ID_LEN];
    int indice_producto;
    char confirmacion;

    printf("\n\t--- Eliminar Producto ---\n");
     if (numProductos == 0) {
        printf("\tNo hay productos registrados para eliminar.\n");
        return;
    }
    printf("\tIngrese el ID del producto a eliminar: ");
    fgets(id_eliminar, sizeof(id_eliminar), stdin);
    id_eliminar[strcspn(id_eliminar, "\n")] = '\0';
    indice_producto = buscarProductoPorID(id_eliminar);

    if (indice_producto == -1) {
        printf("\tError: Producto con ID '%s' no encontrado.\n", id_eliminar);
        return;
    }
     printf("\tProducto encontrado: ID: %s, Nombre: %s, Stock: %d, Precio: $%.2f\n",
           ids[indice_producto], nombres[indice_producto], stocks[indice_producto], precios[indice_producto]);
    printf("\t¿Está seguro de que desea eliminar este producto? (S/N): ");
    confirmacion = getchar();
    limpiarBufferEntrada();

    if (confirmacion == 'S' || confirmacion == 's') {
        // Eliminar moviendo los elementos posteriores una posición hacia atrás
        for (int i = indice_producto; i < numProductos - 1; i++) {
            strcpy(ids[i], ids[i+1]);
            strcpy(nombres[i], nombres[i+1]);
            stocks[i] = stocks[i+1];
            precios[i] = precios[i+1];
            ventasPorProducto[i] = ventasPorProducto[i+1]; // NUEVO: Mover también las ventas acumuladas
        }
        numProductos--;
        printf("\tProducto con ID '%s' eliminado con éxito.\n", id_eliminar);
    } else {
        printf("\tEliminación cancelada.\n");
    }
}

// NUEVA FUNCIÓN para mostrar el producto con más y menos ventas
void mostrarVentasMaxMinPorProducto() {
    printf("\n\t--- Reporte de Ventas Máximas y Mínimas por Producto ---\n");

    if (numProductos == 0) {
        printf("\tNo hay productos registrados.\n");
        return;
    }
    // Verificar si hubo alguna venta en general
    int huboVentas = 0;
    for(int i=0; i<numProductos; i++){
        if(ventasPorProducto[i] > 0){
            huboVentas = 1;
            break;
        }
    }
    // Alternativamente, podríamos usar contadorVentas > 0, pero chequear el array es más directo
    // if (contadorVentas == 0) {

    if (!huboVentas) {
         printf("\tAún no se han registrado ventas para ningún producto.\n");
         // Mostrar ventas actuales (todas 0)
          printf("\tVentas acumuladas por producto:\n");
          for(int i=0; i<numProductos; i++){
               printf("\t- %s (%s): $%.2f\n", nombres[i], ids[i], ventasPorProducto[i]);
          }
         return;
    }


    // Inicializar con el primer producto
    int indiceMax = 0;
    int indiceMin = 0;
    float maxVentas = ventasPorProducto[0];
    float minVentas = ventasPorProducto[0];

    // Recorrer el resto de productos para encontrar máx y min
    for (int i = 1; i < numProductos; i++) {
        if (ventasPorProducto[i] > maxVentas) {
            maxVentas = ventasPorProducto[i];
            indiceMax = i;
        }
        // Podríamos decidir si un producto con 0 ventas cuenta como mínimo
        // Aquí asumimos que sí cuenta si es menor que el mínimo actual.
        if (ventasPorProducto[i] < minVentas) {
            minVentas = ventasPorProducto[i];
            indiceMin = i;
        }
    }

    // Mostrar resultados
    printf("\tProducto con MAYORES ventas acumuladas:\n");
    printf("\t ID: %s\n", ids[indiceMax]);
    printf("\t Nombre: %s\n", nombres[indiceMax]);
    printf("\t Ventas Totales: $%.2f\n", maxVentas);

    printf("\n\tProducto con MENORES ventas acumuladas:\n");
    printf("\t ID: %s\n", ids[indiceMin]);
    printf("\t Nombre: %s\n", nombres[indiceMin]);
    printf("\t Ventas Totales: $%.2f\n", minVentas);

     // Opcional: Mostrar todas las ventas por producto para contexto
     printf("\n\tVentas acumuladas por producto (detalle):\n");
     for(int i=0; i<numProductos; i++){
          printf("\t- %s (%s): $%.2f\n", nombres[i], ids[i], ventasPorProducto[i]);
     }
}


void mostrarGanancias() {
     // ... (sin cambios internos) ...
    printf("\n\t--- Reporte de Ganancias Globales ---\n");
    if (contadorVentas == 0) {
        printf("\tAún no se han registrado ventas.\n");
    } else {
        printf("\tDetalle de Ventas Individuales (Global):\n");
        for (int i = 0; i < contadorVentas; i++) {
            printf("\t Venta %d: $%.2f\n", i + 1, ganancias[i]);
        }
    }
    printf("\t----------------------------------\n");
    printf("\tTotal de ganancias acumuladas (Global): $%.2f\n", total_ganancias);
}