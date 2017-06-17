#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

struct mp4header {
    char header[8];     // Header
    char mb[4];         // Major brand
    char mbv[4];        // Major brand version
    char cb[4];         // Compatible brands

    char mdb[8];        // Media data box
    char us[24];        // Unused space
};

int file_exists(char *filename);
void print_char_sequence(char *sequence);

int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, "Usage: %s MP4_FILE\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *mp4filename = argv[1];

    if (!file_exists(mp4filename)) {
        fprintf(stderr, "Archivo inexistente (%s).\n", mp4filename);
        exit(EXIT_FAILURE);
    }

    FILE *mp4;
    mp4 = fopen(mp4filename, "rb");

    if (mp4 == NULL) {
        fprintf(stderr, "Cannot open file (%s).\n", mp4filename);
        exit(EXIT_FAILURE);
    }

    struct mp4header header;

    fread(&header, sizeof(header), 1, mp4);

    /* TODO: Checkear que el archivo sea un MP4 valido */
    /* TODO: Leer el resto */

    fclose(mp4);


    char *mp4destfilename = "sample/test.mp4";
    FILE *mp4dest;
    mp4dest = fopen(mp4destfilename, "wb");
    if (mp4dest == NULL) {
        fprintf(stderr, "Cannot open dest file (%s).\n", mp4destfilename);
        exit(EXIT_FAILURE);
    }
    fwrite(&header, sizeof(header), 1, mp4dest);
    fclose(mp4dest);

    printf("\n\nFinished!\n");
}

int file_exists(char *filename)
{
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void print_char_sequence(char *sequence)
{
    for (int x = 0; x < (sizeof sequence); x++) {
        printf("%c", sequence[x]);
    }
}
