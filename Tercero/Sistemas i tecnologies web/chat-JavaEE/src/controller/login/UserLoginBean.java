package controller.login;

import javax.ejb.EJB;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.SessionScoped;

import model.db.CategoryDB;

@ManagedBean
@SessionScoped
public class UserLoginBean {

	@EJB
	private CategoryDB categoryDB;
	private String name;
	private long conversationId;
	private String selectedCategory;
	private String selectedSubCategory;
	
	
	public UserLoginBean() {
	}

	public CategoryDB getCategoryDB() {
		return categoryDB;
	}

	public void setCategoryDB(CategoryDB categoryDB) {
		this.categoryDB = categoryDB;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public long getConversationId() {
		return conversationId;
	}

	public void setConversationId(long conversationId) {
		this.conversationId = conversationId;
	}

	public String getSelectedCategory() {
		return selectedCategory;
	}

	public void setSelectedCategory(String selectedCategory) {
		this.selectedCategory = selectedCategory;
	}

	public String getSelectedSubCategory() {
		if(this.selectedCategory == null) {
			this.selectedSubCategory = this.categoryDB.getSubCategories(selectedCategory).get(0);
		}
		return selectedSubCategory;
	}

	public void setSelectedSubCategory(String selectedSubCategory) {
		this.selectedSubCategory = selectedSubCategory;
	}
	
	
	
}
