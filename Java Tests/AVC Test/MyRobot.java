import ecs100.*;
/**
 * Write a description of class Robot here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class MyRobot{
    double x,y,dir;
    double radius = 15, speed = 2.0;
    double[] robotXCor = new double[4];
    double[] robotYCor = new double[4];
    /**
     * Constructor for objects of class Robot
     */
    public MyRobot(double x, double y){
        this.x = x;
        this.y = y;
        
    }
  
    public void move(){
        x +=  speed*Math.cos(degToRad(dir));
        y +=  speed*Math.sin(degToRad(dir));
        
    }
   
    public void draw(){
        setCor(x , y);
        UI.fillPolygon(robotXCor, robotYCor, 4);
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
    
    public double getX(){
        return x;
    }
    
    public double getY(){
        return y;
    }
    
    public void setDir(double newDir){
        dir = newDir;
    }
    
    public void addDir(double newDir){
        dir += newDir;
    }
}
