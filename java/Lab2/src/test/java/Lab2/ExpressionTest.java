package Lab2;

import org.junit.Test;

import static org.junit.Assert.*;

import java.util.ArrayList;

public class ExpressionTest {

    @Test
    public void testExpression() {
	Expression expression;
        expression = new Expression("2+2");
	ArrayList<Token> tokens = new ArrayList<Token>();
	tokens.add(new Token("2"));
	tokens.add(new Token("+"));
	tokens.add(new Token("2"));
	for (int i = 0; i < tokens.size() ; i++)
        assertEquals(expression.getTokens().get(i).getSymbol(), tokens.get(i).getSymbol());
        /* ??? */
    }
}