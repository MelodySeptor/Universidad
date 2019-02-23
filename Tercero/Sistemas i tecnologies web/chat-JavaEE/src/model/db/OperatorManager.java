package model.db;

import java.util.Map;

import javax.ejb.EJB;
import javax.ejb.LocalBean;
import javax.ejb.Singleton;
import javax.ejb.Startup;
import javax.ejb.Stateless;

import model.core.Operator;

@Stateless
public class OperatorManager {

	@EJB
	private OperatorDB operatorDB;
	
	public OperatorManager() {
		
	}
	
	public boolean isARegisteredOperator(String login, String pass) {
		for(Map.Entry<Long, Operator> entry : this.operatorDB.getOperators().entrySet()) {
			if(entry.getValue().getLogin().equals(login) && entry.getValue().getPassword().equals(pass)) {
				return true;
			}
		}
		return false;
	}
	
	public long getOperatorAvaliable() {
		for(Map.Entry<Long, Operator> entry : this.operatorDB.getOperators().entrySet()) {
			if(entry.getValue().getNumberOfActiveChats()<=3) {
				return entry.getValue().getId();
			}
		}
		return 0;
	}
	
	public Operator getOperatorByLogin(String login) {
		for(Map.Entry<Long, Operator> entry : this.operatorDB.getOperators().entrySet()) {
			if(entry.getValue().getLogin().equals(login)) {
				return entry.getValue();
			}
		}
		return new Operator(0,"Not exist","");
	}
	
	public Operator getOperatorById(long id) {
		for(Map.Entry<Long, Operator> entry : this.operatorDB.getOperators().entrySet()) {
			if(entry.getValue().getId()==id) {
				return entry.getValue();
			}
		}
		return new Operator(0,"Not exist","");
	}

	public OperatorDB getOperatorDB() {
		return operatorDB;
	}

	public void setOperatorDB(OperatorDB operatorDB) {
		this.operatorDB = operatorDB;
	}
}
