void gameMenu()
{
  static int choice = 1;
  
  // start new game
  if (btn_change && btn_state == 3)
  {
    mode = 5;
    game_mode = 0;
    switch(choice)
    {
      case -3:
        p1 = 3UL * 60000UL;
        inc = 2000;
        break;
      case -2:
        p1 = 2UL * 60000UL;
        inc = 1000;
        break;
      case -1:
        p1 = 1UL * 60000UL;
        inc = 1000;
        break;
      case 0:
        p1 = 150000UL;
        inc = 0;
        game_mode = 1;
        break;
      case 1:
        p1 = 1UL * 60000UL;
        inc = 0;
        break;
      case 2:
        p1 = 3UL * 60000UL;
        inc = 0;
        break;
      case 3:
        p1 = 5UL * 60000UL;
        inc = 0;
        break;
      case 4:
        p1 = 10UL * 60000UL;
        inc = 0;
        break;
      case 5:
        p1 = 20UL * 60000UL;
        inc = 0;
        break;
      case 6:
        p1 = 30UL * 60000UL;
        inc = 0;
        break;
      case 7:
        p1 = 1000;
        inc = 0;
        break;
    }
    p2 = p1;
    return;
  }
  
  else if(btn_change && btn_state == 2)
    choice++;
  else if (btn_change && btn_state == 1)
    choice--;

  if (choice < -3)
    choice = -3;
  else if (choice > 7)
    choice = 7;
  
  switch(choice)
  {
    case -3:
      setDisplayLine(0, "3 min | 2");
      break;
    case -2:
      setDisplayLine(0, "2 min | 1");
      break;
    case -1:
      setDisplayLine(0, "1 min | 1");
      break;
    case 0:
      setDisplayLine(0, "5 min diff");
      break;
    case 1:
      setDisplayLine(0, "1 min ");
      break;
    case 2:
      setDisplayLine(0, "3 min ");
      break;
    case 3:
      setDisplayLine(0, "5 min ");
      break;
    case 4:
      setDisplayLine(0, "10 min");
      break;
    case 5:
      setDisplayLine(0, "20 min");
      break;
    case 6:
      setDisplayLine(0, "30 min");
      break;
    case 7:
      setDisplayLine(0, "music");
      break;
  }
}

void gamePause()
{
  if (mode == 5)
  {
    setDisplayLine(1, " STAND BY ");
    
    if(!btn_change)
      return;
    if (btn_state == 1)
    {
      mode = 2;
      digitalWrite(P1_LED_PIN, LOW);
      digitalWrite(P2_LED_PIN, HIGH);
    }
    else if (btn_state == 2)
    {
      mode = 1;
      digitalWrite(P1_LED_PIN, HIGH);
      digitalWrite(P2_LED_PIN, LOW);
    }
    else if (btn_state == 3)
    {
      digitalWrite(P1_LED_PIN, LOW);
      digitalWrite(P2_LED_PIN, LOW);
      oled.clear();
      mode = 0;
    }
  }
  if (mode == 3)
  {
    digitalWrite(P1_LED_PIN, HIGH);
    digitalWrite(P2_LED_PIN, HIGH);
    oled.clear();
    setDisplayLine(0, "          ");
    setDisplayLine(1, "  P1 WIN  ");
    setDisplayLine(2, "          ");
    setDisplayLine(3, "          ");
    victoryMusic();
    oled.clear();
    digitalWrite(P1_LED_PIN, LOW);
    digitalWrite(P2_LED_PIN, LOW);
    mode = 0;
  }
  else if (mode == 4)
  {
    digitalWrite(P1_LED_PIN, HIGH);
    digitalWrite(P2_LED_PIN, HIGH);
    oled.clear();
    setDisplayLine(0, "          ");
    setDisplayLine(1, "  P2 WIN  ");
    setDisplayLine(2, "          ");
    setDisplayLine(3, "          ");
    victoryMusic();
    oled.clear();
    digitalWrite(P1_LED_PIN, LOW);
    digitalWrite(P2_LED_PIN, LOW);
    mode = 0;
  }
}
