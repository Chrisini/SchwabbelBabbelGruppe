package at.iteratec.gameOfLife;

public class Verknuepfung {

	Zelle akt_zelle;
	int pos_row;
	int pos_col;
	
	public Verknuepfung(Zelle akt_zelle, int pos_row, int pos_col) {
		this.akt_zelle = akt_zelle;
		this.pos_row = pos_row;
		this.pos_col = pos_col;
	}

	public Zelle getAkt_zelle() {
		return akt_zelle;
	}

	public void setAkt_zelle(Zelle akt_zelle) {
		this.akt_zelle = akt_zelle;
	}

	public int getPos_row() {
		return pos_row;
	}

	public void setPos_row(int pos_row) {
		this.pos_row = pos_row;
	}

	public int getPos_col() {
		return pos_col;
	}

	public void setPos_col(int pos_col) {
		this.pos_col = pos_col;
	}
	
	
	
}
