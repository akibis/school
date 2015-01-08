/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wingman;

import java.awt.Image;
import java.awt.image.ImageObserver;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;


/**
 *
 * @author rusky
 */
public class Explosion extends Wingman{
    Image[] frames;
    int x, y, numFrames, frameCount;
    String path = System.getProperty("user.dir");
    private final Wingman outer;
    
    /**
     * 
     * @param img: array of explosion images
     * @param x: x coordinate
     * @param y: y coordinate
     * @throws IOException if image file is not found
     */
    Explosion(String name, int numFrames, int x, int y, final Wingman outer) throws IOException{
        this.outer = outer;
        this.x = x;
        this.y = y;
        this.numFrames = numFrames;
        frameCount = 0;
        frames = new Image[numFrames];
        path = path + name;
               
        // load individual frames of explosion animation
        for(int i=1; i <= numFrames; i++){
            frames[i - 1] = ImageIO.read(new File(path  + i + ".png"));
            //System.out.println(path + i + ".png");
            
        }
    }
    
    public void draw(ImageObserver obs) throws InterruptedException, IOException{
        
        outer.g2.drawImage(this.frames[frameCount], x, y, obs);
    }
    
    
    public void update() throws InterruptedException{
            y += speed;
            frameCount++;
    }
    
}
