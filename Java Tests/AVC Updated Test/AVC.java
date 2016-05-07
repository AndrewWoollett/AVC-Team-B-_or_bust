import ecs100.*;

public class AVC
{
    private MyRobot bot;
    String shape = "line";
    /**
     * Constructor for objects of class AVC
     */
    public AVC(){
        UI.initialise();
        UI.setDivider(0.0);
        UI.setWindowSize(1100,700);
        UI.addButton("Only Correction Factor",this::createRobot);
        UI.addButton("Line",()-> this.shape = "line");
        UI.addButton("Curve",()-> this.shape = "curve");
        UI.addButton("Right angle",()-> this.shape = "angle");
    }

    public void createRobot(){
        this.bot = null;
        UI.sleep(100);
        this.bot = new MyRobot(120,100,shape);

        while(bot != null){
            bot.move();
            UI.clearGraphics();
            bot.draw();
            UI.sleep(25);
        }
    }

}
