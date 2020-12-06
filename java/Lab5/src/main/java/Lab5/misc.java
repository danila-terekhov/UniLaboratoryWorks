package Lab5;

interface SomeInterface{
    public void doSomething();
}

interface SomeOtherInterface{
    public void doSomeOther();
}

class SomeImpl implements SomeInterface{
    public void doSomething(){
        System.out.println("A");
    }
}

class OtherImpl implements SomeInterface{
    public void doSomething(){
        System.out.println("B");
    }
}

class SODoer implements SomeOtherInterface{
    public void doSomeOther(){
        System.out.println("C");
    }
}

class SomeBean{

    @AutoInjectable
    private SomeInterface field1;
    @AutoInjectable
    private SomeOtherInterface field2;
    public void foo(){
        field1.doSomething();
        field2.doSomeOther();
    }
}