package Lab2;

public class Token {


    String symbol;
    TypeOfToken type;
    final String matchNumber = "[-+]?[0-9]*\\.?[0-9]+";
    final String matchOperator = "+-/*^";
    final String matchBracket = "()";
    //final String matchFunction = "^sin$|^cos$";

    public Token(String symbol) {
        this.symbol = symbol;
        type = classificateType();
    }


    private TypeOfToken classificateType() {
        if (symbol.matches(matchNumber))
            return TypeOfToken.NUMBER;
        if (matchOperator.contains(symbol))
            return TypeOfToken.OPERATOR;
        if (matchBracket.contains(symbol))
            return TypeOfToken.BRACKET;
        return TypeOfToken.ERROR;
    }
    public TypeOfToken getType() {
        return type;
    }
    public String getSymbol() {
	    return symbol;
    }


}
