package ast;

import visitor.*;

public class DoTree extends AST {

    public DoTree() {
    }

    public Object accept(ASTVisitor v) {
        return v.visitDoTree(this);
    }
}
