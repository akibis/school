/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tankgame;

import java.awt.Image;
import java.awt.Rectangle;
import java.awt.image.ImageObserver;
import java.io.IOException;
import java.net.MalformedURLException;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

/**
 *
 * @author netdom
 */
public class Wall {

    Image img;
    Rectangle box;
    int x, sizeX;
    int y, sizeY;
    boolean breakable, show;
    String pickup;

    private final TankGame outer;

    Wall(Image img, int x, int y, boolean breakable, String pickup, final TankGame outer) {
        this.outer = outer;
        this.img = img;
        this.x = x;
        this.y = y;
        this.sizeX = img.getWidth(null);
        this.sizeY = img.getHeight(null);
        this.breakable = breakable;
        this.pickup = pickup;
        show = true;
    }

    /**
     * 
     * @throws IOException file not found
     * @throws MalformedURLException badly formatted url 
     * @throws LineUnavailableException sound device is busy
     * @throws UnsupportedAudioFileException  incorrect file format
     */
    public void update() throws IOException, MalformedURLException, LineUnavailableException, UnsupportedAudioFileException {

        if (outer.m1.collision(x, y, sizeX, sizeY)) {
            show = true;

            outer.m1.speed = -5;
            if (outer.m1.x < this.x - 5) {
                outer.m1.x -= 5;
            } else {
                outer.m1.x += 5;
            }
            if (outer.m1.y < this.y - 5) {
                outer.m1.y -= 5;
            } else {
                outer.m1.y += 5;
            }
            outer.m1.speed = 5;

            if (this.pickup != null && this.pickup.equals("health")) {
                outer.m1.health += 25;
                outer.healthBar1.reverse();
                System.out.println("Player 1 picked up health.");
                this.show = false;
                this.y = -100;
            }

        }
        if (outer.m2.collision(x, y, sizeX, sizeY)) {
            show = true;

            outer.m2.speed = -5;
            if (outer.m2.x < this.x - 5) {
                outer.m2.x -= 5;
            } else {
                outer.m2.x += 5;
            }
            if (outer.m2.y < this.y - 5) {
                outer.m2.y -= 5;
            } else {
                outer.m2.y += 5;
            }
            outer.m2.speed = 5;

            if (this.pickup != null && this.pickup.equals("health")) {
                outer.m2.health += 25;
                outer.healthBar2.reverse();
                System.out.println("Player 2 picked up health.");
                this.show = false;
                this.y = -100;
            }            
            
            
        }
        for (TankGame.Bullet clip : outer.clip) {
            if (clip != null) {
                if (this.collision(clip.x, clip.y, clip.width, clip.height)) {
                    //System.out.println(outer.fire.getOwnedBy());
                    switch (clip.getOwnedBy()) {
                        case "m1":
                            //System.out.println("Explosion created.");
                            clip.show = false;
                            outer.explode1 = new Explosion("/Resources/explosion1_", 6, clip.x, clip.y, outer);
                            if (this.breakable) {
                                this.show = false;
                                this.y = -100;
                            }
                            break;
                        case "m2":
                            //System.out.println("Explosion created.");
                            clip.show = false;
                            outer.explode1 = new Explosion("/Resources/explosion1_", 6, clip.x, clip.y, outer);
                            if (this.breakable) {
                                this.show = false;
                                this.y = -100;
                            }
                            break;
                        default:
                            break;
                    }
                } else {
                }
            }
        }
//System.out.println("Clip size: " + outer.clip.size());
    }

    /**
     * 
     * @param obs the image observer
     */
    public void draw(ImageObserver obs) {
        outer.g2.drawImage(img, x, y, obs);
    }

    /**
     * 
     * @param x coordinate of wall
     * @param y coordinate of wall
     * @param w width of wall
     * @param h height of wall
     * @return true if collision has occured 
     */
    public boolean collision(int x, int y, int w, int h) {
        box = new Rectangle(this.x, this.y, this.sizeX, this.sizeY);
        Rectangle otherBBox = new Rectangle(x, y, w, h);
        return this.box.intersects(otherBBox);
    }

}
