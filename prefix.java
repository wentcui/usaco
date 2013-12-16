/*
ID: wentcui1
LANG: JAVA
TASK: prefix
*/
import java.io.*;
import java.util.*;

class prefix {
	static boolean strComp(String s, String str, int index) {
		int curs = 0;
		int cur = index;
		while(curs < s.length() && cur < str.length() && s.charAt(curs) == str.charAt(cur)) {
			curs++;
			cur++;
		}
		if (curs == s.length())
			return true;
		return false;
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

		int best = 0;
		boolean[] visited = new boolean[200001];
		Stack<Integer> st = new Stack<Integer>();
		Stack<Integer> maxst = new Stack<Integer>();
		st.push(0);
		maxst.push(0);
		while (!st.empty()) {
			int cur = st.pop();
			best = Math.max(best, cur);
			for(int i = 0; i < strlist.size(); i++) {
				String s = strlist.get(i);
				int lens = s.length();
				if (cur + lens <= str.length() && !visited[cur + lens] && strComp(s, str, cur)) {
					st.push(cur + lens);
					visited[cur + lens] = true;
				}
			}
		}
		fout.println(best);
		fout.close();
		System.exit(0);
	}
}

