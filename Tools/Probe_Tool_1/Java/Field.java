package project1;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Scanner;

public class Field {
	public static final int MAXR = 6;
	public String[] field= new String[MAXR];
	private Map<String, Rover> rovers=new HashMap<>();
	
	public Field(String fieldfile, String roverfile) throws FileNotFoundException, IOException, ExceptionError {
		try(BufferedReader in=new BufferedReader(new FileReader(fieldfile))){
			String line;
			int i=0;
			while((line=in.readLine())!=null) {
				if(i>=MAXR) throw new ExceptionError();
				field[i]=line;
				i++;
			}
		}
		loadRovers(roverfile);
		scanField();
	}
	
	private void loadRovers(String roverfile) throws IOException {
		try(BufferedReader in= new BufferedReader(new FileReader(roverfile))){
			String line;
			Scanner s=null;
			line=in.readLine();
			s=new Scanner(line);
			int N=s.nextInt();
			s.close();
			for(int i=0;i<N;i++) {
				line=in.readLine();
				try {
					s=new Scanner(line);
					s.useDelimiter(" ");
					String name= s.next().trim();
					int id=s.nextInt();
					int nStones=s.nextInt();
					Rover r= new Rover(name, id);
					rovers.put(name, r);
					for(int j=0;j<nStones;j++) {
						line=in.readLine();
						try {
						s=new Scanner(line);
						s.useDelimiter(" ");
						s.useLocale(Locale.UK);
						name=s.next().trim();
						double qn=s.nextDouble();
						r.addStone(name, qn);
						}catch(Exception e) {};
					}
				}catch(Exception e) {};
			}
		}
	}
	
	private void scanField() {
		int i;
		for(Rover r:rovers.values()) {
			for(Stone s:r.getStones()) {
				i=0;
				while((i=this.toString().indexOf(s.name, i))!=-1) {
					s.addCollected();
					i=i+s.name.length();
				}
			}
		}
	}
	
	public String toString() {
		StringBuilder result=new StringBuilder(""+field[0]);
		for(int i=1;i<MAXR;i++)
			result.append("\n"+field[i]);
		return result.toString();
	}
	
	public void storeOutput() throws IOException {
		StringBuilder line=new StringBuilder("");
		for(Rover r:this.getRovers()) {
			line.append(r.getName()+" "+r.getId()+" "+r.nStonesCollected()+"\n");
			for(Stone s:r.getStones()) {
				for(int i=0;i<s.collected;i++) {
					if(i==0) line.append(s.qn);
					line.append(" "+s.qn);
				}
			}
			line.append("\n");
		}
		Writer w = new FileWriter("output.txt");
		w.write(line.toString());
		w.close();
	}
	
	public List<Rover> getRovers(){
		return this.rovers.values().stream().toList();
	}
}