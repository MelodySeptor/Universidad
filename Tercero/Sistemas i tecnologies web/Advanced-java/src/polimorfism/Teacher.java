package polimorfism;

import java.util.ArrayList;
import java.util.List;

/**
 * Class who contains Teacher information and
 * students who has that teacher.
 * Extends person.
 */
public class Teacher extends Person{
	List<Student> students;
	
	/**
	 * Constructor without students.
	 * @param name
	 * @param age
	 */
	public Teacher(String name, int age) {
		super(name, age);
		this.students = new ArrayList<>();
	}
	
	/**
	 * Constructor with students.
	 * @param name
	 * @param age
	 * @param students
	 */
	public Teacher(String name, int age, ArrayList<Student> students){
		super(name, age);
		this.students = students;
	}
	
	/**
	 * Add new student for teacher.
	 * @param student
	 */
	public void addStudent(Student student){
		this.students.add(student);
	}
	
	/**
	 * @return String with teacher data and all students data.
	 */
	@Override
	public String toString(){
		String result = super.toString();
		
		for (Student stud: this.students){
			result = result + " " + stud.toString(); 
		}
		return result;
	}

}
