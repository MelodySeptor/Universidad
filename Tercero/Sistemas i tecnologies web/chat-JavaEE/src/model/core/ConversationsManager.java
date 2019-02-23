package model.core;

import java.util.Hashtable;
import java.util.Map;

import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.ejb.Stateless;
import javax.faces.bean.ManagedProperty;

import model.db.OperatorManager;


@Singleton
public class ConversationsManager {

	private static long lastConversation;
	private Hashtable<Long, Conversation> conversations;
	@EJB
	private OperatorManager operatorManager;
	
	public ConversationsManager() {
	}
	
	@PostConstruct
	private void init() {
		setLastConversation(System.currentTimeMillis());
		this.conversations = new Hashtable<Long, Conversation>();
	}
	
	public String getConvForWeb(long id) {
		String returnInErrorCase = "";
		if(this.containsConversationId(id)) {
			for(Map.Entry<Long, Conversation> entry : this.conversations.entrySet()) {
				if(entry.getValue().getConversationID() == id) {
					return entry.getValue().toString();
				}
			}
			return returnInErrorCase;
		} else {
			Operator operatorFake = this.operatorManager.getOperatorById(id);
			for(Map.Entry<Long, Conversation> entry : this.conversations.entrySet()) {
				if(entry.getValue().getConversationID() == operatorFake.getCurrentConversation().getConversationID()) {
					return entry.getValue().toString();
				}
			}
			return returnInErrorCase;
		}
	}
	
	private static synchronized long generateConversationID() {
		lastConversation++;
		return lastConversation;
	}
	
	public long createConversation(String userName) { 
		long id = this.operatorManager.getOperatorAvaliable();
		Conversation conv = new Conversation(generateConversationID(), id, userName);
		this.operatorManager.getOperatorById(id).addConversation(conv);
		if(this.operatorManager.getOperatorById(id).getActiveChats().size() == 1) {
			this.operatorManager.getOperatorById(id).setCurrentConversation(conv);
		}
		this.conversations.put(conv.getConversationID(), conv);
		return conv.getConversationID();
	}
	
	public Conversation getConversatonById(long id) {
		for(Map.Entry<Long, Conversation> entry : this.conversations.entrySet()) {
			if(entry.getKey()==id) {
				return entry.getValue();
			}
		}
		return new Conversation(0,1,"Not Exist");
	}
	
	public boolean containsConversationId(long id) {
		return this.conversations.containsKey(id) ? true:false;
	}

	public Hashtable<Long, Conversation> getConversations() {
		return conversations;
	}

	public void setConversations(Hashtable<Long, Conversation> conversations) {
		this.conversations = conversations;
	}

	public OperatorManager getOperatorManager() {
		return operatorManager;
	}

	public void setOperatorManager(OperatorManager operatorManager) {
		this.operatorManager = operatorManager;
	}

	public static long getLastConversation() {
		return lastConversation;
	}

	public static void setLastConversation(long lastConversation) {
		ConversationsManager.lastConversation = lastConversation;
	}
}
