package model;

import java.util.Map.Entry;

public class TestFactory {
	
	public static void main(String[] args) {
		for (Entry<String, User> entry : UsersDBFactory.getUsersDB().getUsers().entrySet()){
			System.out.println(entry.getValue());			
		}
	}	
}
