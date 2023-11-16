# In order to gain access to std::format, we use the /std:c++latest flag.
# According to the Microsoft docs at https://learn.microsoft.com/en-us/cpp/build/reference/std-specify-language-standard-version?view=msvc-170
# std::format is only available when using /std:c++latest.

all:
	cl /W3 /WX /EHsc /std:c++latest main.cpp /Fe"formatting.exe"
