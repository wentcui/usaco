/*
*/

import java.io.*;
import java.util.*;

class milk2 {
	static class Interval {
		int start;
		int end;
		public Interval(int s, int e) {
			this.start = s;
			this.end = e;
		}
	}
	static final Comparator<Interval> INTERVAL_ORDER = new Comparator<Interval>(){
        public int compare (Interval i, Interval j) {
            return new Integer(i.start).compareTo(new Integer(j.start));
        }
    };
    public static ArrayList<Interval> merge(ArrayList<Interval> intervals) {
        // Start typing your Java solution below
        // DO NOT wriintervalste main() function
        int len = intervals.size();
        if (len < 2)
            return intervals;
            
        Collections.sort(intervals, INTERVAL_ORDER);
        ArrayList<Interval> ret = new ArrayList<Interval>();
        ret.add(intervals.get(0));
        
        for(int i = 1; i < len; i++) {
           Interval last = ret.get(ret.size() - 1);
           Interval cur = intervals.get(i);
           if (cur.start > last.end) {
               ret.add(cur);
           } else if (last.end < cur.end) {
               last.end = cur.end;
           }
        }
        
        return ret;
    }

	public static void main(String[] args) throws IOException{
		BufferedReader f = new BufferedReader(new FileReader("milk2.in"));
		// input file name goes above
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("milk2.out")));
		// Use StringTokenizer vs. readLine/split -- lots faster
		StringTokenizer st = new StringTokenizer(f.readLine());
		// Get line, break into tokens
		ArrayList<Interval> intervals = new ArrayList<Interval>();
		int longestMilked = 0, longestNotMilked = 0;
		int n = Integer.parseInt(st.nextToken());    // first integer

		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(f.readLine());
			int s = Integer.parseInt(st.nextToken());
			int e = Integer.parseInt(st.nextToken());
			
			intervals.add(new Interval(s, e));
		}
		intervals = merge(intervals);
		for(int i = 0; i < intervals.size(); i++) {
			Interval in = intervals.get(i);
			if (in.end - in.start > longestMilked)
				longestMilked = in.end - in.start;
			if (i < intervals.size() - 1) {
				if (intervals.get(i + 1).start - in.end > longestNotMilked)
					longestNotMilked = intervals.get(i + 1).start - in.end;
			}
		}
		
		out.println(longestMilked + " " + longestNotMilked);                           // output result
		out.close();                                  // close the output file
		System.exit(0); 
	}
}
