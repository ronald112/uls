echo "ls -lR / & ./uls -lR /"
ls -lR / > test_recursive
./uls -R / > test2_recursive
diff test_recursive test2_recursive > result_recursive