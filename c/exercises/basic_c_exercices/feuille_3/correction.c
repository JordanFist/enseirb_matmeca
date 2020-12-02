#include <stdio.h>

int is_leep(int y)
{
  return (y % 4 == 0 && y % 100) || (y % 400 == 0);
}

int day_count(int m, int y) {
 case 1:
 case 3:
 case 5:
 case 7:
 case 9:
 case 11:
   return 31;
 case 2:
   return 28 + is_leep(y);
 case 4:
 case 6:
 case 8:
 case 10:
 case 12 :
   return 30;
 default : 
   return -1;
}

int bit_count1(int n) {
  int count = 0;
  int j = 0;
  for (j = 0; j < sizeof(n) * 8, ++j) {
    if (n & (1 << j))
      ++count;
  }
  return count;
}

int bit_count2(unsigned n) { 
// il ne doit pas etre signé pour ne pas avoir de bit fort a 1 d'ou le unsigned
  int count = 0;
  while (n) {
    if (n & 1) 
      ++count;
    n = n >> 1;
  }
  return count;
}
     
