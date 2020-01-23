clear
for i in {1..4}; do
	touch ../test/file$i
done
make all
./uls ../test/
echo
echo "****"
echo
ls ../test/
for i in {1..4}; do
	rm -rf ../test/file$i
done