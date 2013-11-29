all: lumber

lumber: main.c HistoryParser.c
	gcc main.c HistoryParser.c -o lumber

clean:
	rm -rf lumber

