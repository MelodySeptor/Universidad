package model.db;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;
import java.util.Set;

import javax.annotation.PostConstruct;
import javax.ejb.Singleton;

@Singleton
public class CategoryDB {
	private Hashtable<String, List<String>> categories;
	
	public CategoryDB() {
		
	}
	
	@PostConstruct
	private void init() {
		ArrayList<String> aux = new ArrayList<>();
		this.categories = new Hashtable<String, List<String>>();
		aux.add("Especias");
		aux.add("Cosas Bonitas");
		aux.add("Azucar");
		aux.add("Sustancia X");
		this.categories.put("Supernenas", aux);
		
		ArrayList<String> aux2 = new ArrayList<>();
		aux2.add("Huevos");
		aux2.add("Patatas");
		aux2.add("Cebolla");
		aux2.add("Aceite");
		aux2.add("Sal");
		this.categories.put("Tortilla", aux2);
	}

	public Hashtable<String, List<String>> getCategories() {
		return categories;
	}

	public void setCategories(Hashtable<String, List<String>> categories) {
		this.categories = categories;
	}
	
	public Set<String> getCategories1(){
		return this.categories.keySet();
	}
	
	public List<String> getSubCategories(String category){
		return this.categories.get(category);
	}
	
	public String getFirstCategory() {
		return this.categories.keys().nextElement();
	}
}
