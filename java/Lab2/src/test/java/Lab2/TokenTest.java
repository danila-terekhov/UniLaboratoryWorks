package Lab2;

import org.junit.Test;

import static org.junit.Assert.*;

public class TokenTest {

    @Test
    public void testToken() {
        Token token = new Token("");
        assertNotNull(token);
    }
    @Test
    public void testClassificateType() {
	Token token;
        token = new Token("123");
        assertEquals(TypeOfToken.NUMBER, token.getType());
        token = new Token("(");
        assertEquals(TypeOfToken.BRACKET, token.getType());
        token = new Token("-");
        assertEquals(TypeOfToken.OPERATOR, token.getType());
//        token = new Token("sin");
//        assertEquals(TypeOfToken.FUNCTION, token.getType());
        token = new Token("qwe");
        assertEquals(TypeOfToken.ERROR, token.getType());
        /* ??? */
    }
}
