clear
for i in {1..10}; do
	touch ../test/file$i
done
make all
./uls ../test/
echo
echo "****"
echo
ls ../test/
for i in {1..10}; do
	rm ../test/file$i
done