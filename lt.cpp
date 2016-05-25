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
float kd = 0.0012;        //tune this

int speed = 50;
int intError = 0;
int proportional_signal = 0;


int sPoint = 80;        //Sample piont, where the sample line is split.
bool redStop = false;
/*
*This method will return the error between 2 given points.
*/
int returnError(int height){
    float current_error = 0;
    int w, s;

    for (int i=0; i<320; i++){
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

bool checkAcross(int height){
    int w, s=0;
    for (int i=40; i<280; i++){
        w = get_pixel(i, height, 3);
        if (w > 130){
        s++;
    }
    if(s>30){
        return true;
  }
}
return false;
}

bool checkDown(int pos){
    int w, s=0;
    for (int i=40; i<280; i++){
        w = get_pixel(pos, i, 3);
        if (w > 130){
        s++;
    }
    if(s>30){
        return true;
  }
}
return false;
}


bool top(){
  return checkAcross(20);
}
bool mid(){
  return checkAcross(120);
}
bool bot(){
  return checkAcross(200);
}
bool left(){
  return checkDown(30);
}
bool right (){
  return checkDown(290);
}

bool checkRed(){
        for (int i= 80; i<210; i++){
                int r = get_pixel(i, 120, 0);
                int g = get_pixel(i,120,1);
                int b = get_pixel(i,120,2);
                if (r >200 && g < 100 && b < 100){ //theory for red detection
                        printf("Red");
                        return true;
                }
        }
        return false;
}

void turnLeft(){
        set_motor(1,60);
        set_motor(2,60);
        Sleep(0,200000);
        set_motor(1,-60); 
        set_motor(2,60);
        Sleep(0,300000);
        set_motor(1,60);
        set_motor(2,60);
        Sleep(0,200000);

}

void turnRight(){
        set_motor(1,60);
        set_motor(2,60);
        Sleep(0,200000);
        set_motor(1,60); 
        set_motor(2,-60);
        Sleep(0,300000);
        set_motor(1,60);
        set_motor(2,60);
        Sleep(0,200000);

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

    set_PWM(1,180);
    Sleep(2,0);

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

        current_error = returnError(120);

        proportional_signal = current_error*kp;

        derivative_signal = (current_error - previous_error / 0.1) * kd;
        previous_error = current_error;

        set_motor(1,speed + proportional_signal - derivative_signal);
        set_motor(2,speed - proportional_signal + derivative_signal);

        if (!top() && !mid() && !bot() && !left() && !right()){
                set_motor(1,-50);
                set_motor(2,-50);
                Sleep(0,500000);
                printf("Stop\n");
        }

         if(top() && mid() && bot() && left() && right()){
                redStop  = true;
                break;
        }

        //Sleep is last so the motors dont update too late.
        Sleep(0,25);

}
while(1){
        // take camera shot
        take_picture();
        //summing across image
        intError = 0;
        float current_error = 0;
        float previous_error = 0;
      int derivative_signal;

        current_error = returnError(120);

        proportional_signal = current_error*kp;

        derivative_signal = (current_error - previous_error / 0.1) * kd;
        previous_error = current_error;



        if (checkRed() && redStop){ //theory for red detection
                break;
        }

        // turn left at a T junction
        if(!top() && mid() && bot() && left() && right()){
                turnLeft();
                printf("t-junction\n");
                redStop  = true;
        }
        // turn 180 at dead end
        else if(!top() && !mid() && bot() && !left() && !right()){
                turnRight();
turnRight();
                printf("turn-180\n");
        }
        // stop and reverse when it cant see the line
        else if (!top() && !mid() && !bot() && !left() && !right()){
                set_motor(1,-50);
                set_motor(2,-50);
                Sleep(0,500000);
                printf("Stop\n");
        // turn left at sharp corners.
        }else if(!top() && mid() && bot() && left() && !right()){
                turnLeft();
                printf("Left\n");
        // turn right  at sharp corners.
        }else if(!top() && mid() && bot() && !left() && right()){
                turnRight();
                printf("Right\n");
        }else{
        set_motor(1,speed + proportional_signal - derivative_signal);
        set_motor(2,speed - proportional_signal + derivative_signal);
        }

        //Sleep is last so the motors c=dont update too late.
        Sleep(0,25);
}    set_PWM(1,100);
        Sleep(2,0);

        turnLeft();
        printf("Turn");

        set_motor(1,0);
        set_motor(2,0);

        while(0){
        int dis = read_analog(0);
        printf("%d\n",dis);     
        Sleep(0,25);
        }

   // terminate hardware
    close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);

    return 0;
}

   
