// Environment variables in C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// The maximum size of the buffers used to hold our environment variables.
#define ENV_BUFF_SIZE 256

/**
 * Reads an environment variable into a character buffer.
 *
 * Params:
 *   cosnt char* - the name of the environment variable.
 *   char* - the buffer to receive the environment variable value
 */
void load_env_var(const char *name, char *buffer)
{
    // According to https://en.cppreference.com/w/c/program/getenv
    // getenv_s is only guaranteed to be available if __STDC_LIB_EXT1__ is
    // defined by the implementation and __STDC_WANT_LIB_EXT1__ is set to 1
    // before including stdlib.h.
    // However, on current versions of MSVC, the __STDC_WANT_SECURE_LIB__
    // may be defined, in which case that compiler expects getenv_s to be used
    // instead of getenv.
#if (defined(__STDC_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ == 1) || \
    (defined(_WIN32) && defined(__STDC_WANT_SECURE_LIB__))
    size_t res_count;
    if (getenv_s(&res_count, buffer, ENV_BUFF_SIZE, name))
    {
        buffer[0] = '\0';
        return;
    }

    if (res_count < ENV_BUFF_SIZE)
    {
        buffer[res_count] = '\0';
        return;
    }

    buffer[0] = '\0';
#else
    char *v = getenv(name);
    if (v == NULL)
    {
        buffer[0] = '\0';
        return;
    }

    size_t l = strlen(v);
    if (l >= ENV_BUFF_SIZE)
    {
        buffer[0] = '\0';
        return;
    }

    for (size_t i = 0; i < l; i++)
    {
        buffer[i] = v[i];
    }
    buffer[l] = '\0';
#endif
}

int main()
{
    char e_username[ENV_BUFF_SIZE];
    char e_password[ENV_BUFF_SIZE];
    char e_host[ENV_BUFF_SIZE];
    char e_number[ENV_BUFF_SIZE];

    load_env_var("EXAMPLE_USERNAME", &e_username[0]);
    load_env_var("EXAMPLE_PASSWORD", &e_password[0]);
    load_env_var("EXAMPLE_HOST", &e_host[0]);
    load_env_var("EXAMPLE_PORT", &e_number[0]);

    printf("EXAMPLE_USERNAME: %s\n", e_username);
    printf("EXAMPLE_PASSWORD: %s\n", e_password);
    printf("EXAMPLE_HOST: %s\n", e_host);
    printf("EXAMPLE_PORT: %s\n", e_number);

    long n_number = strtol(&e_number[0], NULL, 10);
    printf("port (as an actual number): %ld\n", n_number);

    return 0;
}
