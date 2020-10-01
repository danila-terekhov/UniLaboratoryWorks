package Lab2;

public class App {
    public String getGreeting() {
        return "Hello world.";
    }

    public static void main(String[] args) {
        System.out.println(new App().getGreeting());
	    Expression exp = new Expression("2+2");
	    exp.show();

    }

}
