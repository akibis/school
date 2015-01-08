/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tankgame;

import java.awt.Image;
import java.awt.image.ImageObserver;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

/**
 *
 * @author netdom
 */
public class HUDelement extends TankGame {

    Image[] element;
    int x, y, numFrames;
    String path = System.getProperty("user.dir");
    int frameCount = 0;

    final TankGame outer;

    /**
     *
     * Initializes HUD game element. Used for any objects displayed on screen
     * which do not interface with other objects. Health bars, score, overlayed
     * images, etc...
     *
     * @param name of image file
     * @param numFrames number of images in animation
     * @param x coordinate
     * @param y coordinate
     * @param outer reference to game
     * @throws IOException
     */
    HUDelement(String name, int numFrames, int x, int y, final TankGame outer) throws IOException {
        this.x = x;
        this.y = y;
        this.numFrames = numFrames;
        path = path + name;
        this.outer = outer;

        element = new Image[numFrames];
        if (numFrames == 1) {
            element[0] = ImageIO.read(new File(path + ".png"));
        } else {
            for (int i = 0; i < numFrames; i++) {
                //System.out.println(path + i + ".png");
                element[i] = ImageIO.read(new File(path + i + ".png"));
            }
        }

    }

    /**
     *
     * @param obs the image observer
     */
    public void draw(ImageObserver obs) {
        outer.g2.drawImage(element[frameCount], x, y, obs);
    }

    /**
     * Updates animation frame
     */
    public void update() {
        if (!(frameCount == numFrames - 1)) {
            frameCount++;
        }

    }

    /**
     *  Rewinds animation by 1 frame. 
     */
    public void reverse() {
        if (frameCount != 0) {
            frameCount--;
        }
    }

}
