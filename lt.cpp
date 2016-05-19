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

float kp = 0.003;        //tune this
float kd = 0.001;        //tune this

int speed = 45;
int intError = 0;
int proportional_signal = 0;
float error[3][4];

int sPoint = 80;        //Sample piont, where the sample line is split.

/*
*This method will return the error between 2 given points.
*/
int returnError(int lowValue, int highValue, int height){
    float current_error = 0;
    int w, s;

    for (int i=lowValue; i<highValue; i++){
        w = get_pixel(i, height, 3);
         if (w > 127){
            s = 1;
        } else {
            s = 0;
        }
        intError = (i-160)*s;
        current_error += intError;
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
    connect_to_server("130.195.6.196", 1024);
    char password[24];
    send_to_server("Please");
    receive_from_server(password);
    send_to_server(password);
    Sleep(1, 0);
    printf("Gate Open");
*/
    while(1){
        // take camera shot
        take_picture();
        //summing across image
        intError = 0;
        float current_error = 0;
        float previous_error = 0;
        int derivative_signal;

        for(int i = 0; i < 3; i ++){
            int h = i*60 + 80;
            error[i][0] = returnError(0,sPoint,h);
            error[i][1] = returnError(sPoint,160,h);
            error[i][2] = returnError(160,160 + sPoint,h);
            error[i][3] = returnError(160 + sPoint,320,h);
        }

        current_error = error[0][0] + error[0][1] + error[0][2] + error[0][3] + //possibly remove this line
                        error[1][0] + error[1][1] + error[1][2] + error[1][3] +
                        error[2][0] + error[2][1] + error[2][2] + error[2][3];

        proportional_signal = current_error*kp;

        derivative_signal = (current_error - previous_error / 0.1) * kd;
        previous_error = current_error;

        // turn left at a T junction
        if(error[0][0] == 0 && error[0][1] == 0 && error[0][2] == 0 && error[0][3] == 0 && 
        error[1][0] != 0 && error[1][1] != 0 && error[1][2] != 0 && error[1][3] != 0 &&
        error[2][0] == 0 && (error[2][1] != 0 || error[2][2] != 0) && error[2][3] == 0){
                set_motor(1,-50);
                set_motor(2,50);
                Sleep(0,500000);
                printf("t-junction\n");
        }
        // turn 180 at dead end
        else if(error[0][0] == 0 && error[0][1] == 0 && error[0][2] == 0 && error[0][3] == 0  &&
        error[1][0] == 0 && (error[1][1] != 0 || error[1][2] != 0) && error[1][3] == 0 &&
        error[2][0] == 0 && (error[2][1] != 0 || error[2][2] != 0) && error[2][3] == 0){
                set_motor(1,60);
                set_motor(2,-60);
                Sleep(1,0);
                printf("turn-180\n");
        }
        // stop and reverse when it cant see the line
        else if (error[0][0] == 0 && error[0][1] == 0 && error[0][2] == 0 && error[0][3] == 0 &&
        error[1][0] == 0 && error[1][1] == 0 && error[1][2] == 0 && error[1][3] == 0 &&
        error[2][0] == 0 && error[2][1] == 0 && error[2][2] == 0 && error[2][3] == 0){
                set_motor(1,-50);
                set_motor(2,-50);
                Sleep(1,0);
                printf("Stop\n");
        }

        set_motor(1,speed + proportional_signal - derivative_signal);
        set_motor(2,speed - proportional_signal + derivative_signal);

        //Sleep is last so the motors c=dont update too late.
        Sleep(0,25);
    }

   // terminate hardware
    close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);

    return 0;
}
