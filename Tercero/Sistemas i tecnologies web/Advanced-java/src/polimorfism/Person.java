package polimorfism;

import java.util.ArrayList;
import java.util.List;

/**
 * Class who contains all data of Person, and
 * has a inner class called Address.
 *
 */
public class Person {
	/**
	 * List of address for one person
	 */
	private List<Person.Address> addresses;
	
	/**
	 * String with name.
	 */
	private String name;
	
	/**
	 * Integer with age.
	 */
	private int age;
	
	/**
	 * Constructor
	 * @param name
	 * @param age
	 */
	public Person(String name, int age){
		this.addresses = new ArrayList<Person.Address>();
		this.name = name;
		this.age = age;
	}
	
	/**
	 * Add address without pass Address type variable.
	 * @param country
	 * @param province
	 * @param street
	 * @param number
	 */
	public void addAddress(String country, String province, String street, int number){
		this.addresses.add(new Person.Address(country,province,street,number));
	}
	
	/**
	 * Add address with Adress variable type.
	 * @param address
	 */
	public void addAddress(Address address){
		this.addresses.add(address);
	}
	
	/**
	 * Print all address of person.
	 */
	public void printAddresses(){
		for (Person.Address addr : this.addresses){
			System.out.println(addr.toString());
		}
	}
	
	/**
	 * @return String with name and age.
	 */
	@Override
	public String toString(){
		return this.name+" "+Integer.toString(this.age);
	}
	
	/**
	 * Inner class Adress.
	 * Contains adress.
	 */
	public class Address{
		
		/**
		 * String whit country.
		 */
		private String country;
		/**
		 * String whit province.
		 */
		private String province;
		/**
		 * String whit street.
		 */
		private String street;
		/**
		 * Integer with number.
		 */
		private int number;
		
		/**
		 * Constructor.
		 * @param country
		 * @param province
		 * @param street
		 * @param number
		 */
		public Address(String country, String province, String street, int number){
			this.country = country;
			this.province = province;
			this.street = street;
			this.number = number;
		}
		
		/**
		 * @return String with street, number, province and country.
		 */
		@Override
		public String toString(){
			return this.street+" "+Integer.toString(this.number)+" "+this.province+" "+this.country;
		}
		
	}

}


