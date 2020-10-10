
import java.util.*;
import java.time.*;

public class Main {

    public static void fill(List list, int N) {
	while (--N >= 0)
	list.add("0");
    }

    public static void main(String[] args) {

	if ( args.length != 1 ) {
		System.out.println("Usage: java Main.java numberOfOperations"); // it works w/o precompilation!
		System.exit(1);
	}

	int N = Integer.parseInt(args[0]);
	Instant start,end;

	ArrayList arr = new ArrayList();
	LinkedList link = new LinkedList();

	long []times = new long[17];

	//add to the end
	start = Instant.now();
	for (int i = 0; i < N; i++)
		arr.add("0");
	end = Instant.now();
	times[0] = Duration.between(start,end).toNanos();

	arr.clear();
	arr.trimToSize();

	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.add("0");
	end = Instant.now();
	times[1] = Duration.between(start,end).toNanos();

	link.clear();

	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.addLast("0");
	end = Instant.now();
	times[2] = Duration.between(start,end).toNanos();

	link.clear();

	//add to the middle
	start = Instant.now();
	for (int i = 0; i < N; i++)
		arr.add(i/2,"0");
	end = Instant.now();
	times[3] = Duration.between(start,end).toNanos();

	arr.clear();
	arr.trimToSize();

	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.add(i/2,"0");
	end = Instant.now();
	times[4] = Duration.between(start,end).toNanos();

	link.clear();

	//add to the begin
	start = Instant.now();
	for (int i = 0; i < N; i++)
		arr.add(0, "0");
	end = Instant.now();
	times[5] = Duration.between(start,end).toNanos();


	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.add(0,"0");
	end = Instant.now();
	times[6] = Duration.between(start,end).toNanos();

	link.clear();


	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.addFirst("0");
	end = Instant.now();
	times[7] = Duration.between(start,end).toNanos();


	//remove from the end
	start = Instant.now();
	for (int i = N-1; i>=0; i--)
		arr.remove(i);
	end = Instant.now();
	times[8] = Duration.between(start,end).toNanos();
	fill(arr, N);

	start = Instant.now();
	for (int i = N-1; i>=0; i--)
		link.remove(i);
	end = Instant.now();
	times[9] = Duration.between(start,end).toNanos();
	fill(link, N);


	start = Instant.now();
	for (int i = N-1; i>=0; i--)
		link.remove();
	end = Instant.now();
	times[10] = Duration.between(start,end).toNanos();
	fill(link, N);

	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.removeLast();
	end = Instant.now();
	times[11] = Duration.between(start,end).toNanos();
	fill(link, N);

	// remove from the middle
	start = Instant.now();
	for (int i = N-1; i>=0; i--)
		arr.remove(i/2);
	end = Instant.now();
	times[12] = Duration.between(start,end).toNanos();
	fill(arr, N);

	start = Instant.now();
	for (int i = N-1; i>=0; i--)
		link.remove(i/2);
	end = Instant.now();
	times[13] = Duration.between(start,end).toNanos();
	fill(link,N);

	//remove from the begin
	
	start = Instant.now();
	for (int i = 0; i < N; i++)
		arr.remove(0);
	end = Instant.now();
	times[14] = Duration.between(start,end).toNanos();

	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.remove(0);
	end = Instant.now();
	times[15] = Duration.between(start,end).toNanos();
	fill(link, N);

	start = Instant.now();
	for (int i = 0; i < N; i++)
		link.removeLast();
	end = Instant.now();
	times[16] = Duration.between(start,end).toNanos();

	final Object[][] table = new String[18][];
	table[0] = new String[] { "Structure", "Operations", "Time(Nano sec)" };

	table[1] = new String[] { "ArrayList",	"Add(value)",		String.valueOf(times[0]) };
	table[2] = new String[] { "LinkedList",	"Add(value)",		String.valueOf(times[1]) };
	table[3] = new String[] { "LinkedList",	"AddLast(value)",	String.valueOf(times[2]) };

	table[4] = new String[] { "ArrayList", 	"Add(i/2, value)",	String.valueOf(times[3]) };
	table[5] = new String[] { "LinkedList",	"Add(i/2, value)",	String.valueOf(times[4])};

	table[6] = new String[] { "ArrayList",	"Add(0,value)",		String.valueOf(times[5])};
	table[7] = new String[] { "LinkedList",	"Add(0,value)",		String.valueOf(times[6])};
	table[8] = new String[] { "LinkedList",	"AddFirst(value)",	String.valueOf(times[7])};

	table[9] = new String[] { "ArrayList",	"remove(iLast)",	String.valueOf(times[8])};
	table[10]= new String[] { "LinkedList",	"remove(iLast)",	String.valueOf(times[9])};
	table[11]= new String[] { "LinkedList",	"removeLast",		String.valueOf(times[10])};
	table[12]= new String[] { "LinkedList",	"remove()",		String.valueOf(times[11])};

	table[13]= new String[] { "ArrayList",	"remove(i/2)",		String.valueOf(times[12])};
	table[14]= new String[] { "LinkedList",	"remove(i/2)",		String.valueOf(times[13])};

	table[15]= new String[] { "ArrayList",	"remove(0)",		String.valueOf(times[14])};
	table[16]= new String[] { "LinkedList",	"remove(0)",		String.valueOf(times[15])};
	table[17]= new String[] { "LinkedList",	"removeFirst",		String.valueOf(times[16])};

	for (final Object[] row : table) {
	    System.out.format("%12s%20s%15s\n", row);
	}
    }
}
