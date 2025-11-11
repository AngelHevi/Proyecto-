#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------
// Proyecto menu
// -----------------------------
struct Producto {
    char nombre[30];
    float precio;
};

struct Pedido {
    struct Producto productos[20];
    int cantidad[20];
    int numProductos;
};

// -----------------------------
// Loops
// -----------------------------
void mostrarMenu();
void tomarPedido(struct Pedido *pedido);
void mostrarPedido(struct Pedido pedido);
void guardarTicket(struct Pedido *pedido);
void mostrarTickets();

// -----------------------------
// contador de tickets
// -----------------------------
int contadorTickets = 1;

// -----------------------------
// Aqui la main, la mera buena
// -----------------------------
int main() {
    struct Pedido pedido;
    pedido.numProductos = 0;

    int opcion;
    do {
        printf("\n--------- SISTEMA DE MENU PARA MESEROS ---------\n");
        printf("1. Ver menu de restaurante\n");
        printf("2. Tomar pedido\n");
        printf("3. Mostrar pedido actual\n");
        printf("4. Guardar ticket\n");
        printf("5. Salir\n");
        printf("6. Mostrar tickets guardados\n");
        printf("---------------------------------------------------\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion) {
            case 1:
                mostrarMenu();
                break;
            case 2:
                tomarPedido(&pedido);
                break;
            case 3:
                mostrarPedido(pedido);
                break;
            case 4:
                guardarTicket(&pedido);
                break;
            case 5:
                printf("\nSaliendo del sistema...\n");
                break;
            case 6:
                mostrarTickets();
                break;
            default:
                printf("\nOpcion no valida.\n");
        }
    } while(opcion != 5);


    return 0;
}

// -----------------------------
// Funcones
// -----------------------------

void mostrarMenu() {
    printf("\n---- MENU DE COMIDAS Y BEBIDAS ----\n");
    printf("1. Hamburguesa ............ $80\n");
    printf("2. Tacos al pastor ........ $60\n");
    printf("3. Enchiladas ............. $75\n");
    printf("4. Refresco ............... $25\n");
    printf("5. Agua natural ........... $15\n");
    printf("6. Cafe ................... $30\n");
    printf("----------------------------------\n");
}

void tomarPedido(struct Pedido *pedido) {
    int opcion, cantidad;
    char continuar;

    do {
        mostrarMenu();
        printf("\nSelecciona un producto (1-6): ");
        scanf("%d", &opcion);

        if (opcion < 1 || opcion > 6) {
            printf("Opcion no valida.\n");
            continue;
        }

        printf("Cantidad: ");
        scanf("%d", &cantidad);

        struct Producto p;

        switch(opcion) {
            case 1: strcpy(p.nombre, "Hamburguesa"); p.precio = 80; break;
            case 2: strcpy(p.nombre, "Tacos al pastor"); p.precio = 60; break;
            case 3: strcpy(p.nombre, "Enchiladas"); p.precio = 75; break;
            case 4: strcpy(p.nombre, "Refresco"); p.precio = 25; break;
            case 5: strcpy(p.nombre, "Agua natural"); p.precio = 15; break;
            case 6: strcpy(p.nombre, "Cafe"); p.precio = 30; break;
        }

        pedido->productos[pedido->numProductos] = p;
        pedido->cantidad[pedido->numProductos] = cantidad;
        pedido->numProductos++;

        printf("\n�Desea agregar otro producto? (s/n): ");
        scanf(" %c", &continuar);

    } while((continuar == 's' || continuar == 'S') && pedido->numProductos < 20);

    printf("\nPedido registrado correctamente.\n");
    system("cls");
}

void mostrarPedido(struct Pedido pedido) {
    if (pedido.numProductos == 0) {
        printf("\nNo hay productos en el pedido.\n");
        return;
    }

    printf("\n------ PEDIDO ACTUAL ------\n");
    float total = 0;
    for (int i = 0; i < pedido.numProductos; i++) {
        float subtotal = pedido.productos[i].precio * pedido.cantidad[i];
        printf("%d. %s x%d = $%.2f\n", i + 1, pedido.productos[i].nombre,
               pedido.cantidad[i], subtotal);
        total += subtotal;
    }
    printf("----------------------------\n");
    printf("TOTAL: $%.2f\n", total);
}

void guardarTicket(struct Pedido *pedido) {
    if (pedido->numProductos == 0) {
        printf("\nNo hay pedido para guardar.\n");
        return;
    }

    char nombreArchivo[50];
    sprintf(nombreArchivo, "ticket_%d.txt", contadorTickets);

    FILE *archivo = fopen(nombreArchivo, "w");
    if (!archivo) {
        printf("\nError al guardar el ticket.\n");
        return;
    }

    float total = 0;
    fprintf(archivo, "------ TICKET %d ------\n", contadorTickets);
    for (int i = 0; i < pedido->numProductos; i++) {
        float subtotal = pedido->productos[i].precio * pedido->cantidad[i];
        fprintf(archivo, "%s x%d = $%.2f\n",
                pedido->productos[i].nombre,
                pedido->cantidad[i],
                subtotal);
        total += subtotal;

    }
    fprintf(archivo, "TOTAL: $%.2f\n", total);
    fclose(archivo);

    printf("\nTicket guardado como '%s'\n", nombreArchivo);

    pedido->numProductos = 0;
    contadorTickets++;
}

void mostrarTickets() {
    printf("\n------ TICKETS GUARDADOS ------\n");

    for (int i = 1; i < contadorTickets; i++) {
        char nombreArchivo[50];
        sprintf(nombreArchivo, "ticket_%d.txt", i);

        FILE *archivo = fopen(nombreArchivo, "r");
        if (!archivo) {
            continue;
        }

        printf("\nContenido de %s:\n", nombreArchivo);

        char linea[100];
        while (fgets(linea, sizeof(linea), archivo)) {
            printf("%s", linea);
        }
        fclose(archivo);
    }
}
