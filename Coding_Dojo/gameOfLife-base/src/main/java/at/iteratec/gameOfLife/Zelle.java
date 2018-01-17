package at.iteratec.gameOfLife;

import java.util.ArrayList;

public class Zelle {

	String status;
	String neuerStatus = "Leer";
	
	ArrayList<Zelle> nachbarn = new ArrayList<>();
	
	
	public Zelle(String status, Zelle z1, Zelle z2, Zelle z3, Zelle z4,
			 Zelle z5, Zelle z6, Zelle z7, Zelle z8) {
		this.status = status;
		this.nachbarn.add(z1);
		this.nachbarn.add(z2);
		this.nachbarn.add(z3);
		this.nachbarn.add(z4);
		this.nachbarn.add(z5);
		this.nachbarn.add(z6);
		this.nachbarn.add(z7);
		this.nachbarn.add(z8);
		
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getNeuerStatus() {
		return neuerStatus;
	}

	public void setNeuerStatus(String neuerStatus) {
		this.neuerStatus = neuerStatus;
	}

	public ArrayList<Zelle> getNachbarn() {
		return nachbarn;
	}

	public void setNachbarn(ArrayList<Zelle> nachbarn) {
		this.nachbarn = nachbarn;
	}
	
	
	
	
	
}
