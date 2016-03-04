#/bin/bash

i=3;
nbTest=10;
args='-s';
genPath='../puzzle/npuzzle-gen.py';
exePath='../npuzzle';
echo "=== 1x1 Test ==="
$exePath "./1-S-0.txt" >& /dev/null;
if [ $? = "0" ]; then echo ok ; else echo Bad ; fi

echo "=== 2x2 Solv ==="
$exePath "./2-S-0.txt" >& /dev/null;
if [ $? = "0" ]; then echo ok ; else echo Bad ; fi

echo "=== 2x2 UnSolv ==="
$exePath "./2-U-0.txt" >& /dev/null;
if [ $? = "1" ]; then echo ok ; else echo Bad ; fi

echo "=== 5x5 BadSize ==="
$exePath "./5-S-BadSize.txt" >& /dev/null;
if [ $? = "1" ]; then echo ok ; else echo Bad ; fi

echo "=== 4x4 BadChar ==="
$exePath "./4-S-BadChar.txt" >& /dev/null;
if [ $? = "1" ]; then echo ok ; else echo Bad ; fi

echo "=== 4x4 BadLine ==="
$exePath "./4-S-BadLine.txt" >& /dev/null;
if [ $? = "1" ]; then echo ok ; else echo Bad ; fi

echo "=== 4x4 BadSigne ==="
$exePath "./4-S-BadSigne.txt" >& /dev/null;
if [ $? = "1" ]; then echo ok ; else echo Bad ; fi

echo "=== Solvable ==="
while [ $i -lt $nbTest ] ; do
	echo "Test: puzzle "$i"x"$i;
	file='/tmp/puzzle-'$i'.'$$'.txt';
	$genPath $args $i > file;
	$exePath file >& /dev/null;
	if [ $? = "0" ]; then echo ok ; else echo Bad ; fi
	rm file;
	let i+=1;
done;

i=3;
args='-u';
echo "=== UnSolvable ==="
while [ $i -lt $nbTest ] ; do
	echo "Test: puzzle "$i"x"$i;
	file='/tmp/puzzle-'$i'.'$$'.txt';
	$genPath $args $i > file;
	$exePath file >& /dev/null;
	if [ $? = "1" ]; then echo ok ; else echo Bad ; fi
	rm file;
	let i+=1;
done;
