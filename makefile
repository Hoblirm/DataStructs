all:
	g++ -w -O2 -o ./bin/run main.cpp -I./inc
cxxtest:
	cxxtestgen --error-printer -o ./test/src/addressed_map_test.cpp ./test/inc/addressed_map_test.h
	g++ -w -o ./test/bin/addressed_map_bin ./test/src/addressed_map_test.cpp -I${CXXTEST} -I./inc -I./
	./test/bin/addressed_map_bin
clean:
	rm -rf ./obj/*
	rm -rf ./bin/*
	rm -rf ./test/src/*
	rm -rf ./test/bin/*
