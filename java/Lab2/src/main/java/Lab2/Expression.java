package Lab2;

import java.util.ArrayList;

public class Expression {
    String text;
    ArrayList<Token> tokens;
    int textIndex = 0;
    int tokenIndex = 0;

    public Expression(String input) {
        text = input.trim();
        tokens = new ArrayList<Token>();
        parse();
    }

    private void parse(){
        String tmp;
        for (char ch: text.toCharArray()){
            if (Character.isSpaceChar(ch)) {
                textIndex++;
                continue;
            } else
            if (Character.isDigit(ch)) {
                tmp = get_number(textIndex);
                textIndex += tmp.length();
                tokens.add(new Token(tmp));
            }
            /*
            if (Character.isAlphabetic(ch)) {
                tmp = get_word(textIndex);
            }
             */
            else
                tokens.add(new Token(String.valueOf(ch)));
                textIndex++;
        }
    }
    public void show(){
        for (int i=0; i< tokens.size(); i++) {
            System.out.println(tokens.get(i).getSymbol()+":"+tokens.get(i).getType());
        }
    }

    private String get_number(int textIndex) {
        //TODO
        return "1";
    }

}
