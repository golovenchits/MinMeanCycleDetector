pa3:
	g++ -std=c++17 -Wall -Wshadow --pedantic -Wvla *.cpp -g -o pa3 -O3

clean:
	rm -f pa3

test3: clean pa3
	./pa3 examples/7_8.gr

# test8: clean pa3
# 	./pa3 examples/8.txt 8_1.dim 8_1.pck 8_all.dim 8_all.pck
# 	diff 8_1.dim examples/8_1.dim
# 	diff 8_1.pck examples/8_1.pck
# 	diff 8_all.dim examples/8_all.dim
# 	diff 8_all.pck examples/8_all.pck

# memcheck:
# 	valgrind -s --leak-check=full --track-origins=yes ./pa3 examples/500_5.txt 8_1.dim 8_1.pck 8_all.dim 8_all.pck
