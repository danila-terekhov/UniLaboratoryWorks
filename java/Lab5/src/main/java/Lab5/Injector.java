package Lab5;

//import ncedu.annotations.SecretField;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.util.Properties;

public class Injector<T> {



    public T inject(T object, String filename) throws IOException {

        Properties prop = readPropertiesFile(filename);
        Class cl = object.getClass();
        Field[] fl = cl.getDeclaredFields();
        for(Field f: fl){
            System.out.println(f.getName());
            f.setAccessible(true);
            Annotation a = f.getAnnotation(cl);
            if (a != null) {
                

            }
        }
        return object;
    }

    public static Properties readPropertiesFile(String fileName) throws IOException {
        FileInputStream fis = null;
        Properties prop = null;
        try {
            fis = new FileInputStream(fileName);
            prop = new Properties();
            prop.load(fis);
        } catch(FileNotFoundException fnfe) {
            fnfe.printStackTrace();
        } catch(IOException ioe) {
            ioe.printStackTrace();
        } finally {
            fis.close();
        }
        return prop;
    }

}
