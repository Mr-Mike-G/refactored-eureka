package project1;

import java.io.FileNotFoundException;
import java.io.IOException;

public class TestApp {
	
	public static void main(String[] args) throws ExceptionError, FileNotFoundException, IOException {
		Field f=new Field("field.txt","rovers.txt");
		f.storeOutput();
	}
}