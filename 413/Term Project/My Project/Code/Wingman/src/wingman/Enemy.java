/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wingman;

import java.awt.Image;
import java.awt.Rectangle;
import java.awt.image.ImageObserver;
import java.io.IOException;
import java.net.MalformedURLException;
import java.util.Random;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

/**
 *
 * @author netdom
 */
public class Enemy {

    Image img;
    int x;
    int y;
    int sizeX;
    int sizeY;
    int speed;
    Random gen;
    Rectangle bbox;
    boolean show;
    private final Wingman outer;

    Enemy(Image img, int speed, Random gen, final Wingman outer) {
        this.outer = outer;
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

    public boolean collision(int x, int y, int w, int h) {
        bbox = new Rectangle(this.x, this.y, this.sizeX, this.sizeY);
        Rectangle otherBBox = new Rectangle(x, y, w, h);
        return this.bbox.intersects(otherBBox);
    }

    public Enemy getInstance() {
        return this;
    }

    public void update() throws IOException, InterruptedException, MalformedURLException, LineUnavailableException, UnsupportedAudioFileException {
        y += speed;
        if (outer.m1.collision(x, y, sizeX, sizeY)) {
            show = false;
            // You need to remove this one and increase score etc
            outer.gameEvents.setValue("m1_collision");
            outer.gameEvents.setValue("");
            outer.score1 += 50;
            outer.explode1 = new Explosion("/Resources/explosion1_", 6, this.x, this.y, outer);
            this.reset();
            show = true;
        }
        if (outer.m2.collision(x, y, sizeX, sizeY)) {
            show = false;
            // You need to remove this one and increase score etc
            outer.gameEvents.setValue("m2_collision");
            outer.gameEvents.setValue("");
            outer.score2 += 50;
            outer.explode1 = new Explosion("/Resources/explosion1_", 6, this.x, this.y, outer);
            this.reset();
            show = true;
        }
        if (outer.fire != null) {
            if (this.collision(outer.fire.x, outer.fire.y, outer.fire.width, outer.fire.height)) {
                //System.out.println(outer.fire.getOwnedBy());
                switch (outer.fire.getOwnedBy()) {
                    case "m1":
                        this.show = false;
                        outer.score1 += 100;
                        outer.explode1 = new Explosion("/Resources/explosion1_", 6, this.x, this.y, outer);
                        //System.out.println("Explosion created.");
                        outer.boom1.play();
                        this.reset();
                        break;
                    case "m2":
                        this.show = false;
                        outer.score2 += 100;
                        outer.explode1 = new Explosion("/Resources/explosion1_", 6, this.x, this.y, outer);
                        //System.out.println("Explosion created.");
                        outer.boom1.play();
                        this.reset();
                        break;
                    case "enemy":

                        break;
                }
                show = true;
            } else {
            }
        }
        if (this.y >= 480) {
            this.reset();
        } else {
            outer.gameEvents.setValue("");
        }
    }

    public void reset() {
        this.x = Math.abs(outer.generator.nextInt() % (600 - 30));
        this.y = -10;
    }

    public void draw(ImageObserver obs) {
        if (show) {
            outer.g2.drawImage(img, x, y, obs);
        }
    }

}
