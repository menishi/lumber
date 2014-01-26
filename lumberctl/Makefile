all: lumber

lumber: lumber.c HistoryParser.c ArgumentProcessing.c Networking.c
	gcc lumber.c HistoryParser.c ArgumentProcessing.c Networking.c -o lumber.x

clean:
	rm -rf lumber.x
