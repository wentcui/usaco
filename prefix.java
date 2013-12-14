/*
ID: wentcui1
LANG: JAVA
TASK: calfflac
*/
import java.io.*;
import java.util.*;

class prefix {
	public static void main (String [] args) throws IOException {
		// Use BufferedReader rather than RandomAccessFile; it's much faster
		BufferedReader fin = new BufferedReader(new FileReader("prefix.in"));
		PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("prefix.out")));
		HashMap<String, Boolean> map = new HashMap<String, Boolean>();
		ArrayList<String> strlist = new ArrayList<String>();
		int longest = 0;
		String str = new String("");
		String line = fin.readLine();
		while(line.charAt(0) != '.') {
			String[] arr = line.split(" ");
			for(int i = 0; i < arr.length; i++) {
				strlist.add(arr[i]);
				map.put(arr[i], true);
				if (arr[i].length() > longest)
					longest = arr[i].length();
			}
			line = fin.readLine();
		}

		line = fin.readLine();
		while(line != null) {
			str += line;
			line = fin.readLine();
		}
		boolean[] dp = new boolean[str.length() + 1];
		dp[0] = true;
		int start = 0;
		for(int i = 0; i < strlist.size(); i++) {
			int len = strlist.get(i).length();
			String s = str.substring(0, len);
			if (map.containsKey(s)) {
				dp[len] = true;
				if (len > start)
					start = len;
			}
		}
		if (start == 0) {
			fout.println(0);
			fout.close();
			System.exit(0);
		}
		start++;
		while(start <= str.length()) {
			for(int i = 0; i < strlist.size(); i++) {
				String s = strlist.get(i);
				int len = s.length();
				if (start - len - 1 < 0)
					continue;
				String ss = str.substring(start - len - 1, start);
				if (dp[start - len - 1] && s.equals(ss)) {
					dp[start] = true;
					start++;
					break;
				}
			}
			fout.println(start - 1);
			fout.close();
			System.exit(0);
		}
		
		System.exit(0);
	}
}
