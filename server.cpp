#include <iostream>
#include <cstdlib>
#include <string>
#include <SDL/SDL_net.h>

using namespace std;


int main(int argc, char **argv)
{
	//initializations....
	IPaddress ip,*remoteIP;
	TCPsocket sd,csd;
	char buffer[512];
	// intialize SDL
	if (SDLNet_Init() == -1)
    {
        cout << "Failed to intialise SDL_net: " << SDLNet_GetError() << endl;
        exit(-1); // Quit!
    }
    // resolve host
    if(SDLNet_ResolveHost(&ip, NULL, 1234) == -1)
    {
    	cout << "Failed to resolve the server host: " << SDLNet_GetError() << endl;
    	exit(-1);
    }
    //open socket
    sd = SDLNet_TCP_Open(&ip);
 
    if (!sd)
    {
        cout << "Failed to open the server socket: " << SDLNet_GetError() << "\n";
        exit(-1);
    }
    else
    {
        cout << "Sucessfully created server socket." << endl;
    }


    int exitt = 0;
    while(exitt == 0)
    {

    	if (csd = SDLNet_TCP_Accept(sd))
		{

			if (remoteIP = SDLNet_TCP_GetPeerAddress(csd))
				cout<<"Host connected:"<<SDLNet_Read32(&remoteIP->host)<<SDLNet_Read16(&remoteIP->port);
			else
				cout<<"Failed to connect:"<<SDLNet_GetError();
			int quit =0;
			while(quit==0)
			{
				if (SDLNet_TCP_Recv(csd, buffer, 512) > 0)
				{
					for(int i =0; i < 512; i++)
					{
						if(buffer[i] == '\n')
							buffer[i] = '\0';
					}
					printf("Client say: %s\n", buffer);
 
					if(strncmp(buffer, "exit",4) == 0)	/* Terminate this connection */
					{
						quit = 1;
						printf("Terminate connection\n");
					}
					if(strncmp(buffer, "quit",4) == 0)	/* Quit the program */
					{
						quit = 1;
						exitt = 1;
						printf("Quit program\n");
					}



				}
					
			}
			SDLNet_TCP_Close(csd);
 


		}

    }
    SDLNet_TCP_Close(sd);
	SDLNet_Quit();


};
