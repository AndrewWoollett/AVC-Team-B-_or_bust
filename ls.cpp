
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


int speed = 40;
int v_left = 40;
int v_right = 40;
int error = 0;
int proportional_signal = 0;


int main(){

    int i;
    init(0);
    // connect camera to the screen
    open_screen_stream();
    // set all didgital outputs to +5V
    for (i = 0; i < 8; i++){
        // set all digital channels as outputs
      select_IO(i,0);
      write_digital(i,1);
    }

        set_motor(1,v_left);
        set_motor(2,v_right);

    while(1)
    {
       take_picture();      // take camera shot
           /*
       // draw some line
       set_pixel(100, 55 ,255,0,0);
       set_pixel(101, 55 ,255,0,0);
       set_pixel(102, 55 ,255,0,0);
       set_pixel(10set_motor(1,0);
           set_motor(2,0);3, 55 ,255,0,0);
       // display picture
       update_screen();
           */

        //summing across image
        error = 0;
        int i, w, s;
                float kp = 0.0035;
                float kd = 0.002; //change this
                int current_error = 0;
                int previous_error = 0;
                int derivative_signal;

        for (i=0; i<320; i++){
                w = get_pixel(i, 120, 3);

                 if (w > 127){
                        s = 1;
                } else {
                        s = 0;
                }

                error = (i-160)*s;
                current_error = current_error + error;
        }
        proportional_signal = current_error*kp;

        Sleep(0,25);

        derivative_signal = (current_error-previous_error/0.1)*kd;
        previous_error = current_error;
//      printf("Derivative signal is: %d", derivative_signal );

/*      if (proportional_signal == 0){
                set_motor(1,-40);
                set_motor(2,-40);
                Sleep(1,0);
                printf("Stop/n");
}
*/


        set_motor(1,speed + proportional_signal - derivative_signal);
        set_motor(2,speed - proportional_signal + derivative_signal);

//        printf("%d\n",error);
    }

   // terminate hardware
    close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);

    return 0;
}
