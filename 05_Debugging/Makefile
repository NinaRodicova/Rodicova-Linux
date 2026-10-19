all:
	gcc -o0 -g range.c

test: all
	gdb --batch --quiet -x gdb1.txt ./0 > gdb1.log
	gdb --batch --quiet -x gdb2.txt ./0 > gdb2.log
	printf '@@@1 12 1 5\n@@@1 12 1 10\n' > true1.txt
	printf '@@@-100 100 3 -19\n@@@-100 100 3 -16\n@@@-100 100 3 -13\n@@@-100 100 3 -10\n@@@-100 100 3 -7\n@@@-100 100 3 -4\n@@@-100 100 3 -1\n@@@-100 100 3 2\n' > true2.txt
	grep "@@@" gdb1.log > res1.txt
	grep "@@@" gdb2.log > res2.txt
	diff -u res1.txt true1.txt
	diff -u res2.txt true2.txt

clean:
	rm -f 0
	rm -f true1.txt
	rm -f true2.txt
	rm -f res1.txt
	rm -f res2.txt
	rm -f gdb1.log
	rm -f gdb2.log
