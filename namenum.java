/*
ID: wentcui1
LANG: JAVA
TASK: namenum
*/
import java.io.*;
import java.util.*;

class namenum {
  public static HashMap<Character, ArrayList<Character>> initmap() {
	HashMap<Character, ArrayList<Character>> map = new HashMap<Character, ArrayList<Character>>();
	ArrayList<Character> l = new ArrayList<Character>();
	l.add('A');
	l.add('B');
	l.add('C');
	map.put('2', l);

	l = new ArrayList<Character>();
    l.add('D');
    l.add('E');
    l.add('F');
    map.put('3', l);

	l = new ArrayList<Character>();
    l.add('G');
    l.add('H');
    l.add('I');
    map.put('4', l);

	l = new ArrayList<Character>();
    l.add('J');
    l.add('K');
    l.add('L');
    map.put('5', l);

	l = new ArrayList<Character>();
    l.add('M');
    l.add('N');
    l.add('O');
    map.put('6', l);

	l = new ArrayList<Character>();
    l.add('P');
    l.add('R');
    l.add('S');
    map.put('7', l);

	l = new ArrayList<Character>();
    l.add('T');
    l.add('U');
    l.add('V');
    map.put('8', l);

	l = new ArrayList<Character>();
    l.add('W');
    l.add('X');
    l.add('Y');
    map.put('9', l);
	
	return map;
  }
  
  public static boolean validate(char c, ArrayList<Character> l) {
	for (int i = 0; i < l.size(); i++) {
		if (l.get(i) == c)
			return true;
	}
	return false;
  }

  public static void main (String [] args) throws IOException {
    BufferedReader f = new BufferedReader(new FileReader("namenum.in"));
    BufferedReader fdict = new BufferedReader(new FileReader("dict.txt"));
	ArrayList<String> dict = new ArrayList<String>();
    PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("namenum.out")));
    StringTokenizer st = new StringTokenizer(f.readLine());
    String s = st.nextToken(), line;
	int len = s.length();
	HashMap<Character, ArrayList<Character>> map = initmap();
	
	while ((line = fdict.readLine()) != null) {
		if (line.length() != len)
			continue;
		if (validate(line.charAt(0), map.get(s.charAt(0)))) {
			dict.add(line);
		}
	}

	for(int i = 1; i < len; i++) {
		char c = s.charAt(i);
		ArrayList<String> newdict = new ArrayList<String>();
		for(int j = 0; j < dict.size(); j++) {
			if (validate(dict.get(j).charAt(i), map.get(c))) {
				newdict.add(dict.get(j));
			}
		}
		dict = newdict;
	}
	if (dict.size() == 0) {
		out.println("NONE");
		out.close();
		System.exit(0);
	}
	
	for(int i = 0; i < dict.size(); i++) {
		out.println(dict.get(i));
	}
	out.close();
	System.exit(0);
  }
}

