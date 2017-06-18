#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

struct mp4header {
    long unsigned offset;   // offset
    char ftyp[4];           // "ftyp"

    char mb[4];             // Major brand
    char mbv[4];            // Major brand version
    char cb[4];             // Compatible brands

    char mdb[8];            // Media data box
    char us[24];            // Unused space
};

struct MP4MediaData {
    long unsigned offset;
    char mdat[4];
};

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
    creation_time; 8bits
    modification_time; 8bits
    time_scale; 4
    duration; 8
};

struct MP4MovieHeaderData {
    /* Si la version que levantamos en MP4MovieHeader != 1 */
    creation_time; 4
    modification_time; 4
    time_scale; 4
    duration; 4
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
