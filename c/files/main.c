#include <stdio.h>
#include <errno.h>

FILE *open_file(const char *name, const char *mode)
{
    FILE *f;

#if (defined(__STDC_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1) || \
    (defined(_WIN32) && defined(__STDC_WANT_SECURE_LIB__))
    if (fopen_s(&f, name, mode))
    {
        return NULL;
    }
#else
    f = fopen(name, mode);
    if (f == NULL)
    {
        return NULL;
    }
#endif

    return f;
}

void write_data(FILE *stream)
{
    unsigned char buffer[64];

    buffer[0] = 'J';
    buffer[1] = 'E';
    buffer[2] = 'P';
    buffer[3] = 0xDE;
    buffer[4] = 0xAD;
    buffer[5] = 0xBE;
    buffer[6] = 0xEF;

    size_t res = fwrite(
        buffer,                // buffer
        sizeof(unsigned char), // size of each element
        7,                     // number of elements
        stream                 // output stream
    );

    printf("wrote %zu elements\n", res);
}

void read_data(FILE *stream)
{
    unsigned char buffer[64];

    size_t res = fread(
        buffer,                // buffer
        sizeof(unsigned char), // size of each element
        7,                     // number of elements
        stream                 // input stream
    );

    printf("read %zu elements\n", res);
    for (size_t i = 0; i < res; i++)
    {
        printf("%X ", buffer[i]);
    }
    printf("\n");
}

int main()
{
    FILE *f;

    // Write binary data.
    // f = open_file("bin.jep", "wb");
    // if (f == NULL)
    // {
    //     fprintf(stderr, "failed to open file for writing\n");
    //     return 1;
    // }
    // write_data(f);
    // fclose(f);

    // Read binary data.
    f = open_file("bin.jep", "rb");
    if (f == NULL)
    {
        fprintf(stderr, "failed to open file for reading\n");
        return 1;
    }
    read_data(f);
    fclose(f);

    return 0;
}