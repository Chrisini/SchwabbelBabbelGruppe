
public class TennisGame1 implements TennisGame {
    
    private Player player1 = new Player();
    private Player player2 = new Player();

    public TennisGame1(String player1Name, String player2Name) {
        player1.setPlayerName(player1Name);
        player2.setPlayerName(player2Name);
    }

    public void wonPoint(String playerName) {
    	
        if (playerName == "player1")
            player1.incrementScore();

        else
            player2.incrementScore();
    }
    
    private String getIndividualScoreName(int tmpscore) {
    	String individual_score = "";
    	
    	switch (tmpscore)
        {
            case 0:
                individual_score = "Love";
                break;
            case 1:
            	individual_score = "Fifteen";
                break;
            case 2:
            	individual_score = "Thirty";
                break;
            default:
        		individual_score = "Forty";
                break;
        }
    	
    	return individual_score;
    }
    
    
    String getScoreName() {
    	String score = "";
    	
    	for (int player_counter = 1; player_counter < 3; player_counter++) {
    		//System.out.println("player1.getScore(): " + player1.getScore());
	    	if (player_counter == 1) {
	    		score += getIndividualScoreName(player1.getScore());
	    		if (player1.getScore() == player2.getScore()) {
	    			if (player1.getScore() >= 3) {
	    				score = "Deuce";
	    				break;
	    			}
	    			score += "-All";
	    			break;
	    		}
	    	} else { 
	        	score += "-" + getIndividualScoreName(player2.getScore());
	        }
	    	
    	}
    	
    	return score;
    }
    
    String equalScore() {
    	String score = "";
    	
    	score = getScoreName();
    	
    	return score;
    }
    
    String advantageScored() {
    	String score = "";
    	
    	int minusResult = player1.getScore()-player2.getScore();
        if (minusResult==1) score ="Advantage player1";
        else if (minusResult ==-1) score ="Advantage player2";
        else if (minusResult>=2) score = "Win for player1";
        else score ="Win for player2";
        
        return score;
    }
    
    String defaultScore() {
    	String score = "";
    	
    	score = getScoreName();
    	
    	return score;
    }

    public String getScore() {
        String score = "";
        if (player1.getScore()==player2.getScore())
        {
            score = equalScore();
        }
        else if (player1.getScore()>=4 || player2.getScore()>=4)
        {
        	score = advantageScored();
            
        }
        else
        {
        	score = defaultScore();
            
        }
        System.out.println("score: " + score);
        return score;
    }
}
