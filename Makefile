pa3: clean
	g++ -std=c++17 -Wall -Wshadow --pedantic -Wvla *.cpp -g -o pa3 -O3

pa3-debug: clean
	g++ -std=c++17 -Wall -Wshadow --pedantic -Wvla *.cpp -g -o pa3 -O3 -DDEBUG -DCOMPARE

pa3-compare: clean
	g++ -std=c++17 -Wall -Wshadow --pedantic -Wvla *.cpp -g -o pa3 -O3 -DCOMPARE


clean:
	rm -f pa3

testall: test7 test7neg test10

test7:
	./pa3 examples/7_8.gr 7_8.mcm
	diff 7_8.mcm examples/7_8.mcm

test7neg:
	./pa3 examples/neg7_8.gr neg7_8.mcm
	diff neg7_8.mcm examples/neg7_8.mcm

test10:
	./pa3 examples/10_40.gr 10_40.mcm
	diff 10_40.mcm examples/10_40.mcm

test100:
	./pa3 examples/100_400.gr 100_400.mcm

test200:
	./pa3 examples/200_800.gr 200_800.mcm

test500:
	./pa3 examples/500_2000.gr 500_2000.mcm

memcheck:
	valgrind -s --leak-check=full --track-origins=yes ./pa3 examples/7_8.gr 7_8.mcm