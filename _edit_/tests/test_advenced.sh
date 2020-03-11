clear
echo "./uls -lh /dev"
ls -lh /dev/ > test & ./uls -lh /dev/ > test2
diff test test2
ls -lh / > test & ./uls -lh / > test2
diff test test2
echo "./uls -lh /"
ls -lh /../ > test & ./uls -lh /../ > test2
diff test test2
echo "./uls -lh /../"
ls -l / > test & ./uls -l / > test2
diff test test2
echo "./uls -l /"
ls -lh libmx/ > test & ./uls -lh libmx/ > test2
diff test test2
echo "./uls -lh libmx/"
ls * > test & ./uls * > test2
diff test test2
echo "./uls *"
ls ///////* > test
./uls ///////* > test2
diff test test2
echo "./uls /*"
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