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
        printf("Usage: %s MP4_FILE\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *mp4filename = argv[1];

    if (!file_exists(mp4filename)) {
        printf("Archivo inexistente (%s).\n", mp4filename);
        return EXIT_FAILURE;
    }

    FILE *mp4;
    mp4 = fopen(mp4filename, "rb");

    struct mp4header header;

    fread(&header, sizeof(header), 1, mp4); //mp4.read((char *) &header, sizeof header);

    // print_char_sequence(header.header);
    // print_char_sequence(header.mdb);
    // printf("\n\n");

    // ofstream outmp4("sample/test.mp4", ios::out | ios::binary);
    //
    // if (!outmp4) {
    //     printf("No se puede escribir el archivo");
    //     return EXIT_FAILURE;
    // }
    //
    // outmp4.write((char *) &header, sizeof header);

    // outmp4.write((char *) &frames, sizeof frames);

    // printf("\n\n%s", header);
    printf("\n\n");
    printf("Finished!\n");
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
