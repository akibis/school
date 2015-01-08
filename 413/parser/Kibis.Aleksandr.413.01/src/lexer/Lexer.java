package lexer;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;

/**
 * The Lexer class is responsible for scanning the source file which is a stream
 * of characters and returning a stream of tokens; each token object will
 * contain the string (or access to the string) that describes the token along
 * with an indication of its location in the source program to be used for error
 * reporting; we are tracking line numbers; white spaces are space, tab,
 * newlines
 */
public class Lexer {

    private boolean atEOF = false;
    private char ch;     // next character to process
    private SourceReader source;

    // positions in line of current token
    private int startPosition, endPosition;

    public Lexer(String sourceFile) throws Exception {
        new TokenType();  // init token table
        source = new SourceReader(sourceFile);
        ch = source.read();
    }

    // Borrowed code online for read file function.
    // http://stackoverflow.com/questions/326390/how-to-create-a-java-string-from-the-contents-of-a-file
    static String readFile(String path, Charset encoding)
            throws IOException {
        byte[] encoded = Files.readAllBytes(Paths.get(path));
        return new String(encoded, encoding);
    }

    public static void main(String args[]) throws IOException {
        if (args.length == 0) {
            System.err.println("Usage: java -jar <fileName.jar> <inputFile>");
            System.exit(1);
        }
        Token tok;
        try {
            Lexer lex = new Lexer(args[0]);
            while (true) {
                tok = lex.nextToken();
                String p = "L: " + tok.getLeftPosition()
                        + " R: " + tok.getRightPosition() + "  "
                        + TokenType.tokens.get(tok.getKind()) + " ";
                if ((tok.getKind() == Tokens.Identifier)
                        || (tok.getKind() == Tokens.INTeger)
                        || (tok.getKind() == Tokens.FLOAT)
                        || (tok.getKind() == Tokens.SCIENTIFICN)
                        || (tok.getKind() == Tokens.CHAR)) {
                    p += tok.toString();
                }
                //(tok.getKind() == Tokens.FLOAT))

                System.out.println(p + ": " + lex.source.getLineno());
            }

        } catch (Exception e) {
        }
        // Print out file after tokenizing
        System.out.println("\n****************************************\n");
        System.out.println(readFile(args[0], Charset.defaultCharset()));
    }

    /**
     * newIdTokens are either ids or reserved words; new id's will be inserted
     * in the symbol table with an indication that they are id's
     *
     * @param id is the String just scanned - it's either an id or reserved word
     * @param startPosition is the column in the source file where the token
     * begins
     * @param endPosition is the column in the source file where the token ends
     * @return the Token; either an id or one for the reserved words
     */
    public Token newIdToken(String id, int startPosition, int endPosition) {
        return new Token(startPosition, endPosition, Symbol.symbol(id, Tokens.Identifier));
    }

    /**
     * number tokens are inserted in the symbol table; we don't convert the
     * numeric strings to numbers until we load the bytecodes for interpreting;
     * this ensures that any machine numeric dependencies are deferred until we
     * actually run the program; i.e. the numeric constraints of the hardware
     * used to compile the source program are not used
     *
     * @param number is the int String just scanned
     * @param startPosition is the column in the source file where the int
     * begins
     * @param endPosition is the column in the source file where the int ends
     * @return the int Token
     */
    public Token newNumberToken(String number, int startPosition, int endPosition) {
        return new Token(startPosition, endPosition, Symbol.symbol(number, Tokens.INTeger));
    }

    /**
     * float tokens are inserted in the symbol table; we don't convert the
     * numeric strings to numbers until we load the bytecodes for interpreting;
     * this ensures that any machine numeric dependencies are deferred until we
     * actually run the program; i.e. the numeric constraints of the hardware
     * used to compile the source program are not used
     *
     * @param aFloat is the float String just scanned
     * @param startPosition is the column in the source file where the int
     * begins
     * @param endPosition is the column in the source file where the int ends
     * @return the float Token
     */
    public Token newFloatToken(String aFloat, int startPosition, int endPosition) {
        return new Token(startPosition, endPosition, Symbol.symbol(aFloat, Tokens.FLOAT));
    }

    /**
     * ScientificN tokens are inserted in the symbol table; we don't convert the
     * numeric strings to numbers until we load the bytecodes for interpreting;
     * this ensures that any machine numeric dependencies are deferred until we
     * actually run the program; i.e. the numeric constraints of the hardware
     * used to compile the source program are not used
     *
     * @param SN is the scientific String just scanned
     * @param startPosition is the column in the source file where the int
     * begins
     * @param endPosition is the column in the source file where the int ends
     * @return the ScientificN Token
     */
    public Token newScientificToken(String SN, int startPosition, int endPosition) {
        return new Token(startPosition, endPosition, Symbol.symbol(SN, Tokens.SCIENTIFICN));
    }

    /**
     * char tokens are inserted in the symbol table; we don't convert the char
     * strings to chars until we load the bytecodes for interpreting; this
     * ensures that any machine numeric dependencies are deferred until we
     * actually run the program; i.e. the numeric constraints of the hardware
     * used to compile the source program are not used
     *
     * @param aChar is the char String just scanned
     * @param startPosition is the column in the source file where the char
     * begins
     * @param endPosition is the column in the source file where the char ends
     * @return the ScientificN Token
     */
    public Token newCharToken(String aChar, int startPosition, int endPosition) {
        if (aChar.length() == 3) {
            return new Token(startPosition, endPosition, Symbol.symbol(aChar, Tokens.CHAR));
        } else {
            System.out.println("******** char expected but String found: " + aChar);
            return new Token(startPosition, endPosition, Symbol.symbol(aChar, Tokens.BogusToken));
        }
    }

    /**
     * build the token for operators (+ -) or separators (parens, braces) filter
     * out comments which begin with two slashes
     *
     * @param s is the String representing the token
     * @param startPosition is the column in the source file where the token
     * begins
     * @param endPosition is the column in the source file where the token ends
     * @return the Token just found
     */
    public Token makeToken(String s, int startPosition, int endPosition) {
        if (s.equals("//")) {  // filter comment
            try {
                int oldLine = source.getLineno();
                do {
                    ch = source.read();
                } while (oldLine == source.getLineno());
            } catch (Exception e) {
                atEOF = true;
            }
            return nextToken();
        }
        Symbol sym = Symbol.symbol(s, Tokens.BogusToken); // be sure it's a valid token
        if (sym == null) {
            System.out.println("******** illegal character: " + s);
            atEOF = true;
            return nextToken();
        }
        return new Token(startPosition, endPosition, sym);
    }

    /**
     * @return the next Token found in the source file
     */
    public Token nextToken() { // ch is always the next char to process
        if (atEOF) {
            if (source != null) {
                source.close();
                source = null;
            }
            return null;
        }
        try {
            while (Character.isWhitespace(ch)) {  // scan past whitespace
                ch = source.read();
            }
        } catch (Exception e) {
            atEOF = true;
            return nextToken();
        }
        startPosition = source.getPosition();
        endPosition = startPosition - 1;

        if (Character.isJavaIdentifierStart(ch)) {
            // return tokens for ids and reserved words
            String id = "";
            try {
                do {
                    endPosition++;
                    id += ch;
                    ch = source.read();
                } while (Character.isJavaIdentifierPart(ch));
            } catch (Exception e) {
                atEOF = true;
            }
            return newIdToken(id, startPosition, endPosition);
        }
        if (Character.isDigit(ch) || ch == '-') {
            // return number tokens
            String number = "";
            try {
                do {
                    endPosition++;
                    number += ch;
                    ch = source.read();
                    if (ch == '.') {
                        do {
                            endPosition++;
                            number += ch;
                            ch = source.read();
                            if (ch == 'e') {
                                do {
                                    endPosition++;
                                    number += ch;
                                    ch = source.read();
                                } while (Character.isDigit(ch) || ch == '-');
                                return newScientificToken(number, startPosition, endPosition);
                            }
                        } while (Character.isDigit(ch));
                        return newFloatToken(number, startPosition, endPosition);
                    }
                } while (Character.isDigit(ch));
            } catch (Exception e) {
                atEOF = true;
            }
            // add if statement
            // if "." then start float, continue until ends
            // if an "e" is reached during float, start scientific
            // else run code below
            // if only "." then syntax error (ie exception)
            return newNumberToken(number, startPosition, endPosition);
        }
        if (ch == '.') {
            String number = "";
            try {
                do {
                    endPosition++;
                    number += ch;
                    ch = source.read();

                } while (Character.isDigit(ch));
                return newFloatToken(number, startPosition, endPosition);
            } catch (Exception e) {
                atEOF = true;
            }
        }
        if (ch == '\'') {
            String aChar = "";
            try {
                do {
                    endPosition++;
                    aChar += ch;
                    ch = source.read();
//                    if (aChar.length() >= 3 && aChar.charAt(2) != '\''){
//                        System.out.println("******** illegal character: " + aChar);
//                        //System.exit(1);
//                        break;
//                    }
                } while (Character.isLetter(ch) || ch == '\'');

                return newCharToken(aChar, startPosition, endPosition);
            } catch (Exception e) {
                atEOF = true;
            }
        }

        // At this point the only tokens to check for are one or two
        // characters; we must also check for comments that begin with
        // 2 slashes
        String charOld = "" + ch;
        String op = charOld;
        Symbol sym;
        try {
            endPosition++;
            ch = source.read();
            op += ch;
            // check if valid 2 char operator; if it's not in the symbol
            // table then don't insert it since we really have a one char
            // token
            sym = Symbol.symbol(op, Tokens.BogusToken);
            if (sym == null) {  // it must be a one char token
                return makeToken(charOld, startPosition, endPosition);
            }
            endPosition++;
            ch = source.read();
            return makeToken(op, startPosition, endPosition);
        } catch (Exception e) {
        }
        atEOF = true;
        if (startPosition == endPosition) {
            op = charOld;
        }
        return makeToken(op, startPosition, endPosition);
    }
}
