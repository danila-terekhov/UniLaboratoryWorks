package Lab4;

import java.util.HashMap;
import java.util.Map;

/**
 * сущность подразделения.
 */
class Division{
    static int idCounter = 0;

    public String getLetter() {
        return letter;
    }

    final String letter;
    final int id;
    Division(String letter){
        this.letter = letter;
        id = idCounter++;
    }

    @Override
    public String toString() {
        return "Division{" +
                "letter='" + letter + '\'' +
                ", id=" + id +
                '}';
    }
}
/**
 * Создатель словарей, которые можно назвать сущностью человека.
 * Из-за того, что главная тема лабораторной - структуры данных,
 * мне показалось излишним создавать отдельный класс человека.
 */
class ManDictionaryFacric extends DictionaryFabric {

    public ManDictionaryFacric() {
        super(new String[]{"id",
                           "name",
                           "gender",
                           "BirtDate",
                           "Division",
                           "Salary"});
    }

    @Override
    public Map<String, Object> createNewNode(String[] values) throws IllegalArgumentException {
        if (values.length != keys.length) throw new IllegalArgumentException();

        Map<String, Object> dictionary = new HashMap<String, Object>();

        for (int i = 0; i < keys.length; i++)
            if (keys[i].equals("Division"))
                dictionary.put(keys[i], new Division(values[i]));
            else
                dictionary.put(keys[i], values[i]);

        return dictionary;
    }
}

