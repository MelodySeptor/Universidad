package controller.login;

import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;

@ManagedBean
@SessionScoped
public class OperatorLoginBean {

	private String login;
	private String password;
	private boolean logged;
	private long operatorId;
	private boolean tryConnected = false;
	
	public OperatorLoginBean() {
		
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

	public boolean isLogged() {
		return logged;
	}

	public void setLogged(boolean logged) {
		this.logged = logged;
	}

	public long getOperatorId() {
		return operatorId;
	}

	public void setOperatorId(long operatorId) {
		this.operatorId = operatorId;
	}

	public boolean isTryConnected() {
		return tryConnected;
	}

	public void setTryConnected(boolean tryConnected) {
		this.tryConnected = tryConnected;
	}
	
}
