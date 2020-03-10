echo "ls -lR / & ./uls -lR /"
ls -lR / > test 
./uls -lR / > test2_recursive
diff test_recursive test2_recursive > result_recursive