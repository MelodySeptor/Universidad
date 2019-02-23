package exceptions;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class TestExceptions {
	
	/**
	 * Constructor.
	 */
	public TestExceptions(){
		
	}
	
	/**
	 * Throws.
	 * @param fileName
	 * @throws FileNotFoundException
	 * @throws IOException
	 */
	private static void processFile(String fileName) throws FileNotFoundException,IOException{
		FileReader fr = new FileReader(fileName);
		BufferedReader br = new BufferedReader(fr);

		String sCurrentLine;

		while ((sCurrentLine = br.readLine()) != null) {
			System.out.println(sCurrentLine);
		}
		br.close();
	}
	
	/**
	 * Exception on open and write.
	 * @param fileName
	 */
	private static void processFile2(String fileName){
		try{
			FileReader fr = new FileReader(fileName);
			BufferedReader br = new BufferedReader(fr);

			String sCurrentLine;

			while ((sCurrentLine = br.readLine()) != null) {
				System.out.println(sCurrentLine);
			}
			br.close();
		}catch(FileNotFoundException e1){
			System.err.println("ERROR: No s'ha trobat el fitxer.");
		}catch(IOException e1){
			System.err.println("ERROR: Escritura o lectura fallida.");
		}
	}
	
	/**
	 * Custom Exception.
	 * @param fileName
	 * @throws MyException
	 * @throws IOException 
	 */
	private static void processFile3(String fileName) throws MyException{

		try{
		FileReader fr = new FileReader(fileName);
		BufferedReader br = new BufferedReader(fr);

		String sCurrentLine;

		while ((sCurrentLine = br.readLine()) != null) {
			System.out.println(sCurrentLine);
		}
		br.close();
		
		}catch(FileNotFoundException e1){
			throw new MyException("ERROR: No es troba el fitxer");
		}catch(IOException e1){
			throw new MyException("ERROR: Escritura o lectura fallida.");
		}
	}
	
	/**
	 * Use finally.
	 * @param fileName
	 */
	private static void processFile4(String fileName){
		try{
			FileReader fr = new FileReader(fileName);
			BufferedReader br = new BufferedReader(fr);

			String sCurrentLine;

			while ((sCurrentLine = br.readLine()) != null) {
				System.out.println(sCurrentLine);
			}
			br.close();
		}catch(FileNotFoundException e1){
			System.err.println("ERROR: No s'ha trobat el fitxer.");
		}catch(IOException e1){
			System.err.println("ERROR: Escritura o lectura fallida.");
		}finally{
			System.out.println("Thank you for using our tool.");
		}
	}

	/**
	 * Main
	 * @param args
	 * @throws FileNotFoundException
	 * @throws IOException
	 * @throws MyException
	 */
	public static void main(String[] args) throws FileNotFoundException, IOException, MyException {
		processFile("test.exe");
		processFile2("test.exe");
		processFile3("test.exe");
		processFile4("test.exe");
	}

}
