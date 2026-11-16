run:
	patch -o lab1.c lab.c 0001-Define-W.patch
	patch -o lab2.c lab1.c 0002-Define-cells.patch
	patch -o lab3.c lab2.c 0003-Define-seed.patch
	gcc lab.c -o lab0
	gcc lab1.c -o lab1
	gcc lab2.c -o lab2
	gcc lab3.c -o lab3
	./lab0
	./lab1 8
	./lab2 ' @' 5
	./lab3 12 '.#' 4
	./lab3 11 '.#' 4
	./lab3 12 '.#' 4

clean:
	rm -f lab0
	rm -f lab1
	rm -f lab2
	rm -f lab3
	rm -f lab1.c
	rm -f lab2.c
	rm -f lab3.c
