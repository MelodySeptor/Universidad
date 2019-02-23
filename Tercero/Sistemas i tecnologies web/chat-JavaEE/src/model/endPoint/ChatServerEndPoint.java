package model.endPoint;

import java.io.IOException;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import javax.ejb.EJB;
import javax.websocket.OnClose;
import javax.websocket.OnMessage;
import javax.websocket.OnOpen;
import javax.websocket.Session;
import javax.websocket.server.PathParam;
import javax.websocket.server.ServerEndpoint;

import model.core.Conversation;
import model.core.ConversationsManager;
import model.core.Message;
import model.core.Operator;
import model.db.OperatorManager;

@ServerEndpoint(value="/chat/{channel}")
public class ChatServerEndPoint {
	private ConcurrentHashMap<String,Session> channelSessionMapping = new ConcurrentHashMap<>();
	@EJB
	private ConversationsManager conversationsManager;
	@EJB
	private OperatorManager operatorManager;
	
	public ChatServerEndPoint() {
	}
	
	@OnMessage
	public void handleMessage(String message, Session session) {
		Map<String,String> pathParam = session.getPathParameters();
		
		long channel/*numero 5*/, id;
		channel = Long.parseLong((pathParam.get("channel")));
		long toChannel;
		boolean hasToBeSent = true;
		String loging;
		
		//Alt + opt
		if(this.doesChannelBelongToUser(channel)) {
			Conversation conv = this.conversationsManager.getConversatonById(channel);
			toChannel = conv.getConversationID();
			long opld = toChannel;
			Operator operator = this.operatorManager.getOperatorById(conv.getOperatorID());
			
			if(operator.getCurrentConversation().getConversationID() != conv.getConversationID()) {
				hasToBeSent = false;
				conv.setChanged(true);
			} else {
				conv.setChanged(false);
			}
			
			
			loging = conv.getUserName();
			//falta meter el string de login del user
		}
		else {
			Operator currentOperator = operatorManager.getOperatorById(channel);
			
			id = currentOperator.getCurrentConversation().getConversationID();	
			toChannel = id;
			//toChannel = channel;
			loging = currentOperator.getLogin();
		}
		
		this.conversationsManager.getConversatonById(toChannel).addMessage(new Message(loging, message));
		
		if(hasToBeSent) {
			session = this.channelSessionMapping.get(toChannel + "");
			try {
				session.getBasicRemote().sendText(message);
				//System.out.println(this.conversationsManager.getConversatonById(channel).toString());
			} catch (IOException e) {
				e.printStackTrace();
			}
			//System.out.println("" + message);
		}
	}
	
	@OnOpen
	public void onOpen(Session session, @PathParam("channel") String channel) {
		String fromChannel=session.getPathParameters().get("channel");
		
		if(this.doesChannelBelongToUser(Long.parseLong(fromChannel))) {
			if(!(channelSessionMapping.containsKey(fromChannel))) 
				this.channelSessionMapping.put(fromChannel, session);
		} else {
			long id = this.conversationsManager.getOperatorManager().getOperatorById(Long.parseLong(fromChannel)).getCurrentConversation().getConversationID();
			if(!(channelSessionMapping.containsKey(id))) 
				this.channelSessionMapping.put(id+"", session);
		}
	}
	
	//NO SE SI ESTA BIEN
	@OnClose
	public void onClose(Session session, @PathParam("channel") String name) {
		this.channelSessionMapping.remove(session.getPathParameters().get("channel"));
	}
	
	private boolean doesChannelBelongToUser(Long number) {
		return this.conversationsManager.containsConversationId(number);
	}
	
	private void sendRefreshMsgUserOpenedASession(String name) {
		//@TODO
	}

	public ConcurrentHashMap<String,Session> getChannelSessionMapping() {
		return channelSessionMapping;
	}

	public void setChannelSessionMapping(ConcurrentHashMap<String,Session> channelSessionMapping) {
		this.channelSessionMapping = channelSessionMapping;
	}

	public ConversationsManager getConversationsManager() {
		return conversationsManager;
	}

	public void setConversationsManager(ConversationsManager conversationsManager) {
		this.conversationsManager = conversationsManager;
	}

	public OperatorManager getOperatorManager() {
		return operatorManager;
	}

	public void setOperatorManager(OperatorManager operatorManager) {
		this.operatorManager = operatorManager;
	}
	
	
}
