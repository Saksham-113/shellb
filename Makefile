all:
	g++ *.cpp -o shell

clean:
	rm -f shell

it:
	g++ test.cpp -o test
