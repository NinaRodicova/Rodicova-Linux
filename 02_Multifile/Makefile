GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.*

%.o:    %.c
	cc -fPIC $< -c -o $@

all:    README prog

prog:   const.o fun.o prog.o
	cc $^ -o $@

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH) libout.a libout.so outfile outfile_a outfile_so
	rm -rf $(GENERATES)

test: prog
	ar -rcs libout.a const.o fun.o
	cc -shared fun.o const.o -o libout.so
	cc -L. prog.o ./libout.a -o prog-a
	cc -L. prog.o -lout -o prog-so
	./prog > outfile 2>&1
	./prog-a > outfile_a 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > outfile_so 2>&1
	cmp outfile outfile_a
	cmp outfile outfile_so
	./prog > outfile sdfsdfs 2>&1
	./prog-a > outfile_a sdfsdfs 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so sdfsdfs > outfile_so 2>&1
	cmp outfile outfile_a
	cmp outfile outfile_so
	./prog > outfile sdfsdfs sde gh 2>&1
	./prog-a > outfile_a sdfsdfs sde gh 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so sdfsdfs sde gh > outfile_so 2>&1
	cmp outfile outfile_a
	cmp outfile outfile_so
