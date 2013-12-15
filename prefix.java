/*
ID: wentcui1
LANG: JAVA
TASK: prefix
*/
import java.io.*;
import java.util.*;

class prefix {
	static boolean strComp(String s, String str, int index) {
		int last = s.length() - 1;
		while(last >= 0 && index >= 0 && s.charAt(last) == str.charAt(index)) {
			last--;
			index--;
		}
		if (last >= 0)
			return false;
		return true;
	}
	
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
				if (!map.containsKey(arr[i])) {
					strlist.add(arr[i]);
					map.put(arr[i], true);
					if (arr[i].length() > longest)
						longest = arr[i].length();
				}
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
		int start = 0, prevpos;
		for(int i = 0; i < strlist.size(); i++) {
			int len = strlist.get(i).length();
			if (len >= str.length()) continue;
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
		prevpos = start;
		start++;
		while(start <= str.length()) {
			for(int i = 0; i < strlist.size(); i++) {
				String s = strlist.get(i);
				int len = s.length();
				if (start - len - 1 < 0)
					continue;
				if (dp[start - len] && strComp(s, str, start - 1)) {
					dp[start] = true;
					prevpos = start;
					break;
				}
			}
			if (start - prevpos >= longest) {
				break;
			}
			start++;
		}
		fout.println(prevpos);
		fout.close();

		System.exit(0);
	}
}
