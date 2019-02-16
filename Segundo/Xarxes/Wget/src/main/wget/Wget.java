package main.wget;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import url.reader.UrlReader;

public class Wget {
	
	private static ArrayList<String> urls;
	private static ArrayList<String> main_args;
	private static String file_name;
	
	
	private static boolean parseArgs(String[] args) {
		
		for(int i = 0; i < args.length; i++) {
			switch(args[i]) {
				case "-f": 
					main_args.add("-f");
					if(i+1 > args.length) {
						System.err.println("parameter -f doesn't contain a file name");
						return false;
					}
					if(!new File("./" + args[i+1]).exists()) {
						System.err.println("url file : " + args[i+1] + " doesnt' exists");
						return false;
					}
					file_name = args[++i];
					break;
				case "-a":
					main_args.add("-a");
					break;
				case "-z":
					main_args.add("-z");
					break;
				case "-gz":
					main_args.add("-gz");
					break;
				default:
					System.err.println("invalid parameter: " + args[i]);
					return false;
			}
		}
		return true;
	}
	
	/*
	 * Read form text file and put all on the ArrayList urls
	 */
	private static boolean readFile() {
		urls = new ArrayList<String>();

		try {
			BufferedReader in_buffer = new BufferedReader(new FileReader(file_name));
			String current_line = in_buffer.readLine();

			while(current_line != null) {
				urls.add(current_line);
				current_line = in_buffer.readLine();
			}
			in_buffer.close();
			return true;
		} catch(FileNotFoundException e) {
			System.err.println(e.getMessage());
		} catch(IOException e) {
			System.err.println(e.getMessage());
		}
		return false;
	}

	/*
	 * Create-start-join threads
	 */
	private static void use_threads() {
		UrlReader[] url_reader = new UrlReader[urls.size()];

		// Create
		for(int i = 0; i < urls.size(); i++) {
			url_reader[i] = new UrlReader(main_args, urls.get(i));
			url_reader[i].start();
		}
		// End
		for(int i = 0; i < urls.size(); i++) {
			try {
				url_reader[i].join();
			} catch(InterruptedException e) {
				// e.printStackTrace();
				System.err.println(e.getMessage());
			}
		}
	}

	/*
	 * Main
	 */
	public static void main(String[] args) {
		if(parseArgs(args)) {
			if(readFile()) {
				System.out.println("Read File: CORRECT");
				use_threads();
			}
		}
	}

}
