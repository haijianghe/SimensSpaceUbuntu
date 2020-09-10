strVer=v3
rm print_tokens.c
rm stream.h
rm tokens.h
cp ../versions.alt/versions.orig/${strVer}/print_tokens.c .
cp ../versions.alt/versions.orig/${strVer}/stream.h .
cp ../versions.alt/versions.orig/${strVer}/tokens.h .
#-Wimplicit-int
#-Wimplicit-function-declaration
rm print_tokens.exe
rm print_tokens.gcda
rm print_tokens.gcno
#-include stdlib.h
gcc -fprofile-arcs -ftest-coverage -include stdlib.h -include string.h print_tokens.c -o print_tokens.exe
