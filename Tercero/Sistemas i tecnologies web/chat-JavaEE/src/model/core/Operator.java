package model.core;

import java.util.ArrayList;
import java.util.List;

public class Operator {

	private boolean online;
	private String login;
	private String password;
	private long id;
	private Conversation currentConversation;
	private List<Conversation> activeChats = new ArrayList<>();
	
	public Operator(long id, String login, String password) {
		this.id = id;
		this.login = login;
		this.password = password;
	}

	public boolean isOnline() {
		return online;
	}

	public void setOnline(boolean online) {
		this.online = online;
	}

	public String getLogin() {
		return login;
	}

	public void setLogin(String login) {
		this.login = login;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public Conversation getCurrentConversation() {
		return currentConversation;
	}

	public void setCurrentConversation(Conversation currentConversation) {
		this.currentConversation = currentConversation;
	}

	public List<Conversation> getActiveChats() {
		return activeChats;
	}
	
	public int getNumberOfActiveChats() {
		return this.activeChats.size();
	}

	public void addConversation(Conversation conver) {
		this.activeChats.add(conver);
	}
	
	public void setActiveChats(List<Conversation> activeChats) {
		this.activeChats = activeChats;
	}
}
