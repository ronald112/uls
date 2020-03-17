clear
mkdir attributes
touch attributes/test_attribute1
touch attributes/test_attribute2
touch attributes/test_attribute3
touch attributes/test_attribute4
touch attributes/test_attribute6
xattr -w 1 1 attributes/test_attribute1
xattr -w 2 1 attributes/test_attribute2
xattr -w 3 1 attributes/test_attribute3
xattr -w erxferfearfae 99999 attributes/test_attribute4
xattr -w apple.com g attributes/test_attribute6

#echo "ls -l@ attributes/"
#ls -l@ attributes/
#echo "./uls -l@ attributes/"
#./uls -l@ attributes/

echo "ls -l@h /Applications"
ls -l@h /Applications > test
echo "./uls -l@h /Applications"
./uls -l@h /Applications > test2
diff test test2

#echo "ls -l@h /"
#ls -l@h / > test
#echo "./uls -l@h /"
#./uls -l@h / > test2
#diff test test2
#
#echo "ls -l@ attributes/"
#ls -l attributes/ > test
#echo "./uls -l@ attributes/"
#./uls -l attributes/ > test2
#diff test test2

#ls -l@ attributes/ > test
#./uls -l@ attributes/ > test2
rm -rf attributes/