a.out: main.cpp
	g++ -std=c++11 ./main.cpp -lgmp -O2

sample: a.out
	./a.out < ../../problems/762.txt

run: a.out
	./a.out 	< $(FILE)


