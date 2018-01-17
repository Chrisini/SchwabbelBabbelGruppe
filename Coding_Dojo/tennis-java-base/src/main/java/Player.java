
public class Player {
	
	String playerName = "";
	int score = 0;
	
	public Player (String playerName) {
		this.playerName = playerName;
	}
	
	public Player() {
		
	}
	
	void incrementScore () {
		score++;
	}

	public String getPlayerName() {
		return playerName;
	}

	public void setPlayerName(String playerName) {
		this.playerName = playerName;
	}

	public int getScore() {
		return score;
	}

	public void setScore(int score) {
		this.score = score;
	}
}
