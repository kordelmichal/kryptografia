package filesHandling;

import java.io.*;

public class FilesHandler {

    private FileOutputStream fileOutputStream;
    private FileInputStream fileInputStream;
    public FilesHandler(String openPath, String savePath, boolean append){
        this.fileInputStream = openFileToRead(openPath);
        this.fileOutputStream = openFileToWrite(savePath, append);
    }

    public synchronized byte[] read(int filesize){


        byte[] fromFile = new byte[filesize];
        int summary=0;
        int temporary=0;

        try {

            while((temporary=fileInputStream.read(fromFile))!=-1){
                summary+=temporary;
            }
            System.out.println("Read "+summary+" bytess");

        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return fromFile;
    }

    public synchronized void write(byte[] dataToFile){
        try {
            fileOutputStream.write(dataToFile);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private FileInputStream openFileToRead(String pathToFile){
        if(pathToFile==null){
            return null;
        }
        File file = new File(pathToFile);
        try {
            return new FileInputStream(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }

    private FileOutputStream openFileToWrite(String pathToFile, boolean append){
        File file = new File(pathToFile);
        try {
            return new FileOutputStream(file, append);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }
}
