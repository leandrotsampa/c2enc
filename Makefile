all:
	g++ -g -O3 -std=c++11 -Wl,--unresolved-symbols=ignore-in-shared-libs -Wall c2enc.cpp -o c2enc -lhicodec

