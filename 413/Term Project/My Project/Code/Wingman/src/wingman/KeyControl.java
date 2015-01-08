/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package wingman;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

/**
 *
 * @author netdom
 */
public class KeyControl extends KeyAdapter {
    private final Wingman outer;

    public KeyControl(final Wingman outer) {
        this.outer = outer;
    }

    @Override
    public void keyPressed(KeyEvent e) {
        outer.gameEvents.setValue(e);
    }
    
}
