void gamePlay()
{
  setDisplayLine(0, "P1      P2");
  setDisplayLine(1, "          ");

  if (btn_change)
  {
    if (btn_state == 3)
    {
      mode = 5;
      digitalWrite(P1_LED_PIN, HIGH);
      digitalWrite(P2_LED_PIN, HIGH);
    }
    if (btn_state == 1 && mode == 1)
    {
      mode = 2;
      digitalWrite(P1_LED_PIN, LOW);
      digitalWrite(P2_LED_PIN, HIGH);
      p1 = p1 + inc;
    }
    if (btn_state == 2 && mode == 2)
    {
      mode = 1;
      digitalWrite(P1_LED_PIN, HIGH);
      digitalWrite(P2_LED_PIN, LOW);
      p2 = p2 + inc;
    }
  }
  else
  {
    if (mode == 1)
    {
      setDisplayLine(2, longMsToString(p1, false));
      setDisplayLine(3, longMsToString(p2, true));
      p1 = p1 - DELAY;

      if(game_mode == 1)
        p2 = p2 + DELAY;
      
      if (p1 <= 0)
        mode = 4;
    }
    if (mode == 2)
    {
      setDisplayLine(3, longMsToString(p1, false));
      setDisplayLine(2, longMsToString(p2, true));
      p2 = p2 - DELAY;

      if(game_mode == 1)
        p1 = p1 + DELAY;
      
      if (p2 <= 0)
        mode = 3;
    }
  }
}
