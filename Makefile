all:
	@g++ server.cpp -lSDL -lSDL_net -o sdlserver
	@g++ client.cpp -lSDL -lSDL_net -o sdlclient
install:
	@cp sdlserver /bin/
	@cp sdlclient /bin/ 
