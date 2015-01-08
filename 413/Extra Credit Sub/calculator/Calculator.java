/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package calculator;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.text.BadLocationException;

/**
 *
 * @author Aleksandr Kibis
 */
public class Calculator implements ActionListener {

    JButton[] calculatorButtons = new JButton[20];
    JTextArea calcOutput = new JTextArea(2, 20);
    Evaluator myCalc = new Evaluator();

    String display = "";

    Calculator() {
        JFrame mainFrame = new JFrame();
        mainFrame.setResizable(true);
        String[] buttonText = {"1", "2", "3", "+",
            "4", "5", "6", "-",
            "7", "8", "9", "*",
            ".", "0", "=", "/",
            "CE", "C", "(", ")"};

        JPanel[] rows = new JPanel[5];
        for (int i = 0; i < 5; i++) {
            rows[i] = new JPanel();
        }
        GridLayout grid = new GridLayout(7, 1);
        mainFrame.setLayout(grid);

        Dimension buttonSize = new Dimension(60, 60);
        for (int i = 0; i < 20; i++) {
            calculatorButtons[i] = new JButton(buttonText[i]);
            calculatorButtons[i].setFont(new Font("Arial", Font.PLAIN, 40));
            if (i == 16) {
                calculatorButtons[i].setMargin(new Insets(1, 1, 1, 1));
                calculatorButtons[i].setFont(new Font("Arial", Font.PLAIN, 35));
            }
            if (i == 17) {
                calculatorButtons[i].setFont(new Font("Arial", Font.PLAIN, 35));
            }
            calculatorButtons[i].addActionListener(this);
            calculatorButtons[i].setPreferredSize(buttonSize);

        }

        mainFrame.add(calcOutput);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 4; j++) {
                rows[i].add(calculatorButtons[4 * i + j]);
            }
        }

        for (int i = 0; i < 5; i++) {
            mainFrame.add(rows[i]);
        }
        mainFrame.setSize(300, 500);
        mainFrame.setVisible(true);
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Calculator myCalc = new Calculator();

    }

    @Override
    public void actionPerformed(ActionEvent e) {
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.

        if (e.getSource() == calculatorButtons[0]) {
            calcOutput.append("1");
        }
        if (e.getSource() == calculatorButtons[1]) {
            calcOutput.append("2");
        }
        if (e.getSource() == calculatorButtons[2]) {
            calcOutput.append("3");
        }
        if (e.getSource() == calculatorButtons[3]) {
            calcOutput.append("+");
        }
        if (e.getSource() == calculatorButtons[4]) {
            calcOutput.append("4");
        }
        if (e.getSource() == calculatorButtons[5]) {
            calcOutput.append("5");
        }
        if (e.getSource() == calculatorButtons[6]) {
            calcOutput.append("6");
        }
        if (e.getSource() == calculatorButtons[7]) {
            calcOutput.append("-");
        }
        if (e.getSource() == calculatorButtons[8]) {
            calcOutput.append("7");
        }
        if (e.getSource() == calculatorButtons[9]) {
            calcOutput.append("8");
        }
        if (e.getSource() == calculatorButtons[10]) {
            calcOutput.append("9");
        }
        if (e.getSource() == calculatorButtons[11]) {
            calcOutput.append("*");
        }
        if (e.getSource() == calculatorButtons[12]) {
            calcOutput.append(".");
        }
        if (e.getSource() == calculatorButtons[13]) {
            calcOutput.append("0");
        }
        
        // Evaluate expression when '=' is pressed
        if (e.getSource() == calculatorButtons[14]) {
            String expression = calcOutput.getText();
            Evaluator calculator = new Evaluator();
            int result = calculator.eval(expression);
            calcOutput.setText(Integer.toString(result));

        }
        if (e.getSource() == calculatorButtons[15]) {
            calcOutput.append("/");
        }
        // CLEAR
        if (e.getSource() == calculatorButtons[16]) {
            calcOutput.setText("");

        }
        // del
        if (e.getSource() == calculatorButtons[17]) {

            if (calcOutput.getText().length() == 0) {
                calcOutput.setText("");
            } else {
                try {
                    calcOutput.setText(calcOutput.getText(0, calcOutput.getText().length() - 1));
                } catch (BadLocationException ex) {
                    Logger.getLogger(Calculator.class.getName()).log(Level.SEVERE, null, ex);
                }
            }

        }
        if (e.getSource() == calculatorButtons[18]) {
            calcOutput.append("(");
        }
        if (e.getSource() == calculatorButtons[19]) {
            calcOutput.append(")");
        }

    }
}
