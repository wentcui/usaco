/*
ID: wentcui1
LANG: JAVA
TASK: calfflac
*/
import java.io.*;
import java.util.*;

class calfflac {
  public static boolean isalf(char c) {
	if ((c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z'))
		return true;
		
	return false;
  }
  public static boolean validate(char a, char b) {
	if (Character.toUpperCase(a) != Character.toUpperCase(b))
		return false;
	return true;
  }
  public static int getnext(String s, int index) {
	int start = index + 1;
	while (start < s.length() && !isalf(s.charAt(start)))
		start++;
	return start;
  }
  public static void main (String [] args) throws IOException {
    // Use BufferedReader rather than RandomAccessFile; it's much faster
    BufferedReader fin = new BufferedReader(new FileReader("calfflac.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("calfflac.out")));
	ArrayList<String> reslist = new ArrayList<String>();
	int longest = 0, start = 0, end;
	String str = "";
	String line	= fin.readLine();
	while(line != null) {
		str += (line + "\n");
		line = fin.readLine();
	}

	while(start < str.length() && !isalf(str.charAt(start)))
		start++;
	end = str.length() - 1;
	while(end >= 0 && !isalf(str.charAt(end)))
		end--;

	for(int i = start; i <= end; i++) {
		int runninglen = 0;
		int next = getnext(str, i);
		int left = i - 1, lastright = -1;
		int right = i + 1;
		if (isalf(str.charAt(i)))
			runninglen = 1;
		if (!isalf(str.charAt(i)) && i < end && !isalf(str.charAt(i + 1)))
			continue;
		while (left >= start && right <= end) {
			while (left >= start && !isalf(str.charAt(left)))
				left--;
			while (right <= end && !isalf(str.charAt(right)))
				right++;
			if (left >= start && right <= end && validate(str.charAt(left), str.charAt(right))) {
				runninglen += 2;
				if (runninglen > longest) {
					if (runninglen > longest) {
						lastright = -1;
						reslist = new ArrayList<String>();
					}
					if (left > lastright) {
						reslist.add(str.substring(left, right + 1));
						lastright = right;
					}
					longest = runninglen;
				}
				left--;
				right++;
			} else
				break;
		}

		left = i;
		if (next <= end && str.charAt(next) == str.charAt(i)) {
			right = next + 1;
			while (left >= start && right <= end) {
				while (left >= start && !isalf(str.charAt(left)))
					left--;
				while (right <= end && !isalf(str.charAt(right)))
					right++;
				if (left >= start && right <= end && validate(str.charAt(left), str.charAt(right))) {
					runninglen += 2;
					if (runninglen > longest) {
						if (runninglen > longest) {
							lastright = -1;
							reslist = new ArrayList<String>();
						}
						if (left > lastright) {
							reslist.add(str.substring(left, right + 1));
							lastright = right;
						}
						longest = runninglen;
					}
					left--;
					right++;
				} else
					break;
			}
		}
	}

	fout.println(longest);
	fout.println(reslist.get(0));
	fout.close();
	System.exit(0);                               // don't omit this!
  }
}
