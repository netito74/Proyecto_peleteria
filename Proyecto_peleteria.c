#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Para SetConsoleCursorPosition y Sleep

struct productos {
    int codigo;
    char nombre[50];
    float cantidad;
    int precio;
    char tallas[10];
    char descripcion[50];
};

void margen(int x1, int y1, int x2, int y2, char p, char t);
void altas(struct productos *produc);
void consultas(struct productos *produc);
void bajas(struct productos *produc);
void modificaciones(struct productos *produc);
void reportes(struct productos *produc);
void ventas(struct productos *produc);
void gotoxy(int x, int y); // Función para mover el cursor

int reg = 0;

int main() {
    char op1;
    struct productos produc[6];
    
    system("cls"); // Limpia la pantalla
    margen(1, 1, 79, 24, 223, 177);
    gotoxy(30, 3); printf("Universidad Del Mar");
    gotoxy(34, 5); printf("Informatica");
    gotoxy(32, 7); printf("Segundo Semestre");
    gotoxy(26, 9); printf("Ramos Barrera Ernesto Manuel");
    gotoxy(30, 11); printf("Jorge Ochoa Samuano");
    gotoxy(21, 13); printf("Programa De Control Para Una Peleteria");
    gotoxy(21, 17); printf("Presione una tecla para continuar [ ]");
    getchar(); // Espera una tecla

    do {
        Sleep(1000); // Pausa de un segundo
        system("cls");
        margen(1, 1, 79, 24, 223, 177);
        margen(27, 2, 51, 4, 223, 177);
        margen(15, 5, 65, 23, 223, 177);
        gotoxy(28, 3); printf("<<< PELETERIA BARRERA >>>");
        gotoxy(20, 6); printf("1. [A]ltas");
        gotoxy(20, 7); printf("2. [B]ajas");
        gotoxy(20, 8); printf("3. [C]onsultas");
        gotoxy(20, 9); printf("4. [M]odificaciones");
        gotoxy(20, 10); printf("5. [R]eportes");
        gotoxy(20, 11); printf("6. [V]entas");
        gotoxy(20, 12); printf("7. [S]alir");

        gotoxy(20, 13); printf("Seleccione la opción [ ]");
        scanf(" %c", &op1);

        switch (op1) {
            case '1': case 'A': case 'a': altas(&produc[reg]); break;
            case '2': case 'B': case 'b': bajas(produc); break;
            case '3': case 'C': case 'c': consultas(produc); break;
            case '4': case 'M': case 'm': modificaciones(produc); break;
            case '5': case 'R': case 'r': reportes(produc); break;
            case '6': case 'V': case 'v': ventas(produc); break;
            case '7': case 'S': case 's': gotoxy(20, 16); printf("Has seleccionado salir."); break;
            default: gotoxy(20, 16); printf("Opcion incorrecta."); break;
        }
    } while (op1 != '7');

    gotoxy(20, 22); printf("Ingrese cualquier tecla para salir [ ]");
    getchar();

    return 0;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void margen(int x1, int y1, int x2, int y2, char p, char t) {
    int x, y;
    for (x = x1; x <= x2; x++) {
        gotoxy(x, y1); printf("%c", p);
        gotoxy(x, y2); printf("%c", p);
    }
    for (y = y1; y <= y2; y++) {
        gotoxy(x1, y); printf("%c", t);
        gotoxy(x2, y); printf("%c", t);
    }
}

void altas(struct productos *produc) {
    system("cls");
    margen(1, 1, 79, 18, 223, 177); // Marco ajustado
    gotoxy(28, 3); printf("<><> Altas <><>");
    gotoxy(28, 7); printf("Código: ");
    scanf("%d", &produc->codigo);
    gotoxy(28, 9); printf("Nombre: ");
    fflush(stdin); // Limpiar el buffer
    gets(produc->nombre);
    gotoxy(28, 11); printf("Cantidad: ");
    scanf("%f", &produc->cantidad);
    gotoxy(28, 13); printf("Precio: ");
    scanf("%d", &produc->precio);
    gotoxy(28, 15); printf("Tallas: ");
    fflush(stdin);
    gets(produc->tallas);
    gotoxy(28, 17); printf("Descripcion: ");
    gets(produc->descripcion);
    reg++;
}

void consultas(struct productos *produc) {
    system("cls");
    margen(1, 1, 79, 24, 223, 177); // Marco ajustado para mostrar productos
    int i;
    
    if (reg == 0) {
        gotoxy(28, 3); printf("No hay productos registrados.");
    } else {
        gotoxy(28, 3); printf("<><> Consultas <><>");
        for (i = 0; i < reg; i++) {
            gotoxy(10, 5 + i * 2); printf("Producto %d:", i + 1);
            gotoxy(10, 6 + i * 2); printf("Código: %d, Nombre: %s, Cantidad: %.2f, Precio: %d, Tallas: %s, Descripción: %s",
                                          produc[i].codigo, produc[i].nombre, produc[i].cantidad,
                                          produc[i].precio, produc[i].tallas, produc[i].descripcion);
        }
    }
    
    gotoxy(20, 22); printf("Ingrese cualquier tecla para regresar al menu [ ]");
    getchar(); getchar(); // Para hacer la pausa y esperar la entrada
}

void bajas(struct productos *produc) {
    system("cls");
    margen(1, 1, 79, 18, 223, 177); // Marco ajustado para las bajas
    int i, j;
    if (reg == 0) {
        gotoxy(28, 3); printf("No hay productos registrados.");
    } else {
        int codigo;
        gotoxy(28, 3); printf("<><> Bajas <><>");
        gotoxy(28, 7); printf("Ingrese el codigo del producto a eliminar: ");
        scanf("%d", &codigo);
        
        int encontrado = 0;
        for ( i = 0; i < reg; i++) {
            if (produc[i].codigo == codigo) {
                for (j = i; j < reg - 1; j++) {
                    produc[j] = produc[j + 1];
                }
                reg--; // Reducir el número de registros
                encontrado = 1;
                gotoxy(28, 9); printf("Producto eliminado exitosamente.");
                break;
            }
        }
        if (!encontrado) {
            gotoxy(28, 9); printf("Producto no encontrado.");
        }
    }

    gotoxy(20, 17); printf("Ingrese cualquier tecla para regresar al menu [ ]");
    getchar(); getchar(); // Esperar entrada del usuario
}

void modificaciones(struct productos *produc) {
    system("cls");
    margen(1, 1, 79, 22, 223, 177); // Marco ajustado
    int i;
    
    if (reg == 0) {
        gotoxy(28, 3); printf("No hay productos registrados.");
    } else {
        int codigo;
        gotoxy(28, 3); printf("<><> Modificaciones <><>");
        gotoxy(28, 7); printf("Ingrese el código del producto a modificar: ");
        scanf("%d", &codigo);
        
        int encontrado = 0;
        for (i = 0; i < reg; i++) {
            if (produc[i].codigo == codigo) {
                gotoxy(28, 9); printf("Modificando el producto con codigo %d:", codigo);
                gotoxy(28, 11); printf("Nuevo nombre: ");
                fflush(stdin); // Limpiar el buffer
                gets(produc[i].nombre);
                gotoxy(28, 13); printf("Nueva cantidad: ");
                scanf("%f", &produc[i].cantidad);
                gotoxy(28, 15); printf("Nuevo precio: ");
                scanf("%d", &produc[i].precio);
                gotoxy(28, 17); printf("Nuevas tallas: ");
                fflush(stdin);
                gets(produc[i].tallas);
                gotoxy(28, 19); printf("Nueva descripción: ");
                gets(produc[i].descripcion);
                
                encontrado = 1;
                gotoxy(28, 21); printf("Producto modificado exitosamente.");
                break;
            }
        }
        if (!encontrado) {
            gotoxy(28, 9); printf("Producto no encontrado.");
        }
    }

    gotoxy(20, 22); printf("Ingrese cualquier tecla para regresar al menu [ ]");
    getchar(); getchar(); // Pausa y espera de entrada
}

void reportes(struct productos *produc) {
    system("cls");
    int i;
    
    if (reg == 0) {
        gotoxy(28, 3); printf("No hay productos registrados.");
    } else {
        gotoxy(28, 3); printf("<><> Reportes <><>");
        for (i = 0; i < reg; i++) {
            gotoxy(10, 5 + i * 2); printf("Producto %d:", i + 1);
            gotoxy(10, 6 + i * 2); printf("Código: %d, Nombre: %s, Cantidad: %.2f, Precio: %d, Tallas: %s, Descripción: %s",
                                          produc[i].codigo, produc[i].nombre, produc[i].cantidad,
                                          produc[i].precio, produc[i].tallas, produc[i].descripcion);
        }
    }

    gotoxy(20, 22); printf("Ingrese cualquier tecla para regresar al menu [ ]");
    getchar(); getchar(); // Pausa para esperar entrada
}

void ventas(struct productos *produc) {
    system("cls");
    int i;
    
    if (reg == 0) {
        gotoxy(28, 3); printf("No hay productos disponibles para la venta.");
    } else {
        int codigo;
        gotoxy(28, 3); printf("<><> Ventas <><>");
        gotoxy(28, 7); printf("Ingrese el codigo del producto a vender: ");
        scanf("%d", &codigo);

        int encontrado = 0;
        for (i = 0; i < reg; i++) {
            if (produc[i].codigo == codigo) {
                if (produc[i].cantidad > 0) {
                    produc[i].cantidad--; // Reducir cantidad
                    gotoxy(28, 9); printf("Venta realizada con exito.");
                } else {
                    gotoxy(28, 9); printf("No hay suficiente stock para vender.");
                }
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            gotoxy(28, 9); printf("Producto no encontrado.");
        }
    }

    gotoxy(20, 17); printf("Ingrese cualquier tecla para regresar al menu [ ]");
    getchar(); getchar(); // Espera de entrada
}

