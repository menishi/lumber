all: lumberd

lumberd: lumberd.c lumberd.h Network.c Network.h ../Config.c ../Config.h
	gcc lumberd.c Network.c ../Config.c -o lumberd.x

clean:
	rm lumberd.x
