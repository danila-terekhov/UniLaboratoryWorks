package Lab2;

public class App {
    public String getGreeting() {
        return "Hello world.";
    }

    public static void main(String[] args) {
        System.out.println(new App().getGreeting());
        //Parser expression = ;
        System.out.format("2*2+2 = %f\n", new Parser("2*2+2").evaluate());
        System.out.format("2*(2+2) = %f\n", new Parser("2*(2+2)").evaluate());
        System.out.format("sin(Pi) = %f\n", new Parser("sin(Pi)").evaluate());
        System.out.format("1+x = %f\n", new Parser("1+x").evaluate());
        System.out.format("1++1 = %f\n", new Parser("1++1").evaluate());
        System.out.format("1(+1 = %f\n", new Parser("1(+1").evaluate());

    }

}
