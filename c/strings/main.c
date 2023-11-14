#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

// an enum could also be defined as
// enum my_enum { A, B, C };
// but then it would need to be used like so:
// enum my_enum e = A;
// By wrapping it in a typedef, it can be used like:
// my_enum e = A;
typedef enum my_type
{
    MY_TYPE_CHAR = 0,
    MY_TYPE_SHORT,
    MY_TYPE_INT,
    MY_TYPE_LONG,
    MY_TYPE_LONG_LONG,
    MY_TYPE_FLOAT,
    MY_TYPE_DOUBLE,
    MY_TYPE_LONG_DOUBLE,
    MY_TYPE_MAX,
} my_type;

const char *my_type_names[MY_TYPE_MAX] = {
    "char",
    "short",
    "int",
    "long",
    "long long",
    "float",
    "double",
    "long double"};

/**
 * Converts a NUL-terminated string into one of the primitive types.
 *
 * primitive types:
 *   char
 *   short
 *   int
 *   long
 *   long long
 *   float
 *   double
 *   long double
 */
void from_str(const char *str, my_type type, void *dest)
{
    if (type >= MY_TYPE_MAX)
        return;

    printf("This is where we would convert the string %s to a %s\n", str, my_type_names[type]);

    long long_res = strtol(str, NULL, 10);

    switch (type)
    {
    case MY_TYPE_CHAR:
        *((char *)dest) = (char)long_res;
        break;
    case MY_TYPE_SHORT:
        *((short *)dest) = (short)long_res;
        break;
    case MY_TYPE_INT:
        *((int *)dest) = (int)long_res;
        break;
    case MY_TYPE_LONG:
        *((long *)dest) = long_res;
        break;
    default:
        return;
    }
}

int main()
{
    const char *char_str = "97";
    const char *short_str = "1234";
    const char *int_str = "1234";
    const char *long_str = "1234";
    const char *long_long_str = "1234";
    const char *float_str = "3.14";
    const char *double_str = "3.14";
    const char *long_double_str = "3.14";

    char char_n = 0;
    short short_n = 0;
    int int_n = 0;
    long long_n = 0;
    long long long_long_n = 0;
    float float_n = 0;
    double double_n = 0;
    long double long_double_n = 0;

    printf("raw string: %s\n", long_str);

    from_str(char_str, MY_TYPE_CHAR, &char_n);
    from_str(short_str, MY_TYPE_SHORT, &short_n);
    from_str(int_str, MY_TYPE_INT, &int_n);
    from_str(long_str, MY_TYPE_LONG, &long_n);
    from_str(long_long_str, MY_TYPE_LONG_LONG, &long_long_n);

    printf("converted char:  %c\n", char_n);
    printf("converted short: %hd\n", short_n);
    printf("converted int:   %d\n", int_n);
    printf("converted long:  %ld\n", long_n);

    // TODO: convert strings to these types
    printf("converted long long:  %lld\n", long_long_n);
    printf("converted float:  %.2f\n", float_n);
    printf("converted double: %.2f\n", double_n);
    printf("converted long double:   %.2f\n", long_double_n);

    return 0;
}
