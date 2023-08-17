worker: worker.cpp
	@g++ worker.cpp -o worker -lzmq -pthread -ldl

master: master.cpp
	@g++ master.cpp -o master -lzmq -pthread

libmrFunc.so:map_reduceFun.o
	@g++ -shared map_reduceFun.o -o libmrFunc.so
	
map_reduceFun.o:map_reduceFun.cpp
	@g++ -fpic -c map_reduceFun.cpp

.PHONY:clean
clean:
	rm *.o *.so