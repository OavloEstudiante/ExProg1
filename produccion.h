#ifndef PRODUCCION_H
#define PRODUCCION_H

#include <stdio.h> 

#define MAX_PRODUCTOS 5
#define MAX_NOMBRE 50

void limpiarBufferEntradaStdin();
int leerCadenaValida(char mensaje[], char destino[], int longitudMax);
int leerEnteroPositivo(char mensaje[]);
float leerFlotantePositivo(char mensaje[]);
void mostrarMenuProduccion(); // <--- Necesaria si se llama desde main
int existeProducto(char nombres[][MAX_NOMBRE], int numProductosActual, const char nombreNuevo[]);
int buscarProductoIndice(char nombres[][MAX_NOMBRE], int numProductosActual, const char nombreBuscado[]);
void ingresarDatosProductos(char nombres[][MAX_NOMBRE], int demandas[], float tiemposUnidad[], float recursosUnidad[], int *numProductosActual);
void mostrarDatosProductos(const char nombres[][MAX_NOMBRE], const int demandas[], const float tiemposUnidad[], const float recursosUnidad[], int numProductosActual);
float calcularTiempoTotal(const int demandas[], const float tiemposUnidad[], int numProductosActual);
float calcularRecursosTotales(const int demandas[], const float recursosUnidad[], int numProductosActual);
void verificarViabilidadProduccion(const int demandas[], const float tiemposUnidad[], const float recursosUnidad[], int numProductosActual);
void editarProducto(char nombres[][MAX_NOMBRE], int demandas[], float tiemposUnidad[], float recursosUnidad[], int numProductosActual);
void eliminarProducto(char nombres[][MAX_NOMBRE], int demandas[], float tiemposUnidad[], float recursosUnidad[], int *numProductosActual);
void mostrarConsideraciones();

#endif 