package tankgame;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import javax.swing.*;
import javax.sound.sampled.*;

/**
 * 
 * @author rusky
 */
public class Sound {
    URL url;
    private Clip clip;
    boolean loop;
    String path = System.getProperty("user.dir");
    /**
     * 
     * Creates sound clip for game effects
     * 
     * @param name name of sound file (.WAV ONLY!)
     * @param loop true if sound is to be looped
     * @throws MalformedURLException
     * @throws LineUnavailableException
     * @throws UnsupportedAudioFileException
     * @throws IOException 
     */
    Sound(String name, boolean loop) throws MalformedURLException, LineUnavailableException, UnsupportedAudioFileException, IOException{
        url = new URL(
            //"file:///home/netdom/Dropbox/Fall 2014/413/Term Project/My Project/Code/Wingman/gucci.wav" LINUX ONLY
                "file:///" + path + name
        );
        clip = AudioSystem.getClip();
        this.loop = loop;
        // getAudioInputStream() also accepts a File or InputStream
        AudioInputStream ais = AudioSystem.
            getAudioInputStream( url );
        clip.open(ais);
        SwingUtilities.invokeLater(() -> {
        });
    }
    
    /**
     * Plays sound clip
     */
    public void play(){
        // loop clip playback
        
        if(loop){
            clip.loop(Clip.LOOP_CONTINUOUSLY);
        
        // play clip once
        }else{
            clip.setFramePosition(clip.getFrameLength()); // so that clip won't play twice intially
            clip.loop(1);
        }
        
    }
    
    /**
     * Flushes clip data stream. Used in case playback in interrupted.
     */
    public void flush(){    
        clip.flush();
    }
}