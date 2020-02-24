clear
ls -lh /Library > test
./uls -lh /Library > test2
diff test test2
echo "/ "
ls -lh libmx/ > test
./uls -lh libmx/ > test2
diff test test2
echo "libmx/"
# for i in {1..12}; do
# 	touch ../test/file$i
# done
# make all
# ./uls ../test/* #> user
# echo
# echo "****"
# echo
# ls -aC ../test/* #> out
# diff user out
# for i in {1..11}; do
# 	rm -rf ../test/file$i
# done