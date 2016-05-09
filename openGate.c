# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

int main (){
   // This sets up the RPi hardware and ensures
   // everything is working correctly
   init(1);
   //connects to server with the ip address 
   connect_to_server("130.195.6.169", 22);
   //sends a message to the connected server
   send_to_server("Please");
   //receives message from the connected server
   char message[24];
   receive_from_server(message); 
   printf("%s", message);

return 0;}
