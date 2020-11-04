package Lab4;

import java.util.HashMap;
import java.util.Map;
import java.lang.IllegalArgumentException;

/**
 * Класс для создания словарей HashMap &ltString, Object&gt
 */
class DictionaryFabric {
    String[] keys;

    /**
     * Конструктор, определяет ключи создаваемых словарей. ¯\_(ツ)_/¯
     * @param keys
     */
    public DictionaryFabric(String[] keys){
        this.keys = keys;
    }

    /**
     * Создание карты ¯\_(ツ)_/¯
     * @param values - значения соответствующие ключам в конструкторе
     * @return карту соответствий
     * @throws IllegalArgumentException
     */
    public Map<String, Object> createNewNode(String[] values) throws IllegalArgumentException {
        if (values.length != keys.length) throw new IllegalArgumentException();

        Map<String, Object> dictionary = new HashMap<String, Object>();

        for (int i = 0; i < keys.length; i++)
            dictionary.put(keys[i], values[i]);

        return dictionary;
    }
}
