// Fundamentals of C, with which pretty much anything can be done.
// Most or all of these features are expected to be present in some form or
// fashion in all languages invented after C.
//
// variables
// arrays (static and dynamic)
// functions
// passing functions as arguments
// structures
// type definitions

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define EXAMPLE_BUFFER_SIZE 16

// custom types
typedef unsigned char my_byte;

// Define a custom type called "my_callback" that denotes a function that
// takes two integer arguments and returns an int.
typedef int (*my_callback)(int, int);

typedef struct my_object
{
    my_byte b;
    void (*hello)();      // function without typedef
    my_callback callback; // function with typedef
} my_object;

void print_array(const my_byte *a, size_t s)
{
    for (size_t i = 0; i < s; i++)
    {
        printf("%X ", a[i]);
    }
    printf("\n");
}

void do_callback_without_typedef(int (*callback)(int, int))
{
    printf("callback result: %d\n", callback(1, 2));
}

void do_callback_with_typedef(my_callback callback)
{
    printf("other callback result: %d\n", callback(1, 2));
}

int example_add(int a, int b)
{
    return a + b;
}

void greet()
{
    printf("Hello, World!\n");
}

void print_bits(my_byte b)
{
    for (int i = 0; i < CHAR_BIT; i++)
    {
        putc((b & (1 << (CHAR_BIT - i - 1))) ? '1' : '0', stdout);
    }
    putc('\n', stdout);
}

int main()
{
    //------------------------------------------------------------------------
    // primitive data types
    //
    // Each of these primitives can be specified as signed or unsigned, but
    // signed is the default.
    //
    // Integer Types
    // ----------------
    // type        size
    // ----------------
    // char        at least 8 bits
    // short       at least 16 bits
    // int         at least 16 bits (often 32 bits)
    // long        at least 32 bits (can be 64 bits)
    // long long   at least 64 bits
    //
    //
    // Floating Point Types
    // --------------------
    // float         single precision floating point
    // double        double precision floating point
    // long double   extended precision floating point

    // A char is the smallest addressable unit of memory that can contain the
    // basic character set. Therefore, sizeof(char) is 1.
    // It contains CHAR_BIT bits.
    char c = 'a';
    short ns = 4;
    int ni = 4;
    long nl = 4;
    float sf = 4.250;
    double df = 4.350;

    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("type    value  sizeof(type)\n");
    printf("---------------------------\n");
    printf("char    %-5c  %zu\n", c, sizeof(c));
    printf("short   %-5hd  %zu\n", ns, sizeof(ns));
    printf("int     %-5d  %zu\n", ni, sizeof(ni));
    printf("long    %-5ld  %zu\n", nl, sizeof(nl));
    printf("float   %-5.2f  %zu\n", sf, sizeof(sf));
    printf("double  %-5.2f  %zu\n", df, sizeof(df));

    //------------------------------------------------------------------------
    // static arrays
    my_byte data[EXAMPLE_BUFFER_SIZE];
    my_byte b = 0x00;
    for (int i = 0; i < EXAMPLE_BUFFER_SIZE; i++)
    {
        data[i] = b + i;
    }

    // sizeof effectively returns the number of elements of a static array.
    printf("sizeof static array: %zu (number of elements)\n", sizeof(data));

    // Since print_array expects a pointer to a my_byte, we pass in the
    // address of the first element of the data array.
    print_array(&data[0], sizeof(data));

    //------------------------------------------------------------------------
    // dynamic arrays
    size_t dy_size = EXAMPLE_BUFFER_SIZE;
    my_byte *dy_data = (my_byte *)malloc(sizeof(my_byte) * dy_size);
    for (int i = 0; i < dy_size; i++)
    {
        dy_data[i] = b + (0xF - i);
    }

    // sizeof returns the size of a pointer when given a pointer to dynamic
    // memory. In this case, dy_data is just a pointer like any any other
    // pointer.
    printf("sizeof dynamic array: %zu (size of a pointer)\n", sizeof(dy_data));

    print_array(dy_data, dy_size);

    // Resize the dynamic array and append more elements.
    // On success, realloc returns a pointer to the new block of mmeory and
    // the original pointer is invalidated.
    // On failure, it returns NULL and the original pointer is still valid.
    dy_size += 8;
    dy_data = realloc(dy_data, dy_size);
    for (size_t i = dy_size - 8; i < dy_size; i++)
    {
        dy_data[i] = b + (my_byte)i;
    }
    print_array(dy_data, dy_size);

    // Free anything that was allocated with malloc.
    free(dy_data);

    //------------------------------------------------------------------------
    // passing functions as arguments
    do_callback_without_typedef(example_add);
    do_callback_with_typedef(example_add);

    //------------------------------------------------------------------------
    // structures
    my_object obj;
    obj.b = 0xFF;
    obj.callback = example_add;
    obj.hello = greet;

    obj.hello();
    printf("callback result from within a struct: %d\n", obj.callback(2, 3));

    //------------------------------------------------------------------------
    // bitwise operations

    // Bitwise notation:
    // Bits start at bit 0, like array indices.
    // A range of bits is often represents in the form [<high>:<low>]
    // for example, the first 8 bits of a number would be [7:0].
    //
    // The number 129 represented as a bit string:
    // value: 1  0  0  0  0  0  0  1
    // bit:   7  6  5  4  3  2  1  0

    // single bit set to 1
    my_byte bit_demo = 0x00;

    // set bit 0
    bit_demo |= 0x01;
    print_bits(bit_demo);

    // set bits 3 and 7
    bit_demo |= (0x08 | 0x80);
    print_bits(bit_demo);

    // clear bit 3
    bit_demo &= ~(1 << 3);
    print_bits(bit_demo);

    // toggle all bits
    bit_demo = ~bit_demo;
    print_bits(bit_demo);

    // clear all bits
    bit_demo ^= bit_demo;
    print_bits(bit_demo);

    // set all bits
    bit_demo ^= ~(bit_demo);
    print_bits(bit_demo);

    return 0;
}
