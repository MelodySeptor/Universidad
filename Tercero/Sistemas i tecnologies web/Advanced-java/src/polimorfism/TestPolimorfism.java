package polimorfism;

/**
 * Test for polimorfism.
 *
 */
public class TestPolimorfism {

	/**
	 * Constructor.
	 */
	public TestPolimorfism(){
		
	}
	
	/**
	 * Print Person object
	 * @param person
	 */
	public static void printInformation(Person person){
		System.out.println(person.toString());
	}
	/**
	 * Main 
	 * @param args
	 */
	public static void main(String [] args){
		Person lia = new Person("Lia", 23);
		//Student pep = new Person("Pep", 19); Bad heritage.
		Person ana = new Student("Ana", 20);
		Teacher ian = new Teacher("Ian", 25);

		((Student) ana).addSubject("STW");
		
		printInformation(lia);
		printInformation(ana);
		printInformation(ian);
	}
}
