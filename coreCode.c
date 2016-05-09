#include <stdio.h>
#include <time.h>
#include <string.h>

//ch_adc
//A0 motor 1
//A1 motor 2
//A2 IR1
//A3 IR2
//A4 IR3
//A5 camera
//A6 
//A7

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


int v_left = 0;
int v_right = 0;

int main()
{
    int i;
    init(0);
    // connect camera to the screen
    open_screen_stream();
    // set all didgital outputs to +5V
    for (i = 0; i < 8; i++)
    {
      // set all digital channels as outputs
      select_IO(i,0);
      write_digital(i,1);
    }
	
    while(1)
    {
       take_picture();      // take camera shot
       // draw some line
       set_pixel(100, 55 ,255,0,0);
       set_pixel(101, 55 ,255,0,0);
       set_pixel(102, 55 ,255,0,0);
       set_pixel(103, 55 ,255,0,0);
       // display picture
       update_screen();

       // check motors
       v_left = -135;
       v_right = -135;
       set_motor(1,v_right);
       set_motor(2,v_left);
       Sleep(1,0);
       v_left = 135;
       v_right = 135;
       set_motor(1,v_right);
       set_motor(2,v_left);
       Sleep(1,0);
       for (i = 0 ; i < 8; i++)
       {
        int av = read_analog(i);
        printf("ai=%d av=%d\n",i,av);
   	
	//summing across image
	int sum = 0;
	int i, w, s;
	for (i=0, i<320, i++){
		w = i*get_pixel(i, 120, 3);      //Should not be * by i at this point.
		if (w > 127){s = 1;}
		else {s = 0;}
		sum = sum + (i-160)*s;
	}
	printf("Signal is: %d", sum )

	//computing out error
	int errorSig = 0;
	int num;
	for (i=0, i<320, i++){
	num = (i-160)*get_pixel(i, 120, 3);
	errorSig = errorSig + num
	}
	printf("Signal is: %d", errorSig )
   
   	//turning
   	if (sum < TEST){
   		turn_left();	
   	}
   	else if (sum > TEST){
   		turn_right();	
   	}
   	else if (sum = TEST){
   		drive_foward();	
   	}
   	
    }


     }

   // terminate hardware
    close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);
  
    return 0;


}
