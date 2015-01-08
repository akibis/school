package ast;

import lexer.Symbol;
import lexer.Token;
import visitor.*;

public class UnaryOpTree extends AST {

    private Symbol symbol;

    public UnaryOpTree(Token tok) {
        this.symbol = tok.getSymbol();
    }

    public Object accept(ASTVisitor v) {
        return v.visitUnaryOpTree(this);
    }

    public Symbol getSymbol() {
        return symbol;
    }

}
