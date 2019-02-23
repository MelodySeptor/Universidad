package controller.chat;

import java.util.List;
import java.util.Map;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;

import model.core.Conversation;
import model.core.Operator;


@ManagedBean
@SessionScoped
public class OperatorChatBean {

	private String history;
	private ConversationDetails currentConversation;
	private List<ConversationDetails> conversations;
	
	public OperatorChatBean() {
		
	}

	public String getHistory() {
		return history;
	}

	public void setHistory(String history) {
		this.history = history;
	}

	public ConversationDetails getCurrentConversation() {
		return currentConversation;
	}

	public void setCurrentConversation(ConversationDetails currentConversation) {
		this.currentConversation = currentConversation;
	}

	public List<ConversationDetails> getConversations() {
		return conversations;
	}

	public void setConversations(List<ConversationDetails> conversations) {
		this.conversations = conversations;
	}
	
	
}
