/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tankgame;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

/**
 *
 * @author netdom
 */
public class KeyControl extends KeyAdapter {
    private final TankGame outer;

    public KeyControl(final TankGame outer) {
        this.outer = outer;
    }

    @Override
    public void keyPressed(KeyEvent e) {
        outer.gameEvents.setValue(e);
    }
    
}
