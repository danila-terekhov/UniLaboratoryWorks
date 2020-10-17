package Lab3;

import java.time.Duration;
import java.time.Instant;
import java.util.ArrayList;
import java.util.List;

public class ListTester {
    final List<String> list;
    Instant start,end;

    ListTester(List list) {
        this.list = list;
    }

    public long testAdd(int N){
        list.clear();
        if (list instanceof ArrayList)
            ((ArrayList<String>) list).trimToSize();


        start = Instant.now();
        while (N-- > 0)
            list.add("0");
        end = Instant.now();

        return Duration.between(start,end).toNanos();
    }


}
