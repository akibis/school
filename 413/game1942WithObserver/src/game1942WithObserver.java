/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

//package wingman;


import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.util.Random;
import javax.swing.*;
import javax.imageio.ImageIO;
import java.io.File;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;

/**
 *
 * @author Ilmi
 */
public class game1942WithObserver extends JApplet implements Runnable {

    private Thread thread;
    Image sea;
    Image myPlane;
    private BufferedImage bimg;
    Graphics2D g2;
    int speed = 1, move = 0;
    Random generator = new Random(1234567);
    Island I1, I2, I3;
    MyPlane m;
    int w = 640, h = 480; // fixed size window game 
    Enemy e1;
    GameEvents gameEvents;
    
    @Override
    public void init() {
        
        setBackground(Color.white);
        Image island1, island2, island3, enemyImg;

        try {
        //sea = getSprite("Resources/water.png");
        sea = ImageIO.read(new File("Resources/water.png"));
        island1 = ImageIO.read(new File("Resources/island1.png"));
        island2 = ImageIO.read(new File("Resources/island2.png"));
        island3 = ImageIO.read(new File("Resources/island3.png"));
        myPlane = ImageIO.read(new File("Resources/myplane_1.png"));
        enemyImg = ImageIO.read(new File("Resources/enemy1_1.png"));
        
        I1 = new Island(island1, 100, 100, speed, generator);
        I2 = new Island(island2, 200, 400, speed, generator);
        I3 = new Island(island3, 300, 200, speed, generator);
        e1 = new Enemy(enemyImg, 1, generator);
        m = new MyPlane(myPlane, 300, 360, 5);
        
        gameEvents = new GameEvents();
        gameEvents.addObserver(m);
        KeyControl key = new KeyControl();
        addKeyListener(key);
        }
        catch (IOException e) {
            System.out.print("No resources are found");
        }
    }

public class GameEvents extends Observable {
       int type;
       Object event;
       
   public void setValue(KeyEvent e) {
          type = 1; // let's assume this means key input. 
          //Should use CONSTANT value for this when you program
          event = e;
          setChanged();
         // trigger notification
         notifyObservers(this);  
   }

   public void setValue(String msg) {
          type = 2; 
          event = msg;
          setChanged();
         // trigger notification
         notifyObservers(this);  
        }
    }
    
public class Island {

        Image img;
        int x, y, speed;
        Random gen;

        Island(Image img, int x, int y, int speed, Random gen) {
            this.img = img;
            this.x = x;
            this.y = y;
            this.speed = speed;
            this.gen = gen;
        }

        public void update() {
            y += speed;
            if (y >= h) {
                y = -100;
                x = Math.abs(gen.nextInt() % (w - 30));
            }
        }

        public void draw(ImageObserver obs) {
            g2.drawImage(img, x, y, obs);
        }
    }

public class Enemy {

        Image img;
        int x, y, sizeX, sizeY, speed;
        Random gen;
        boolean show;
   
        Enemy(Image img, int speed, Random gen) {
            this.img = img;
            this.x = Math.abs(gen.nextInt() % (600 - 30));
            this.y = -20;
            this.speed = speed;
            this.gen = gen;
            this.show = true;
            sizeX = img.getWidth(null);
            sizeY = img.getHeight(null);
            System.out.println("w:" + sizeX + " y:" + sizeY);
       }

        public void update() {
            y += speed;
            if(m.collision(x, y, sizeX, sizeY)) {
                show = false;
                // You need to remove this one and increase score etc
                gameEvents.setValue("Explosion");
                gameEvents.setValue("");
                this.reset();
                show = true;
            }
            else 
                gameEvents.setValue("");
        }
        
        public void reset() {
            this.x = Math.abs(generator.nextInt() % (600 - 30));
            this.y = -10;
        }

        public void draw(ImageObserver obs) {
            if (show) {
                g2.drawImage(img, x, y, obs);
            }
        }
    }

 public class KeyControl extends KeyAdapter {

        @Override
        public void keyPressed(KeyEvent e) {
            gameEvents.setValue(e);
        }
    }
 
   
 public class MyPlane implements Observer {
        Image img;
        int x, y, speed, width, height;
        Rectangle bbox;
        boolean boom;

        MyPlane(Image img, int x, int y, int speed) {
            this.img = img;
            this.x = x;
            this.y = y;
            this.speed = speed;
            width = img.getWidth(null);
            height = img.getHeight(null);
            boom = false;
        }

        public void draw(ImageObserver obs) {
            g2.drawImage(img, x, y, obs);
        }
        
        public boolean collision(int x, int y, int w, int h) {
            bbox = new Rectangle(this.x, this.y, this.width, this.height);
            Rectangle otherBBox = new Rectangle (x,y,w,h);
            return this.bbox.intersects(otherBBox);
        }
      
        @Override
        public void update(Observable obj, Object arg) {
            GameEvents ge = (GameEvents) arg;
            if(ge.type == 1) {
                KeyEvent e = (KeyEvent) ge.event;
                switch (e.getKeyCode()) {    
                    case KeyEvent.VK_LEFT:
                        x -= speed;
	        	break; 
                    case KeyEvent.VK_RIGHT:
                        x += speed;
	        	break;
                    case KeyEvent.VK_UP:
                        y -= speed;
	        	break; 
                    case KeyEvent.VK_DOWN:
                        y += speed;
	        	break;
                    default:
                  if(e.getKeyChar() == ' ') {
                        System.out.println("Fire");  
                  }
                }
            }
            else if(ge.type == 2) {
                String msg = (String)ge.event;
                if(msg.equals("Explosion")) {
                    System.out.println("Explosion! Reduce Health");
        
                }
            }
        }
    }

 public void drawBackGroundWithTileImage() {
        int TileWidth = sea.getWidth(this);
        int TileHeight = sea.getHeight(this);

        int NumberX = (int) (w / TileWidth);
        int NumberY = (int) (h / TileHeight);

        for (int i = -1; i <= NumberY; i++) {
            for (int j = 0; j <= NumberX; j++) {
                g2.drawImage(sea, j * TileWidth, 
                        i * TileHeight + (move % TileHeight), TileWidth, 
                        TileHeight, this);
            }
        }
        move += speed;
    }

    public void drawDemo() {
            drawBackGroundWithTileImage();
            I1.update();
            I2.update();
            I3.update();
            e1.update();
            
            I1.draw(this);
            I2.draw(this);
            I3.draw(this);
            m.draw(this);
            e1.draw(this);
    }

    @Override
    public void paint(Graphics g) {
        if(bimg == null) {
            Dimension windowSize = getSize();
            bimg = (BufferedImage) createImage(windowSize.width, 
                    windowSize.height);
            g2 = bimg.createGraphics();
        }
        drawDemo();
        g.drawImage(bimg, 0, 0, this);
    }

    @Override
    public void start() {
        thread = new Thread(this);
        thread.setPriority(Thread.MIN_PRIORITY);
        thread.start();
    }

    @Override
    public void run() {
    	
        Thread me = Thread.currentThread();
        while (thread == me) {
            repaint();  
          try {
                Thread.sleep(25);
            } catch (InterruptedException e) {
                break;
            }
            
        }
    }

    public static void main(String argv[]) {
        final game1942WithObserver demo = new game1942WithObserver();
        demo.init();
        JFrame f = new JFrame("Scrolling Shooter");
        f.addWindowListener(new WindowAdapter() {
        });
        f.getContentPane().add("Center", demo);
        f.pack();
        f.setSize(new Dimension(640, 480));
        f.setVisible(true);
        f.setResizable(false);
        demo.start();
    }

}

