/*
ID: wentcui1
LANG: JAVA
TASK: zerosum
 */
import java.io.*;
import java.util.*;

class zerosum {
	static ArrayList<String> res = new ArrayList<String>();
	static boolean validate(String str) {
		String suffix = "";
		Stack<Character> operand = new Stack<Character>();
		Stack<Integer> operator = new Stack<Integer>();

		for(int i = 0; i < str.length(); i++) {
			char c = str.charAt(i);
			if (c >= '1' && c <= '9') {
				suffix += c;
			} else if (operand.empty() || (c == ' ' && (operand.peek() == '+' || operand.peek() == '-'))) {
				operand.push(c);
			} else {
				if (c == '+' || c == '-') {
					while(!operand.empty()) {	
						suffix += operand.pop();
					}
				} else {
					while(!operand.empty() && operand.peek() == ' ') {
						suffix += operand.pop();
					}
				}
				operand.push(c);
			}
		}
		while(!operand.empty()) {
			suffix += operand.pop();
		}

		for(int i = 0; i < suffix.length(); i++) {
			char c = suffix.charAt(i);
			if (c >= '1' && c <= '9')
				operator.push((int)(c - '0'));
			else {
				int b = operator.pop();
				int a = operator.pop();
				if (c == '+')
					operator.push(a + b);
				else if (c == '-')
					operator.push(a - b);
				else
					operator.push(10 * a + b);
			}
		}
		if (operator.peek() == 0)
			return true;
		return false;
	}
	static void strGen(int curindex, int n, String str) {
		int nextindex = curindex + 1;
		if (curindex == n) {
			if (validate(str))
				res.add(str);
			return;
		}

		strGen(nextindex, n, new String(str) + "+" + nextindex);
		strGen(nextindex, n, new String(str) + '-' + nextindex);
		strGen(nextindex, n, new String(str) + ' ' + nextindex);
	}
	public static void main(String[] args) throws IOException {
        BufferedReader f = new BufferedReader(new FileReader("zerosum.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("zerosum.out")));
        StringTokenizer st = new StringTokenizer(f.readLine());
		int n = Integer.parseInt(st.nextToken());
		strGen(1, n, "1");
		if (res.size() > 0) {
			String[] arr = new String[res.size()];
			for(int i = 0; i < res.size(); i++) {
				arr[i] = res.get(i);
			}
			Arrays.sort(arr);
			for(int i = 0; i < arr.length; i++) {
				fout.println(arr[i]);
			}
		}
		fout.close();
		System.exit(0);
	}
}
