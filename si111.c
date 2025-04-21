#include <stdio.h>
#include <string.h> // Solo las dos librerías originales
#include <float.h>  // Necesaria para FLT_MAX y -FLT_MAX (o DBL_MAX/-DBL_MAX si usas double)

// --- Constantes Globales ---
const int MAX_ESTUDIANTES = 5;
const int MAX_MATERIAS = 3;
const int MAX_NOMBRE = 50;

// --- Prototipos de Funciones ---
int obtenerNumeroEstudiantes();
int obtenerNumeroMaterias();
void ingresarNombresEstudiantes(int numEstudiantes, char estudiantes[][MAX_NOMBRE]);
void ingresarNombresMaterias(int numMaterias, char materias[][MAX_NOMBRE]);
void ingresarNotasEstudiantes(int numEstudiantes, int numMaterias, char estudiantes[][MAX_NOMBRE], char materias[][MAX_NOMBRE], float notas[][MAX_MATERIAS]);
void mostrarYProcesarMenuReportes(int numEstudiantes, int numMaterias, char estudiantes[][MAX_NOMBRE], char materias[][MAX_NOMBRE], float notas[][MAX_MATERIAS]);
int preguntarRepetir();
// --- NUEVOS PROTOTIPOS ---
void mostrarEstudianteMejorPeorPromedio(int numEstudiantes, int numMaterias, char estudiantes[][MAX_NOMBRE], float notas[][MAX_MATERIAS]);
void mostrarMateriaMejorPeorPromedio(int numEstudiantes, int numMaterias, char materias[][MAX_NOMBRE], float notas[][MAX_MATERIAS]);


// --- Función Principal (Orquestador) ---
int main(int argc, char *argv[]) {
    // Variables principales declaradas en main
    char estudiantes[MAX_ESTUDIANTES][MAX_NOMBRE];
    char materias[MAX_MATERIAS][MAX_NOMBRE];
    float notas[MAX_ESTUDIANTES][MAX_MATERIAS]; // Correcta dimensión
    int numEstudiantes = 0;
    int numMaterias = 0;
    int repetir;

    do {
        // Llamadas secuenciales a las funciones que encapsulan la lógica original
        numEstudiantes = obtenerNumeroEstudiantes();
        numMaterias = obtenerNumeroMaterias();

        ingresarNombresEstudiantes(numEstudiantes, estudiantes);
        ingresarNombresMaterias(numMaterias, materias);

        // Solo ingresar notas si hay estudiantes Y materias
        if (numEstudiantes > 0 && numMaterias > 0) {
             ingresarNotasEstudiantes(numEstudiantes, numMaterias, estudiantes, materias, notas);
             mostrarYProcesarMenuReportes(numEstudiantes, numMaterias, estudiantes, materias, notas);
        } else {
             printf("\n\tNo se pueden ingresar notas ni mostrar reportes sin estudiantes y materias.\n");
        }


        repetir = preguntarRepetir();

    } while (repetir == 1);

    printf("\n\tQue tenga un lindo dia lleno de emocion\n");
    return 0;
}

// --- Implementación de Funciones (Lógica 100% copiada del main original + Nuevas Funciones) ---

// ... (Las funciones obtenerNumeroEstudiantes, obtenerNumeroMaterias,
//      ingresarNombresEstudiantes, ingresarNombresMaterias, ingresarNotasEstudiantes
//      permanecen EXACTAMENTE IGUAL que en tu código original) ...

int obtenerNumeroEstudiantes() {
    char entrada[100]; // Buffer local para la entrada
    int numEstudiantes = 0;
    // Bucle y validación exactamente como en el original
    do {
        printf("\tIngrese el numero de estudiantes (1-%d): ", MAX_ESTUDIANTES);
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0'; // Quitar newline
        if (strlen(entrada) == 0) {
            printf("\tError, la entrada no puede estar vacia.\n");
            numEstudiantes = 0; // Asegurar estado inválido para el bucle
            continue;
        }
        int valido = 1;
        for (int i = 0; entrada[i] != '\0'; i++) {
            if (entrada[i] < '0' || entrada[i] > '9') {
                valido = 0;
                break;
            }
        }
        if (!valido) {
            printf("\tError, solo se permiten numeros.\n");
            numEstudiantes = 0;
            continue;
        }
        // Conversión manual y chequeo de overflow original
        numEstudiantes = 0;
        for (int i = 0; entrada[i] != '\0'; i++) {
             // Chequeo de overflow INT_MAX (asumiendo 32 bits como en original)
             // Nota: Usar <limits.h> e INT_MAX sería más portable
            if (numEstudiantes > (2147483647 / 10) || (numEstudiantes == (2147483647 / 10) && (entrada[i] - '0') > (2147483647 % 10))) {
                 printf("\tError, numero demasiado grande.\n");
                 numEstudiantes = 0; // Resetear para invalidar
                 valido = 0;       // Marcar como inválido
                 break;            // Salir del bucle de conversión
            }
            numEstudiantes = numEstudiantes * 10 + (entrada[i] - '0');
        }
        if (!valido) continue; // Si hubo overflow, repetir el do-while

        // Chequeo de rango original
        if (numEstudiantes < 1 || numEstudiantes > MAX_ESTUDIANTES) {
            printf("\tError, el numero debe estar entre 1 y %d.\n", MAX_ESTUDIANTES);
            // numEstudiantes ya tiene el valor inválido o fuera de rango, el bucle continuará
        }
        // La condición del while se encarga de repetir si es necesario
    } while (numEstudiantes < 1 || numEstudiantes > MAX_ESTUDIANTES);
    return numEstudiantes; // Retorna el número validado
}

int obtenerNumeroMaterias() {
    char entrada[100]; // Buffer local
    int numMaterias = 0;
    // Bucle y validación exactamente como en el original
    do {
        printf("\tIngrese el numero de materias (1-%d): ", MAX_MATERIAS);
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
        if (strlen(entrada) == 0) {
            printf("\tError, la entrada no puede estar vacia.\n");
            numMaterias = 0;
            continue;
        }
        int valido = 1;
        for (int i = 0; entrada[i] != '\0'; i++) {
            if (entrada[i] < '0' || entrada[i] > '9') {
                valido = 0;
                break;
            }
        }
        if (!valido) {
            printf("\tError, solo se permiten numeros.\n");
            numMaterias = 0;
            continue;
        }
        // Conversión manual y chequeo de overflow original
        numMaterias = 0;
        for (int i = 0; entrada[i] != '\0'; i++) {
            if (numMaterias > (2147483647 / 10) || (numMaterias == (2147483647 / 10) && (entrada[i] - '0') > (2147483647 % 10))) {
                 printf("\tError, numero demasiado grande.\n");
                 numMaterias = 0;
                 valido = 0;
                 break;
            }
            numMaterias = numMaterias * 10 + (entrada[i] - '0');
        }
         if (!valido) continue;

        // Chequeo de rango original
        if (numMaterias < 1 || numMaterias > MAX_MATERIAS) {
            printf("\tError, el numero de materias debe estar entre 1 y %d.\n", MAX_MATERIAS);
        }
    } while (numMaterias < 1 || numMaterias > MAX_MATERIAS);
    return numMaterias; // Retorna el número validado
}

void ingresarNombresEstudiantes(int numEstudiantes, char estudiantes[][MAX_NOMBRE]) {
    char entrada[MAX_NOMBRE]; // Buffer local adecuado para nombres
    printf("\n\tIngreso de Nombres de Estudiantes\n");
    for (int i = 0; i < numEstudiantes; i++) {
        // Bucle while(1) y validaciones internas copiadas tal cual
        while (1) {
            printf("\tIngrese el nombre del estudiante %d: ", i + 1);
            fgets(entrada, sizeof(entrada), stdin); // Leer en buffer temporal
            entrada[strcspn(entrada, "\n")] = '\0';

            if (strlen(entrada) == 0) {
                printf("\tError, el nombre no puede estar vacio.\n");
                continue;
            }

            int valido = 1;
            for (int j = 0; entrada[j] != '\0'; j++) {
                if (!((entrada[j] >= 'A' && entrada[j] <= 'Z') ||
                      (entrada[j] >= 'a' && entrada[j] <= 'z') ||
                      entrada[j] == ' ')) {
                    valido = 0;
                    break;
                }
            }
            if (!valido) {
                printf("\tError, solo se permiten letras y espacios.\n");
                continue;
            }

            int repetido = 0;
            for (int j = 0; j < i; j++) { // Comparar con los ya ingresados en 'estudiantes'
                if (strcmp(entrada, estudiantes[j]) == 0) {
                    repetido = 1;
                    break;
                }
            }
            if (repetido) {
                printf("\tError, el nombre ya ha sido ingresado.\n");
                continue;
            }

            // Si todo es válido, copiar al array final y salir del while(1)
            strcpy(estudiantes[i], entrada);
            break;
        }
    }
}

void ingresarNombresMaterias(int numMaterias, char materias[][MAX_NOMBRE]) {
    char entrada[MAX_NOMBRE]; // Buffer local
    printf("\n\tIngreso de Nombres de Materias\n");
    for (int i = 0; i < numMaterias; i++) {
        // Bucle while(1) y validaciones internas copiadas tal cual
        while (1) {
            printf("\tIngrese el nombre de la materia %d: ", i + 1);
            fgets(entrada, sizeof(entrada), stdin); // Leer en buffer temporal
            entrada[strcspn(entrada, "\n")] = '\0';

            if (strlen(entrada) == 0) {
                printf("\tError, el nombre no puede estar vacio.\n");
                continue;
            }

            int valido = 1;
            for (int j = 0; entrada[j] != '\0'; j++) {
                 if (!((entrada[j] >= 'A' && entrada[j] <= 'Z') ||
                       (entrada[j] >= 'a' && entrada[j] <= 'z') ||
                       entrada[j] == ' ')) {
                    valido = 0;
                    break;
                 }
            }
            if (!valido) {
                printf("\tError, solo se permiten letras y espacios.\n");
                continue;
            }

            int repetido = 0;
            for (int j = 0; j < i; j++) { // Comparar con las ya ingresadas en 'materias'
                if (strcmp(entrada, materias[j]) == 0) {
                    repetido = 1;
                    break;
                }
            }
            if (repetido) {
                printf("\tError, el nombre ya ha sido ingresado.\n");
                continue;
            }
            // Si todo es válido, copiar al array final y salir del while(1)
            strcpy(materias[i], entrada);
            break;
        }
    }
}

void ingresarNotasEstudiantes(int numEstudiantes, int numMaterias, char estudiantes[][MAX_NOMBRE], char materias[][MAX_NOMBRE], float notas[][MAX_MATERIAS]) {
    char entrada[100]; // Buffer local para leer la nota como texto
    printf("\n\tIngreso de Notas\n");
    for (int i = 0; i < numEstudiantes; i++) {
        printf("\tNotas para %s:\n", estudiantes[i]);
        for (int j = 0; j < numMaterias; j++) {
            // Bucle while(1) y validaciones copiadas tal cual, incluyendo parseo manual
            while (1) {
                printf("\tIngrese la nota de %s (0-10): ", materias[j]);
                fgets(entrada, sizeof(entrada), stdin);
                entrada[strcspn(entrada, "\n")] = '\0';

                if (strlen(entrada) == 0) {
                    printf("\tError, ingrese un numero valido entre 0 y 10.\n");
                    continue;
                }
                // Validación de formato original (dígitos y un punto)
                int valido = 1;
                int puntos = 0;
                for (int k = 0; entrada[k] != '\0'; k++) {
                    if (entrada[k] < '0' || entrada[k] > '9') {
                        if (entrada[k] == '.' && puntos == 0) {
                            puntos++;
                        } else {
                            valido = 0;
                            break;
                        }
                    }
                }
                if (strlen(entrada) == 1 && entrada[0] == '.') { // Check extra original
                    valido = 0;
                }
                if (!valido) {
                    printf("\tError, formato invalido. Ingrese un numero valido entre 0 y 10 (ej: 7, 9.5).\n");
                    continue;
                }

                // Parseo manual de float original
                float numNota = 0.0f;
                int puntoDecimal = 0;
                float divisor = 10.0f;
                for (int k = 0; entrada[k] != '\0'; k++) {
                    if (entrada[k] == '.') {
                        puntoDecimal = 1;
                    } else {
                        if (puntoDecimal) {
                            numNota += (float)(entrada[k] - '0') / divisor;
                            divisor *= 10.0f;
                        } else {
                            // Chequeo de overflow antes de multiplicar (simplificado para float)
                            // El parseo original no tenía chequeo explícito aquí, lo mantenemos así
                            numNota = numNota * 10 + (float)(entrada[k] - '0');
                        }
                    }
                }

                // Validación de rango original
                if (numNota < 0.0f || numNota > 10.0f) {
                    printf("\tError, la nota debe estar entre 0.0 y 10.0.\n");
                } else {
                    notas[i][j] = numNota; // Asignar nota válida
                    break; // Salir del while(1)
                }
            } // Fin while(1) validación nota
        } // Fin for materias
    } // Fin for estudiantes
}

// --- NUEVA FUNCIÓN: Estudiante con Mejor/Peor Promedio ---
void mostrarEstudianteMejorPeorPromedio(int numEstudiantes, int numMaterias, char estudiantes[][MAX_NOMBRE], float notas[][MAX_MATERIAS]) {
    // Verificación inicial
    if (numEstudiantes <= 0 || numMaterias <= 0) {
        printf("\n\tNo hay suficientes datos para calcular promedios de estudiantes.\n");
        return;
    }

    float mejorPromedio = -1.0f; // Inicializar con un valor menor que cualquier promedio posible
    float peorPromedio = 11.0f; // Inicializar con un valor mayor que cualquier promedio posible
    int indiceMejor = -1;
    int indicePeor = -1;

    printf("\n\t===== Mejor y Peor Promedio General por Estudiante =====\n");

    // Calcular promedio para cada estudiante
    for (int i = 0; i < numEstudiantes; i++) {
        float sumaNotasEstudiante = 0.0f;
        for (int j = 0; j < numMaterias; j++) {
            sumaNotasEstudiante += notas[i][j];
        }
        float promedioActual = sumaNotasEstudiante / numMaterias;

        // Actualizar mejor promedio
        // La condición 'indiceMejor == -1' maneja el primer estudiante
        if (indiceMejor == -1 || promedioActual > mejorPromedio) {
            mejorPromedio = promedioActual;
            indiceMejor = i;
        }

        // Actualizar peor promedio
        // La condición 'indicePeor == -1' maneja el primer estudiante
        if (indicePeor == -1 || promedioActual < peorPromedio) {
            peorPromedio = promedioActual;
            indicePeor = i;
        }
    }

    // Mostrar resultados
    if (indiceMejor != -1) { // Verificar que se encontró al menos un estudiante
        printf("\tEstudiante con MEJOR promedio: %s (%.2f)\n", estudiantes[indiceMejor], mejorPromedio);
    }
    if (indicePeor != -1) { // Verificar que se encontró al menos un estudiante
         printf("\tEstudiante con PEOR promedio: %s (%.2f)\n", estudiantes[indicePeor], peorPromedio);
    }
     if (indiceMejor == -1 || indicePeor == -1) { // Si algo falló (aunque no debería con las verificaciones)
         printf("\tNo se pudieron determinar los promedios.\n");
     }

}

// --- NUEVA FUNCIÓN: Materia con Mejor/Peor Promedio ---
void mostrarMateriaMejorPeorPromedio(int numEstudiantes, int numMaterias, char materias[][MAX_NOMBRE], float notas[][MAX_MATERIAS]) {
     // Verificación inicial
    if (numEstudiantes <= 0 || numMaterias <= 0) {
        printf("\n\tNo hay suficientes datos para calcular promedios de materias.\n");
        return;
    }

    float mejorPromedioMateria = -1.0f;
    float peorPromedioMateria = 11.0f;
    int indiceMejorMateria = -1;
    int indicePeorMateria = -1;

    printf("\n\t===== Mejor y Peor Promedio General por Materia =====\n");

    // Calcular promedio para cada materia
    for (int j = 0; j < numMaterias; j++) {
        float sumaNotasMateria = 0.0f;
        for (int i = 0; i < numEstudiantes; i++) {
            sumaNotasMateria += notas[i][j];
        }
        float promedioActualMateria = sumaNotasMateria / numEstudiantes;

        // Actualizar mejor promedio de materia
        if (indiceMejorMateria == -1 || promedioActualMateria > mejorPromedioMateria) {
            mejorPromedioMateria = promedioActualMateria;
            indiceMejorMateria = j;
        }

        // Actualizar peor promedio de materia
        if (indicePeorMateria == -1 || promedioActualMateria < peorPromedioMateria) {
            peorPromedioMateria = promedioActualMateria;
            indicePeorMateria = j;
        }
    }

    // Mostrar resultados
    if (indiceMejorMateria != -1) {
        printf("\tMateria con MEJOR promedio general: %s (%.2f)\n", materias[indiceMejorMateria], mejorPromedioMateria);
    }
     if (indicePeorMateria != -1) {
        printf("\tMateria con PEOR promedio general: %s (%.2f)\n", materias[indicePeorMateria], peorPromedioMateria);
     }
      if (indiceMejorMateria == -1 || indicePeorMateria == -1) {
         printf("\tNo se pudieron determinar los promedios de las materias.\n");
     }
}


// --- MODIFICADA: Función del Menú ---
void mostrarYProcesarMenuReportes(int numEstudiantes, int numMaterias, char estudiantes[][MAX_NOMBRE], char materias[][MAX_NOMBRE], float notas[][MAX_MATERIAS]) {
    char entrada[100]; // Buffer local
    int salirMenu = 0;
    do {
        printf("\n\tMenu de Reportes\n");
        printf("\t1.- Notas por estudiante\n");
        printf("\t2.- Promedios por materia\n");
        printf("\t3.- Aprobados/reprobados por materia\n");
        printf("\t4.- Ver TODOS los reportes generales\n");
        // --- NUEVAS OPCIONES ---
        printf("\t5.- Estudiante con mejor/peor promedio\n");
        printf("\t6.- Materia con mejor/peor promedio\n");
        // --- SALIR AHORA ES 7 ---
        printf("\t7.- Salir\n");
        printf("\tSeleccione una opcion (1-7): "); // Rango actualizado
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        // Validación de opción del menú actualizada
        if (strlen(entrada) != 1 || entrada[0] < '1' || entrada[0] > '7') { // Rango actualizado
            printf("\tError, opcion invalida. Ingrese un numero entre 1 y 7.\n"); // Mensaje actualizado
            continue; // Repetir bucle do-while del menú
        }

        int opcion = entrada[0] - '0'; // Conversión simple

        // Switch case original (con toda su lógica interna) + Nuevos Cases
        switch (opcion) {
            case 1: { // Usar llaves para crear un nuevo scope si se declaran variables dentro
                  // Bucle while(1) para selección de estudiante (copiado)
                  while (1) {
                      printf("\n\tSeleccione el estudiante\n");
                      for (int i = 0; i < numEstudiantes; i++) {
                          printf("\t%d.- %s\n", i + 1, estudiantes[i]);
                      }
                      printf("\t%d.- Todos los estudiantes\n", numEstudiantes + 1);
                      printf("\tIngrese el numero del estudiante (1-%d): ", numEstudiantes + 1);
                      fgets(entrada, sizeof(entrada), stdin);
                      entrada[strcspn(entrada, "\n")] = '\0';

                      if (strlen(entrada) == 0) {
                          printf("\tError, la entrada no puede estar vacia.\n");
                          continue;
                      }
                      // Validación de número original
                      int valido = 1;
                      for(int k=0; entrada[k] != '\0'; k++) {
                          if (entrada[k] < '0' || entrada[k] > '9') {
                              valido = 0; break;
                          }
                      }
                      if (!valido) {
                          printf("\tError, solo se permiten numeros.\n");
                          continue;
                      }
                      // Conversión manual original y chequeo de overflow
                      int seleccionEstudiante = 0;
                      valido = 1; // Resetear valido para el chequeo de overflow
                      for (int k = 0; entrada[k] != '\0'; k++) {
                          if (seleccionEstudiante > (2147483647 / 10) || (seleccionEstudiante == (2147483647 / 10) && (entrada[k] - '0') > (2147483647 % 10))) {
                               printf("\tError, numero demasiado grande.\n");
                               seleccionEstudiante = 0;
                               valido = 0;
                               break;
                          }
                          seleccionEstudiante = seleccionEstudiante * 10 + (entrada[k] - '0');
                      }
                      if (!valido) continue; // Si hubo overflow

                      // Chequeo de rango original
                      if (seleccionEstudiante < 1 || seleccionEstudiante > (numEstudiantes + 1)) {
                          printf("\tError, opcion invalida. Debe ser entre 1 y %d.\n", numEstudiantes + 1);
                          continue;
                      }

                      // Lógica de impresión de reportes (copiada)
                      if (seleccionEstudiante == numEstudiantes + 1) { // Todos
                          printf("\n\tNotas de Todos los Estudiantes\n");
                          for (int idx_loop = 0; idx_loop < numEstudiantes; idx_loop++) {
                              printf("\n\tEstudiante: %s\n", estudiantes[idx_loop]);
                              printf("\t%-25s\tNota\tEstado\n", "Materia");
                              int aprobadas = 0, reprobadas = 0;
                              float sumaNotas = 0.0f;
                              float maxNota = -1.0f, minNota = 11.0f; // Init seguro
                              if (numMaterias > 0) {
                                  // Inicializar min/max con la primera nota si existe
                                  maxNota = notas[idx_loop][0]; minNota = notas[idx_loop][0];
                                  for (int j = 0; j < numMaterias; j++) {
                                      sumaNotas += notas[idx_loop][j];
                                      const char *estado = (notas[idx_loop][j] >= 6.0f) ? "Aprobado" : "Reprobado";
                                      printf("\t%-25s\t%.2f\t%s\n", materias[j], notas[idx_loop][j], estado);
                                      if (notas[idx_loop][j] >= 6.0f) aprobadas++; else reprobadas++;
                                      if (notas[idx_loop][j] > maxNota) maxNota = notas[idx_loop][j];
                                      if (notas[idx_loop][j] < minNota) minNota = notas[idx_loop][j];
                                  }
                                  printf("\tPromedio: %.2f | Aprobadas: %d | Reprobadas: %d\n", (numMaterias > 0 ? sumaNotas / numMaterias : 0.0), aprobadas, reprobadas);
                                  printf("\tNota Maxima: %.2f | Nota Minima: %.2f\n", maxNota, minNota);
                              } else { printf("\tNo hay materias registradas.\n"); }
                          }
                      } else { // Uno solo
                          int idx = seleccionEstudiante - 1;
                          printf("\n\tNotas de %s:\n", estudiantes[idx]);
                          printf("\t%-25s\tNota\tEstado\n", "Materia");
                          int aprobadas = 0, reprobadas = 0;
                          float sumaNotas = 0.0f;
                          float maxNota = -1.0f, minNota = 11.0f; // Init seguro
                          if (numMaterias > 0) {
                               // Inicializar min/max con la primera nota si existe
                              maxNota = notas[idx][0]; minNota = notas[idx][0];
                              for (int j = 0; j < numMaterias; j++) {
                                  sumaNotas += notas[idx][j];
                                  const char *estado = (notas[idx][j] >= 6.0f) ? "Aprobado" : "Reprobado";
                                  printf("\t%-25s\t%.2f\t%s\n", materias[j], notas[idx][j], estado);
                                  if (notas[idx][j] >= 6.0f) aprobadas++; else reprobadas++;
                                  if (notas[idx][j] > maxNota) maxNota = notas[idx][j];
                                  if (notas[idx][j] < minNota) minNota = notas[idx][j];
                              }
                              printf("\tPromedio: %.2f | Aprobadas: %d | Reprobadas: %d\n", (numMaterias > 0 ? sumaNotas / numMaterias : 0.0), aprobadas, reprobadas);
                              printf("\tNota Maxima: %.2f | Nota Minima: %.2f\n", maxNota, minNota);
                          } else { printf("\tNo hay materias registradas.\n"); }
                      }
                      break; // Salir del while(1) de selección de estudiante
                  } // Fin while(1) selección estudiante
                  break; // Fin case 1
            } // Fin scope case 1
            case 2: {
                  // Lógica de promedios por materia (copiada)
                  printf("\n\t===== Promedios por materia =====\n");
                  printf("\t%-25s\tPromedio\tNota mas alta\tNota mas baja\n", "Materia");
                  for (int j = 0; j < numMaterias; j++) {
                      if (numEstudiantes > 0) {
                          float suma = 0;
                          // Inicializar min/max con la primera nota si existe
                          float maxNota = notas[0][j]; float minNota = notas[0][j];
                          for (int i = 0; i < numEstudiantes; i++) {
                              suma += notas[i][j];
                              if (notas[i][j] > maxNota) maxNota = notas[i][j];
                              if (notas[i][j] < minNota) minNota = notas[i][j];
                          }
                          printf("\t%-25s\t%.2f\t\t%.2f\t\t%.2f\n", materias[j], (numEstudiantes > 0 ? suma / numEstudiantes : 0.0), maxNota, minNota);
                      } else {
                          printf("\t%-25s\t N/A\t\t N/A\t\t N/A\n", materias[j]);
                      }
                  }
                  if (numMaterias == 0) printf("\t(No hay materias registradas)\n");
                  break; // Fin case 2
            } // Fin scope case 2
            case 3: {
                  // Lógica aprobados/reprobados (copiada)
                  printf("\n\t===== Aprobados y Reprobados por materia =====\n");
                  printf("\t%-25s\tAprobados\tReprobados\n", "Materia");
                  for (int j = 0; j < numMaterias; j++) {
                      int aprob = 0, reprob = 0;
                      if (numEstudiantes > 0) {
                          for (int i = 0; i < numEstudiantes; i++) {
                              if (notas[i][j] >= 6.0f) aprob++; else reprob++;
                          }
                          printf("\t%-25s\t%d\t\t%d\n", materias[j], aprob, reprob);
                      } else {
                           printf("\t%-25s\t0\t\t0\n", materias[j]);
                      }
                  }
                  if (numMaterias == 0) {
                      printf("\t(No hay materias registradas)\n");
                      break; // Salir si no hay materias
                  }

                  printf("\n\t===== Nombres de Aprobados y Reprobados por materia =====\n");
                  for (int j = 0; j < numMaterias; j++) {
                      printf("\t--- Materia: %s ---\n", materias[j]);
                      printf("\t Aprobados: "); int countAprob = 0;
                      for (int i = 0; i < numEstudiantes; i++) {
                          if (notas[i][j] >= 6.0f) {
                              if (countAprob > 0) printf(", "); printf("%s", estudiantes[i]); countAprob++;
                          }
                      } if (countAprob == 0) printf("(Ninguno)"); printf("\n");
                      printf("\t Reprobados: "); int countReprob = 0;
                      for (int i = 0; i < numEstudiantes; i++) {
                          if (notas[i][j] < 6.0f) {
                              if (countReprob > 0) printf(", "); printf("%s", estudiantes[i]); countReprob++;
                          }
                      } if (countReprob == 0) printf("(Ninguno)"); printf("\n");
                  }
                  break; // Fin case 3
            } // Fin scope case 3
            case 4: {
                  // Lógica "Todos los reportes" (copiada)
                  printf("\n\tReportes:\n");
                  // Promedio por estudiante
                  printf("\n\t===== Promedios por estudiante =====\n");
                  printf("\t%-25s\tPromedio\tNota mas alta\tNota mas baja\n", "Nombre Estudiante");
                  if (numEstudiantes > 0 && numMaterias > 0) {
                      for (int i = 0; i < numEstudiantes; i++) {
                          float suma = 0;
                          // Inicializar min/max con la primera nota si existe
                          float maxNota = notas[i][0]; float minNota = notas[i][0];
                          for (int j = 0; j < numMaterias; j++) {
                              suma += notas[i][j];
                              if (notas[i][j] > maxNota) maxNota = notas[i][j];
                              if (notas[i][j] < minNota) minNota = notas[i][j];
                          }
                          printf("\t%-25s\t%.2f\t\t%.2f\t\t%.2f\n", estudiantes[i], (numMaterias > 0 ? suma / numMaterias : 0.0), maxNota, minNota);
                      }
                  } else { printf("\t (No hay suficientes datos para calcular promedios por estudiante)\n"); }
                  // Promedio por materia
                  printf("\n\t===== Promedios por materia =====\n");
                  printf("\t%-25s\tPromedio\tNota mas alta\tNota mas baja\n", "Materia");
                  for (int j = 0; j < numMaterias; j++) {
                      if (numEstudiantes > 0) {
                          float suma = 0;
                          // Inicializar min/max con la primera nota si existe
                           float maxNota = notas[0][j]; float minNota = notas[0][j];
                          for (int i = 0; i < numEstudiantes; i++) {
                              suma += notas[i][j];
                              if (notas[i][j] > maxNota) maxNota = notas[i][j];
                              if (notas[i][j] < minNota) minNota = notas[i][j];
                          }
                          printf("\t%-25s\t%.2f\t\t%.2f\t\t%.2f\n", materias[j], (numEstudiantes > 0 ? suma / numEstudiantes : 0.0), maxNota, minNota);
                      } else { printf("\t%-25s\t N/A\t\t N/A\t\t N/A\n", materias[j]); }
                  } if (numMaterias == 0) printf("\t(No hay materias registradas)\n");
                  // Aprobados/Reprobados
                  printf("\n\t===== Aprobados y Reprobados por materia =====\n");
                  printf("\t%-25s\tAprobados\tReprobados\n", "Materia");
                  for (int j = 0; j < numMaterias; j++) {
                      int aprob = 0, reprob = 0;
                      if (numEstudiantes > 0) {
                          for (int i = 0; i < numEstudiantes; i++) { if (notas[i][j] >= 6.0f) aprob++; else reprob++; }
                          printf("\t%-25s\t%d\t\t%d\n", materias[j], aprob, reprob);
                      } else { printf("\t%-25s\t0\t\t0\n", materias[j]); }
                  } if (numMaterias == 0) printf("\t(No hay materias registradas para mostrar conteos)\n");
                  // Nombres Aprobados/Reprobados
                  if(numMaterias > 0 && numEstudiantes > 0) { // Solo mostrar si hay datos
                      printf("\n\t===== Nombres de Aprobados y Reprobados por materia =====\n");
                      for (int j = 0; j < numMaterias; j++) {
                          printf("\t--- Materia: %s ---\n", materias[j]);
                          printf("\t Aprobados: "); int countAprob = 0;
                          for (int i = 0; i < numEstudiantes; i++) { if (notas[i][j] >= 6.0f) { if (countAprob > 0) printf(", "); printf("%s", estudiantes[i]); countAprob++; } } if (countAprob == 0) printf("(Ninguno)"); printf("\n");
                          printf("\t Reprobados: "); int countReprob = 0;
                          for (int i = 0; i < numEstudiantes; i++) { if (notas[i][j] < 6.0f) { if (countReprob > 0) printf(", "); printf("%s", estudiantes[i]); countReprob++; } } if (countReprob == 0) printf("(Ninguno)"); printf("\n");
                      }
                  } else { printf("\t(No hay suficientes datos para mostrar nombres)\n"); }

                  // --- LLAMADAS A LAS NUEVAS FUNCIONES DENTRO DEL REPORTE GENERAL ---
                  mostrarEstudianteMejorPeorPromedio(numEstudiantes, numMaterias, estudiantes, notas);
                  mostrarMateriaMejorPeorPromedio(numEstudiantes, numMaterias, materias, notas);
                  // --- FIN LLAMADAS NUEVAS ---

                  break; // Fin case 4
            } // Fin scope case 4

            // --- NUEVOS CASES ---
            case 5:
                mostrarEstudianteMejorPeorPromedio(numEstudiantes, numMaterias, estudiantes, notas);
                break; // Fin case 5 (nuevo)

            case 6:
                 mostrarMateriaMejorPeorPromedio(numEstudiantes, numMaterias, materias, notas);
                break; // Fin case 6 (nuevo)

            // --- SALIR AHORA ES 7 ---
            case 7:
                printf("\tSaliendo del menu de reportes.\n"); // Mensaje actualizado ligeramente
                salirMenu = 1; // Poner la bandera para salir del do-while del menú
                break;
            // El default original no es necesario porque la validación ya se hizo antes del switch
        } // Fin switch
    } while (!salirMenu); // Fin bucle do-while del menú
}


int preguntarRepetir() {
    char entrada[100]; // Buffer local
    int repetir = 0; // Valor por defecto o inválido
    int respuestaRepetirValida = 0;
    // Bucle y validación originales
    do {
        printf("\n\tDesea ingresar un nuevo conjunto de datos? (1 = Si, 0 = No): ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (strlen(entrada) == 1 && (entrada[0] == '1' || entrada[0] == '0')) {
            repetir = entrada[0] - '0';
            respuestaRepetirValida = 1;
        } else {
            printf("\tError: Por favor ingrese solo 1 para Si o 0 para No.\n");
        }
    } while (!respuestaRepetirValida);
    return repetir; // Retorna 1 o 0
}