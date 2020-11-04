package Lab4;

import java.util.HashMap;
import java.util.Map;


/**
 * Создатель словарей, которые можно назвать сущностью человека.
 * Из-за того, что главная тема лабораторной - структуры данных,
 * мне показалось излишним создавать отдельный класс человека.
 */
class ManFabric extends DictionaryFabric {
    DivisionFabric divisionFabric;

    public ManFabric() {
        super(new String[]{"id",
                           "name",
                           "gender",
                           "BirtDate",
                           "Division",
                           "Salary"});
        divisionFabric = new DivisionFabric();
    }


    @Override
    public Map<String, Object> createNewNode(String[] values) throws IllegalArgumentException {
        if (values.length != keys.length) throw new IllegalArgumentException();

        Map<String, Object> dictionary = new HashMap<String, Object>();

        for (int i = 0; i < keys.length; i++)
            if (!keys[i].equals("Division"))
                dictionary.put(keys[i], values[i]);
            else
                dictionary.put(keys[i], divisionFabric.createNewDivision(values[i]));

        return dictionary;
    }
}

