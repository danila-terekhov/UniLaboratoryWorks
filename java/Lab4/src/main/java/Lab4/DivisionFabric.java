package Lab4;

import java.util.HashMap;
import java.util.Map;

/**
 * Создатель словарей - отделений
 */
class DivisionDictionaryFabric extends DictionaryFabric {
    static int divisionIdCounter = 1;
    Map<String,Integer> map;

    /**
     * Конструктор - создание нового объекта
     * Поле map необходимо для проверки id у
     * отделений - если отделение уже встречалось ранее, то
     * будет использован тот же id что и в первый раз.
     * @see DictionaryFabric#DictionaryFabric(String[])
     */
    public DivisionDictionaryFabric(){
        super(new String[]{"Letter", "Id"});
        map = new HashMap<>();
    }


    public Map<String, Object> createNewDivision(String letter) {
        if (!map.containsKey(letter))
            map.put(letter, divisionIdCounter++);

        Map<String, Object> dictionary = new HashMap();
        dictionary.put("Letter", letter);
        dictionary.put("Id", map.get(letter));

        return dictionary;
    }
}