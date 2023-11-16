# In order to gain access to std::format, we use the -std=c++20 flag.
# At the time of writing this, support for the c++20 argument is experimental
# according to the GNU docs at https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html

all:
	g++ -Wall -Werror -std=c++20 main.cpp -o formatting.exe
