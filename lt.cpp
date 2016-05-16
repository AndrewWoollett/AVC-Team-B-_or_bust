
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

float kp = 0.004;
float kd = 0.001;        //change this

int speed = 45;
int error = 0;
int proportional_signal = 0;
float error[2][4];

int sPoint = 80;        //Aample piont, where the samle line is split.

/*
*This method will return the error between 2 given points.
*/
int returnError(int lowValue, int highValue, int height){
    int current_error = 0;
    int w, s;

    for (int i=lowValue; i<highValue; i++){
        w = get_pixel(i, height, 3);

         if (w > 127){
            s = 1;
        } else {
            s = 0;
        }
        error = (i-160)*s;
        current_error += error;
    }
 return current_error;
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

        set_motor(1,speed);
        set_motor(2,speed);
/*
        //open the gate
        connect_to_server("130.195.6.196", 22);
        char password[24];
        send_to_server("Please");
        receive_from_server(password);
        send_to_server(password);
//      Sleep(2, 0);
        printf("Gate Open");
*/
    while(1)
    {
        take_picture();      // take camera shot

        //summing across image
        error = 0;
        
        
        float current_error = 0;
        float previous_error = 0;
        int derivative_signal;
        
        for(int i = 0; i <= 2; i ++){
            int h = i*2 + 60;
            error[i][0] = returnError(0,sPoint,h);
            error[i][1] = returnError(sPoint,160,h);
            error[i][2] = returnError(160,160 + sPoint,h);
            error[i][3] = returnError(160 + sPoint,320,h);
        }

        current_error = error[0][0] + error[0][1] + error[0][2] + error[0][3]; 
        proportional_signal = current_error*kp;

        derivative_signal = (current_error-previous_error/0.1)*kd;
        previous_error = current_error;
//      printf("Derivative signal is: %d", derivative_signal );


        if (error[1] == 0 && error[2] == 0 && error[2] == 0 && error[3]){
            set_motor(1,-30);
            set_motor(2,-30);
            Sleep(0,600000);
            printf("Stop\n");
        }

        /*
        *You can put the code for the dead end here, I thik we will need ot take $
        *closer to the AVC. this will allow us to check if there is nothing at th$
        *small part in the bottom.
        */

        set_motor(1,speed + proportional_signal - derivative_signal);
        set_motor(2,speed - proportional_signal + derivative_signal);

        //Sleep is last so the motors c=dont update too late.
        Sleep(0,25);

//        printf("%d\n",error);
    }

   // terminate hardware
 close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);

    return 0;
}

