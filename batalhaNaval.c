#include <stdio.h>

#define TAM 10
#define TAM_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define AREA 5

// Cria matriz da habilidade Cone
void construir_cone(int mat[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for(int i=0;i<TAM_HABILIDADE;i++){
        for(int j=0;j<TAM_HABILIDADE;j++){
            if((j-centro <= i) && (centro-j <= i)) mat[i][j] = 1;
            else mat[i][j] = 0;
        }
    }
}

// Cria matriz da habilidade Cruz
void construir_cruz(int mat[TAM_HABILIDADE][TAM_HABILIDADE]){
    int centro = TAM_HABILIDADE / 2;
    for(int i=0;i<TAM_HABILIDADE;i++){
        for(int j=0;j<TAM_HABILIDADE;j++){
            if(i==centro || j==centro) mat[i][j] = 1;
            else mat[i][j] = 0;
        }
    }
}

// Cria matriz da habilidade Octaedro (losango)
void construir_octaedro(int mat[TAM_HABILIDADE][TAM_HABILIDADE]){
    int centro = TAM_HABILIDADE / 2;
    for(int i=0;i<TAM_HABILIDADE;i++){
        for(int j=0;j<TAM_HABILIDADE;j++){
            if((i-centro<0?-(i-centro):(i-centro)) + (j-centro<0?-(j-centro):(j-centro)) <= centro)
                mat[i][j]=1;
            else 
                mat[i][j]=0;
        }
    }
}

// Aplica habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origem_linha, int origem_coluna){
    int metade = TAM_HABILIDADE / 2;
    for(int i=0;i<TAM_HABILIDADE;i++){
        for(int j=0;j<TAM_HABILIDADE;j++){
            if(habilidade[i][j]==1){
                int r = origem_linha + i - metade;
                int c = origem_coluna + j - metade;
                if(r>=0 && r<TAM && c>=0 && c<TAM){
                    if(tabuleiro[r][c] != NAVIO){
                        tabuleiro[r][c] = AREA;
                    }
                }
            }
        }
    }
}

// Imprime tabuleiro
void imprimir_tabuleiro(int tabuleiro[TAM][TAM]){
    for(int i=0;i<TAM;i++){
        for(int j=0;j<TAM;j++){
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf(" Posicionamento dos Navios\n");

    // Tabuleiro base com navios
    int tabuleiro[TAM][TAM];
    for(int i=0;i<TAM;i++)
        for(int j=0;j<TAM;j++)
            tabuleiro[i][j]=AGUA;

    // Navios
    for(int i=5;i<8;i++) tabuleiro[i][5]=NAVIO;        // vertical
    for(int j=6;j<9;j++) tabuleiro[4][j]=NAVIO;        // horizontal
    for(int i=0;i<3;i++) tabuleiro[1+i][1+i]=NAVIO;    // diagonal direita
    for(int i=0;i<3;i++) tabuleiro[1+i][8-i]=NAVIO;    // diagonal esquerda

    printf("========= JOGO DE BATALHA NAVAL =============\n\n");
    imprimir_tabuleiro(tabuleiro);

    // ---- Criar matrizes de habilidades ----
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    construir_cone(cone);
    construir_cruz(cruz);
    construir_octaedro(octaedro);

    // ---- Criar tabuleiros para habilidades ----
    int tabuleiro_cone[TAM][TAM], tabuleiro_cruz[TAM][TAM], tabuleiro_octaedro[TAM][TAM];
    for(int i=0;i<TAM;i++)
        for(int j=0;j<TAM;j++){
            tabuleiro_cone[i][j]=tabuleiro[i][j];
            tabuleiro_cruz[i][j]=tabuleiro[i][j];
            tabuleiro_octaedro[i][j]=tabuleiro[i][j];
        }

    // ---- Aplicar habilidades (origens fixas) ----
    aplicar_habilidade(tabuleiro_cone, cone, 2, 7);      // cone
    aplicar_habilidade(tabuleiro_cruz, cruz, 5, 3);      // cruz
    aplicar_habilidade(tabuleiro_octaedro, octaedro, 6, 6); // octaedro

    printf("\nTabuleiro com Habilidade CONE:\n");
    imprimir_tabuleiro(tabuleiro_cone);
    printf("\nTabuleiro com Habilidade CRUZ:\n");
    imprimir_tabuleiro(tabuleiro_cruz);
    printf("\nTabuleiro com Habilidade OCTAEDRO:\n");
    imprimir_tabuleiro(tabuleiro_octaedro);

    return 0;
}
