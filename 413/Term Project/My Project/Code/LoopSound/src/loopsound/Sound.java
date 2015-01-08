package loopsound;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import javax.swing.*;
import javax.sound.sampled.*;

public class Sound {
    URL url;
    Clip clip;
    Sound() throws MalformedURLException, LineUnavailableException, UnsupportedAudioFileException, IOException{
        url = new URL(
            "file:///home/netdom/Dropbox/Fall 2014/413/Term Project/My Project/Code/Wingman/gucci.wav");
        clip = AudioSystem.getClip();
        // getAudioInputStream() also accepts a File or InputStream
        AudioInputStream ais = AudioSystem.
            getAudioInputStream( url );
        clip.open(ais);
        clip.loop(Clip.LOOP_CONTINUOUSLY);
        SwingUtilities.invokeLater(() -> {
        });
    }

    public static void main(String[] args) throws Exception {
        Sound sound = new Sound();
    }
}