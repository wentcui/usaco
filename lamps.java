/*
ID: wentcui1
LANG: JAVA
TASK: lamps
 */
import java.io.*;
import java.util.*;

class lamps {
	static int n, count;
	static int[] finalon = new int[101], finaloff = new int[101];
	static long gotOne = 0;
	static PrintWriter out = null;
	static HashMap<String, Boolean> existed = new HashMap<String, Boolean>();
	static String[] strarr = new String[20];
	static int strarr_pos = 0;

	static void flip(char []arr, int type) {
		int i;
		char mask = '\0';
		switch(type) {
			case 1: mask = 0xFF; break;
			case 2: mask = 0x55; break;
			case 3: mask = 0xAA; break;
			case 4: mask = 0x49; break;
			default: break;
		}

		if (type <= 3) {
			for(i = 0; i <= (n - 1) / 8; i++)
				arr[i] ^= mask;
		} else {
			for(i = 0; i <= (n - 1) / 8; i++) {
				arr[i] ^= (mask << (i % 3));
			}
		}
	}


	static boolean checkBit(char []arr, int pos) {
		return (arr[(pos - 1) / 8] & (1 << ((pos - 1) % 8))) > 0;
	}


	static boolean validate(char []arr) {
		int i = 0;
		for(i = 0; finalon[i] > 0; i++)
			if (!checkBit(arr, finalon[i])) {
				return false;
			}

		for(i = 0; finaloff[i] > 0; i++)
			if (checkBit(arr, finaloff[i])) {
				return false;
			}
		return true;
	}

	static void outputSingle(String str, char c, int left) {
		int j = 0;
		while (j < 8 && j <= left) {
			str += (((c & (1 << j)) > 0) ? "1" : "0");
			j++;
		}
	}

	static void output(char []arr) {
		int i = 1, j = 0, nr = 0;
		String str = new String("");
		char c;
		while (i <= n) {
			c = arr[nr];
			j = 0;
			while (j < 8 && i <= n) {
				str += (((c & (1 << j)) > 0) ? "1" : "0");
				j++;
				i++;
			}
			nr++;
		}
		if (!existed.containsKey(str)) {
			//out.println(str);
			strarr[strarr_pos++] = str;
			existed.put(str, true);
		}
	}

	static void dfs(char []arr, int curtype, int curcount) {
		if (((curcount % 2) == (count % 2)) && validate(arr)) {
			output(arr);
			gotOne++;
		}

		if (curcount >= count || curtype > 4) {
			return;
		}

		dfs(arr, curtype + 1, curcount);

		flip(arr, curtype);
		dfs(arr, curtype + 1, curcount + 1);
		flip(arr, curtype);

	}


	public static void main(String[] args) throws IOException {
		BufferedReader f = new BufferedReader(new FileReader("lamps.in"));
		out = new PrintWriter(new BufferedWriter(new FileWriter("lamps.out")));
		StringTokenizer st = new StringTokenizer(f.readLine());
		int i, pos;
		n = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(f.readLine());
		count = Integer.parseInt(st.nextToken());
		char[] arr = new char[(n - 1) / 8 + 1];
		for(i = 0; i < arr.length; i++)
			arr[i] = 0xFF;

		st = new StringTokenizer(f.readLine());
		i = 0;
		pos = Integer.parseInt(st.nextToken());
		while(pos != -1) {
			finalon[i++] = pos;
			pos = Integer.parseInt(st.nextToken());
		}

		st = new StringTokenizer(f.readLine());
		i = 0;
		pos = Integer.parseInt(st.nextToken());
		while(pos != -1) {
			finaloff[i++] = pos;
			pos = Integer.parseInt(st.nextToken());
		}

		dfs(arr, 1, 0);
		if (gotOne == 0) {
			out.println("IMPOSSIBLE");
		}
		Arrays.sort(strarr, 0, strarr_pos);
		for(i = 0; i < strarr_pos; i++) {
			out.println(strarr[i]);
		}
		out.close();
		System.exit(0);
	}
}
