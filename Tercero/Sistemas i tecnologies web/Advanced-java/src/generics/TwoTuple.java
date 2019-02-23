package generics;

/**
 * Class who contains a tuple of objects.
 * @param <A>
 * @param <B>
 */
public class TwoTuple<A,B> {

	/**
	 * A type.
	 */
	public A first;
	
	/**
	 * B type.
	 */
	public B second;
	
	/**
	 * Constructor.
	 * @param aElement
	 * @param bElement
	 */
	public TwoTuple(A aElement, B bElement){
		this.first = aElement;
		this.second = bElement;
	}
	
	/**
	 * @return first element plus second element.
	 */
	public String toString(){
		return this.first.toString() + " " + this.second.toString();
	}
}
