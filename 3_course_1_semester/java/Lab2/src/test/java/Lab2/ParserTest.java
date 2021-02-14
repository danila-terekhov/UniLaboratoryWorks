package Lab2;

import org.junit.Before;
import org.junit.Test;
import org.junit.Rule;
import org.junit.rules.ExpectedException;
import static org.junit.Assert.*;

public class ParserTest {


    @Test
    public void computeExpression() {
        //Parser p1 = new Parser("2*(2+2)");
        //Parser p2 = new Parser("2*2+2");
        //Parser p3 = new Parser("3/2");
        //assertEquals(8.0, p1.evaluate(),0);
        //assertEquals(6.0, p2.evaluate(),1);
        //assertEquals(1.5, p3.evaluate(),0);


    }

    @Rule
    public ExpectedException exception = ExpectedException.none();

    @Test
    public void testEvaluate() {
        //exception.expect(Exception.class);
        //Parser parser = new Parser("2+2)");
        //parser.evaluate();
        //exception.expectMessage("Wrong order");


    }
}