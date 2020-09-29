package Lab2;

import java.util.ArrayList;

public class Expression {
    String text;
    ArrayList<Token> tokens;
    int tokenIndex = 0;

    public Expression(String input) {
        text = input.trim();
        tokens = new ArrayList<Token>();
        parse();
    }

    private void parse(){
        String tmp;
	int textIndex = 0;
        for (char ch: text.toCharArray()){
            if (Character.isSpaceChar(ch)) {
                textIndex++;
            } else
            if (Character.isDigit(ch)) {
                tmp = fetchNumber(textIndex);
                textIndex += tmp.length();
                tokens.add(new Token(tmp));
            }
            /*
            if (Character.isAlphabetic(ch)) {
                tmp = fetchWord(textIndex);
            }
             */
            else {
                tokens.add(new Token(String.valueOf(ch)));
                textIndex++;
	    }
        }
    }
    public void show(){
	for (Token i : tokens) {
            System.out.println(i.getSymbol() + ":" + i.getType());
        }
    }

    private String fetchNumber(int textIndex) {
        //TODO
        return String.valueOf(text.charAt(textIndex));
    }
    public ArrayList<Token> getTokens() {
	    return tokens;
    }

}
