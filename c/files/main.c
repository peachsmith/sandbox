#include <stdio.h>
#include <errno.h>

#define BIN_BUFFER_SIZE 16
#define TXT_BUFFER_SIZE 10

FILE *open_file(const char *name, const char *mode)
{
    FILE *f;

#if (defined(__STDC_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1) || \
    (defined(_WIN32) && !defined(_CRT_SECURE_NO_WARNINGS))
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
    unsigned char buffer[BIN_BUFFER_SIZE];

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
    unsigned char buffer[BIN_BUFFER_SIZE];

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

void write_text(FILE *stream)
{
    int numbers[TXT_BUFFER_SIZE] = {
        24601,
        1776,
        2319,
        42,
        69,
        420,
        8080,
        8443,
        0xBEEF,
        1000000};

    for (int i = 0; i < TXT_BUFFER_SIZE; i++)
    {
        fprintf(stream, "%d\n", numbers[i]);
    }
}

void read_text(FILE *stream)
{
    int numbers[TXT_BUFFER_SIZE];
    int reading = 1;

    // Notes about the %c and %s format specifiers from https://en.cppreference.com/w/c/io/fscanf
    //
    // %c
    // Matches a character or a sequence of characters.
    // If a width specifier is used, matches exactly width characters (the
    // argument must be a pointer to an array with sufficient room).
    // Unlike %s and %[, does not append the null character to the array.
    //
    // %s
    // Matches a sequence of non-whitespace characters (a string).
    // If width specifier is used, matches up to width or until the first
    // whitespace character, whichever appears first. Always stores a null
    // character in addition to the characters matched (so the argument array
    // must have room for at least width+1 characters)

    // Read one more than the number of elements written to test handling of
    // error or EOF.
    for (int i = 0; i < TXT_BUFFER_SIZE + 1 && reading; i++)
    {
        int n;
        int res;

#if (defined(__STDC_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1) || \
    (defined(_WIN32) && !defined(_CRT_SECURE_NO_WARNINGS))
        res = fscanf_s(stream, "%d", &n);
#else
        res = fscanf(stream, "%d", &n);
#endif

        if (!res || res == EOF)
        {
            if (feof(stream))
            {
                printf("reached end of input file\n");
            }
            if (ferror(stream))
            {
                printf("an error occurred while reading the input file\n");
            }
            reading = 0;
        }
        else
        {
            numbers[i] = n;
        }
    }

    printf("data from file:\n");
    for (int i = 0; i < TXT_BUFFER_SIZE; i++)
    {
        if (i == 8)
            printf("txt[%d] %X\n", i, numbers[i]);
        else
            printf("txt[%d] %d\n", i, numbers[i]);
    }
}

int main()
{
    FILE *f;

    //------------------------------------------------------------------------
    // Binary File IO

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
    // f = open_file("bin.jep", "rb");
    // if (f == NULL)
    // {
    //     fprintf(stderr, "failed to open file for reading\n");
    //     return 1;
    // }
    // read_data(f);
    // fclose(f);

    //------------------------------------------------------------------------
    // Text File IO

    // Write text data.
    // f = open_file("data.txt", "w");
    // if (f == NULL)
    // {
    //     fprintf(stderr, "failed to open file for writing\n");
    //     return 1;
    // }
    // write_text(f);
    // fclose(f);

    // Read text data.
    f = open_file("data.txt", "r");
    if (f == NULL)
    {
        fprintf(stderr, "failed to open file for reading\n");
        return 1;
    }
    read_text(f);
    fclose(f);

    return 0;
}