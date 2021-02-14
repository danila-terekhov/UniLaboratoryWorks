package Lab4;

import com.opencsv.CSVReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * Реализация класса, используемого для чтения файлов формата csv.
 */
public class MyCSVReader {
    /** разделитель столбцов */
    char separator;
    /** имя файла */
    String fileName;
    CSVReader reader = null;
    DictionaryFabric csvFabric = null;

    /**
     * Конструктор - создание нового объекта
     * @see MyCSVReader#MyCSVReader(String, char, DictionaryFabric)
     */
    public MyCSVReader(String fileName, char separator) {
        this.fileName = fileName;
        this.separator = separator;
    }
    /**
     * Конструктор - создание нового объекта c предопределенной фабрикой
     * @see MyCSVReader#MyCSVReader(String, char)
     */
    public MyCSVReader(String fileName, char separator, DictionaryFabric csvFabric) {
        this.fileName = fileName;
        this.separator = separator;
        this.csvFabric = csvFabric;
    }

    /**
     * Открывает файл, а именно заполняет поле {@link MyCSVReader#reader}
     * @throws FileNotFoundException
     */
    @SuppressWarnings( "deprecation" )
    private void openFile() throws FileNotFoundException {
        InputStream in = getClass().getClassLoader().getResourceAsStream(fileName);
        reader = in == null ? null : new CSVReader(new InputStreamReader(in), separator);
        if (reader == null) {
            throw new FileNotFoundException(fileName);
        }
    }

    /**
     * Основная процедура чтения файла.
     * @return строки csv файла в словаре, ключи которого
     * соответсвуют полям заголовка из файла
     */
    public List<Map<String, Object>> readCSV() {
        ArrayList<Map<String, Object>> csvList = new ArrayList<>();
        try {
            if (reader == null)
                openFile();

            String[] nextLine = reader.readNext(); // csv header
            if (nextLine == null)
                throw new IOException("File is empty!");

            if (csvFabric == null)
                csvFabric = new DictionaryFabric(nextLine);


            while ((nextLine = reader.readNext()) != null) {
                try {
                    csvList.add(csvFabric.createNewNode(nextLine));
                }
                catch (IllegalArgumentException e){
                    System.out.println("Wrong format!");
                    break;
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
        return csvList;
    }
}
