package model.core;

public class Message {
	private String message;
	private String from;
	static final String REFRESH_MSG = "Loading...";
	
	public Message(String from, String msg) {
		this.setMessage(msg);
		this.setFrom(from);
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}

	public String getFrom() {
		return from;
	}

	public void setFrom(String from) {
		this.from = from;
	}
	
	public String toString() {
		return this.from + " > " + this.message + "\n";
	}
	
}
