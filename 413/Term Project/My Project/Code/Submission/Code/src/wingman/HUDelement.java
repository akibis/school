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
 * @author netdom
 */
public class HUDelement extends Wingman{

    Image[] element;
    int x, y, numFrames;
    String path = System.getProperty("user.dir");
    int frameCount = 0;
    
    final Wingman outer;

    HUDelement(String name, int numFrames, int x, int y, final Wingman outer) throws IOException {
        this.x = x;
        this.y = y;
        this.numFrames = numFrames;
        path = path + name;
        this.outer = outer;

        element = new Image[numFrames];
        if(numFrames == 1){
            element[0] = ImageIO.read(new File(path + ".png"));
        }
        else{
        for (int i = 0; i < numFrames; i++) {
            System.out.println(path + i + ".png");
            element[i] = ImageIO.read(new File(path + i + ".png"));
        }
        }
//        System.out.println(path + 0 + ".png");
//        element[0] = ImageIO.read(new File(path + 0 + ".png"));

    }
    
    public void draw(ImageObserver obs){
        outer.g2.drawImage(element[frameCount], x, y, obs);
    }
    
    public void update(){
        if(!(frameCount == numFrames - 1)) {
            frameCount++;
        }
            

    }

}
