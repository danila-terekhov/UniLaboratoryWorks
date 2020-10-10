
import java.util.*;
import java.time.*;

public class Main {

    public static void main(String[] args) {

	if ( args.length != 1 ) {
		System.out.println("Usage: java Main.java numberOfOperations"); // it works w/o precompilation!
		System.exit(1);
	}

	int N = Integer.parseInt(args[0]);
	Instant start,end;

	ArrayList<Integer> arr = new ArrayList<>();
	LinkedList<Integer> link = new LinkedList<>();

	long []times = new long[6];

	start = Instant.now();
	for (int i = 0; i < N; i++)
		arr.add(i);
	end = Instant.now();
	times[0] = Duration.between(start,end).toNanos();

	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.add(i);
	end = Instant.now();
	times[1] = Duration.between(start,end).toNanos();

	start = Instant.now();
	for (int i = 0; i < N; i++)
		arr.get(N-1);
	end = Instant.now();
	times[2] = Duration.between(start,end).toNanos();

	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.get(N-1);
	end = Instant.now();
	times[3] = Duration.between(start,end).toNanos();

	start = Instant.now();
	for (int i = N-1; i >= 0; i--)
		arr.remove(i);
	end = Instant.now();
	times[4] = Duration.between(start,end).toNanos();

	start = Instant.now();
	for (int i = N-1; i >= 0; i--)
		link.remove(i);
	end = Instant.now();
	times[5] = Duration.between(start,end).toNanos();


	
	final Object[][] table = new String[7][];
	table[0] = new String[] { "Structure", "Operations", "Time(Nano sec)" };
	table[1] = new String[] { "ArrayList", "Add",	String.valueOf(times[0]) };
	table[2] = new String[] { "LinkedList", "Add",	String.valueOf(times[1]) };
	table[3] = new String[] { "ArrayList", "Get",	String.valueOf(times[2]) };
	table[4] = new String[] { "LinkedList", "Get",	String.valueOf(times[3])};
	table[5] = new String[] { "ArrayList", "Delete",String.valueOf(times[4])};
	table[6] = new String[] { "LinkedList", "Delete",String.valueOf(times[5])};

	for (final Object[] row : table) {
	    System.out.format("%15s%15s%15s\n", row);
	}
    }
}
