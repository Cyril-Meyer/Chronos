bool strCmp10(const char *s1, const char *s2)
{
  return !(s1[0] == s2[0] &&
           s1[1] == s2[1] &&
           s1[2] == s2[2] &&
           s1[3] == s2[3] &&
           s1[4] == s2[4] &&
           s1[5] == s2[5] &&
           s1[6] == s2[6] &&
           s1[7] == s2[7] &&
           s1[8] == s2[8] &&
           s1[9] == s2[9]);
}

void setDisplay(const char *l1, const char *l2, const char* l3, const char *l4)
{
  setDisplayLine(0, l1);
  setDisplayLine(1, l2);
  setDisplayLine(2, l3);
  setDisplayLine(3, l4);
}

void setDisplayLine(int i, const char* l)
{
  if(strCmp10(L[i], l))
  {
    for(int j = 0; j < 10; ++j)
      L[i][j] = l[j];
    
    oled.setCursor(0, 2*i);
    oled.clearToEOL();
    oled.println(L[i]);
  }
}

const char* longMsToString(long t, bool blank_pad_5)
{
  // Got some problem using snprintf with more than 1 var.
  // This little hack make it works.
  
  static char buff[11];
  
  for(int i = 0 ; i < 11 ; ++i)
    buff[i] = ' ';
  
  char *buff_1 = buff;
  if (blank_pad_5)
    buff_1 += 5;
  char *buff_2 = buff_1;
  buff_2 += 3;
  
  if (t < 0)
  {
    snprintf(buff_1, 6, "00000");
  }
  else if (t <= 60000)
  {
    snprintf(buff_1, 6, "%02d.", t/1000);
    snprintf(buff_2, 3, "%02d", t/10%100);
  }
  else if (t < 3600000)
  {
    snprintf(buff_1, 6, "%02d:", t/60000);
    snprintf(buff_2, 3, "%02d", (t/1000)%60);
  }
  // less than 24h
  else if (t < 86400000)
  {
    snprintf(buff_1, 6, "%02d:", t/3600000);
    snprintf(buff_2, 3, "%02d", (t/60000)%60);
  }
  else
  {
    snprintf(buff_1, 6, "\\0_0/");
  }
  
  return buff;
}
