#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float X;
    float Y;
} Ponto;

FILE* abrirArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    return arquivo;
}

void fecharArquivo(FILE* arquivo) {
    fclose(arquivo);
}

Ponto* lerVertices(FILE* arquivo, int numVertices) {
    Ponto* vertices = (Ponto*)malloc(numVertices * sizeof(Ponto));
    if (vertices == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    for (int i = 0; i < numVertices; ++i) {
        fscanf(arquivo, "%f %f", &vertices[i].X, &vertices[i].Y);
    }
    return vertices;
}

float AreaTrg(Ponto A, Ponto B, Ponto C) {
    float det = (A.X * B.Y + A.Y * C.X + B.X * C.Y) - (C.X * B.Y + C.Y * A.X + B.X * A.Y);
    return fabs(det) / 2.0; // Retorna o valor dividido por 2
}

float ClcAreaPlgn(Ponto* vertices, int numVertices) {
    float areaTotal = 0.0;
    for (int i = 1; i < numVertices - 1; ++i) {
        areaTotal += AreaTrg(vertices[0], vertices[i], vertices[i + 1]);
    }
    return areaTotal;
}

int main() {
    FILE* arquivo;
    int numVertices;
    Ponto* vertices;
    float area;

    arquivo = abrirArquivo("vertices.txt");

    fscanf(arquivo, "%d", &numVertices);

    vertices = lerVertices(arquivo, numVertices);

    fecharArquivo(arquivo);

    area = ClcAreaPlgn(vertices, numVertices);

    printf("A area do poligono eh: %.2f\n", area);

    free(vertices);

    return 0;
}
