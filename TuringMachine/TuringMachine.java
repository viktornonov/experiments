import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class TuringMachine {
    private final String[] action;
    private final Map<Character, Integer>[] next;
    private final Map<Character, Character>[] out;

    public TuringMachine(String filename) throws FileNotFoundException {
        Scanner scanner = new Scanner(
                new BufferedInputStream(new FileInputStream(new File(filename))),
                StandardCharsets.UTF_8
                );
        int n = scanner.nextInt();
        String alphabet = scanner.next();
        action = new String[n];
        next = (Map<Character, Integer>[]) new Map[n];
        out = (Map<Character, Character>[]) new Map[n];
        for (int st = 0; st < n; st++) {
            action[st] = scanner.next();
            if (action[st].equals("Halt") || action[st].equals("Yes") || action[st].equals("No")) {
                continue;
            }

            next[st] = new HashMap<>();
            for (int i = 0; i < alphabet.length(); i++) {
                int state = scanner.nextInt();
                next[st].put(alphabet.charAt(i), state);
            }

            out[st] = new HashMap<>();
            for (int i = 0; i < alphabet.length(); i++) {
                char symbol = scanner.next().charAt(0);
                out[st].put(alphabet.charAt(i), symbol);
            }
        }
    }

    public String simulate(String input) {
        Tape tape = new Tape(input);
        int state = 0;
        while (action[state].equals("L") || action[state].equals("R")) {
            if (action[state].equals("R")) { tape.moveRight(); }
            if (action[state].equals("L")) { tape.moveLeft(); }
            char c = tape.read();
            tape.write(out[state].get(c));
            state = next[state].get(c);
        }
        return action[state] + " " + tape;
    }

    public static void main(String[] args) throws FileNotFoundException {
        if (args.length < 2) {
            System.out.println("Usage: java TuringMachine MachingConfig.txt input");
            return;
        }
        TuringMachine tm = new TuringMachine(args[0]);
        //"1010+1010"
        System.out.println(tm.simulate(args[1]));
    }
}
