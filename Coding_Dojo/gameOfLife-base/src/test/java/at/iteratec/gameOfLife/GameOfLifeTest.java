package at.iteratec.gameOfLife;

import org.junit.Test;

import static org.hamcrest.core.Is.is;
import static org.junit.Assert.*;

import java.util.ArrayList;

public class GameOfLifeTest {

	@Test
	public void checkLife() {
		
		int max_col;
		int max_row;
		
		ArrayList<Verknuepfung> allZellen = ArrayList()<>;
		
		for(int col=0; col <max_col; col++) {
			for(int row=0; row <max_row; row++) {
				alleZellen.add(new Verknuepfung(new Zelle(xxx), col, row)));
			}
		}
		
		ArrayList<
		Zelle zelle1 = new Zelle("Leer", );
	}

	@Test
	public void returnZero() throws Exception {
		assertThat(new GameOfLife().returnZero(), is(0));

	}

}