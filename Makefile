#!/bin/bash/
P4: inputbuf.o lexer.o parser.o 
	g++ inputbuf.o lexer.o parser.o -o P4

parser.o: parser.cc parser.h
	g++ -c parser.cc
lexer.o: lexer.cc lexer.h
	g++ -c lexer.cc
inputbuf.o: inputbuf.cc inputbuf.h
	g++ -c inputbuf.cc
clean: 
	rm -f *.o *~
	
