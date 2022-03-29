package project1;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Rover {
	private String name;
	private int id;
	private Map<String, Stone> stones= new HashMap<>();
	
	public Rover(String name, int id) {
		this.name=name;
		this.id=id;
	}
		
	public String getName() {
		return name;
	}

	public int getId() {
		return id;
	}
	
	public List<Stone> getStones(){
		return this.stones.values().stream().toList();
	}
	
	public String getStonesString() {
		StringBuilder result=new StringBuilder("");
		for(Stone s:stones.values()) {
			result.append(s.name+" "+s.qn+"\n");
		}
		return result.toString();
	}
	public void addStone(String name, double qn) throws ExceptionError {
		if(stones.containsKey(name)) throw new ExceptionError();
		else
			this.stones.put(name, new Stone(name, qn));
	}
	
	public int nStonesCollected() {
		return stones.values().stream().collect(Collectors.summingInt(s->s.getCollected()));
	}
}