package controller.chat;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;

import model.core.Conversation;
import model.core.ConversationsManager;
import model.core.Operator;

@ManagedBean
public class Showner {
	public ConversationsManager getConversationsManager() {
		return conversationsManager;
	}

	public void setConversationsManager(ConversationsManager conversationsManager) {
		this.conversationsManager = conversationsManager;
	}
	
	public List<String> getListUsers(long idOperator) {
		List<String> listaReturn = new ArrayList<String>();
		for(Map.Entry<Long, Conversation> entry : this.conversationsManager.getConversations().entrySet()) {
			if(entry.getValue().getOperatorID() == idOperator) {
				if(!entry.getValue().getChanged()) {
					listaReturn.add(entry.getValue().getUserName());
				} else {
					listaReturn.add("#" + entry.getValue().getUserName());
				}
				//System.out.println("." + entry.getValue().getUserName());
			}
		}
		return listaReturn;
	}
	
	public void changeConv(long idOperator, String name) {
		String nameUsed = name;
		for(Conversation entry : this.conversationsManager.getOperatorManager().getOperatorById(idOperator).getActiveChats()) {
			if(name.contains("#")) {
				nameUsed = name.split("#")[1];
			}
			if(entry.getUserName().equalsIgnoreCase(nameUsed)) {
				entry.setChanged(false);
				this.conversationsManager.getOperatorManager().getOperatorById(idOperator).setCurrentConversation(entry);
			}
		}
	}

	@EJB
	ConversationsManager conversationsManager;

}
