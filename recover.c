#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Garante o uso correto
    if (argc != 2)
    {
        printf("Usage: %s 'target'\n", argv[0]);
        return 1;
    }

    // Abrindo arquivo
    FILE *infile_ptr = fopen(argv[1], "r");
    if (infile_ptr == NULL)
    {
        printf("Unable to open the file.\n");
        return 1;
    }

    const int BLOCK_SIZE = 512;
    int found = -1;
    FILE *imagem;
    char name[8];
    BYTE *buffer = malloc(512 * sizeof(BYTE));

    while (fread(buffer, 1, BLOCK_SIZE, infile_ptr) == BLOCK_SIZE)
    {
        // Verifica se é cabeçalho de JPEG (Faltando 2 condições)
        if (buffer[0] == 255 && buffer[3] == 224)
        {
            if (found != -1)
                fclose(imagem);
            found++;
            sprintf(name, "%03i.jpg", found);
            imagem = fopen(name, "w");
            fwrite(buffer, 1, BLOCK_SIZE, imagem);
        }
        else
        {
            if (found != -1)
                fwrite(buffer, 1, BLOCK_SIZE, imagem);
        }
    }
    // Libera memória alocada
    fclose(imagem);
    fclose(infile_ptr);
    free(buffer);
    return 0;
}