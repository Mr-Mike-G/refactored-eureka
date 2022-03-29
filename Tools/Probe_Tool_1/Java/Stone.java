package project1;

public class Stone {
	public String name;
	public double qn;
	public int collected;
	
	public Stone(String name, double qn) {
		this.name=name;
		this.qn=qn;
		this.collected=0;
	}
	
	public int getCollected() {
		return collected;
	}
	
	public void addCollected() {
		this.collected++;
	}
}