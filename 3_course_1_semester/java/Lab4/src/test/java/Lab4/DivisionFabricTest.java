package Lab4;

import org.junit.Test;

import java.util.HashMap;
import java.util.Map;

import static org.junit.Assert.*;

public class DivisionFabricTest {

    @Test
    public void testId() {
        DivisionFabric df = new DivisionFabric();
        df.createNewDivision("A");
        df.createNewDivision("B");
        assertEquals((Integer)1, df.getId("A"));
        assertEquals((Integer)2, df.getId("B"));
        df.createNewDivision("A");
        assertEquals((Integer)1, df.getId("A"));
    }

    @Test
    public void testCreateNewDivision() {
        DivisionFabric df = new DivisionFabric();
        Map<String,Object> check = new HashMap<String,Object>();
        check.put("Letter","C");
        check.put("Id",(Integer)3);
        assertEquals(check, df.createNewDivision("C"));
    }
}