import ecs100.*;
import java.sql.Timestamp;

/**
 * Write a description of class AVC here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class AVC
{
    MyRobot bot;

    double lastTime= 0, currentTime = 0;
    /**
     * Constructor for objects of class AVC
     */
    public AVC(){
        UI.initialise();
        UI.setDivider(0.0);
        UI.addButton("Only Correction Factor",this::correctionFactor);
        UI.addButton("Derivative",this::derivative);
    }

    public void correctionFactor(){

        bot = new MyRobot(100,100);

        double botY = 100;
        while(true){
            botY = bot.getY();

            if(botY <200){
                bot.addDir(1);
            }else if(botY >200){
                bot.addDir(-1);
            }
            bot.move();
            redraw();
            UI.sleep(25);

        }
    }
    public void derivative(){
        bot = new MyRobot(100,100);
        double botY = 100, lastBotY = 100;
        while(true){
            botY = bot.getY();

            double d=((botY-lastBotY)/getPeriod())*.03;
            lastBotY = botY;
            if(botY <200){
                bot.addDir(1-d);
            }else if(botY >200){
                bot.addDir(-1-d);
            }
            bot.move();
            redraw();
            UI.sleep(25);

        }
    }

    public double getPeriod(){
        double period;
        currentTime = System.nanoTime()/1000000000.0;
        period = currentTime - lastTime;
        lastTime = currentTime;
        return period;
    }

    public void redraw(){
        UI.clearGraphics();
        UI.drawLine(0,200,1000,200);
        bot.draw();
        //UI.println();
    }
}
