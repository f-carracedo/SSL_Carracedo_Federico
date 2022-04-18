#include <stdio.h>
#include <stdbool.h>

bool esHexa(char palabra[21], short counter){
    for(short i = 2; i < counter; i++) {
        char ch = palabra[i];
        if(!(ch >= 65 && ch <= 70) && !(ch >= 97 && ch <= 102) && !(ch >= 48 && ch <= 57)) {
            return false;
        }
    }
    return true;
}

bool esOctal(char palabra[21], short counter) {
    for(short i = 0; i < counter; i++) {
        char ch = palabra[i];
        if(!(ch >= 48 && ch <= 55)) {
            return false;
        }
    }
    return true;
}

bool esDecimal(char palabra[21], short counter) {
    for(short i = 0; i < counter; i++) {
        char ch = palabra[i];
        if(!(ch >= 48 && ch <= 57)) {
            return false;
        }
    }
    return true;
}

void imprimirPalabra(char palabra[21], short counter) {
    for(short i = 0; i < counter; i++) {
        printf("%c", palabra[i]);
    }
}

void clasificar(char palabra[21], FILE *pFile, short counter) {
    switch(palabra[0]) {
        case '0':
            if((palabra[1] == 'x' || palabra[1] == 'X') && counter > 1) {
                if(esHexa(palabra, counter)) {
                    char mensaje[13] = " HEXADECIMAL\n";
                    fwrite(palabra, sizeof(char), (sizeof(char) * counter), pFile);
                    fwrite(mensaje, sizeof(char), sizeof(mensaje), pFile);
                    break;
                }
            } 
            if(esOctal(palabra, counter)) {
                char mensaje[7] = " OCTAL\n";
                fwrite(palabra, sizeof(char), (sizeof(char) * counter), pFile);
                fwrite(mensaje, sizeof(char), sizeof(mensaje), pFile);
                break;
            }
            char mensaje[15] = " NO RECONOCIDA\n";
            fwrite(palabra, sizeof(char), (sizeof(char) * counter), pFile);
            fwrite(mensaje, sizeof(char), sizeof(mensaje), pFile);
            break;
        default:
            if(esDecimal(palabra, counter)) {
                char mensaje[9] = " DECIMAL\n";
                fwrite(palabra, sizeof(char), (sizeof(char) * counter), pFile);
                fwrite(mensaje, sizeof(char), sizeof(mensaje), pFile);
                break;
            } else {
                char mensaje[15] = " NO RECONOCIDA\n";
                fwrite(palabra, sizeof(char), (sizeof(char) * counter), pFile);
                fwrite(mensaje, sizeof(char), sizeof(mensaje), pFile);
            }
    }
}

void leer(FILE *stream, FILE *pFile) {
    char ch;
    char word[21];
    short counter = 0;
    while((ch = fgetc(stream)) != EOF) {
        if(ch == ',') {
            clasificar(word, pFile, counter);
            counter = 0;
            ch = fgetc(stream); // Salteo el centinela
            char word[21];
        }
        word[counter] = ch;
        counter++;
    }
    clasificar(word, pFile, counter); // Incluyo la última palabra, que quedó en el buffer
}

int main() {
    FILE *archivo = fopen("entrada.txt", "r");
    FILE *pFile = fopen("salida.txt", "w");
    leer(archivo, pFile);
    fclose(archivo);
    fclose(pFile);
    return 1;
}

