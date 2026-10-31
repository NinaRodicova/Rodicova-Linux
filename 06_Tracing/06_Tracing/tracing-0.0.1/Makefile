move:
	gcc -shared -fPIC -o my_remove.so my_remove.c -ldl
	gcc -o move move.c

test: move
	rm -f infilePROTECT.txt
	rm -f outfile.txt
	echo "green" > infilePROTECT.txt
	LD_PRELOAD=./my_remove.so ./move infilePROTECT.txt outfile.txt
	cmp outfile.txt infilePROTECT.txt

	rm -f infilePROTECT.txt
	rm -f outfile.txt
	rm -f infile.txt
	echo "green" > infilePROTECT.txt
	echo "green" > infile.txt
	./move infilePROTECT.txt outfile.txt
	cmp outfile.txt infile.txt
	[ ! -e infilePROTECT.txt ]

	rm -f infile.txt
	rm -f outfile.txt
	rm -f true.txt
	echo "green" > infile.txt
	echo "13" > true.txt
	strace -e trace=openat -e inject=openat:error=EACCES -P infile.txt ./move infile.txt outfile.txt > /dev/null 2> /dev/null; echo $$? > trace.txt
	cmp true.txt trace.txt

	rm -f infile.txt
	rm -f outfile.txt
	rm -f true.txt
	echo "green" > infile.txt
	echo "139" > true.txt
	strace -e trace=openat -e inject=openat:error=EACCES -P outfile.txt ./move infile.txt outfile.txt > /dev/null 2> /dev/null; echo $$? > trace.txt
	cmp true.txt trace.txt
	echo "green" > in.txt
	cmp in.txt infile.txt
	[ ! -e outfile.txt ]

	rm -f infile.txt
	rm -f outfile.txt
	rm -f true.txt
	echo "green" > infile.txt
	echo "5" > true.txt
	strace -e trace=read -e inject=read:error=EIO -P infile.txt ./move infile.txt outfile.txt > /dev/null 2> /dev/null; echo $$? > trace.txt
	cmp true.txt trace.txt
	[ ! -e outfile.txt ]

	rm -f infile.txt
	rm -f outfile.txt
	rm -f true.txt
	echo "green" > infile.txt
	echo "127" > true.txt
	strace -e trace=close -e inject=close:error=EIO ./move infile.txt outfile.txt > /dev/null 2> /dev/null; echo $$? > trace.txt
	cmp true.txt trace.txt
	cmp in.txt infile.txt

	rm -f infile.txt
	rm -f outfile.txt
	rm -f true.txt
	echo "green" > infile.txt
	echo "13" > true.txt
	strace -e trace=unlink -e inject=unlink:error=EACCES -P infile.txt ./move infile.txt outfile.txt > /dev/null 2> /dev/null; echo $$? > trace.txt
	cmp true.txt trace.txt
	cmp in.txt infile.txt

	rm -f infile.txt
	rm -f outfile.txt
	rm -f true.txt
	echo "green" > infile.txt
	echo "22" > true.txt
	strace -e trace=lseek -e inject=lseek:error=EINVAL -P infile.txt ./move infile.txt outfile.txt > /dev/null 2> /dev/null; echo $$? > trace.txt
	cmp true.txt trace.txt
	cmp in.txt infile.txt
	[ ! -e outfile.txt ]

	rm -f infile.txt
	rm -f outfile.txt
	rm -f true.txt
	echo "green" > infile.txt
	echo "5" > true.txt
	strace -e trace=write -e inject=write:error=EIO ./move infile.txt outfile.txt > /dev/null 2> /dev/null; echo $$? > trace.txt
	cmp true.txt trace.txt
	cmp in.txt infile.txt

install: move
	mkdir -p $(DESTDIR)/usr/bin
	mkdir -p $(DESTDIR)/usr/share/doc/tracing/
	cp move $(DESTDIR)/usr/bin
	cp my_remove.so $(DESTDIR)/usr/bin
	cp README $(DESTDIR)/usr/share/doc/tracing/
	cp safemove $(DESTDIR)/usr/bin

clean:
	rm -f move
	rm -f infile.txt
	rm -f outfile.txt
	rm -f true.txt
	rm -f trace.txt
	rm -f infilePROTECT.txt
	rm -f in.txt
