package url.reader;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.util.ArrayList;

public class UrlReader extends Thread {
	
	private ArrayList<String> args;
	private String url;
	private InputStream in_stream;

	/*
	 * Constructor
	 */
	public UrlReader(ArrayList<String> args, String url) {
		try {
			this.in_stream = new URL(url).openStream();
		} catch (IOException e) {
			// e.printStackTrace();
			System.err.println(e.getMessage());
		}
		this.args = args;
		this.url = url;
	}
	
	/*
	 * Add to ArraList args of all posible web extensions without implicit file
	 * extension
	 */
	private void addUrlsNoExtension(ArrayList<String> text_ext) {
		text_ext.add(".es");
		text_ext.add(".com");
		text_ext.add(".cat");
		text_ext.add(".org");
		text_ext.add(".net");
	}

	/*
	 * Evaluate if url is a text DISABLED
	 */
	private boolean isText() {
		ArrayList<String> text_ext = new ArrayList<String>();
		addUrlsNoExtension(text_ext);
		return !text_ext.contains(this.url.substring(this.url.lastIndexOf('.')));
	}

	/*
	 * Get name of file to download
	 */
	private synchronized String getNameFile() {
		ArrayList<String> text_ext = new ArrayList<String>();
		addUrlsNoExtension(text_ext);
		String name_file = this.url.substring(this.url.lastIndexOf('.'));

		if (text_ext.contains(name_file))
			return "index" + Thread.currentThread().getId() + ".html";

		name_file = this.url.substring(this.url.lastIndexOf('/'));
		return name_file.substring(1, name_file.length());
	}

	/*
	 * Get all of the content from the url
	 */
	private void getContentUrl() {
		try {
			FileOutputStream out_stream = new FileOutputStream(getNameFile());
			int byte_web = 0;

			byte_web = this.in_stream.read();
			while(byte_web != -1) {

				if(isText() && this.args.contains("-a")) {
					// Aplicar filtro si es texto y tiene -a
				}
				out_stream.write(byte_web);
				byte_web = this.in_stream.read();
			}
			out_stream.close();
		} catch (FileNotFoundException e) {
			System.err.println(e.getMessage());
			// e.printStackTrace();
		} catch (IOException e1) {
			System.err.println(e1.getMessage());
			// e1.printStackTrace();
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Thread#run()
	 */
	@Override
	public void run() {
		this.getContentUrl();
	}
}
