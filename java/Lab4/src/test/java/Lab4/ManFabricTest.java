package Lab4;

import org.junit.Test;

import java.util.HashMap;
import java.util.Map;

import static org.junit.Assert.*;

public class ManFabricTest {

    @Test
    public void testCreateNewNode() {
        DictionaryFabric df = new DictionaryFabric(new String[]{"qwe","rty"});
        Map<String,Object> check = new HashMap<String,Object>();
        check.put("qwe","123");
        check.put("rty","456");
        assertEquals(check, df.createNewNode(new String[]{"123","456"}));

    }
}