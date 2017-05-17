#Christopher Snyder ICSI402 Programming Project 4 CS146375

p4: main.o hash.o r.o j.o i.o opcode.o symbol.o pass1.o pass2.o error.o
	gcc main.o hash.o r.o j.o i.o opcode.o symbol.o pass1.o pass2.o error.o -o p4

main.o: main.c header.h
	gcc -c main.c

hash.o: hash.c header.h
	gcc -c hash.c

r.o: r.c header.h
	gcc -c r.c

j.o: j.c header.h
	gcc -c j.c

i.o: i.c header.h
	gcc -c i.c

opcode.o: opcode.c header.h
	gcc -c opcode.c

symbol.o: symbol.c hash.c header.h
	gcc -c symbol.c hash.c

pass1.o: pass1.c header.h
	gcc -c pass1.c

pass2.o: pass2.c header.h
	gcc -c pass2.c

error.o: error.c header.h
	gcc -c error.c

clean:
	rm -f *.o core p4
