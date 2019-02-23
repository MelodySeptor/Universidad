package model.db;

import java.util.Hashtable;

import javax.annotation.PostConstruct;
import javax.ejb.Singleton;

import model.core.Operator;

@Singleton
public class OperatorDB {

	private Hashtable<Long,Operator> operators;
	
	public OperatorDB() {
		
	}
	
	@PostConstruct
	private void init() {
		this.operators = new Hashtable<Long, Operator>();
		this.operators.put((long) 12345, new Operator(12345,"admin","admin"));
	}

	public Hashtable<Long, Operator> getOperators() {
		return operators;
	}

	public void setOperators(Hashtable<Long, Operator> operators) {
		this.operators = operators;
	}
	
}
