package exceptions;

@SuppressWarnings("serial")
public class MyException extends java.lang.Exception{

	/**
	 * Constructor.
	 */
	public MyException(){
		super();
	}
	
	/**
	 * Construcor with name.
	 * @param name
	 */
	public MyException(String name){
		super(name);
	}
}
