#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include "websocket.h"

using namespace std;

webSocket server;

/* called when a client connects */
void openHandler(int clientID){
    ostringstream os;
    os << "Stranger " << clientID << " has joined.";
    vector<int> clientIDs = server.getClientIDs();
    for (int i = 0; i < clientIDs.size(); i++){
        if (clientIDs[i] != clientID)
            server.wsSend(clientIDs[i], os.str());
    }
    server.wsSend(clientID, "0:0");
}

/* called when a client disconnects */
void closeHandler(int clientID){
    ostringstream os;
    //os << "Stranger " << clientID << " has leaved.";

    vector<int> clientIDs = server.getClientIDs();
    for (int i = 0; i < clientIDs.size(); i++){
        if (clientIDs[i] != clientID)
            server.wsSend(clientIDs[i], os.str());
    }
}

/* called when a client sends a message to the server */
void messageHandler(int clientID, string message){
    ostringstream os;
    //os << "Stranger " << clientID << " says: " << message;
	//cout << message;

    vector<int> clientIDs = server.getClientIDs();
    for (int i = 0; i < clientIDs.size(); i++){
        if (clientIDs[i] != clientID)
        
		server.wsSend(clientIDs[i], os.str());
    }
	if(message.compare("DONE")==0)
	{
		//server.wsSendClientClose(clientID);
		server.wsClose(clientID);
		server.ClientScore[0] = 0;
		server.ClientScore[1] = 0;
	
	}
	else
	{		
		ostringstream give_string;
		
		int num1= atoi(message.c_str());//str_array[0].c_str());
		int num2= !atoi(message.c_str());
		int inc1,inc2;
		inc1 = 100 * num1;
		inc2 = 100 * num2;
		ostringstream stream;
		server.ClientScore[0] = server.ClientScore[0]+ inc1;
		server.ClientScore[1] = server.ClientScore[1]+ inc2;
		stream << server.ClientScore[0] <<":"<< server.ClientScore[1];
		server.wsSend(clientID, stream.str());
	}
}

/* called once per select() loop */
void periodicHandler(){
    static time_t next = time(NULL) + 10;
    time_t current = time(NULL);
    if (current >= next){
        ostringstream os;
        string timestring = ctime(&current);
        timestring = timestring.substr(0, timestring.size() - 1);
        os << timestring;

        vector<int> clientIDs = server.getClientIDs();
        for (int i = 0; i < clientIDs.size(); i++)
            server.wsSend(clientIDs[i], os.str());

        next = time(NULL) + 10;
    }
}

int main(int argc, char *argv[]){
    int port;

	port = 21234;
    /* set event handler */
    server.setOpenHandler(openHandler);
    server.setCloseHandler(closeHandler);
    server.setMessageHandler(messageHandler);
    //server.setPeriodicHandler(periodicHandler);

    /* start the chatroom server, listen to ip '127.0.0.1' and port '8000' */
    server.startServer(port);

    return 1;
}
