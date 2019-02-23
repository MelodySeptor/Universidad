package controller.chat;

public class ConversationDetails {

	private long conversationID;
	private String user;
	private String conversationLinkStyle;
	private final static String UNSELECTED_CHAT_STYLE = "notSelectedChat";
	private final static String SELECTED_CHAT_STYLE="selectedChat";
	
	private ConversationDetails(long id, String user, String link) {
		this.conversationID = id;
		this.user = user;
		this.conversationLinkStyle = link;
	}
	
	public static ConversationDetails getUnselectedConversationDetailsInstance(long id, String name) {
		return new ConversationDetails(id, name, UNSELECTED_CHAT_STYLE);
	}
	
	public static ConversationDetails getSelectedConversationDetailsInstance(long id, String name) {
		return new ConversationDetails(id, name, SELECTED_CHAT_STYLE);
	}
	
	public void switchLinkStyle() {
		if(this.conversationLinkStyle.equalsIgnoreCase(UNSELECTED_CHAT_STYLE)) {
			this.conversationLinkStyle = SELECTED_CHAT_STYLE;
		}
		else {
			this.conversationLinkStyle = UNSELECTED_CHAT_STYLE;
		}
	}

	public long getConversationID() {
		return conversationID;
	}

	public void setConversationID(long conversationID) {
		this.conversationID = conversationID;
	}

	public String getUser() {
		return user;
	}

	public void setUser(String user) {
		this.user = user;
	}

	public String getConversationLinkStyle() {
		return conversationLinkStyle;
	}

	public void setConversationLinkStyle(String conversationLinkStyle) {
		this.conversationLinkStyle = conversationLinkStyle;
	}

	public String getUNSELECTED_CHAT_STYLE() {
		return UNSELECTED_CHAT_STYLE;
	}

	public String getSELECTED_CHAT_STYLE() {
		return SELECTED_CHAT_STYLE;
	}
}
