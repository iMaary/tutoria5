bin: main.c
	gcc $< -o $@ -pthread

.PHONY: run clean

run:
	./bin 

clean:
	rm -f bin
