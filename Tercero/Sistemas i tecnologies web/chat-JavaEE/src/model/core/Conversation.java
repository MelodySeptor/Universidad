package model.core;

import java.util.ArrayList;
import java.util.List;

public class Conversation {
	private long conversationID;
	private long operatorID;
	private String userName;
	private List<Message> messages = new ArrayList<>();
	private boolean changed = false;
	
	public Conversation(long convID, long operID, String userName) {
		this.conversationID = convID;
		this.operatorID = operID;
		this.userName = userName;
	}
	
	public void addMessage(Message msg) {
		this.messages.add(msg);
	}
	
	public String toString() {
		String conv="";
		for(Message mess: this.messages) {
			conv = conv+mess.toString()+"\n";
		}
		return conv;
	}

	public long getConversationID() {
		return conversationID;
	}

	public void setConversationID(long conversationID) {
		this.conversationID = conversationID;
	}

	public long getOperatorID() {
		return operatorID;
	}

	public void setOperatorID(long operatorID) {
		this.operatorID = operatorID;
	}

	public String getUserName() {
		return userName;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}

	public List<Message> getMessages() {
		return messages;
	}

	public void setMessages(List<Message> messages) {
		this.messages = messages;
	}

	public boolean getChanged() {
		return changed;
	}

	public void setChanged(boolean changed) {
		this.changed = changed;
	}
}
