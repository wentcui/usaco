
/*
ID: wentcui1
LANG: JAVA
TASK: castle
*/

import java.io.*;
import java.util.*;

public class castle {
	static class point{
		int x;
		int y;
		public point(int a, int b) {
			this.x = a;
			this.y = b;
		}
	}
	static class wall{
		int x;
		int y;
		char d;
		public wall(int a, int b, char direction) {
			this.x = a;
			this.y = b;
			this.d = direction;
		}
	}
	public static int bfs(int[][] matrix, int[][] areamatrix, int x, int y, int nr) {
		Queue<point> q = new LinkedList<point>();
		int area = 0;
		q.offer(new point(x, y));
		while(!q.isEmpty()) {
			point p = q.poll();
			x = p.x;
			y = p.y;
			
			area++;
			int v = matrix[x][y];
			areamatrix[x][y] = nr;
			if (v == 15) continue;
			
			if ((v & 1) == 0 && areamatrix[x][y - 1] == 0) {
				q.offer(new point(x, y - 1));
			}
			if ((v & 2) == 0 && areamatrix[x - 1][y] == 0) {
				q.offer(new point(x - 1, y));
			}
			if ((v & 4) == 0 && areamatrix[x][y + 1] == 0) {
				q.offer(new point(x, y + 1));
			}
			if ((v & 8) == 0 && areamatrix[x + 1][y] == 0) {
				q.offer(new point(x + 1, y));
			}
		}
		return area;
	}
	public static void main(String[] args) throws IOException {
		// Use BufferedReader rather than RandomAccessFile; it's much faster
		BufferedReader f = new BufferedReader(new FileReader("castle.in"));
		// input file name goes above
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter(
				"castle.out")));
		// Use StringTokenizer vs. readLine/split -- lots faster
		StringTokenizer st = new StringTokenizer(f.readLine());
		// Get line, break into tokens
		int col = Integer.parseInt(st.nextToken()); // first integer
		int row = Integer.parseInt(st.nextToken());
		int[][] matrix = new int[row][col];
		int[][] areamatrix = new int[row][col];
		int[] areamap = new int[2500];
		int area_nr = 0;
		int max_area = 0;
		int merge_max_area = 0;
		wall walle = null;
		wall walln = null;
		for(int i = 0; i < row; i++) {
			st = new StringTokenizer(f.readLine());
			for(int j = 0; j < col; j++) {
				matrix[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		
		for(int i = 0; i < row; i++) {
			for(int j = 0; j < col; j++) {
				if(areamatrix[i][j] == 0) {
					area_nr++;
					areamap[area_nr] = bfs(matrix, areamatrix, i, j, area_nr);
					if (areamap[area_nr] > max_area)
						max_area = areamap[area_nr];
				}
			}
		}
		for(int j = 0; j < col; j++) {
			for(int i = row - 1; i >= 0; i--) {
				if (j < col - 1 && areamatrix[i][j] != areamatrix[i][j + 1]) {
					int newarea = areamap[areamatrix[i][j]] + areamap[areamatrix[i][j + 1]];
					if (newarea > merge_max_area) {
						merge_max_area = newarea;
						walle = new wall(i + 1, j + 1, 'E');
					}
				}
				if (i > 0 && areamatrix[i][j] != areamatrix[i - 1][j]) {
					int newarea = areamap[areamatrix[i][j]] + areamap[areamatrix[i - 1][j]];
					if (newarea > merge_max_area) {
						merge_max_area = newarea;
						walln = new wall(i + 1, j + 1, 'N');
					}
				}
			}
		} 
		out.println(area_nr);
		out.println(max_area);
		out.println(merge_max_area);
		if (walle != null) {
			out.println(walle.x + " " + walle.y + " " + walle.d);
		} else
			out.println(walln.x + " " + walln.y + " " + walln.d);
		out.close();
		System.exit(0);
	}
}
