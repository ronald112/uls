clear
echo "./uls -z"
./uls -z
echo "./uls xxx ?"
./uls xxx
echo "$?"
mkdir dir1 dir2
touch file1 file2 file3
touch dir1/A.txt dir1/B.txt dir1/C.txt dir1/D.txt dir1/E.txt dir1/F.txt
touch dir1/G.txt dir1/H.txt dir1/I.txt dir1/J.txt dir1/K.txt dir1/L.txt
touch dir1/M.txt dir1/N.txt dir1/O.txt dir1/P.txt dir1/R.txt dir1/S.txt
touch dir1/T.txt dir1/U.txt dir1/V.txt dir1/W.txt dir1/X.txt dir1/Y.txt
touch dir1/Z.txt
echo "./uls | cat -e"
./uls | cat -e
echo "./uls dir1 dir2 file1 file2 file3"
./uls dir1 dir2 file1 file2 file3
echo "./uls -l | cat -e"
./uls -l | cat -e
rm -rf dir1 dir2 file1 file2 file3