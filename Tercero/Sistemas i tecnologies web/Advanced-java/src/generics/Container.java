package generics;

/**
 * Class who contains something.
 * @param <T>
 */
public class Container<T> {
	/**
	 * Element.
	 */
	private T element;
	
	/**
	 * Next element.
	 */
	private T nextElement ;
	
	/**
	 * Constructor.
	 */
	public Container(){
		
	}
	
	/**
	 * Add value of this.element.
	 * @param element
	 */
	public void addElement(T element){
		this.element = element;
	}
	
	/**
	 * Add value of this.nextElement.
	 * @param nextElement
	 */
	public void addNextElement(T nextElement){
		this.nextElement = nextElement;
	}
	
	/**
	 * Get element.
	 * @return T
	 */
	public T getElement(){
		return this.element;
	}
	
	/**
	 * Get next element.
	 * @return T
	 */
	public T getNextElement(){
		return this.nextElement;
	}
	
	/**
	 * @return element and nextElement with string.
	 */
	public String toString(){
		return this.element.toString() + " " + this.nextElement.toString();
	}
}
