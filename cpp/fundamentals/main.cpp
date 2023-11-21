#include <iostream>

// C headers can still be included.
// The C++ way of doing so is prepending 'c' to the header name and removing
// the ".h" suffix.
#include <cstdio>
#include <climits>

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
    std::cout << "Hello, World!" << std::endl;
}

void print_bits(my_byte b)
{
    for (int i = 0; i < CHAR_BIT; i++)
    {
        putc((b & (1 << (CHAR_BIT - i - 1))) ? '1' : '0', stdout);
    }
    putc('\n', stdout);
}

void multiply_by_reference(int &a, int b)
{
    a *= b;
}

int main()
{
    //------------------------------------------------------------------------
    // primitive data types
    // The fundamental primitive data types are mostly the same as C.

    char c = 'a';
    short ns = 4;
    int ni = 4;
    long nl = 4;
    float sf = 4.250;
    double df = 4.350;

    // Until C++ 20, C++ did not provide a standard drop-in replacement for
    // printf, but printf can be used pretty much the same way as in C.
    // C++ 20 introduced std::format, which allows for a more C++ way of
    // formatting output.

    // The C way of formatting output
    printf("C formatting\n");
    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("type    value  sizeof(type)\n");
    printf("---------------------------\n");
    printf("char    %-5c  %zu\n", c, sizeof(c));
    printf("short   %-5hd  %zu\n", ns, sizeof(ns));
    printf("int     %-5d  %zu\n", ni, sizeof(ni));
    printf("long    %-5ld  %zu\n", nl, sizeof(nl));
    printf("float   %-5.2f  %zu\n", sf, sizeof(sf));
    printf("double  %-5.2f  %zu\n", df, sizeof(df));
    printf("\n");

    //------------------------------------------------------------------------
    // static arrays
    my_byte data[EXAMPLE_BUFFER_SIZE];
    my_byte b = 0x00;
    for (int i = 0; i < EXAMPLE_BUFFER_SIZE; i++)
    {
        data[i] = b + i;
    }

    // sizeof effectively returns the number of elements of a static array.
    std::cout << "sizeof static array: " << sizeof(data) << " (number of elements)" << std::endl;

    // Since print_array expects a pointer to a my_byte, we pass in the
    // address of the first element of the data array.
    print_array(&data[0], sizeof(data));

    //------------------------------------------------------------------------
    // dynamic arrays
    size_t dy_size = EXAMPLE_BUFFER_SIZE;
    my_byte *dy_data = new my_byte[dy_size];
    for (int i = 0; i < dy_size; i++)
    {
        dy_data[i] = b + (0xF - i);
    }

    std::cout << "sizeof dynamic array: " << sizeof(dy_data) << " (size of a pointer)" << std::endl;

    // There is currently no C++ version of realloc for plain arrays.
    // For such functionality, either allocate an array the C way, or use
    // something like std::vector.

    delete[] dy_data;

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
    std::cout << "callback result from within a struct: " << obj.callback(2, 3) << std::endl;

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

    //------------------------------------------------------------------------
    // references

    int some_value = 4;
    int other_value = 5;

    // A reference is basically just a prettier pointer.
    // It allows modification of the referenced value without the dereference
    // operator.
    int &some_reference = some_value;

    // Once a reference has been declared, it cannot be changed to point to a
    // different value. Attempting to do so will simply assign the referenced
    // variable to a new value.
    // So the following statement is basically the same as
    // some_value = other_value
    some_reference = other_value;

    std::cout << "some_reference " << some_reference << std::endl;
    multiply_by_reference(some_reference, 2);
    std::cout << "some_reference " << some_reference << std::endl;

    return 0;
}
