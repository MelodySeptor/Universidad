package anonymous;

public class TestAnonymous {

	/**
	 * Counter to up/down one.
	 */
	private Counter counterByOne;
	
	/**
	 * Counter to up/down/ two.
	 */
	private Counter counterByTwo;
	
	/**
	 * Constructor.
	 */
	public TestAnonymous(){
		this.counterByOne = new Counter(){
			public int increment(int number){
				return ++number;
			}
		};
		
		this.counterByTwo = new Counter(){
			public int increment(int number){
				return number+2;
			}
		};
	}
	
	/**
	 * Get counter by one.
	 * @return
	 */
	public Counter getCounterByOne(){
		return this.counterByOne;	
	}
	
	/**
	 * Get counter by two.
	 * @return
	 */
	public Counter getCounterByTwo(){
		return this.counterByTwo;
	}
	
	/**
	 * Main
	 * @param args
	 */
	public static void main(String[] args) {
		TestAnonymous tA = new TestAnonymous();
		System.out.println(Integer.toString(tA.getCounterByOne().increment(2)));
		System.out.println(Integer.toString(tA.getCounterByTwo().increment(2)));
	}

}
