all:
  @g++ server.cpp -lSDL -lSDL_net -o sdlserver
install:
cp sdlserver /bin/ 
