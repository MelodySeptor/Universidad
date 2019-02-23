package generics;

/**
 * Test for two containers.
 */
public class TestGenerics {

	/**
	 * Constructor.
	 */
	public TestGenerics(){
		
	}
	
	/**
	 * Test container class.
	 */
	private static void testContainer(){
		Container<String> contA = new Container<>();
		Container <Integer> contB = new Container<>();
		
		contA.addElement("Hola");
		contA.addNextElement("Mundo");
		contB.addElement(1);
		contB.addNextElement(5);
		
		System.out.println(contA.toString());
		System.out.println(contB.toString());
	}
	
	/**
	 * Test two tuple class.
	 */
	private static void testTwoTuple(){
		TwoTuple<String, Integer> tupleA = new TwoTuple<>("Hola", 3);
		TwoTuple<Boolean, Double> tupleB = new TwoTuple<>(true, 3.4);
		
		System.out.println(tupleA.toString());
		System.out.println(tupleB.toString());
	}
	
	/**
	 * Main
	 * @param args
	 */
	public static void main(String [] args){
		testContainer();
		testTwoTuple();
	}
}
