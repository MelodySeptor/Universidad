package module;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;
import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.ejb.Startup;
import javax.ejb.Stateful;

@Singleton
@Startup
public class AdderSingleton2Bean {

	private int value;
	
	@PostConstruct
	private void init() {
		DateFormat df = new SimpleDateFormat("hh:mm:ss");
		System.out.println(df.format(System.currentTimeMillis()) + " - " + "Creat el Bean: "+this);
	}
	
	@PreDestroy
	private void destroy() {
		DateFormat df = new SimpleDateFormat("hh:mm:ss");
		System.out.println(df.format(System.currentTimeMillis()) + " - " + "Destruint el Bean: "+this);
	}

	public int getValue() {
		return value;
	}

	public void setValue(int value) {
		this.value = value;
	}
	
	/**
	* Method that incerments in one unit the value property.
	* @return the new value of the value property.
	*/
	public int add() {
		return ++this.value;
	}
	
	/**
	* Method that sets to 0 the value property.
	* @return the new value of the value property.
	*/
	private int reset() {
		return (this.value = 0);
	}
}
