#include <stdio.h>

#define SIZE 8

void inicializarTabuleiro(char tabuleiro[SIZE][SIZE]) {
    const char *linhas = "RNBQKBNR";
    for (int i = 0; i < SIZE; i++) {
        tabuleiro[0][i] = linhas[i];       // Primeira linha
        tabuleiro[1][i] = 'P';              // Peões
        tabuleiro[6][i] = 'p';              // Peões pretos
        tabuleiro[7][i] = linhas[i] + 32;   // Segunda linha (minúsculas)
    }
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < SIZE; j++) {
            tabuleiro[i][j] = '.';          // Espaços vazios
        }
    }
}

void exibirTabuleiro(char tabuleiro[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int caminhoLivre(char tabuleiro[SIZE][SIZE], int x1, int y1, int x2, int y2) {
    int stepX = (x2 - x1) == 0 ? 0 : (x2 - x1) / abs(x2 - x1);
    int stepY = (y2 - y1) == 0 ? 0 : (y2 - y1) / abs(y2 - y1);
    for (int i = 1; i < abs(x2 - x1 + y2 - y1); i++) {
        if (tabuleiro[x1 + stepX * i][y1 + stepY * i] != '.') {
            return 0; // Caminho obstruído
        }
    }
    return 1; // Caminho livre
}

int movimentoValido(char tabuleiro[SIZE][SIZE], int x1, int y1, int x2, int y2) {
    char peca = tabuleiro[x1][y1];

    // Verificar se a posição de origem e destino estão dentro dos limites
    if (x2 < 0 || x2 >= SIZE || y2 < 0 || y2 >= SIZE) {
        return 0; // Movimento inválido
    }

    // Validação para Peão
    if (peca == 'P') {
        if (x2 == x1 + 1 && y2 == y1 && tabuleiro[x2][y2] == '.') {
            return 1; // Movimento simples
        }
        if (x1 == 1 && x2 == 3 && y2 == y1 && tabuleiro[2][y1] == '.' && tabuleiro[x2][y2] == '.') {
            return 1; // Movimento duplo
        }
        if (x2 == x1 + 1 && abs(y2 - y1) == 1 && tabuleiro[x2][y2] >= 'a' && tabuleiro[x2][y2] <= 'z') {
            return 1; // Captura
        }
    }

    // Validação para Torres
    if (peca == 'R' || peca == 'r') {
        if (x1 == x2 || y1 == y2) { // Movimento horizontal ou vertical
            return caminhoLivre(tabuleiro, x1, y1, x2, y2);
        }
    }

    // Validação para Bispos
    if (peca == 'B' || peca == 'b') {
        if (abs(x2 - x1) == abs(y2 - y1)) { // Movimento diagonal
            return caminhoLivre(tabuleiro, x1, y1, x2, y2);
        }
    }

    // Validação para Rainhas
    if (peca == 'Q' || peca == 'q') {
        if (x1 == x2 || y1 == y2 || abs(x2 - x1) == abs(y2 - y1)) {
            return caminhoLivre(tabuleiro, x1, y1, x2, y2);
        }
    }

    return 0; // Movimento inválido
}

int main() {
    char tabuleiro[SIZE][SIZE];
    inicializarTabuleiro(tabuleiro);
    exibirTabuleiro(tabuleiro);
    
    // Exemplo de movimento (modifique conforme necessário)
    int x1 = 0, y1 = 0; // Posição da torre branca
    int x2 = 3, y2 = 0; // Nova posição desejada
    if (movimentoValido(tabuleiro, x1, y1, x2, y2)) {
        tabuleiro[x2][y2] = tabuleiro[x1][y1]; // Mover peça
        tabuleiro[x1][y1] = '.';                // Limpar posição anterior
    }

    printf("\nApós o movimento:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
