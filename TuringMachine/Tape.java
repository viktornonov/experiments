import java.util.Stack;

public class Tape {
    private final Stack<Character> left = new Stack<>();
    private final Stack<Character> right = new Stack<>();
    private char current;

    public Tape(String input) {
        right.push('#');
        for(int i = input.length() - 1; i >= 0; i--) {
            right.push(input.charAt(i));
        }
        current = right.pop();
    }

    public char read() {
        return current;
    }

    public void write(char symbol) {
        current = symbol;
    }

    public void moveLeft() {
        right.push(current);
        if (left.isEmpty()) {
            left.push('#');
        }
        current = left.pop();
    }

    public void moveRight() {
        left.push(current);
        if (right.isEmpty()) right.push('#');
        current = right.pop();
    }

    public String toString() { // the result ends up in the left stack
        Object[] leftChars = left.toArray();
        StringBuilder sb = new StringBuilder();
        for (Object c : leftChars) {
            sb.append((char)c);
        }
        sb.append(current);
        Object[] rightChars = right.toArray();
        for (Object c : rightChars) {
            sb.append((char)c);
        }
        return sb.toString();
    }
}
