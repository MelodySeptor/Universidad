package containers;

public enum FruitType {
	
	/**
	 * Enums.
	 */
	ORANGE(1,"orange"),
	APPLE(2, "apple");
	
	/**
	 * ID of enum.
	 */
	private int id;
	
	/**
	 * Name of enum.
	 */
	private String name;
	
	/**
	 * Constructor.
	 * @param id
	 * @param name
	 */
	private FruitType(int id, String name){
		this.id = id;
		this.name = name;
	}
	
	/**
	 * 
	 * @return int with id.
	 */
	public int getId(){
		return this.id;
	}
	
	/**
	 * 
	 * @return String with name.
	 */
	public String getName(){
		return this.name;
	}
	
	/**
	 * @return String with name.
	 */
	@Override
	public String toString(){
		return this.name;
	}
}
