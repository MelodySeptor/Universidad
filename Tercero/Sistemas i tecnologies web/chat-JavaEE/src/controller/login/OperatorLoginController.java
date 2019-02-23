package controller.login;

import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.ManagedProperty;
import javax.faces.context.FacesContext;

import model.core.ConversationsManager;
import model.db.OperatorManager;

@ManagedBean
public class OperatorLoginController {
	static final String USER_NOT_EXIST="User not exist or it's incorrect.";
	@EJB
	private OperatorManager operatorManager;
	@ManagedProperty(value = "#{operatorLoginBean}")
	private OperatorLoginBean operatorLoginBean;
	
	@EJB
	private ConversationsManager convman;
	@ManagedProperty(value = "#{userLoginBean}")
	private UserLoginBean userLoginBean;
	
	public OperatorLoginController() {
		
	}
	
	
	public String verifyUser() {
		if(this.operatorManager.isARegisteredOperator(this.operatorLoginBean.getLogin(), this.operatorLoginBean.getPassword())) {
			this.operatorLoginBean.setTryConnected(false);
			this.operatorLoginBean.setLogged(true);
			this.operatorLoginBean.setOperatorId(operatorManager.getOperatorByLogin(this.operatorLoginBean.getLogin()).getId());
			return "xatOperari.xhtml";
		}
		else {
			this.operatorLoginBean.setTryConnected(true);
		}
		return"";
	}
	
	public String logout() {
		FacesContext.getCurrentInstance().getExternalContext().invalidateSession();
		this.operatorLoginBean.setTryConnected(false);
		this.operatorLoginBean.setLogged(false);
		return "index.xhtml";
	}

	public OperatorManager getOperatorManager() {
		return operatorManager;
	}

	public void setOperatorManager(OperatorManager operatorManager) {
		this.operatorManager = operatorManager;
	}

	public UserLoginBean getUserLoginBean() {
		return userLoginBean;
	}

	public void setUserLoginBean(UserLoginBean userLoginBean) {
		this.userLoginBean = userLoginBean;
	}

	public OperatorLoginBean getOperatorLoginBean() {
		return operatorLoginBean;
	}

	public void setOperatorLoginBean(OperatorLoginBean operatorLoginBean) {
		this.operatorLoginBean = operatorLoginBean;
	}

	public static String getUserNotExist() {
		return USER_NOT_EXIST;
	}
	
	
}
	