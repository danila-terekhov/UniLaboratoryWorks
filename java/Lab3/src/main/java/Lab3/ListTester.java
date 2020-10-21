package Lab3;

import java.time.Duration;
import java.time.Instant;
import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

/**
 * Класс - тестер?
 */
public class ListTester {
    final List<String> list;
    Instant start,end;
    final int N;
    final String value;

    /**
     * Конструктор с параметрами
     * @param list тестируемый List
     * @param N количество элементов
     * @param value используемое для вставки значение
     */
    ListTester(List list, int N, String value) {
        this.list = list;
        this.N = N;
        this.value = value;
    }

    /**
     * Измерение времени, требуемое на
     * добавление {@link ListTester#N} элементов в конец {@link ListTester#list}.
     * @return Затраченное время
     */
    public long testAdd(){
        list.clear();
        if (list instanceof ArrayList)
            ((ArrayList<String>) list).trimToSize();

        start = Instant.now();
        for (int i = 0; i < N; i++)
            list.add(value);
        end = Instant.now();

        return Duration.between(start,end).toNanosPart();
    }

    /**
     * Измерение времени, требуемое на
     * добавление {@link ListTester#N} элементов на определенный индекс.
     * (Используется для теста вставки в начало).
     * @param index - индекс вставки
     * @return Затраченное время
     */
    public long testAdd(int index){
        list.clear();
        if (list instanceof ArrayList)
            ((ArrayList<String>) list).trimToSize();

        start = Instant.now();
        for (int i = 0; i < N; i++)
            list.add(index, value);
        end = Instant.now();

        return Duration.between(start,end).toNanosPart();
    }
    /**
     * Измерение времени, требуемое на
     * добавление {@link ListTester#N} элементов в середину {@link ListTester#list}.
     * @return Затраченное время
     */
    public long testAddMiddle(){
        int N = this.N;
        list.clear();
        if (list instanceof ArrayList)
            ((ArrayList<String>) list).trimToSize();

        start = Instant.now();
        for (int i = 0; i < N; i++)
            list.add(i/2,value);
        end = Instant.now();

        return Duration.between(start,end).toNanosPart();
    }

    /**
     * Заполняет {@link ListTester#list}  {@link ListTester#N} элементами.
     */
    public void fill(){
        while (list.size() < N)
            list.add(value);
    }

    /**
     * Аналогично {@link ListTester#testAdd(int)}
     */
    public long testGetByIndex(int index){
        if (list.size() < N)
            fill();

        start = Instant.now();
        for (int i = 0; i < N; i++)
            list.get(index);
        end = Instant.now();

        return Duration.between(start,end).toNanosPart();
    }

    /**
     * Аналогично {@link ListTester#testAddMiddle()}
     */
    public long testGetMiddle(){
        if (list.size() < N)
            fill();

        start = Instant.now();
        for (int i = 0; i < N; i++)
            list.get(i/2);
        end = Instant.now();

        return Duration.between(start,end).toNanosPart();
    }

    /**
     * Аналогично {@link ListTester#testAdd()}
     */
    public long testRemove(){

        if (list.size() < N)
            fill();
        int N = this.N - 1;
        start = Instant.now();
        do {
            list.remove(N);
        } while (--N > 0);
        end = Instant.now();

        return Duration.between(start,end).toNanosPart();
    }

    /**
     * Аналогично {@link ListTester#testAdd(int)}
     */
    public long testRemove(int index){
        if (list.size() < N)
            fill();

        start = Instant.now();
        for (int i = 0; i < N; i++)
            list.remove(index);
        end = Instant.now();

        return Duration.between(start,end).toNanosPart();
    }

    /**
     * Аналогично {@link ListTester#testAddMiddle()}
     */
    public long testRemoveMiddle( ){
        if (list.size() < N)
            fill();

        start = Instant.now();
        for (int i = N-1; i > 0; i--)
            list.remove(i/2);
        end = Instant.now();

        return Duration.between(start,end).toNanosPart();
    }

    /**
     * Обходит список с помощью итератора.
     * @return Затраченное время.
     */
    public long testGetWithIterator(){
        if (list.size() < N)
            fill();
        ListIterator iter = list.listIterator();

        start = Instant.now();
        while(iter.hasNext())
            iter.next();
        end = Instant.now();

        return Duration.between(start,end).toNanosPart();
    }

}
