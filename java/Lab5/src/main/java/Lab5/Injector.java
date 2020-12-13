package Lab5;

//import ncedu.annotations.SecretField;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.Properties;

public class Injector<T> {



    public T inject(T object, String filename) throws IOException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, ClassNotFoundException {

        Properties prop = readPropertiesFile(filename);
        Class cl = object.getClass();
        Field[] fl = cl.getDeclaredFields();

        Class an = AutoInjectable.class;

        for(Field f: fl){
            System.out.println(f.getName());
            f.setAccessible(true);
            Annotation a = f.getAnnotation(an);
            if (a != null) {
                String st=(String) f.getType().getName();
                st = prop.getProperty(st);

                Class<?> c = Class.forName(st);
                Constructor<?> tmp = c.getDeclaredConstructors()[0];
                Object tmp2 = tmp.newInstance();
                f.set(object, tmp2);


            }
        }
        return object;
    }

    public Properties readPropertiesFile(String fileName) throws IOException {
        InputStream fis = null;
        Properties prop = null;
        try {
            prop = new Properties();
            fis = new FileInputStream(fileName);
            if (fis != null) {
                prop.load(fis);
            } else {
                throw new FileNotFoundException("property file '" + fileName + "' not found in the classpath");
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            fis.close();
        }

        return prop;
    }

}
