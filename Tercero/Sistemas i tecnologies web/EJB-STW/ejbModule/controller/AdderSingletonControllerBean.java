package controller;

import javax.annotation.PostConstruct;
import javax.ejb.EJB;
import javax.ejb.Singleton;
import javax.ejb.Startup;

import module.AdderBean;
import module.AdderSingletonBean;

@Singleton
@Startup
public class AdderSingletonControllerBean {
//STARTUP AL CREAR AL INICI, SI ES TREU NO FUNCIONA A NO SER QUE S'INJECTI.
	@EJB
	AdderSingletonBean adder1;

	@EJB
	AdderSingletonBean adder2;
	
	@PostConstruct
	private void init() {
		System.out.println(this.getClass().toString());
		
		System.out.println(adder1.getValue());
		adder1.add();
		adder1.add();
		System.out.println(adder1.getValue());
		
		System.out.println(adder2.getValue());
		adder2.add();
		adder2.add();
		System.out.println(adder2.getValue());
		
		System.out.println(adder1.getValue());
		adder1.add();
		adder1.add();
		System.out.println(adder1.getValue());
	}
}
