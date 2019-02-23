package controller.login;

import java.util.List;
import java.util.Set;

import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ManagedProperty;
import javax.faces.event.ValueChangeEvent;

import model.core.ConversationsManager;
import model.db.CategoryDB;

@ManagedBean
public class UserLoginController {

	@EJB
	private CategoryDB categoryDB;
	@EJB
	private ConversationsManager convManager;
	@ManagedProperty(value = "#{userLoginBean}")
	private UserLoginBean userLoginBean;
	
	public UserLoginController() {
		
	}
	
	public Set<String> getCategories(){
		return this.categoryDB.getCategories1();
	}
	
	public List<String> getSubCategories() {
		return this.categoryDB.getSubCategories(this.userLoginBean.getSelectedCategory());
	}
	
	//NO SE SI EST BE
	//@TODO
	public String createConversation() {
		/*this.convManager.createConversation(userLoginBean.getName());
		return "xatUser.xhtml";
		*/
		boolean acceder = true; //TODO
		//Probablemente querremos establecer condiciones en esta creación
		if (acceder) {
			this.userLoginBean.setConversationId(this.convManager.createConversation(this.userLoginBean.getName())); //De momento le pasamos el nombre
			return "xatUser.xhtml";
		} else {
			return "";
		}
	}
	
	@PostConstruct
	private void init() {
		this.userLoginBean.setSelectedCategory(this.categoryDB.getFirstCategory());
	}
	
	public void categoryChanged(ValueChangeEvent value) {
		this.userLoginBean.setSelectedCategory(value.getNewValue().toString());
	}

	public void setCategoryDB(CategoryDB categoryDB) {
		this.categoryDB = categoryDB;
	}

	public ConversationsManager getConvManager() {
		return convManager;
	}

	public void setConvManager(ConversationsManager convManager) {
		this.convManager = convManager;
	}

	public UserLoginBean getUserLoginBean() {
		return userLoginBean;
	}

	public void setUserLoginBean(UserLoginBean userLoginBean) {
		this.userLoginBean = userLoginBean;
	}

	public CategoryDB getCategoryDB() {
		return categoryDB;
	}
}
