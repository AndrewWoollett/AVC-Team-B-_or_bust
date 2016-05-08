import ecs100.*;
import java.awt.Polygon;
import java.awt.Color;
/**
 * Write a description of class Robot here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class MyRobot{
    //Fields for moving Robot
    double x,y,dir;
    double radius = 15, speed = 2.0, camersPosition = 20;
    boolean go = true;
    //Constant
    double k=0.01;

    //Feilds for drawing robot
    double[] robotXCor = new double[4];
    double[] robotYCor = new double[4];

    //Feilds for drawing track
    int pointNum=10;
    int[] polyX = new int[pointNum];
    int[] polyY = new int[pointNum];
    double[] polyXD = new double[pointNum];
    double[] polyYD = new double[pointNum];
    private Polygon polygon1;
    String shape = "line";

    /**
     * Constructor for objects of class Robot
     */
    public MyRobot(double x, double y, String shape){
        this.x = x;
        this.y = y;
        this.shape = shape;
        if(shape.equals("angle")){
            pointNum=8;
            setRightAngle();
        }else if(shape.equals("curve")){
            pointNum=10;
            setCurve();
        }else{
            pointNum=4;
            setLine();
        }
        polygon1 = new Polygon(polyX,polyY,pointNum);

    }


    public void calcAngle(){
        double p,totalSum=0,sum=0,farLeft,nearLeft,farRight,nearRight;
        for(int a = -1; a<=1; a+=1){
            int p2 = 30;
            farLeft = getSum(-75,-p2,a);
            farRight = getSum(p2,75,a);
            nearLeft = getSum(-p2+1,0,a);
            nearRight = getSum(0,p2-1,a);
            sum=farLeft+farRight+nearLeft+nearRight;
            totalSum+=sum;
            if(farLeft==0 && farRight == 0 && nearLeft==0 && nearRight == 0){
                stopTurn();
            }
                 }
        totalSum/=3;

        addDir(totalSum*k);
        UI.drawPolygon(polyXD,polyYD,pointNum);

    }

    public void stopTurn(){
        go=false;
        double newDir = dir +180;  
        while(dir < newDir){
            dir+=5;
            UI.clearGraphics();
            this.draw();
            UI.sleep(25);
        }
        go = true;
    }

    public double getSum(int lowValue, int highValue, int a){
        double xL,yL,sum=0;
        for(int i = lowValue; i <=highValue;i++){
            xL = (camersPosition-a*8)*Math.cos(degToRad(dir)) - i*Math.cos(degToRad(dir-90)) + x;
            yL = (camersPosition-a*8)*Math.sin(degToRad(dir)) - i*Math.sin(degToRad(dir-90)) + y;
            UI.fillRect(xL ,yL,1,1);
            if(polygon1.contains(xL,yL)){
                UI.setColor(Color.black);
                sum += i;
            }else{                
                UI.setColor(Color.white);
            }

            UI.fillRect(i*6 +500,500 +(a*10),6,6);
            UI.setColor(Color.black);
            UI.drawRect(i*6 +500,500+(a*10),6,6);

        }
        return sum;
    }

    public void setLine(){
        polyX[0]=75;
        polyX[1]=1000;
        polyX[2]=1000;
        polyX[3]=75;

        polyY[0]=130;
        polyY[1]=130;
        polyY[2]=140;
        polyY[3]=140;

        for(int i=0; i <pointNum; i++){
            polyXD[i] = polyX[i];
            polyYD[i] = polyY[i];
        }
    }

    public void setCurve(){
        polyX[0]=95;
        polyX[1]=380;
        polyX[2]=571;
        polyX[3]=720;
        polyX[4]=800;
        polyX[5]=780;
        polyX[6]=700;
        polyX[7]=566;
        polyX[8]=370;
        polyX[9]=95;

        polyY[0]=134;
        polyY[1]=130;
        polyY[2]=161;
        polyY[3]=260;
        polyY[4]=410;
        polyY[5]=421;
        polyY[6]=271;
        polyY[7]=177;
        polyY[8]=147;
        polyY[9]=147;

        for(int i=0; i <pointNum; i++){
            polyXD[i] = polyX[i];
            polyYD[i] = polyY[i];
        }
    }

    public void setRightAngle(){
        polyX[0]=100;
        polyX[1]=563;
        polyX[2]=560;
        polyX[3]=353;
        polyX[4]=354;
        polyX[5]=330;
        polyX[6]=327;
        polyX[7]=100;

        polyY[0]=130;
        polyY[1]=128;
        polyY[2]=152;
        polyY[3]=152;
        polyY[4]=400;
        polyY[5]=400;
        polyY[6]=153;
        polyY[7]=153;

        for(int i=0; i <pointNum; i++){
            polyXD[i] = polyX[i];
            polyYD[i] = polyY[i];
        }
    }

    public void move(){
        if(go){
            x +=  speed*Math.cos(degToRad(dir));
            y +=  speed*Math.sin(degToRad(dir));
        }

    }

    public void draw(){
        setCor(x , y);
        UI.fillPolygon(robotXCor, robotYCor, 4);

        calcAngle();
    }

    public double degToRad(double deg){
        double rad = deg*Math.PI/180;
        return rad;
    }

    public void setCor(double x, double y){
        robotXCor[0] = x +radius*Math.cos(degToRad(225 + dir));
        robotXCor[1] = x +radius*Math.cos(degToRad(315 + dir));
        robotXCor[2] = x +radius*Math.cos(degToRad(45  + dir));
        robotXCor[3] = x +radius*Math.cos(degToRad(135 + dir));

        robotYCor[0] = y +radius*Math.sin(degToRad(225 + dir));
        robotYCor[1] = y +radius*Math.sin(degToRad(315 + dir));
        robotYCor[2] = y +radius*Math.sin(degToRad(45  + dir));
        robotYCor[3] = y +radius*Math.sin(degToRad(135 + dir));
    }

    public void addDir(double newDir){
        dir += newDir;
    }

    public void setK(double k){
        this.k = k;
    }
}
