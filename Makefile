main : main.cpp
	g++ main.cpp -o main.out
debug : main.cpp
	g++ -g main.cpp -o main.out
clean:
	rm main.out
