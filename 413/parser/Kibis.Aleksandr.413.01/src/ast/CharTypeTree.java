package ast;

import visitor.*;

public class CharTypeTree extends AST {

    public CharTypeTree() {
    }

    public Object accept(ASTVisitor v) {
        return v.visitCharTypeTree(this);
    }

}
