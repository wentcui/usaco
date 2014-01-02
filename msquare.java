/*
ID: wentcui1
LANG: JAVA
TASK: msquare
 */

import java.io.*;
import java.util.*;

class msquare {
	static HashMap<Integer, Boolean> visited = new HashMap<Integer, Boolean>();
	static int finalstate = 0;
	static char[] res = new char[500];
	static char[] copiedres = new char[500];

	static int get(int state, int pos) {
		int mask = 0x0000000f;
		return ((state & (mask << (4 * pos))) >> (4 * pos) & mask);
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
		newstate += ((state >> 16) & masklow);
		return newstate;
	}

	// wu chi de da biao
	static int finallen = 23;
	static void dfs(int state, int finalstate, int curlen, HashMap<Integer, Integer> visited) {
		if (finalstate == state) {
			if (curlen < finallen) {
				finallen = curlen;
				System.arraycopy(res, 0, copiedres, 0, finallen);
			}
			return;
		}

		if (curlen >= finallen)
			return;
		if (visited.containsKey(state) && visited.get(state) <= curlen)
			return;
		visited.put(state, curlen);

		int nextstate = trans_A(state);
		res[curlen] = 'A';
		dfs(nextstate, finalstate, curlen + 1, visited);

		nextstate = trans_B(state);
		res[curlen] = 'B';
		dfs(nextstate, finalstate, curlen + 1, visited);

		nextstate = trans_C(state);
		res[curlen] = 'C';
		dfs(nextstate, finalstate, curlen + 1, visited);
	}

	public static void main(String[] args) throws IOException {
		BufferedReader f = new BufferedReader(new FileReader("msquare.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("msquare.out")));
		StringTokenizer st = new StringTokenizer(f.readLine());
		int init_s = 0x87651234;
		HashMap<Integer, Integer> visited = new HashMap<Integer, Integer>();
		int curstate, nextstate, curpos, finalpos = 0;
		String path, nextpath;
		char[] res = new char[500];
		Queue<Integer> q1 = new LinkedList<Integer>();
		Queue<Integer> q2 = new LinkedList<Integer>();

		for(int i = 3; i >= 0; i--) {
			finalstate = set(i, finalstate, Integer.parseInt(st.nextToken()));
		}

		for(int i = 4; i <= 7; i++) {
			finalstate = set(i, finalstate, Integer.parseInt(st.nextToken()));
		}
		if (init_s == finalstate) {
			out.println("0\n");
			out.close();
			System.exit(0);
		}
		dfs(init_s, finalstate, 0, visited);
/*
		q1.offer(init_s);
		q2.offer(0);

		while(!q1.isEmpty()) {
			curstate = q1.poll();
			curpos = q2.poll();
			visited.put(curstate, curpos);

			nextstate = trans_A(curstate);
			if (!visited.containsKey(nextstate) || visited.get(nextstate) > curpos + 1) {
				System.out.println(curpos + "ops: " + 'A');
				res[curpos] = 'A';
				if (nextstate == finalstate) {
					finalpos = curpos;
					System.out.println("catched1");
					break;
				}
				q1.offer(nextstate);
				q2.offer(curpos + 1);
			}

			nextstate = trans_B(curstate);
			if (!visited.containsKey(nextstate) || visited.get(nextstate) > curpos + 1) {
				System.out.println(curpos + "ops: " + 'B');
				res[curpos] = 'B';
				if (nextstate == finalstate) {
					finalpos = curpos;
					System.out.println("catched2");
					break;
				}
				q1.offer(nextstate);
				q2.offer(curpos + 1);
			}

			nextstate = trans_C(curstate);
			if (!visited.containsKey(nextstate) || visited.get(nextstate) > curpos + 1) {
				System.out.println(curpos + "ops: " + 'C');
				res[curpos] = 'C';
				if (nextstate == finalstate) {
					finalpos = curpos;
					System.out.println("catched3");
					break;
				}
				q1.offer(nextstate);
				q2.offer(curpos + 1);
			}
		}
		out.println(finalpos + 1);
		for(int i = 0; i <= finalpos; i++) {
			out.print(res[i]);
		}
		out.close();
*/
		out.println(finallen);
		for(int i = 0; i < finallen; i++) {
			out.print(copiedres[i]);
		}
		out.println();
		out.close();
		System.exit(0);
	}
}
