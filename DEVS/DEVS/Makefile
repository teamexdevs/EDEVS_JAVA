main.out : tglobal.o entstr.o genr.o transd.o process.o
	g++ tglobal.o entstr.o genr.o transd.o process.o -o main.out -std=c++11

tglobal.o :
	g++ -c src/Output.cpp -o tglobal.o

entstr.o : digraph.o list.o
	g++ -c -o entstr.o digraph.o list.o src/EntStr.cpp include/Atomic.hpp

digraph.o :
	g++ -c -o digraph.o src/Digraph.cpp

list.o : model.o include/List.hpp src/List.cpp
	g++ -c model.o src/List.cpp -o list.o

model.o : entity.o port.o message.o
	g++ -c entity.o port.o message.o src/Model.cpp -o model.o

entity.o :
	g++ -c src/Entity.cpp -o entity.o

port.o :
	g++ -c src/Port.cpp -o port.o

message.o : devsdef.o
	g++ -c devsdef.o src/Message.cpp -o message.o

devsdef.o :
	g++ -c include/DEVSDEF.H -o devsdef.o

genr.o :
	g++ -c src/genr.cpp -o genr.o

transd.o :
	g++ -c src/Transd.cpp -o transd.o

process.o :
	g++ -c src/Process.cpp -o process.o