all:
	gcc -o prog server/server.c -lcrypt -lpthread

test:
	gcc -D_XOPEN_SOURCE -o test server/server_test.c -lcrypt -lpthread
	./test

clean:
	@[ -f ./prog ] && rm prog || true
	@[ -f ./test ] && rm test || true