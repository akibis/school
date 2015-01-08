package drawme;

import java.applet.Applet;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.awt.image.RenderedImage;
import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JFrame;

public class OtherSource extends Applet implements ActionListener,
        MouseMotionListener, MouseListener {

    JFileChooser dialog;
    
    JFrame frame = new JFrame("DOODLE BOARD");

    Panel canvas = new Panel();
    Panel box1 = new Panel();
    Panel box2 = new Panel();
    Graphics g;

    Button bB = new Button("Blue");
    Button bBlk = new Button("Black");
    Button bR = new Button("Red");
    Button bP = new Button("Pink");
    Button bY = new Button("Yellow");
    Button b1 = new Button("size 1");
    Button b2 = new Button("size 2");
    Button b3 = new Button("size 3");
    Button b4 = new Button("size 4");
    Button b5 = new Button("size 5");
    Button bEraser = new Button("Eraser");
    Button bLine = new Button("Line On/Off");
    Button bBackground = new Button("Change Background");
    Button bUndo = new Button("Undo");
    Button bSave = new Button("Save");

    int brushSize = 10;
    int line = 0;
    int startX, startY;

    public void init() {
        frame.setLayout(new BorderLayout());
        frame.add(canvas, BorderLayout.CENTER);
        frame.add(box1, BorderLayout.NORTH);
        frame.add(box2, BorderLayout.SOUTH);
        frame.pack();
        frame.setSize(650, 450);
        g = canvas.getGraphics();
        frame.setVisible(true);
        g.setColor(Color.BLACK);
        canvas.addMouseListener(this);
        canvas.addMouseMotionListener(this);

        box1.add(bB);
        box1.add(bBlk);
        box1.add(bR);
        box1.add(bP);
        box1.add(bY);
        box1.add(b1);
        box1.add(b2);
        box1.add(b3);
        box1.add(b4);
        box1.add(b5);
        box2.add(bEraser);
        box2.add(bLine);
        box2.add(bBackground);
        box2.add(bUndo);
        box2.add(bSave);

        bB.addActionListener(this);
        bBlk.addActionListener(this);
        bR.addActionListener(this);
        bP.addActionListener(this);
        bY.addActionListener(this);
        b1.addActionListener(this);
        b2.addActionListener(this);
        b3.addActionListener(this);
        b4.addActionListener(this);
        b5.addActionListener(this);
        bEraser.addActionListener(this);
        bLine.addActionListener(this);
        bBackground.addActionListener(this);
        bUndo.addActionListener(this);
        bSave.addActionListener(this);

        System.out.println("Draw board initialized.");
    }

    @Override
    public void mouseClicked(MouseEvent arg0) {
        // TODO Auto-generated method stub

    }

    @Override
    public void mouseEntered(MouseEvent arg0) {
        // TODO Auto-generated method stub

    }

    @Override
    public void mouseExited(MouseEvent arg0) {
        // TODO Auto-generated method stub

    }

    @Override
    public void mousePressed(MouseEvent arg0) {
        // TODO Auto-generated method stub
        startX = arg0.getX();
        startY = arg0.getY();

    }

    @Override
    public void mouseReleased(MouseEvent arg0) {

    }

    @Override
    public void mouseDragged(MouseEvent arg0) {
		// TODO Auto-generated method stub
        //System.out.println(arg0.getX() + ", " + arg0.getY());
        if (line == 1) {
//			g.drawLine(startX, startY, arg0.getX(), arg0.getY());

                        // add ability to change size of line
            // uses same buttons as oval
            super.paintComponents(g);
            Graphics2D g2 = (Graphics2D) g;
            g2.setStroke(new BasicStroke(brushSize));
            g2.drawLine(startX, startY, arg0.getX(), arg0.getY());
            startX = arg0.getX();
            startY = arg0.getY();
        } else {
            g.fillOval(arg0.getX() - brushSize / 2,
                    arg0.getY() - brushSize / 2,
                    brushSize, brushSize);
        }
    }

    @Override
    public void mouseMoved(MouseEvent arg0) {
        // TODO Auto-generated method stub

    }

    @Override
    public void actionPerformed(ActionEvent arg0) {
        // TODO Auto-generated method stub
        if (arg0.getSource() == b1) {
            brushSize = 5;
        } else if (arg0.getSource() == b2) {
            brushSize = 10;
        } else if (arg0.getSource() == b3) {
            brushSize = 20;
        } else if (arg0.getSource() == b4) {
            brushSize = 40;
        } else if (arg0.getSource() == b5) {
            brushSize = 80;
        } else if (arg0.getSource() == bB) {
            g.setColor(Color.BLUE);
        } else if (arg0.getSource() == bBlk) {
            g.setColor(Color.BLACK);
        } else if (arg0.getSource() == bR) {
            g.setColor(Color.RED);
        } else if (arg0.getSource() == bP) {
            g.setColor(Color.PINK);
        } else if (arg0.getSource() == bY) {
            g.setColor(Color.YELLOW);
        } else if (arg0.getSource() == bEraser) {
            g.setColor(Color.WHITE);
        } else if (arg0.getSource() == bLine) {
            line = (line == 0) ? 1 : 0;
        } 

// change background image
        else if (arg0.getSource() == bBackground) {
            File image = null;
            dialog = new JFileChooser();
            int retVal = dialog.showOpenDialog(frame);

            if (retVal == JFileChooser.APPROVE_OPTION) {
                image = dialog.getSelectedFile();

                try {
                    Image img = ImageIO.read(image);
                    g.drawImage(img, 0, 0, null);
                } catch (IOException ex) {
                    Logger.getLogger(OtherSource.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
        
        // Save drawing
        else if (arg0.getSource() == bSave){
            File image = null;
            dialog = new JFileChooser();
            int retVal = dialog.showSaveDialog(frame);
            
            if (retVal == JFileChooser.APPROVE_OPTION){
                BufferedImage buf = new BufferedImage(
                                                        frame.getContentPane().getWidth(),
                                                        frame.getContentPane().getHeight(),
                                                        BufferedImage.TYPE_INT_RGB);
                frame.paint(buf.getGraphics());
                image = dialog.getSelectedFile();
                try {
                    ImageIO.write(buf, "png", image);
                } catch (IOException ex) {
                    Logger.getLogger(OtherSource.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
            
        }
        
        // Undo last step
        else if (arg0.getSource() == bUndo){
            
        }

    }

}
