package Lab2;

import java.util.*;

public class Parser {
    private static enum CONSTANTS {
        PI("Pi", Math.PI),
        E("E", Math.E);

        private final double value;
        private final String lexemeString;

        CONSTANTS(String lexeme, double value) {
            this.value = value;
            this.lexemeString = lexeme;
        }

        @Override
        public String toString() {
            return String.valueOf(value);
        }
    }


    private interface OperatorInterface {
        double calc(double p1, double p2);
    }
    private enum LEXEMES {
        PLUS("+", 1, (p1,p2) -> { return p1+p2;}),
        MINUS("-", 1, (p1,p2) -> { return p2-p1;}),
        TIMES("*", 2, (p1,p2) -> { return p1*p2;}),
        DIVIDE("/", 2, (p1,p2) -> { return p2/p1;}),
        SIN("sin", 3, (p1,p2) -> { return Math.sin(p1);}),
        COS("cos", 3, (p1,p2) -> { return Math.cos(p1);}),
        EXP("exp", 3, (p1,p2) -> { return Math.exp(p1);}),
        LEFT_BRACKET("(", 0, null),
        RIGHT_BRACKET(")", 0, null);


        private final String lexemeString;
        private final int lexemePriority;
        public OperatorInterface lexemeOperation;
        private static final Map<String, LEXEMES> byName = new HashMap<>();


        static {
            for (LEXEMES e : values()) {
                byName.put(e.lexemeString, e);
            }
        }


        LEXEMES(String s, int i, OperatorInterface f) {
            lexemeString = s;
            lexemePriority = i;
            lexemeOperation = f;
        }

        public static LEXEMES valueByString(String str) {
            return byName.get(str);
        }
        public static boolean contains(String str) {
            return byName.containsKey(str);
        }
    }

    private final String sourceExpression;
    private static Stack<String> output;
    private static Stack<LEXEMES> operations;

    public Parser(String sourceExpression) {
        this.sourceExpression = sourceExpression;
        output = new Stack<>();
        operations = new Stack<>();
    }

    public double evaluate() {
        double retValue;
        try {
            convertToRPN();
            retValue = computeExpression();
            return retValue;
        }
        catch(Exception e) {
                System.out.println(e);
                return Double.NaN;
        }

    }
    private void convertToRPN() throws Exception {
        String expression = sourceExpression.replaceAll(" ", "").concat("\n");
        int i = 0;
        boolean flag = false;
        String var;
        Scanner in = new Scanner(System.in);
        while (!expression.startsWith("\n")) {
            for (i = 0; Character.isDigit(expression.charAt(i)) || expression.charAt(i) == '.'; i++) {/*NOP*/}
            if (i > 0) {
                output.push(expression.substring(0, i));
                expression = expression.replaceFirst(output.peek(), "");
                continue;
            }
            flag = false;
            for (LEXEMES lexeme : LEXEMES.values()) {
                if (expression.startsWith(lexeme.lexemeString)) {
                    putIntoStack(lexeme);
                    expression = expression.substring(lexeme.lexemeString.length());
                    flag = true;
                    break;
                }
            }
            for (CONSTANTS constant : CONSTANTS.values()) {
                if (expression.startsWith(constant.lexemeString)) {
                    output.push(String.valueOf(constant.value));
                    expression = expression.substring(constant.lexemeString.length());
                    flag = true;
                    break;
                }
            }
            //error symbol
            if (!flag){
                System.out.println("Pls inter variable: " + expression.charAt(0));
                while (true) {
                    var = in.nextLine();
                    if (!var.matches("[-+]?[0-9]*\\.?[0-9]+"))
                        System.out.println("wrong format, pls try again");
                    else {
                        output.push(var);
                        expression = expression.substring(1);
                        break;
                    }
                }
            }
        }

        while (!operations.isEmpty()) {
            if (operations.peek() == LEXEMES.LEFT_BRACKET)
                throw new Exception("Mismatched parenthesis");
            output.push(operations.pop().lexemeString);
        }
    }

    private void putIntoStack(LEXEMES lexeme) throws Exception {
        if (operations.isEmpty()) {
            operations.push(lexeme);
        } else if (lexeme == LEXEMES.LEFT_BRACKET) {
            operations.push(lexeme);
        } else if (lexeme == LEXEMES.RIGHT_BRACKET) {
            if (operations.empty()) {
                throw new Exception("Mismatched parenthesis");
            }
            if (operations.peek() == LEXEMES.LEFT_BRACKET) {
                operations.pop();
            } else {
                output.push(operations.pop().lexemeString);
                putIntoStack(lexeme);
            }
        } else if (operations.peek().lexemePriority >= lexeme.lexemePriority) {
            output.push(operations.pop().lexemeString);
            putIntoStack(lexeme);
        } else {
            operations.push(lexeme);
        }

    }

    public double computeExpression() throws Exception {
        char c;
        Stack<Double> computationStack = new Stack<>();
        for (String anOutput : output) {
            c = anOutput.charAt(0);
            if (Character.isDigit(c)) {
                computationStack.push(Double.valueOf(anOutput));
            } else if (Character.isAlphabetic(c)){
                        if (computationStack.empty())
                            throw new Exception("Wrong order");
                        else
                            computationStack.push(
                                    LEXEMES.valueByString(anOutput).
                                    lexemeOperation.calc(
                                    computationStack.pop(),0));
                }
                else if (computationStack.size() < 2)
                    throw new Exception("Wrong order");
                else computationStack.push(
                        LEXEMES.valueByString(anOutput).
                        lexemeOperation.calc(
                        computationStack.pop(), computationStack.pop()));
        }
        if (computationStack.size() > 1)
            throw new Exception("Wrong order");
        else
            return computationStack.pop();
    }

}
