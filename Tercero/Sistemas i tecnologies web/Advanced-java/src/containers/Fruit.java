package containers;

public class Fruit {

	/**
	 * Type of Fruit.
	 */
	private FruitType type;
	
	/**
	 * Counter for fruits.
	 */
	private static int counter=0;
	
	/**
	 * ID of object.
	 */
	private int id;
	
	/**
	 * Construct.
	 * @param type
	 */
	public Fruit(FruitType type){
		this.type = type;
		this.id = (type.getId()*10)+counter;
		counter++;
	}
	
	/**
	 * @return name, ID and counter.
	 */
	public String toString(){
		return type.getName() + "::" + Integer.toString(this.id) ;
	}
}
