#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

/** Mas rapido que usar ifstream.good() */
inline bool file_exists(const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

void print_char_sequence(char *sequence)
{
    for (int x = 0; x < (sizeof sequence); x++) {
        printf("%c", sequence[x]);
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Uso: %s ARCHIVO\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *mp4filename = argv[1];

    if (!file_exists(mp4filename)) {
        printf("Archivo inexistente (%s).\n", mp4filename);
        return EXIT_FAILURE;
    }

    std::ifstream mp4;
    mp4.open(mp4filename);

    char header[8];     // Header
    char mb[4];         // Major brand
    char mbv[4];        // Major brand version
    char cb[4];         // Compatible brands

    char mdb[8];        // Media data box
    char us[24];        // Unused space
    char frames[256];



    mp4.read((char *) &header, sizeof header);
    mp4.read((char *) &mb, sizeof mb);
    mp4.read((char *) &mbv, sizeof mbv);
    mp4.read((char *) &cb, sizeof cb);

    mp4.read((char *) &mdb, sizeof mdb);
    mp4.read((char *) &us, sizeof us);

    mp4.read((char *) &frames, sizeof frames);

    print_char_sequence(header);
    print_char_sequence(mb);
    print_char_sequence(mbv);
    print_char_sequence(cb);
    printf("\n\n");
    print_char_sequence(mdb);
    print_char_sequence(us);
    printf("\n\n");
    print_char_sequence(frames);

    ofstream outmp4("sample/test.mp4", ios::out | ios::binary);

    if (!outmp4) {
        printf("No se puede escribir el archivo");
        return EXIT_FAILURE;
    }

    outmp4.write((char *) &header, sizeof header);
    outmp4.write((char *) &mb, sizeof mb);
    outmp4.write((char *) &mbv, sizeof mbv);
    outmp4.write((char *) &cb, sizeof cb);
    outmp4.write((char *) &mdb, sizeof mdb);
    outmp4.write((char *) &us, sizeof us);

    outmp4.write((char *) &frames, sizeof frames);

    // printf("\n\n%s", header);
    printf("\n\n");
    printf("So vo!\n");
}
