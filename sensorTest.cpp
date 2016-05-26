#include <stdio.h>
#include <time.h>
#include <string.h>

// sudo gcc -Wall
extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
//extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

extern "C" int set_motor(int motor,int speed);

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);
extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

float kpMaze = 0.001;

void turnLeftMaze(){
	int front = read_analog(1);
	while(front > 300){
		set_motor(1,50);
		set_motor(2,-50);
		front = read_analog(1);
	}
	set_motor(1,0);
	set_motor(2,0);
}

void turnRightMaze(){
	int front = read_analog(1);
	while(front > 300){
		set_motor(1,-50);
		set_motor(2,50);
		front = read_analog(1);
	}
	set_motor(1,0);
	set_motor(2,0);
}

void goFowardMaze(){
	int front = read_analog(1);
	while(front > 400){
		int distance = read_analog(0);
		int signal = distance - 500;
        int propSignal = signal * kpMaze;
        set_motor(1, propsignal + speed);
        set_motor(2, -propsignal + speed);
	}
	set_motor(1,0);
	set_motor(2,0);
}

int main(){

    init(0);
    // connect camera to the screen
    open_screen_stream();
    // set all didgital outputs to +5V
    for (int i =0; i < 8; i++){
    // set all digital channels as outputs
    select_IO(i,0);
    write_digital(i,1);
    }

   while(1){

        int disRight = read_analog(2);
	int disFront = read_analog(1);
	int disLeft = read_analog(0);
	
	int minDis = 400;
	int maxDis = 500;
    
	if(disRight < minDis && disRight > maxDis){
		turnRightMaze();
	}else if(disFront  < minDis && disFront > maxDis){
		goFowardMaze();
	}else if(disLeft < minDis && disLeft > maxDis){
		turnLeftMaze();
	}else{
		turnRightMaze();
	}
   
    int frontDistance = read_analog(1); //change channel later
    else if (frontDistance < 600){
        int signal = distance - 500;
        int propSignal = signal * kpMaze;
        set_motor(1, propsignal + speed);
        set_motor(2, -propsignal + speed);

    }



   }
    return 0;
}
