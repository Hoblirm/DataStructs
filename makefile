all:
	g++ -w -O2 -o ./bin/run main.cpp -I./inc -lrt
aix:
	xlC_r -w -O2 -o ./bin/aix_run main.cpp -I./inc
cxxtest:
	cxxtestgen --error-printer -o ./test/src/test.cpp ./test/inc/addressed_map_test.h ./test/inc/addressed_vector_test.h ./test/inc/object_pool_test.h
	g++ -w -o ./test/bin/test_bin ./test/src/test.cpp -I${CXXTEST} -I./inc -I./
	./test/bin/test_bin
clean:
	rm -rf ./obj/*
	rm -rf ./bin/*
	rm -rf ./test/src/*
	rm -rf ./test/bin/*
