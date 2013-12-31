all: lumber

lumber: main.c HistoryParser.c ArgumentProcessing.c
	gcc main.c HistoryParser.c ArgumentProcessing.c -o lumber.x

clean:
	rm -rf lumber.x
