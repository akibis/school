/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package calculator;

/**
 *
 * @author netdom
 */
import java.util.*;

abstract class Operator {

    static HashMap operators = new HashMap();

    public abstract Operand execute(Operand op1, Operand op2);

    public abstract int priority();

    static boolean check(String tok) {
        return operators.containsKey(tok);
    }
}

class Operand {

    private int val;

    Operand(String tok) {
        val = Integer.parseInt(tok);
    }

    Operand(int value) {
        val = value;
    }

    static boolean check(String tok) {
        try {
            Integer.parseInt(tok);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    int getValue() {
        return val;
    }
}

public class Evaluator {

    private Stack<Operand> opdStack;
    private Stack<Operator> oprStack;

    public Evaluator() {
        opdStack = new Stack<Operand>();
        oprStack = new Stack<Operator>();

        Operator.operators.put("+", new AdditionOperator());
        Operator.operators.put("-", new SubtractionOperator());
        Operator.operators.put("*", new MultiplicationOperator());
        Operator.operators.put("/", new DivisionOperator());
        Operator.operators.put("#", new PoundOperator());
        Operator.operators.put("!", new ExclamationOperator());

    }

    public int eval(String expr) {
        String tok;
// init stack - necessary with operator priority schema;
// the priority of any operator in the operator stack other then
// the usual operators - "+-*/" - should be less than the priority
// of the usual operators
        oprStack.push((Operator) Operator.operators.put("#", new PoundOperator()));
        String delimiters = "+-*/#! ";
        StringTokenizer st = new StringTokenizer(expr, delimiters, true);
// the 3rd arg is true to indicate to use the delimiters as tokens, too
// but we'll filter out spaces
        while (st.hasMoreTokens()) {
            if (!(tok = st.nextToken()).equals(" ")) {
// filter out spaces
                if (Operand.check(tok)) {
                    if (tok.equals("(")) {
                        while (!(st.toString().equals(")"))) {
                            opdStack.push(new Operand(tok));
                        }
                    }
// check if tok is an operand
                    opdStack.push(new Operand(tok));
                }

                else {
                    if (Operator.check(tok)) {
                    } else {
                        System.out.println("*****invalid token******");
                        System.exit(1);
                    }
//                    Operator newOpr = new Operator(tok);
                    Operator newOpr = (Operator) Operator.operators.get(tok);
// POINT 1
                    //              System.out.println("TEST1");
                    while (((Operator) oprStack.peek()).priority() >= newOpr.priority()) {

                        //                  System.out.println("TEST2");
// note that when we eval the expression 1 - 2 we will
// push the 1 then the 2 and then do the subtraction operation
// This means that the first number to be popped is the
// second operand, not the first operand - see the following code
                        Operator oldOpr = ((Operator) oprStack.pop());
                        Operand op2 = (Operand) opdStack.pop();
                        Operand op1 = (Operand) opdStack.pop();
                        opdStack.push(oldOpr.execute(op1, op2));
                    }
                    oprStack.push(newOpr);
                }
            }
//            if (opdStack.peek().getValue() == 3) {
//                System.out.println("Stack full.");
//            }
// Control gets here when we've picked up all of the tokens; you must add
// code to complete the evaluation - consider how the code given here
// will evaluate the expression 1+2*3
// When we have no more tokens to scan, the operand stack will contain 1 2 3
// and the operator stack will have + * with 2 and * on the top;
// In order to complete the evaluation we must empty the stacks (except
// the init operator on the operator stack); that is, we should keep
// evaluating the operator stack until it only contains the init operator;
// Suggestion: create a method that takes an operator as argument and
// then executes the while loop; also, move the stacks out of the main
// method

        }
//        while (oprStack.peek() != (Operator) Operator.operators.get("#")) {
//            System.out.println("Check.");
//        }
        int result = evaluate();
        return result;

    }

    int evaluate() {
        int result;
        int counter = 0;
        while (oprStack.peek().priority() > 1) {
            //System.out.println("Eval Round: " + counter++);

            if (opdStack.size() > 1) {
                Operator oldOpr = ((Operator) oprStack.pop());
                Operand op2 = (Operand) opdStack.pop();
                Operand op1 = (Operand) opdStack.pop();
                opdStack.push(oldOpr.execute(op1, op2));
            }
        }

        result = opdStack.peek().getValue();

        return result;
    }

    class AdditionOperator extends Operator {

        AdditionOperator() {
        }

        @Override
        public Operand execute(Operand op1, Operand op2) {
            return new Operand(op1.getValue() + op2.getValue());
        }

        @Override
        public int priority() {
            return 2;
        }
    }

    class SubtractionOperator extends Operator {

        @Override
        public Operand execute(Operand op1, Operand op2) {
            return new Operand(op1.getValue() - op2.getValue());
        }

        @Override
        public int priority() {
            return 3;
        }
    }

    class DivisionOperator extends Operator {

        @Override
        public Operand execute(Operand op1, Operand op2) {
            return new Operand(op1.getValue() / op2.getValue());
        }

        @Override
        public int priority() {
            return 3;
        }
    }

    class MultiplicationOperator extends Operator {

        @Override
        public Operand execute(Operand op1, Operand op2) {
            return new Operand(op1.getValue() * op2.getValue());
        }

        @Override
        public int priority() {
            return 3;
        }
    }

    class PoundOperator extends Operator {

        @Override
        public Operand execute(Operand op1, Operand op2) {
            return null;
        }

        @Override
        public int priority() {
            return 1;
        }
    }

    class ExclamationOperator extends Operator {

        @Override
        public Operand execute(Operand op1, Operand op2) {
            return null;
        }

        @Override
        public int priority() {
            return 0;
        }
    }

}
