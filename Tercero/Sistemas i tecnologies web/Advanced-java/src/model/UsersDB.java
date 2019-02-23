package model;

import java.util.HashMap;
import java.util.Map;

public class UsersDB {
	private Map<String, User> users;
	
	public UsersDB(){ 
		this.users = new HashMap<String, User>();
		this.init();
	}
	
	private void init(){
		users.put("Mar", new User(1,"Mar"));
		users.put("Pol", new User(2,"Pol"));		
	}

	public Map<String, User> getUsers() {
		return this.users;
	}
		
}
