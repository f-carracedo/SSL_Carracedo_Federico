/*
Aclaración para quien esté corrigiendo el TP: Usamos if's anidados porque el switch...case estaba dando problemas con:
    1. Declaraciones de variables dentro de los "case"
    2. Invocaciones a funciones dentro de los "case"
*/

#include <stdio.h>
#include <stdbool.h>

#define longPalabra 31
#define estadoInicial 0

short matrizTransicion[6][5] = {
    {1, 2, 2, 6, 6},
    {5, 5, 6, 6, 3},
    {2, 2, 2, 6, 6},
    {4, 4, 4, 4, 6},
    {4, 4, 4, 4, 6},
    {5, 5, 6, 6, 6}
};

short estadosFinales[5] = {1, 2, 4, 5};

void imprimirPalabra(char palabra[longPalabra], short counter) {
    for(short i = 0; i < counter; i++) {
        printf("%c", palabra[i]);
    }
}

char enRango(char base, char top, char ch) {
    if(ch >= base && ch <= top) {
        return ch;
    } else {
        return 0;
    }
}

int clasificar(char palabra[longPalabra], short counter) {
    int estado = estadoInicial;
    for(short i = 0; i < counter; i++) {
        char ch = palabra[i];
        if(ch == '0')
            estado = matrizTransicion[estado][0];
        if(ch == enRango('1', '7', ch))
            estado = matrizTransicion[estado][1];
        if(ch == enRango('8', '9', ch))
            estado = matrizTransicion[estado][2];
        if(ch == enRango('a', 'f', ch) || ch == enRango('A', 'F', ch))
            estado = matrizTransicion[estado][3];
        if(ch == 'x' || ch == 'X')
            estado = matrizTransicion[estado][4];
        if(estado == 6)
            break;
    }
    return estado;
}

void escribeResultado(char palabra[longPalabra], FILE *pFile, int estado, short counter) {
    imprimirPalabra(palabra, counter);
    printf(" Estado: %d | ", estado);
    if(estado == 1 || estado == 2 || estado == 4 || estado == 5) {
        if(estado == 1 || estado == 5) {
            char mensaje[7] = " OCTAL\n";
            fwrite(palabra, sizeof(char), (sizeof(char) * counter), pFile);
            fwrite(mensaje, sizeof(char), sizeof(mensaje), pFile);
        } if(estado == 2) {
            char mensaje[9] = " DECIMAL\n";
            fwrite(palabra, sizeof(char), (sizeof(char) * counter), pFile);
            fwrite(mensaje, sizeof(char), sizeof(mensaje), pFile);
        } if(estado == 4) {
            char mensaje[13] = " HEXADECIMAL\n";
            fwrite(palabra, sizeof(char), (sizeof(char) * counter), pFile);
            fwrite(mensaje, sizeof(char), sizeof(mensaje), pFile);
        } 
    } else {
        char mensaje[15] = " NO RECONOCIDA\n";
        fwrite(palabra, sizeof(char), (sizeof(char) * counter), pFile);
        fwrite(mensaje, sizeof(char), sizeof(mensaje), pFile);
    }
}

void leer(FILE *stream, FILE *pFile) {
    char ch;
    char word[longPalabra];
    short counter = 0;
    while((ch = fgetc(stream)) != EOF) {
        if(ch == ',') {
            int estado = clasificar(word, counter);
            escribeResultado(word, pFile, estado, counter);
            char word[longPalabra];
            ch = fgetc(stream); // Salteo el centinela
            counter = 0;
        }
        word[counter] = ch;
        counter++;
    }
    short result = clasificar(word, counter); // Incluyo la última palabra, que quedó en el buffer
}

short main() {
    FILE *ENTRADA = fopen("entrada.txt", "r");
    FILE *SALIDA = fopen("salida.txt", "w");
    leer(ENTRADA, SALIDA);
    fclose(ENTRADA);
    fclose(SALIDA);
    return 1;
}