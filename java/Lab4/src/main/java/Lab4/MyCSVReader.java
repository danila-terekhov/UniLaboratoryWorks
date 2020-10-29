package Lab4;

import com.opencsv.CSVReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class MyCSVReader {
    char separator;

    public MyCSVReader(char separator) {
        this.separator = separator;
    }

    public List<Map<String, String>> readCSV(String csvFilePath) {

        try (InputStream in = getClass().getClassLoader().getResourceAsStream(csvFilePath);
             CSVReader reader = in == null ? null : new CSVReader(new InputStreamReader(in), separator)) {
            if (reader == null) {
                throw new FileNotFoundException(csvFilePath);
            }

            String[] nextLine = reader.readNext();
            DictionaryFabric CSVfabric = new DictionaryFabric(nextLine);
            ArrayList<Map<String, String>> CSVList = new ArrayList<>();

            while ((nextLine = reader.readNext()) != null) {
                try {
                    CSVList.add(CSVfabric.createNewNode(nextLine));
                }
                catch (IllegalArgumentException e){
                    System.out.println("Wrong format!");
                    break;
                }

            }
            return CSVList;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}
