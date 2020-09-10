echo script type: R
strVer=v?
echo ">>>>>>>>running test 1"
rm print_tokens.gcda
./print_tokens.exe  < ../inputs/newtst148.tst > ../outputs/t1
mv ../outputs/t1 ../outputs/${strVer}/t1
gcov print_tokens.c
mv print_tokens.c.gcov ../traces/${strVer}/t1.gcov
echo ">>>>>>>>running test 2"
rm print_tokens.gcda
./print_tokens.exe  < ../inputs/newtst1.tst > ../outputs/t2
mv ../outputs/t2 ../outputs/${strVer}/t2
gcov print_tokens.c
mv print_tokens.c.gcov ../traces/${strVer}/t2.gcov
echo ${strVer} is finished.
