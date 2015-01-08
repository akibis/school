/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wingman;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.io.File;
import java.util.Random;
import javax.imageio.ImageIO;
import javax.swing.JApplet;
import javax.swing.JFrame;

/**
 *
 * @author netdom
 */
public class WingmanWithObserver extends JApplet implements Runnable{

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

    boolean enemiesActive, gameOver;
   // Graphics2D g2 = null;
    ImageObserver observer;

    @Override
    public void init() {
        
        setBackground(Color.white);
        Image island1, island2, island3;

        try {
        //sea = getSprite("Resources/water.png");
        sea = ImageIO.read(new File("Resources/water.png"));
        island1 = ImageIO.read(new File("Resources/island1.png"));
        island2 = ImageIO.read(new File("Resources/island2.png"));
        island3 = ImageIO.read(new File("Resources/island3.png"));
        myPlane = ImageIO.read(new File("Resources/myplane_1.png"));
        
        enemiesActive = true;
        gameOver = false;
        observer = this;

        I1 = new Island(island1, 100, 100, speed, generator);
        I2 = new Island(island2, 200, 400, speed, generator);
        I3 = new Island(island3, 300, 200, speed, generator);

        m = new MyPlane(myPlane, 300, 360, 10);
        }
        catch (Exception e) {
            System.out.print("No resources are found");
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


    public class KeyControl extends KeyAdapter {

        public int x, y;
        int speed;

        KeyControl(int x, int y, int speed) {
            this.x = x;
            this.y = y;
            this.speed = speed;
        }

        @Override
        public void keyPressed(KeyEvent e) {
            switch (e.getKeyCode()) {
           
                case KeyEvent.VK_LEFT:
                m.move (-5,0);
	        	break;
          
                default:
                  if(e.getKeyChar() == ' ')
	        		System.out.println("FIRE!!");

            }
        }
    }

    public class MyPlane {

        KeyControl key;
        Image img;
        int x, y, speed, move = 0;
        int boom;

        MyPlane(Image img, int x, int y, int speed) {
            this.img = img;
            this.x = x;
            this.y = y;
            this.speed = speed;
            key = new KeyControl(x, y, speed);
            boom = 0;

            addKeyListener(key);
        }

        public void draw(ImageObserver obs) {
            g2.drawImage(img, this.x, this.y, obs);
        }
        
        public void move (int x, int y) {
            this.x += x;
            this.y += y;
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
        if (!gameOver) {
            drawBackGroundWithTileImage();
            I1.update();
            I2.update();
            I3.update();
            
            I1.draw(this);
            I2.draw(this);
            I3.draw(this);
            m.draw(this);
        }
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
                thread.sleep(15);
            } catch (InterruptedException e) {
                break;
            }
            
        }
    }

    public static void main(String argv[]) {
        final WingmanWithObserver demo = new WingmanWithObserver();
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

