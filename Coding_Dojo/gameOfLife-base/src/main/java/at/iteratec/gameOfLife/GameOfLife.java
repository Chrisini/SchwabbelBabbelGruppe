package at.iteratec.gameOfLife;

import java.util.ListIterator;

public class GameOfLife {

	
	
	
    public int returnZero() {
        return 1;
    }

    
    public void zellverhalten(Zelle aktuellezelle) {
    	
    	ListIterator<Zelle> nachbariterator = aktuellezelle.nachbarn.listIterator(0);
    	
    	int zellennachbarn = 0;
    	int anzahlLebendNachbarn = 0;
    	
    	if(aktuellezelle.getStatus().equals("Leer")) {
    		
    		
    		
    	} else if(aktuellezelle.getStatus().equals("Lebend")) {
    		for (Zelle zelle : aktuellezelle.nachbarn) {
    			if(zelle.getStatus().equals("Lebend")){
    				anzahlLebendNachbarn ++;
    			}
    		} 
    		if(anzahlLebendNachbarn == 1) {
    			aktuellezelle.setNeuerStatus("Leer"); 
    		}else if(anzahlLebendNachbarn == 2 || anzahlLebendNachbarn == 3) {
    			if(aktuellezelle.getStatus().equals("Leer") && anzahlLebendNachbarn == 3) {
    				aktuellezelle.setStatus("Lebend");
    			}
    			aktuellezelle.setNeuerStatus("Lebend");
    			
    		}else if(anzahlLebendNachbarn >= 4) {
    			aktuellezelle.setNeuerStatus("Leer");
    		}
    		
    	}
    	
    	aktuellezelle.setStatus(aktuellezelle.getNeuerStatus());
    	
    	
    }
    
}

