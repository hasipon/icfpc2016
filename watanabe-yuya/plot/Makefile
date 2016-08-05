run: plot.sh problem
	bash ./plot.sh

a.out:
	g++ -std=c++11 ./main.cpp

plot.sh: a.out
	./a.out > ./plot.sh

clean:
	rm ./a.out ./plot.sh

problem:
	mkdir problem
