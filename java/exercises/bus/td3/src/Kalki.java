class Kalki{
  public static void main(String []args) {
	char valeur[] = {'K', 'a', 'l', 'k', 'i'};
    String s1 = new String(valeur);
    s1.intern();
    String s2 = new String(valeur);
    s2 = s2.intern();
    System.out.println(s1 == s2);
    System.out.println(s1 == "Kalki");
}
}
