/********************************************
 nextstep function
 ********************************************/
void nextstep(){
  for(int i=snakeLength-1; i>0; i--){
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  
  if (DEBUG) {
      Serial.print("direction=");
      Serial.println(direction);
    }
    
  switch(direction){
    case TOP:
      snakeY[0] = constrain(snakeY[0]-1, 0, 7);
      break;
    case RIGHT:
      snakeX[0] = constrain(snakeX[0]+1, 0, 7);
      break;
    case BOTTOM:
      snakeY[0] = constrain(snakeY[0]+1, 0, 7);
      break;
    case LEFT:
      snakeX[0]=constrain(snakeX[0]-1, 0, 7);
      break;
  }
  if((snakeX[0] == fruitX) && (snakeY[0] == fruitY)){
    snakeLength++;
    if(snakeLength < MAX_SNAKE_LENGTH){      
      makeFruit();
    } 
    else {
      fruitX = fruitY = -1;
    }
  }
}

/********************************************
 makeFruit function
 ********************************************/
void makeFruit(){
  int x, y;
  x = random(0, 8);
  y = random(0, 8);
  while(isPartOfSnake(x, y)){
    x = random(0, 8);
    y = random(0, 8);
  }
  fruitX = x;
  fruitY = y;
}



