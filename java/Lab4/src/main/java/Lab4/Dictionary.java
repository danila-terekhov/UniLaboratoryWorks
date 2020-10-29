package Lab4;

import java.util.HashMap;
import java.util.Map;
import java.lang.IllegalArgumentException;

class DictionaryFabric {

    String[] keys;

    public DictionaryFabric(String[] keys){
        this.keys = keys;
    }

    public Map<String,String> createNewNode(String[] values) throws IllegalArgumentException {
        if (values.length != keys.length) throw new IllegalArgumentException();

        Map<String, String> dictionary = new HashMap<String, String>();

        for (int i = 0; i < keys.length; i++)
            dictionary.put(keys[i], values[i]);

        return dictionary;
    }
}
