package controller.chat;

import java.util.ArrayList;

import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ManagedProperty;
import javax.faces.bean.RequestScoped;
import javax.faces.bean.SessionScoped;

import controller.login.OperatorLoginBean;
import model.core.Conversation;
import model.core.ConversationsManager;
import model.core.Operator;
import model.db.OperatorManager;

@ManagedBean
@RequestScoped
public class OperatorChatController {

	@EJB
	private OperatorManager operatorManager;
	@EJB
	private ConversationsManager conversationsManager;
	@ManagedProperty(value = "#{operatorLoginBean}")
	private OperatorLoginBean operatorLoginBean;
	@ManagedProperty(value = "#{operatorChatBean}")
	private OperatorChatBean operatorChatBean;
	
	
	public OperatorChatController() {
		
	}
	
	//NO SE SI ESTA BIEN
	public void refreshConversations() {
		ArrayList<ConversationDetails> conversationDetailsList = new ArrayList<>();
		Operator operator = getOperator();
		
		//Opcional
		if(this.operatorChatBean.getCurrentConversation()==null) {
			this.operatorChatBean.setCurrentConversation(ConversationDetails.getSelectedConversationDetailsInstance(
					operator.getCurrentConversation().getConversationID(), operator.getCurrentConversation().getUserName()));
		}
		
		//Loop and alt
		ConversationDetails auxConv;
		for(Conversation conv : operator.getActiveChats()) {
			if(this.operatorChatBean.getCurrentConversation().getConversationID()==conv.getConversationID()) {
				auxConv = this.operatorChatBean.getCurrentConversation();
			}
			else {
				auxConv = ConversationDetails.getUnselectedConversationDetailsInstance(conv.getConversationID(), conv.getUserName());
			}
			
			conversationDetailsList.add(auxConv);
		}
		this.operatorChatBean.setConversations(conversationDetailsList);
	}
	
	//NO SE SI ESTA BIEN
	public void changeToConversation(ConversationDetails conv) {
		this.operatorChatBean.getCurrentConversation().switchLinkStyle();

		ConversationDetails convDet = conv;
		convDet.switchLinkStyle();

		this.operatorChatBean.setCurrentConversation(convDet);
		getOperator().setCurrentConversation(this.conversationsManager.getConversatonById(convDet.getConversationID()));
		
		this.operatorChatBean.setHistory(this.conversationsManager.getConversatonById(convDet.getConversationID()).toString());
	}
	
	//NO SE SI ESTA BIEN
	private Operator getOperator() {
		return operatorManager.getOperatorById(operatorLoginBean.getOperatorId());
	}

	public OperatorManager getOperatorManager() {
		return operatorManager;
	}

	public void setOperatorManager(OperatorManager operatorManager) {
		this.operatorManager = operatorManager;
	}

	public ConversationsManager getConversationsManager() {
		return conversationsManager;
	}

	public void setConversationsManager(ConversationsManager conversationsManager) {
		this.conversationsManager = conversationsManager;
	}

	public OperatorLoginBean getOperatorLoginBean() {
		return operatorLoginBean;
	}

	public void setOperatorLoginBean(OperatorLoginBean operatorLoginBean) {
		this.operatorLoginBean = operatorLoginBean;
	}

	public OperatorChatBean getOperatorChatBean() {
		return operatorChatBean;
	}

	public void setOperatorChatBean(OperatorChatBean operatorChatBean) {
		this.operatorChatBean = operatorChatBean;
	}
	
}
