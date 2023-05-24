timeCounter++;
if (timeCounter % 10 == 0) { 
	speedIncreaseTimer++;
	if (speedIncreaseTimer >= SPEED_INCREASE_TIME) {
		speedIncreaseTimer = 0;
		speed += SPEED_INCREASE_AMOUNT;
	}