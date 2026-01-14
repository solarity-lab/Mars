#include "mbuff.h"

struct mbuff*
mbuff_new(void) {
    struct mbuff *zio = malloc(sizeof(struct mbuff));

    zio->file = "stdin";
    zio->buffer = NULL;
    zio->size = 0;

    zio->nf = 0;
    zio->maxf = 100;
    zio->folders = calloc(zio->maxf, sizeof(char*));

    return zio;    
}

int 
mbuff_free
(struct mbuff *zio) {
    if (!zio) return 0;
    if (zio->buffer) free(zio->buffer);
    free(zio->folders);
    free(zio);
    return 1;
}

struct mbuff*
mbuff_read_file
(char* file) {
    if (!file) {
        return NULL;
    }

    FILE *fp = fopen(file, "rb");
    if (!fp) {
        printf("Error: Could not open file %s\n", file);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);

    struct mbuff *zio = mbuff_new();
    if (!zio) {
        fclose(fp);
        return NULL;
    }

    zio->file = file;
    zio->buffer = (char*)malloc(fsize + 1);
    if (!zio->buffer) {
        free(zio);
        fclose(fp);
        return NULL;
    }

    size_t nread = fread(zio->buffer, 1, fsize, fp);
    fclose(fp);

    zio->buffer[nread] = '\0';
    zio->size = (int)nread;

    return zio;
}