/*
ID: wentcui1
LANG: JAVA
TASK: msquare
 */

import java.io.*;
import java.util.*;

class msquare {
	static char[] res = new char[10000];
	static HashMap<Integer, Boolean> visited = new HashMap<Integer, Boolean>();
	static int finalpos = 0;
	static int finalstate = 0;
	static boolean success = false;

	static int get(int state, int pos) {
		int mask = 0x0000000f;
		return (state & (mask << (4 * pos))) >> (4 * pos);
	}

	static int clear(int pos, int state){
		int mask = (0x0000000f << (4 * pos));
		state &= (~mask);
		return state;
	}

	static int set(int pos, int state, int v) {
		state = clear(pos, state);
		state += (v << (pos * 4));
		return state;
	}

	static int trans_C(int state) {
		int tempv = get(state, 2);
		int newstate = state;
		newstate = set(2, newstate, get(state, 6));
		newstate = set(6, newstate, get(state, 5));
		newstate = set(5, newstate, get(state, 1));
		newstate = set(1, newstate, tempv);
		return newstate;
	}

	static int trans_B(int state) {
		int newstate = (state >> 4);
		int v1 = get(state, 0);
		int v2 = get(state, 4);
		newstate = set(3, newstate, v1);
		newstate = set(7, newstate, v2);

		return newstate;
	}

	static int trans_A(int state) {
		int masklow = 0x0000ffff;
		int newstate = state & masklow;
		newstate = newstate << 16;
		newstate |= (state >> 16);
		return newstate;
	}

	static void dfs(int state, int pos) {
		if (success || visited.containsKey(state))
			return;
		if (state == finalstate) {
			success = true;
			finalpos = pos;
			return;
		}

		int newstate = state;
		dfs(newstate, pos);

		newstate = trans_A(state);
		res[pos] = 'A';
		dfs(newstate, pos + 1);
		if (success)
			return;

		newstate = trans_B(state);
		res[pos] = 'B';
		dfs(newstate, pos + 1);
		if (success)
			return;
		
		newstate = trans_C(state);
		res[pos] = 'C';
		dfs(newstate, pos + 1);
	}

	public static void main(String[] args) throws IOException {
		BufferedReader f = new BufferedReader(new FileReader("msquare.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("msquare.out")));
		StringTokenizer st = new StringTokenizer(f.readLine());
		int s = 0;
		for(int i = 3; i >= 0; i--) {
			s = set(i, s, Integer.parseInt(st.nextToken()));
		}

		for(int i = 7; i >= 4; i--) {
			s = set(i, s, Integer.parseInt(st.nextToken()));
		}
		dfs(s, 0);
		for(int i = 0; i < finalpos; i++) {
			System.out.print(res[i]);
		}
		System.exit(0);
	}
}
