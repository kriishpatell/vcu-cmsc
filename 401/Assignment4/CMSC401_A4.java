// Krish Patel

import java.util.*; 

public class CMSC401_A4 {
    public static void main(String[] args){
        Scanner scr = new Scanner(System.in);

        int rodSize = scr.nextInt(); 
        int numCuts = scr.nextInt();
        int[] cuts = new int[numCuts]; 

        for(int i = 0; i < numCuts; i++){
            cuts[i] = scr.nextInt(); 
        }

        System.out.println(findMinCost(rodSize, cuts));
    }
    
    public static int findMinCost(int length, int[] cuts) {
        int[][] cuttingBoard = new int[cuts.length][cuts.length];
        
        for (int[] val : cuttingBoard) {
            Arrays.fill(val, -1);
        }
        
        Arrays.sort(cuts);
        return recursiveSolution(0, length, cuts, 0, cuts.length - 1, cuttingBoard);
    }
    
    public static int recursiveSolution(int stickStart, int stickEnd, int[] cuts, int leftSegment, int rightSegment, int[][] cuttingBoard) {
        int minCost = Integer.MAX_VALUE;

        if (leftSegment > rightSegment) {
            return 0;
        }

        if (cuttingBoard[leftSegment][rightSegment] != -1) {
            return cuttingBoard[leftSegment][rightSegment];
        }

        for (int i = leftSegment; i <= rightSegment; i++) {
            int leftSideCost = recursiveSolution(stickStart, cuts[i], cuts, leftSegment, i - 1, cuttingBoard);
            int rightSideCost = recursiveSolution(cuts[i], stickEnd, cuts, i + 1, rightSegment, cuttingBoard);
            int segCost = (stickEnd - stickStart) + leftSideCost + rightSideCost;
            minCost = Math.min(minCost, segCost);
        }
        return cuttingBoard[leftSegment][rightSegment] = minCost;
    }
}