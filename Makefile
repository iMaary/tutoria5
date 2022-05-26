bin: main.c
	gcc $< -o $@ -pthread

.PHONY: run clean

run: bin
	./bin 

clean:
	rm -f bin
