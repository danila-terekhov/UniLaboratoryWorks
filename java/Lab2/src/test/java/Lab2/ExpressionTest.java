package Lab2;

import org.junit.Test;

import static org.junit.Assert.*;

import java.util.ArrayList;

public class ExpressionTest {

    @Test
    public void testGetToken() {
		Expression expression;
		expression = new Expression("2+2");
		ArrayList<Token> tokens = new ArrayList<Token>();
		tokens.add(new Token("2"));
		tokens.add(new Token("+"));
		tokens.add(new Token("2"));
		for (int i = 0; i < tokens.size() ; i++)
    	    assertEquals(expression.getTokens().get(i).getSymbol(), tokens.get(i).getSymbol());
    }
	@Test
	public void testFetchNumber() {
    	Expression expression;
		expression = new Expression("11+1");
		Token token = new Token("11");
		assertEquals(expression.getTokens().get(0).getSymbol(), token.getSymbol());
	}
}
