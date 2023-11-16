# ----------------------------------------------------------------------------
# The /EH flag is used to specify how exceptions will be handled.
# The s argument means we only catch standard C++ exceptions.
# The c argument means we assume that functions declared as extern "C" will
# never throw C++ exceptions.
#
# ----------------------------------------------------------------------------
#
# Notes on the /EH flag copied from the Microsoft docs at
# https://learn.microsoft.com/en-us/cpp/build/reference/eh-exception-handling-model?view=msvc-170
#
# s
# Enables standard C++ stack unwinding.
# Catches only standard C++ exceptions when you use catch(...) syntax.
# Unless /EHc is also specified, the compiler assumes that functions declared
# as extern "C" may throw a C++ exception.
#
# c
# When used with /EHs, the compiler assumes that functions declared as extern
# "C" never throw a C++ exception.
# It has no effect when used with /EHa (that is, /EHca is equivalent to /EHa).
# /EHc is ignored if /EHs or /EHa aren't specified.
#
# ----------------------------------------------------------------------------

all:
	cl /W3 /WX /EHsc main.cpp /Fe"hello.exe"
