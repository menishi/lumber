all: lumber

lumber: lumber.c ../HistoryParser.c ArgumentProcessing.c Networking.c ../Config.c ../Config.h
	gcc lumber.c ../HistoryParser.c ArgumentProcessing.c Networking.c ../Config.c -o lumber.x

clean:
	rm -rf lumber.x
