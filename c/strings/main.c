// String conversion functions in C.
//
// The conversion of string to primitive is handled by the strtol function
// and its friends like strtoll and strtof.
// The conversion of primitives to strings is handled by snprintf.
// These functions are available as of the C99 standard.
//
// The str_to_primitive and primitive_to_str rely on casting to and from a
// void pointer, which is a feature that is either concealed, discouraged
// or outright removed in most languages invented after C.
// For example, C++ does not allow casting to and from a void pointer the
// way we do here. It's a little disappointing that newer languages try
// to obscure this important functionality, but it's probably for the best.

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define CONV_BUFF_SIZE 64

// an enum could also be defined as
// enum my_enum { A, B, C };
// but then it would need to be used like so:
// enum my_enum e = A;
// By wrapping it in a typedef, it can be used like:
// my_enum e = A;
typedef enum my_type
{
    MY_TYPE_CHAR = 0,
    MY_TYPE_UNSIGNED_CHAR,
    MY_TYPE_SHORT,
    MY_TYPE_UNSIGNED_SHORT,
    MY_TYPE_INT,
    MY_TYPE_UNSIGNED_INT,
    MY_TYPE_LONG,
    MY_TYPE_UNSIGNED_LONG,
    MY_TYPE_LONG_LONG,
    MY_TYPE_UNSIGNED_LONG_LONG,
    MY_TYPE_FLOAT,
    MY_TYPE_DOUBLE,
    MY_TYPE_LONG_DOUBLE,
    MY_TYPE_MAX,
} my_type;

const char *my_type_names[MY_TYPE_MAX] = {
    "char",
    "unsigned char",
    "short",
    "unsigned short",
    "int",
    "unsigned int",
    "long",
    "unsigned long",
    "long long",
    "unsigned long long",
    "float",
    "double",
    "long double"};

// Assigns a long value, v, to a destination pointed to by pointer p.
// The value is cast as type t.
#define as_value(t,v,p) *((t*) p) = (t)v

/**
 * Converts a NUL-terminated string into one of the primitive types.
 *
 * Params:
 *   const char* - a pointer to a string of characters
 *   my_type - a type enumeration of the value's type
 *   void* - a pointer to the destination for the converted value
 * 
 * Returns:
 *   int - 0 on success, 1 on failure
 */
int str_to_primitive(const char *str, my_type type, void *dest)
{
    if (type >= MY_TYPE_MAX)
        return 1;

    // This function relies on the following functions defined as part of the
    // C99 standard:
    //   strtol
    //   strtoul
    //   strtoll
    //   strtoull
    //   strtof
    //   strtod
    //   strtold
    //
    // Notes on strtol from https://en.cppreference.com/w/c/string/byte/strtol
    // Ignores leading whitespace.
    // The string may start with an optional plus or minus sign.
    // The string may start with an optional 0 for octal or 0x or 0X for hexadecimal.
    // If the base is 0, then the base is detected automatically.
    // If the source string is empty or malformed, no conversion occurs.
    //
    // On success, the integer representation of the string is returned.
    // If the integer value is out of range, then LONG_MIN or LONG_MAX is
    // returned and errno is set to ERANGE.
    // If no conversion is possible, then 0 is returned.

    long               l_res;
    unsigned long      ul_res;
    long long          ll_res;
    unsigned long long ull_res;
    float              f_res;
    double             d_res;
    long double        ld_res;

    if      (type <= MY_TYPE_LONG)               l_res   = strtol   (str, NULL, 10);
    else if (type == MY_TYPE_UNSIGNED_LONG)      ul_res  = strtoul  (str, NULL, 10);
    else if (type == MY_TYPE_LONG_LONG)          ll_res  = strtoll  (str, NULL, 10);
    else if (type == MY_TYPE_UNSIGNED_LONG_LONG) ull_res = strtoull (str, NULL, 10);
    else if (type == MY_TYPE_FLOAT)              f_res   = strtof   (str, NULL);
    else if (type == MY_TYPE_DOUBLE)             d_res   = strtod   (str, NULL);
    else if (type == MY_TYPE_LONG_DOUBLE)        ld_res  = strtold  (str, NULL);

    if (errno == ERANGE)
        return 1;

    switch (type)
    {
    case MY_TYPE_CHAR:               as_value(char,               l_res,   dest);  return 0;
    case MY_TYPE_UNSIGNED_CHAR:      as_value(unsigned char,      l_res,   dest);  return 0;
    case MY_TYPE_SHORT:              as_value(short,              l_res,   dest);  return 0;
    case MY_TYPE_UNSIGNED_SHORT:     as_value(unsigned short,     l_res,   dest);  return 0;
    case MY_TYPE_INT:                as_value(int,                l_res,   dest);  return 0;
    case MY_TYPE_UNSIGNED_INT:       as_value(unsigned int,       l_res,   dest);  return 0;
    case MY_TYPE_LONG:               as_value(long,               l_res,   dest);  return 0;
    case MY_TYPE_UNSIGNED_LONG:      as_value(unsigned long,      ul_res,  dest);  return 0;
    case MY_TYPE_LONG_LONG:          as_value(long long,          ll_res,  dest);  return 0;
    case MY_TYPE_UNSIGNED_LONG_LONG: as_value(unsigned long long, ull_res, dest);  return 0;
    case MY_TYPE_FLOAT:              as_value(float,              f_res,   dest);  return 0;
    case MY_TYPE_DOUBLE:             as_value(double,             d_res,   dest);  return 0;
    case MY_TYPE_LONG_DOUBLE:        as_value(long double,        ld_res,  dest);  return 0;
    default: return 0;
    }
}

/**
 * Converts a primitive to a string of char.
 * 
 * Params:
 *   void* - a pointer to the value to convert
 *   my_type - a type enumeration of the value's type
 *   char* - a pointer to a char buffer
 * 
 * Returns:
 *   int - 0 on success, 1 on failure
 */
int primitive_to_str(void* value, my_type type, char* buffer, size_t s)
{
    // This function relies on snprintf to convert strings.
    //
    // Notes on snprintf from https://en.cppreference.com/w/c/io/fprintf
    // Writes the results to a character string buffer.
    // At most bufsz - 1 characters are written.
    // The resulting character string will be terminated with a null character, unless bufsz is zero.
    // If bufsz is zero, nothing is written and buffer may be a null pointer,
    // however the return value (number of bytes that would be written not including the null terminator)
    // is still calculated and returned.

    int res = 0;

    switch (type)
    {
    case MY_TYPE_CHAR:               res = snprintf(buffer, s, "%c",   *(char*)value);               break;
    case MY_TYPE_UNSIGNED_CHAR:      res = snprintf(buffer, s, "%c",   *(unsigned char*)value);      break;
    case MY_TYPE_SHORT:              res = snprintf(buffer, s, "%hd",  *(short*)value);              break;
    case MY_TYPE_UNSIGNED_SHORT:     res = snprintf(buffer, s, "%hu",  *(unsigned short*)value);     break;
    case MY_TYPE_INT:                res = snprintf(buffer, s, "%d",   *(int*)value);                break;
    case MY_TYPE_UNSIGNED_INT:       res = snprintf(buffer, s, "%u",   *(unsigned int*)value);       break;
    case MY_TYPE_LONG:               res = snprintf(buffer, s, "%ld",  *(long*)value);               break;
    case MY_TYPE_UNSIGNED_LONG:      res = snprintf(buffer, s, "%ld",  *(unsigned long*)value);      break;
    case MY_TYPE_LONG_LONG:          res = snprintf(buffer, s, "%lld", *(long long*)value);          break;
    case MY_TYPE_UNSIGNED_LONG_LONG: res = snprintf(buffer, s, "%llu", *(unsigned long long*)value); break;
    case MY_TYPE_FLOAT:              res = snprintf(buffer, s, "%f",   *(float*)value);              break;
    case MY_TYPE_DOUBLE:             res = snprintf(buffer, s, "%f",   *(double*)value);             break;
    case MY_TYPE_LONG_DOUBLE:        res = snprintf(buffer, s, "%Lf",  *(long double*)value);        break;
    default: break;
    }

    return res >= 0;
}

int main()
{
    const char *char_str        = "97";
    const char *short_str       = "1234";
    const char *int_str         = "12345";
    const char *long_str        = "123456";
    const char *long_long_str   = "1234567";
    const char *float_str       = "3.14";
    const char *double_str      = "3.14";
    const char *long_double_str = "3.14";

    char char_num                     = 0;
    unsigned char uchar_num           = 0;
    short short_num                   = 0;
    unsigned short ushort_num         = 0;
    int int_num                       = 0;
    unsigned int uint_num             = 0;
    long long_num                     = 0;
    unsigned long ulong_num           = 0;
    long long long_long_num           = 0;
    unsigned long long ulong_long_num = 0;
    float float_num                   = 0;
    double double_num                 = 0;
    long double long_double_num       = 0;

    char char_buf[CONV_BUFF_SIZE];
    char uchar_buf[CONV_BUFF_SIZE];
    char short_buf[CONV_BUFF_SIZE];
    char ushort_buf[CONV_BUFF_SIZE];
    char int_buf[CONV_BUFF_SIZE];
    char uint_buf[CONV_BUFF_SIZE];
    char long_buf[CONV_BUFF_SIZE];
    char ulong_buf[CONV_BUFF_SIZE];
    char long_long_buf[CONV_BUFF_SIZE];
    char ulong_long_buf[CONV_BUFF_SIZE];
    char float_buf[CONV_BUFF_SIZE];
    char double_buf[CONV_BUFF_SIZE];
    char long_double_buf[CONV_BUFF_SIZE];

    // convert strings to primitives
    str_to_primitive(char_str,        MY_TYPE_CHAR,               &char_num);
    str_to_primitive(char_str,        MY_TYPE_UNSIGNED_CHAR,      &uchar_num);
    str_to_primitive(short_str,       MY_TYPE_SHORT,              &short_num);
    str_to_primitive(short_str,       MY_TYPE_UNSIGNED_SHORT,     &ushort_num);
    str_to_primitive(int_str,         MY_TYPE_INT,                &int_num);
    str_to_primitive(int_str,         MY_TYPE_UNSIGNED_INT,       &uint_num);
    str_to_primitive(long_str,        MY_TYPE_LONG,               &long_num);
    str_to_primitive(long_str,        MY_TYPE_UNSIGNED_LONG,      &ulong_num);
    str_to_primitive(long_long_str,   MY_TYPE_LONG_LONG,          &long_long_num);
    str_to_primitive(long_long_str,   MY_TYPE_UNSIGNED_LONG_LONG, &ulong_long_num);
    str_to_primitive(float_str,       MY_TYPE_FLOAT,              &float_num);
    str_to_primitive(double_str,      MY_TYPE_DOUBLE,             &double_num);
    str_to_primitive(long_double_str, MY_TYPE_LONG_DOUBLE,        &long_double_num);

    // convert primitives to strings
    primitive_to_str(&char_num,        MY_TYPE_CHAR,               &char_buf[0],        CONV_BUFF_SIZE);
    primitive_to_str(&uchar_num,       MY_TYPE_UNSIGNED_CHAR,      &uchar_buf[0],       CONV_BUFF_SIZE);
    primitive_to_str(&short_num,       MY_TYPE_SHORT,              &short_buf[0],       CONV_BUFF_SIZE);
    primitive_to_str(&ushort_num,      MY_TYPE_UNSIGNED_SHORT,     &ushort_buf[0],      CONV_BUFF_SIZE);
    primitive_to_str(&int_num,         MY_TYPE_INT,                &int_buf[0],         CONV_BUFF_SIZE);
    primitive_to_str(&uint_num,        MY_TYPE_UNSIGNED_INT,       &uint_buf[0],        CONV_BUFF_SIZE);
    primitive_to_str(&long_num,        MY_TYPE_LONG,               &long_buf[0],        CONV_BUFF_SIZE);
    primitive_to_str(&ulong_num,       MY_TYPE_UNSIGNED_LONG,      &ulong_buf[0],       CONV_BUFF_SIZE);
    primitive_to_str(&long_long_num,   MY_TYPE_LONG_LONG,          &long_long_buf[0],   CONV_BUFF_SIZE);
    primitive_to_str(&ulong_long_num,  MY_TYPE_UNSIGNED_LONG_LONG, &ulong_long_buf[0],  CONV_BUFF_SIZE);
    primitive_to_str(&float_num,       MY_TYPE_FLOAT,              &float_buf[0],       CONV_BUFF_SIZE);
    primitive_to_str(&double_num,      MY_TYPE_DOUBLE,             &double_buf[0],      CONV_BUFF_SIZE);
    primitive_to_str(&long_double_num, MY_TYPE_LONG_DOUBLE,        &long_double_buf[0], CONV_BUFF_SIZE);

    printf("+-------------------------------------+\n");
    printf("|       string to primitive           |\n");
    printf("+-------------------------------------+\n");
    printf("raw string:         %s\n",    long_str);
    printf("char:               %c\n",    char_num);
    printf("unsigned char:      %c\n",    uchar_num);
    printf("short:              %hd\n",   short_num);
    printf("unsigned short:     %hd\n",   ushort_num);
    printf("int:                %d\n",    int_num);
    printf("unsigned int:       %d\n",    uint_num);
    printf("long:               %ld\n",   long_num);
    printf("unsigned long:      %ld\n",   ulong_num);
    printf("long long:          %lld\n",  long_long_num);
    printf("unsigned long long: %lld\n",  ulong_long_num);
    printf("float:              %.2f\n",  float_num);
    printf("double:             %.2f\n",  double_num);
    printf("long double:        %.2Lf\n", long_double_num);

    printf("\n");

    printf("+-------------------------------------+\n");
    printf("|       primitive to string           |\n");
    printf("+-------------------------------------+\n");
    printf("char:               %s\n", char_buf);
    printf("unsigned char:      %s\n", uchar_buf);
    printf("short:              %s\n", short_buf);
    printf("unsigned short:     %s\n", ushort_buf);
    printf("int:                %s\n", int_buf);
    printf("unsigned int:       %s\n", uint_buf);
    printf("long:               %s\n", long_buf);
    printf("unsigned long:      %s\n", ulong_buf);
    printf("long long:          %s\n", long_long_buf);
    printf("unsigned long long: %s\n", ulong_long_buf);
    printf("float:              %s\n", float_buf);
    printf("double:             %s\n", double_buf);
    printf("long double:        %s\n", long_double_buf);

    return 0;
}
