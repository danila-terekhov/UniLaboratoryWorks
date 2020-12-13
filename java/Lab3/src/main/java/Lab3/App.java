/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package Lab3;

import java.util.*;

/**
 * Основное приложение
 * @author DanilaTerekhov
 * @version 0.0.1
 */
public class App {
    /**
     *  Простенький класс результатов теста
     */
    public static class Results {

        long timeArr, timeLink;
        String method;

        /**
         *
         * @param timeArr  время теста ArrayList
         * @param timeLink  время теста LinkedList
         * @param method  описание тестируемого метода
         * @see ListTester
         */
        public Results(long timeArr, long timeLink, String method) {
            this.timeArr = timeArr;
            this.timeLink = timeLink;
            this.method = method;
        }
    }

    public String getGreeting() {
        return "Hello world.";
    }

    public static void main(String[] args) {

        System.out.println("Enter number of tests");
        int N = new Scanner(System.in).nextInt();
        ListTester testArr = new ListTester(new ArrayList(), N, "0");
        ListTester testLink = new ListTester(new LinkedList(), N, "0");

        ArrayList<Results> results = new ArrayList<>();

        results.add(new Results (
                testArr.testAdd(),
                testLink.testAdd(),
                "Add to the end"));
        results.add(new Results (
                testArr.testAdd(0),
                testLink.testAdd(0),
                "Add to the begin"));
        results.add(new Results (
                testArr.testAddMiddle(),
                testLink.testAddMiddle(),
                "Add to the middle"));

        results.add(new Results (
                testArr.testGetByIndex(N-1),
                testLink.testGetByIndex(N-1),
                "Get from the end"));
        results.add(new Results (
                testArr.testGetByIndex(0),
                testLink.testGetByIndex(0),
                "Get from the begin"));
        results.add(new Results (
                testArr.testGetMiddle(),
                testLink.testGetMiddle(),
                "Get from the middle"));
        results.add(new Results (
                testArr.testGetWithIterator(),
                testLink.testGetWithIterator(),
                "Get by iter"));

        results.add(new Results (
                testArr.testRemove(),
                testLink.testRemove(),
                "Remove from the end"));
        results.add(new Results (
                testArr.testRemove(0),
                testLink.testRemove(0),
                "Remove from the begin"));
        results.add(new Results (
                testArr.testRemoveMiddle(),
                testLink.testRemoveMiddle(),
                "Remove from the middle"));







        System.out.format("%25s%20s%23s\n", "Method", "ArrayList time", "LinkedList time");
        for(Results res : results )
            System.out.format("%25s%20d%3c%20d\n",
                    res.method,
                    res.timeArr,
                    res.timeArr>res.timeLink?'>':'<',
                    res.timeLink);
    }
}