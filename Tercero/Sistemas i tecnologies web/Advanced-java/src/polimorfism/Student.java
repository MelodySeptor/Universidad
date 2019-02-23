package polimorfism;

import java.util.ArrayList;

/**
 * Class who contains all student information.
 * Extends Person.
 */
public class Student extends Person{
	/**
	 * ArrayList of String with subjects of Student.
	 */
	private ArrayList<String>subjects;
	
	/**
	 * Constructor without subjects.
	 * @param name
	 * @param age
	 */
	public Student(String name, int age){
		super(name, age);
		this.subjects = new ArrayList<>();
	}
	
	/**
	 * Constructor with subjects.
	 * @param name
	 * @param age
	 */
	public Student(String name, int age, ArrayList<String> subjects){
		super(name, age);
		this.subjects = subjects;
	}
	
	/**
	 * Add new subject.
	 * @param subject
	 */
	public void addSubject(String subject){
		this.subjects.add(subject);
	}
	
	/**
	 * @return String with information of Person and subjects.
	 */
	@Override
	public String toString(){
		String result = super.toString();
		
		for(String subj: this.subjects){
			result = result + " "+ subj;
		}
		
		return result;
	}
}
