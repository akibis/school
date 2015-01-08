/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wingman;

import java.awt.Image;
import java.awt.image.ImageObserver;
import java.util.Random;

/**
 *
 * @author netdom
 */
public class Island {
    Image img;
    int x;
    int y;
    int speed;
    Random gen;
    private final Wingman outer;

    Island(Image img, int x, int y, int speed, Random gen, final Wingman outer) {
        this.outer = outer;
        this.img = img;
        this.x = x;
        this.y = y;
        this.speed = speed;
        this.gen = gen;
    }

    public void update() {
        y += speed;
        if (y >= outer.h) {
            y = -100;
            x = Math.abs(gen.nextInt() % (outer.w - 30));
        }
    }

    public void draw(ImageObserver obs) {
        outer.g2.drawImage(img, x, y, obs);
    }
    
}
