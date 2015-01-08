/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package wingman;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.net.URL;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Random;
import javax.swing.*;

/**
 *
 * @author Ilmi
 */
public class gm1942 extends JApplet implements Runnable {

    static int numberOfPlanes = 12;
    private Thread thread;
    Image sea;
    Image bullet, enemyBullet, powerup, healthBar, bossPicture, bigBullet, youWin, extraLife, myPlane;
    Image[] explosion1 = new Image[6];
    Image[] explosion2 = new Image[7];
    private int x = 0, move = 0;
    private BufferedImage bimg;
    int speed = 1, score = 0, life = 4;
    Random generator = new Random(1234567);
    Island I1, I2, I3;
    MyPlane m;

    boolean enemiesActive, gameOver;
   // Graphics2D g2 = null;
    ImageObserver observer;

    public void init() {
        setBackground(Color.white);
        Image island1, island2, island3, enemy;

        sea = getSprite("Resources/water.png");
        island1 = getSprite("Resources/island1.png");
        island2 = getSprite("Resources/island2.png");
        island3 = getSprite("Resources/island3.png");
        myPlane = getSprite("Resources/myplane_1.png");
 
        enemiesActive = true;
        gameOver = false;
        observer = this;

        I1 = new Island(island1, 100, 100, speed, generator);
        I2 = new Island(island2, 200, 400, speed, generator);
        I3 = new Island(island3, 300, 200, speed, generator);

        m = new MyPlane(myPlane, 300, 360, 10);
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

        public void update(int w, int h) {
            y += speed;
            if (y >= h) {
                y = -100;
                x = Math.abs(gen.nextInt() % (w - 30));
            }
        }

        public void draw(Graphics g, ImageObserver obs) {
            g.drawImage(img, x, y, obs);
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

        public void keyPressed(KeyEvent e) {
            switch (e.getKeyCode()) {
           
                case KeyEvent.VK_LEFT:
                
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
        int x, y, speed;
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

        public void draw(Graphics g, ImageObserver obs) {
            g.drawImage(img, key.x, key.y, obs);
        }
    }

    public Image getSprite(String name) {
        URL url = gm1942.class.getResource(name);
        Image img = getToolkit().getImage(url);
        try {
            MediaTracker tracker = new MediaTracker(this);
            tracker.addImage(img, 0);
            tracker.waitForID(0);
        } catch (Exception e) {
        }
        return img;
    }

    // generates a new color with the specified hue
    public void drawBackGroundWithTileImage(int w, int h, Graphics2D g2) {
        int TileWidth = sea.getWidth(this);
        int TileHeight = sea.getHeight(this);

        int NumberX = (int) (w / TileWidth);
        int NumberY = (int) (h / TileHeight);

        Image Buffer = createImage(NumberX * TileWidth, NumberY * TileHeight);
        //Graphics BufferG = Buffer.getGraphics();


        for (int i = -1; i <= NumberY; i++) {
            for (int j = 0; j <= NumberX; j++) {
                g2.drawImage(sea, j * TileWidth, i * TileHeight + (move % TileHeight), TileWidth, TileHeight, this);
            }
        }
        move += speed;
    }

    public void drawDemo(int w, int h, Graphics2D g2) {

        if (!gameOver) {
            drawBackGroundWithTileImage(w, h, g2);
            I1.update(w, h);
            I1.draw(g2, this);

            I2.update(w, h);
            I2.draw(g2, this);

            I3.update(w, h);
            I3.draw(g2, this);

            m.draw(g2, this);
        }
  
    }

    
    public Graphics2D createGraphics2D(int w, int h) {
        Graphics2D g2 = null;
        if (bimg == null || bimg.getWidth() != w || bimg.getHeight() != h) {
            bimg = (BufferedImage) createImage(w, h);
        }
        g2 = bimg.createGraphics();
        g2.setBackground(getBackground());
        g2.setRenderingHint(RenderingHints.KEY_RENDERING,
                RenderingHints.VALUE_RENDER_QUALITY);
        g2.clearRect(0, 0, w, h);
        return g2;
    }

    public void paint(Graphics g) {
        Dimension d = getSize();
        Graphics2D g2 = createGraphics2D(d.width, d.height);
        drawDemo(d.width, d.height, g2);
        g2.dispose();
        g.drawImage(bimg, 0, 0, this);
    }

    public void start() {
        thread = new Thread(this);
        thread.setPriority(Thread.MIN_PRIORITY);
        thread.start();
    }

    public void run() {
    	
        Thread me = Thread.currentThread();
        while (thread == me) {
            repaint();
          
          try {
                thread.sleep(20);
            } catch (InterruptedException e) {
                break;
            }
            
        }
    	    	
       // thread = null;
    }

    private void playSound(String filename, int back) {
      
    }

    public static void main(String argv[]) {
        final gm1942 demo = new gm1942();
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

    /**
     * This method is called from within the init() method to initialize the
     * form. WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        setLayout(new java.awt.BorderLayout());
    }// </editor-fold>//GEN-END:initComponents
    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables
}