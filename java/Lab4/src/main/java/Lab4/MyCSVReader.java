package Lab4;

import com.opencsv.CSVReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;

public class MyCSVReader {
    char separator;

    public MyCSVReader(char separator) {
        this.separator = separator;
    }

    public void read(String csvFilePath) {

        try (InputStream in = getClass().getClassLoader().getResourceAsStream(csvFilePath);
             CSVReader reader = in == null ? null : new CSVReader(new InputStreamReader(in), separator)) {
            if (reader == null) {
                throw new FileNotFoundException(csvFilePath);
            }
            String[] nextLine;
            while ((nextLine = reader.readNext()) != null) {

                System.out.println(nextLine[0]);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
