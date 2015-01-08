/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wingman;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import javax.swing.JApplet;
import javax.swing.JFrame;

/**
 *
 * @author netdom
 */
public class Wingman extends JApplet implements Runnable {

    private Thread thread;
    Image sea, bullet;
    Image playerOne, playerTwo;
    private BufferedImage bimg;
    Graphics2D g2;
    int speed = 1, move = 0;
    int score1 = 0;
    int score2 = 0;
    int fireCounter1, fireCounter2, fireCounter3;
    Random generator = new Random(1234567);
    Island I1;
    Island I2, I3;
    MyPlane m1, m2;
    Bullet fire;
    Explosion explode1, explode2;
    Sound backgroundMusic, boom1, boom2, gameOver;

    // declare HUD elements
    HUDelement healthBar1, healthBar2, healthLabel1, healthLabel2, score_1,
            score_2, scoreLabel1, scoreLabel2, game_over;

    ArrayList<Bullet> clip = new <Bullet>ArrayList();
    int w = 640, h = 480; // fixed size window game 
    Enemy e1;
    Enemy e2, e3;
    GameEvents gameEvents;

    @Override
    public void init() {

        setFocusable(true);
        setBackground(Color.white);
        Image island1, island2, island3, enemyOneImg, enemyTwoImg, enemyThreeImg;

        try {
            //sea = getSprite("Resources/water.png");
            String path = System.getProperty("user.dir");
            path = path + "/";

            System.out.println(path);
            
            
            
            bullet = ImageIO.read(new File(path + "Resources/bullet.png"));
            sea = ImageIO.read(new File(path + "Resources/water.png"));
            island1 = ImageIO.read(new File(path + "Resources/island1.png"));
            island2 = ImageIO.read(new File(path + "Resources/island2.png"));
            island3 = ImageIO.read(new File(path + "Resources/island3.png"));
            playerOne = ImageIO.read(new File(path + "Resources/myplane_3.png"));
            playerTwo = ImageIO.read(new File(path + "Resources/myplane_4.png"));
            enemyOneImg = ImageIO.read(new File(path + "Resources/enemy1_1.png"));
            enemyTwoImg = ImageIO.read(new File(path + "Resources/enemy2_1.png"));
            enemyThreeImg = ImageIO.read(new File(path + "Resources/enemy3_1.png"));

            healthBar1 = new HUDelement("/Resources/health", 5, 10, 420, this);
            healthBar2 = new HUDelement("/Resources/health", 5, 550, 420, this);

            game_over = new HUDelement("/Resources/gameOver", 1, 195, 10, this);

            //explode2 = new Explosion("/Resources/explosion2_", 7, m1.x, m1.y, this);
            I1 = new Island(island1, 100, 100, speed, generator, this);
            I2 = new Island(island2, 200, 400, speed, generator, this);
            I3 = new Island(island3, 300, 200, speed, generator, this);
            e1 = new Enemy(enemyOneImg, 2, generator, this);
            e2 = new Enemy(enemyTwoImg, 3, generator, this);
            e3 = new Enemy(enemyThreeImg, 4, generator, this);
            m1 = new MyPlane(playerOne, 50, 360, 5);
            m2 = new MyPlane(playerTwo, 425, 360, 5);

            fireCounter1 = 50;
            fireCounter2 = 70;
            fireCounter3 = 100;

            // init sounds
            try {
                backgroundMusic = new Sound("/Resources/gucci.wav", true);
                backgroundMusic.play();
                boom1 = new Sound("/Resources/snd_explosion1.wav", false);
                boom2 = new Sound("/Resources/snd_explosion2.wav", false);
                System.out.println("Background music started.");
            } catch (MalformedURLException | LineUnavailableException | UnsupportedAudioFileException ex) {
                Logger.getLogger(Wingman.class.getName()).log(Level.SEVERE, null, ex);
            }

            gameEvents = new GameEvents();
            gameEvents.addObserver(m1);
            gameEvents.addObserver(m2);
            KeyControl key = new KeyControl(this);
            addKeyListener(key);
        } catch (IOException e) {
            System.out.print("No resources are found");
        }
    }

    public class Bullet {

        Image img;
        int x;
        int y;
        int height;
        int width;
        int power;
        Rectangle box;
        boolean show; 
        String shootStyle;
        private String ownedBy;

        Bullet(Image img, int x, int y, String shootStyle) {
            this.img = img;
            this.x = x;
            this.y = y;
            power = 5;
            height = img.getHeight(null);
            width = img.getWidth(null);
            show = true;
            this.shootStyle = shootStyle;
        }

        public void draw(ImageObserver obs) {
            if (show) {
                g2.drawImage(img, x, y, obs);
            }
        }

        // remove bullet object when off screen
        public void update(int i) {
            if("up".equals(shootStyle)){
            this.y -= 10;
            }
            if("down".equals(shootStyle)){
                this.y += 10;
            }
            if("diagDown".equals(shootStyle)){
                this.y += 5;
                this.x += 3;
            }
            // when reached end of screen
            if (this.y <= -20) {
                show = false;
                clip.remove(i);
                clip.trimToSize();
            }

            // when enemy is hit and bullet did not come from enemy
            if ((this.collision(e1.x, e1.y, e1.sizeX, e1.sizeY)
                    || this.collision(e2.x, e2.y, e2.sizeX, e2.sizeY)
                    || this.collision(e3.x, e3.y, e3.sizeX, e3.sizeY))
                    && this.show == true && this != null
                    && !"enemy".equals(this.getOwnedBy())) {
                show = false;
                int j = clip.indexOf(this);
                clip.remove(i);
                clip.trimToSize();
            }

            // when player 1 is hit and bullet came from enemy
            if (this.collision(m1.x, m1.y, m1.width, m1.height)
                    && "enemy".equals(this.getOwnedBy())
                    && this.show == true && this != null) {
                gameEvents.setValue("m1_collision");
                show = false;
                int j = clip.indexOf(this);
                clip.remove(i);
                clip.trimToSize();

            }

            // when player 2 is hit and bullet came from enemy
            if (this.collision(m2.x, m2.y, m2.width, m2.height)
                    && "enemy".equals(this.getOwnedBy())
                    && this.show == true && this != null) {
                gameEvents.setValue("m2_collision");
                show = false;
                int j = clip.indexOf(this);
                clip.remove(i);
                clip.trimToSize();

            } else {
            }
        }

        public boolean collision(int x, int y, int w, int h) {
            box = new Rectangle(this.x, this.y, this.width, this.height);
            Rectangle otherBBox = new Rectangle(x, y, w, h);
            return this.box.intersects(otherBBox);
        }

        public String getOwnedBy() {
            return ownedBy;
        }

        public void setOwnedBy(String planeID) {
            ownedBy = planeID;
        }

    }

    public class MyPlane implements Observer {

        Image img;
        int x, y, speed, width, height;
        private int health = 100;
        Rectangle bbox;
        boolean boom = false;

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
            Rectangle otherBBox = new Rectangle(x, y, w, h);
            return this.bbox.intersects(otherBBox);
        }

        @Override
        public void update(Observable obj, Object arg) {
            GameEvents ge = (GameEvents) arg;
            if (ge.type == 1) {
                KeyEvent e = (KeyEvent) ge.event;
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_LEFT:
                        m2.x -= speed;
                        break;
                    case KeyEvent.VK_RIGHT:
                        m2.x += speed;
                        break;
                    case KeyEvent.VK_UP:
                        m2.y -= speed;
                        break;
                    case KeyEvent.VK_DOWN:
                        m2.y += speed;
                        break;
                    case KeyEvent.VK_A:
                        m1.x -= speed;
                        break;
                    case KeyEvent.VK_D:
                        m1.x += speed;
                        break;
                    case KeyEvent.VK_W:
                        m1.y -= speed;
                        break;
                    case KeyEvent.VK_S:
                        m1.y += speed;
                        break;
                    case KeyEvent.VK_ESCAPE:
                        System.exit(0);
                    default:
                        if (e.getKeyChar() == ' ' && this.equals(m1)) {
                            fire = new Bullet(bullet, m1.x + 17, m1.y, "up");
                            fire.setOwnedBy("m1");
                            clip.add(fire);
                            //System.out.println("Fire 1");
                        }
                        if (e.getKeyChar() == '\n' && this.equals(m2)) {
                            fire = new Bullet(bullet, m2.x + 17, m2.y, "up");
                            fire.setOwnedBy("m2");
                            clip.add(fire);
                            //System.out.println("Fire 2");
                        }

                }
            } else if (ge.type == 2) {
                String msg = (String) ge.event;
                if (msg.equals("m1_collision") && this.equals(m1)) {
                    m1.health -= 25;
                    healthBar1.update();
                    if (health > 0) {
                        boom1.play();
                    }
                    System.out.println("Player 1 health: " + m1.health);
                    if (m1.health == 0) {
                        m1.boom = true;
                        boom2.play();
                    }
                }
                if (msg.equals("m2_collision") && this.equals(m2)) {
                    m2.health -= 25;
                    healthBar2.update();
                    if (health > 0) {
                        boom1.play();
                    }
                    System.out.println("Player 2 health: " + m2.health);
                    if (m2.health == 0) {
                        m2.boom = true;
                        boom2.play();
                    }
                }
//                if (msg.equals("test")) {
//                    System.out.println("test");
//                }
//                if (m1.boom && m2.boom) {
//                    System.out.println("GAME OVER.");
//
//                    //System.exit(0);
//                }
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

    public void drawDemo() throws IOException, InterruptedException, MalformedURLException, LineUnavailableException, UnsupportedAudioFileException {
        drawBackGroundWithTileImage();
        I1.update();
        I2.update();
        I3.update();
        e1.update();
        e2.update();
        e3.update();

        // update bullet locations
        for (int i = 0; i < clip.size(); i++) {
            clip.get(i).update(i);
        }

        // update explosion frames to advance animation
        if (explode1 != null && explode1.frameCount < explode1.numFrames) {
            explode1.update();
        }

        I1.draw(this);
        I2.draw(this);
        I3.draw(this);

        // draw bullets
        clip.stream().forEach((Bullet clip1) -> {
            clip1.draw(this);
        });

        // draw health bars
        healthBar1.draw(this);
        healthBar2.draw(this);

        // draw score
        // draw planes while health > 0
        if (!m1.boom) {
            m1.draw(this);
        }
        if (!m2.boom) {
            m2.draw(this);
        }

        // remove planes from screen upon death
        if (m1.boom) {
            explode2 = new Explosion("/Resources/explosion2_", 7, m1.x, m1.y, this);
            m1.y = -100;

        }
        if (m2.boom) {
            explode2 = new Explosion("/Resources/explosion2_", 7, m2.x, m2.y, this);
            m2.y = -100;
        }
        
        // when both players are dead, display game over logo and final score
        if (m1.boom && m2.boom) {
            game_over.draw(this);
            g2.setFont(new Font("Arial", Font.BOLD, 20));
            g2.setColor(Color.WHITE);
            g2.drawString("FINAL SCORE", 250, 125);
            g2.setFont(new Font("Arial", Font.BOLD, 15));
            g2.drawString("Player 1", 200, 150);
            g2.drawString(Integer.toString(score1), 410, 150);
            g2.drawString("Player 2", 200, 180);
            g2.drawString(Integer.toString(score2), 410, 180);

        }

        // draw enemies
        e1.draw(this);
        e2.draw(this);
        e3.draw(this);

        // Enemy one fire style: fast diagonal
        if (fireCounter1 == 50) {
            fire = new Bullet(bullet, e1.x, e1.y, "diagDown");
            fire.setOwnedBy("enemy");
            clip.add(fire);
            //System.out.println("Fire 1");
        }
        fireCounter1--;
        if (fireCounter1 == 0) {
            fireCounter1 = 50;
        }
        
        // Enemy two fire style: medium down
        if (fireCounter2 == 70) {
            fire = new Bullet(bullet, e2.x, e2.y, "down");
            fire.setOwnedBy("enemy");
            clip.add(fire);
            //System.out.println("Fire 1");
        }
        fireCounter2--;
        if (fireCounter2 == 0) {
            fireCounter2 = 70;
        }
        
        // Enemy three fire style: slow downward
        if (fireCounter3 == 100) {
            fire = new Bullet(bullet, e3.x, e3.y, "down");
            fire.setOwnedBy("enemy");
            clip.add(fire);
            //System.out.println("Fire 1");
        }
        fireCounter3--;
        if (fireCounter3 == 0) {
            fireCounter3 = 100;
        }
        
        
        
        
        
        
        
        // draw explosion frame
        if (explode1 != null && explode1.frameCount < explode1.numFrames) {
            //System.out.println("Draw explosion.");
            explode1.draw(this);
        }
        if (explode2 != null && explode2.frameCount < explode2.numFrames) {
            //System.out.println("Draw explosion.");
            explode2.draw(this);
        }
    }

    @Override
    public void paint(Graphics g) {
        if (bimg == null) {
            Dimension windowSize = getSize();
            bimg = (BufferedImage) createImage(windowSize.width,
                    windowSize.height);
            g2 = bimg.createGraphics();
        }
        try {
            drawDemo();
        } catch (IOException | InterruptedException | LineUnavailableException | UnsupportedAudioFileException ex) {
            Logger.getLogger(Wingman.class.getName()).log(Level.SEVERE, null, ex);
        }
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
        final Wingman demo = new Wingman();
        demo.init();
        JFrame f = new JFrame("Wingman");
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
