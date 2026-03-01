#include <stdio.h>
#include <string.h>

#define PARCIALES 3
#define MATERIAS 4
#define ALUMNOS 3
#define APROBADO 6.0

int main() {

    float calificaciones[PARCIALES][MATERIAS][ALUMNOS];
    char nombresAlumnos[ALUMNOS][50];
    char nombresMaterias[MATERIAS][50];
    char estatus;

    int opcion;
    int p, m, a;

    float promedio;
    float max, min;
    int maxM, maxA;
    int minM, minA;

    char buffer[50]; 

    printf("===== CAPTURA DE NOMBRES =====\n");

    for(a = 0; a < ALUMNOS; a++){
        printf("Nombre del alumno %d: ", a+1);
        fgets(nombresAlumnos[a], 50, stdin);
        nombresAlumnos[a][strcspn(nombresAlumnos[a], "\n")] = '\0';
    }

    for(m = 0; m < MATERIAS; m++){
        printf("Nombre de la materia %d: ", m+1);
        fgets(nombresMaterias[m], 50, stdin);
        nombresMaterias[m][strcspn(nombresMaterias[m], "\n")] = '\0';
    }

    for(p = 0; p < PARCIALES; p++)
        for(m = 0; m < MATERIAS; m++)
            for(a = 0; a < ALUMNOS; a++)
                calificaciones[p][m][a] = 0.0;

    do {

        printf("\n===== SISTEMA DE CALIFICACIONES =====\n");
        printf("1. Capturar calificaciones\n");
        printf("2. Mostrar calificaciones\n");
        printf("3. Modificar calificacion\n");
        printf("4. Promedios\n");
        printf("5. Reporte Maximo y Minimo por Parcial\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &opcion);

        switch(opcion) {

        case 1:
            for(p = 0; p < PARCIALES; p++) {
                printf("\n=== Parcial %d ===\n", p+1);

                for(m = 0; m < MATERIAS; m++) {
                    printf("\nMateria: %s\n", nombresMaterias[m]);

                    for(a = 0; a < ALUMNOS; a++) {

                        do {
                            printf("Calificacion - %s (0-10): ", nombresAlumnos[a]);
                            fgets(buffer, sizeof(buffer), stdin);

                            if (sscanf(buffer, "%f", &calificaciones[p][m][a]) != 1) {
                                printf("Entrada invalida!\n");
                                calificaciones[p][m][a] = -1;
                            }

                            if(!(calificaciones[p][m][a] >= 0 &&
                                 calificaciones[p][m][a] <= 10)) {
                                printf("Error: Calificacion fuera de rango!\n");
                            }

                        } while(!(calificaciones[p][m][a] >= 0 &&
                                  calificaciones[p][m][a] <= 10));
                    }
                }
            }
            break;

        case 2:
            for(p = 0; p < PARCIALES; p++) {

                printf("\n==== PARCIAL %d ====\n", p+1);

                for(m = 0; m < MATERIAS; m++) {
                    for(a = 0; a < ALUMNOS; a++) {

                        printf("%s - %s: %.2f ",
                               nombresMaterias[m],
                               nombresAlumnos[a],
                               calificaciones[p][m][a]);

                        if(calificaciones[p][m][a] >= APROBADO)
                            estatus = 'A';
                        else
                            estatus = 'R';

                        printf("(%c)\n", estatus);
                    }
                }
            }
            break;

        case 3:

            do {
                printf("Parcial (1-%d): ", PARCIALES);
                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer, "%d", &p);

                printf("Materia (1-%d): ", MATERIAS);
                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer, "%d", &m);

                printf("Alumno (1-%d): ", ALUMNOS);
                fgets(buffer, sizeof(buffer), stdin);
                sscanf(buffer, "%d", &a);

                if(!(p >= 1 && p <= PARCIALES &&
                     m >= 1 && m <= MATERIAS &&
                     a >= 1 && a <= ALUMNOS)) {
                    printf("Indices fuera de rango.\n");
                }

            } while(!(p >= 1 && p <= PARCIALES &&
                      m >= 1 && m <= MATERIAS &&
                      a >= 1 && a <= ALUMNOS));

            do {
                printf("Nueva calificacion: ");
                fgets(buffer, sizeof(buffer), stdin);

                if (sscanf(buffer, "%f", &calificaciones[p-1][m-1][a-1]) != 1) {
                    printf("Entrada invalida!\n");
                    calificaciones[p-1][m-1][a-1] = -1;
                }

            } while(!(calificaciones[p-1][m-1][a-1] >= 0 &&
                      calificaciones[p-1][m-1][a-1] <= 10));

            printf("Calificacion modificada correctamente.\n");
            break;

        case 4:

            printf("\n=== PROMEDIO POR ALUMNO (POR PARCIAL) ===\n");

            for(p = 0; p < PARCIALES; p++) {
                for(a = 0; a < ALUMNOS; a++) {

                    promedio = 0;
                    for(m = 0; m < MATERIAS; m++)
                        promedio += calificaciones[p][m][a];

                    promedio /= MATERIAS;

                    printf("Parcial %d - %s: %.2f\n",
                           p+1, nombresAlumnos[a], promedio);
                }
            }

            printf("\n=== PROMEDIO POR MATERIA (POR PARCIAL) ===\n");

            for(p = 0; p < PARCIALES; p++) {
                for(m = 0; m < MATERIAS; m++) {

                    promedio = 0;
                    for(a = 0; a < ALUMNOS; a++)
                        promedio += calificaciones[p][m][a];

                    promedio /= ALUMNOS;

                    printf("Parcial %d - %s: %.2f\n",
                           p+1, nombresMaterias[m], promedio);
                }
            }

            break;

        case 5:

            for(p = 0; p < PARCIALES; p++) {

                max = min = calificaciones[p][0][0];
                maxM = minM = 0;
                maxA = minA = 0;

                for(m = 0; m < MATERIAS; m++) {
                    for(a = 0; a < ALUMNOS; a++) {

                        if(calificaciones[p][m][a] > max) {
                            max = calificaciones[p][m][a];
                            maxM = m;
                            maxA = a;
                        }

                        if(calificaciones[p][m][a] < min) {
                            min = calificaciones[p][m][a];
                            minM = m;
                            minA = a;
                        }
                    }
                }

                printf("\nParcial %d:\n", p+1);
                printf("Maximo: %.2f (%s - %s)\n",
                       max, nombresMaterias[maxM], nombresAlumnos[maxA]);
                printf("Minimo: %.2f (%s - %s)\n",
                       min, nombresMaterias[minM], nombresAlumnos[minA]);
            }

            break;

        case 6:
            printf("Saliendo del sistema...\n");
            break;

        default:
            printf("Opcion invalida.\n");
        }

    } while(opcion != 6);

    return 0;
}
