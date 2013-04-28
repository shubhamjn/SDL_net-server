#include <iostream>
#include <cstdlib>
#include <cstring>
#include <SDL/SDL_net.h>

using namespace std;


int main(int argc, char **argv)
{
	char hostname[512];
	int serverPort, len=512;
	IPaddress ip;
	TCPsocket sd;
	char buffer[512];
	int nbytes = 511;
	string s;

	cout<<"Enter the server name and port"<<endl;
	cin>>hostname>>serverPort;

	if (SDLNet_Init() == -1)
    {
        cout << "Failed to intialise SDL_net: " << SDLNet_GetError() << endl;
        exit(-1); // Quit!
    }

    if(SDLNet_ResolveHost(&ip, hostname, serverPort) == -1)
    {
    	cout << "Failed to resolve the client: " << SDLNet_GetError() << endl;
    	exit(-1);
    }
    else 
    	cout<<"resolved the client"<< endl;
     sd = SDLNet_TCP_Open(&ip);
 
    if (!sd)
    {
        cout << "Failed to open the client socket: " << SDLNet_GetError() << "\n";
        exit(-1);
    }
    else
    {
        cout << "Sucessfully created client socket." << endl;
    }
    int quit = 0;
    while(quit==0)
    {
    	cout<<"Write please  ";
    	cin>>s;
    	//buffer = s.c_str();
    	//getline (std::cin,buffer);
    	//getline(&buffer,&nbytes, stdin);
    	//scanf("%20[0-9a-zA-Z]s",buffer);
    	len = strlen(buffer)+1;
    	if(SDLNet_TCP_Send(sd, (void *)s.c_str(), len) < len)
    	{
    		cout<<"Couldn't send the complete data"<<SDLNet_GetError();
    		exit(-1);
    	}
    	if(strncmp(buffer, "exit",4) == 0 || strncmp(buffer, "quit",4) == 0 )
    		quit = 1;

    }
    SDLNet_TCP_Close(sd);
	SDLNet_Quit();
	return 0;

}