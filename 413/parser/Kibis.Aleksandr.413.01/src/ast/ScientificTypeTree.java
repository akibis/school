package ast;

import visitor.*;

public class ScientificTypeTree extends AST {

    public ScientificTypeTree() {
    }

    public Object accept(ASTVisitor v) {
        return v.visitScientificTypeTree(this);
    }

}
