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
	    int firstIndex, lastIndex;
        for (int i=0; i < text.length(); i++){
            if (Character.isSpaceChar(text.charAt(i)));
            else if (Character.isDigit(text.charAt(i))) {
                firstIndex = i;
                while (i < text.length()-1
                    || Character.isDigit(text.charAt(i))
                    || '.' == text.charAt(i))
                    i++;
                lastIndex = --i;

                tokens.add(new Token(text.substring(firstIndex,lastIndex)));
            }
            /*
            else
            if (Character.isAlphabetic(ch)) {
                tmp = fetchWord(textIndex);
            }
             */
            else
                tokens.add(new Token(String.valueOf(text.charAt(i))));

        }
    }
    public void show(){
	for (Token i : tokens) {
            System.out.println(i.getSymbol() + ":" + i.getType());
        }
    }

    public ArrayList<Token> getTokens() {
	    return tokens;
    }

}
