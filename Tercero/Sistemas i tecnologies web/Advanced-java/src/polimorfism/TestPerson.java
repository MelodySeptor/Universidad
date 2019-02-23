package polimorfism;

/**
 * Test class for person.
 *
 */
public class TestPerson {

	/**
	 * Constructor
	 */
	public TestPerson(){
		
	}
	
	/**
	 * Main 
	 * @param args
	 */
	public static void main(String [] args){
		Person person = new Person("Test", 22);
		person.addAddress("Spain", "Barcelona","Isabel de Villena", 66);	
		System.out.println(person.toString());
		
		Person.Address addr = person.new Address("Spain", "Barcelona", "Sant Jaume", 134);
		System.out.println(addr.toString());
		
		person.addAddress(addr);
		person.printAddresses();
	}
}
