package model;

public class User {
	private int id;
	private String login;
	
	public User(int id, String login) {	
		this.id = id;
		this.login = login;
	}
	
	public String toString(){
		return id + " " + this.login;
	}
}
