#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned int offset;    // offset
    unsigned int ftyp;      // "ftyp"
    char mb[4];             // Major brand
    char mbv[4];            // Major brand version
    char cb[4];             // Compatible brands

    // char mdb[8];            // Media data box
    // char us[24];            // Unused space
} MP4FileTypeIdentification;

typedef struct {
    unsigned offset;
    char mdat[4];
} MP4FileMediaData;

struct MP4MovieHeader {
    /**
    mvhd
    Aca deberiamos leer la duracion
    */
    long unsigned offset;   // Offset
    char mvhd[4];           // "mhvd"

    uint8_t version;        // 8-bit
    char flags[3];          // 0xffffff
};

struct MP4MovieHeaderData_Version1 {
    /* Si la version que levantamos en MP4MovieHeader == 1 */
    unsigned long long creation_time;       // UTC date
    unsigned long long modification_time;   // UTC date
    unsigned int time_scale;
    unsigned long long duration;
};

struct MP4MovieHeaderData {
    /* Si la version que levantamos en MP4MovieHeader != 1 */
    unsigned int creation_time;     // UTC date
    unsigned int modification_time; // UTC date
    unsigned int time_scale;
    unsigned int duration;
};

struct MP4MovieHeaderMetaData {

};

int file_exists(char *filename);
void print_char_sequence(char *sequence);
// char *int_to_string(unsigned int value);

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

    /* Tama;o del archivo */
    long filesize;
    fseek(mp4, 0, SEEK_END);
    filesize = ftell(mp4);
    rewind(mp4);

    /* Leemos las cabeceras */
    MP4FileTypeIdentification header;

    fread(&header, sizeof(header), 1, mp4);

    printf("\n\n");
    if (1887007846 != header.ftyp) {
        fprintf(stderr, "Invalid file format! (%s)\n", mp4filename);
        exit(EXIT_FAILURE);
    }

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
    printf("Tamanio sequence: %lu\n\n", sizeof(sequence));
    for (int x = 0; x < sizeof(sequence); x++) {
        printf("%c", sequence[x]);
    }
}

// char *int_to_string(unsigned int value)
// {
//     const char hex[] = "0123456789abcdef";
//     char buffer[4];
//     buffer[0] = hex[value & f];
//     buffer[1] = hex[(value >> 4) & f];
//     buffer[2] = hex[(value >> 8) & f];
//     buffer[3] = hex[value >> 12];
//     return buffer;
// }
