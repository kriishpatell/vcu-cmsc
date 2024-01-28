// Krish Patel

import java.util.Scanner;
import java.util.ArrayList;

public class CMSC401_A0{
    public static void main(String[] args){
        // Initialize scanner, number of lines variable, and output list
        Scanner scr = new Scanner(System.in);
        int numLines = scr.nextInt();
        ArrayList<Integer> output = new ArrayList<>();

        // Go through number of arrays 
        for(int i = 0; i < numLines; i++){
            int arrLen = scr.nextInt();
            int[] numArr = new int[arrLen];

            // Add consecutive numbers to list
            for(int j = 0; j < arrLen; j++){
                numArr[j] = scr.nextInt();
            }

            // Get two numbers based on last two index values
            int firstNum = numArr[arrLen - 2];
            int secondNum = numArr[arrLen - 1];

            // Add higher number to list
            int higher = Math.max(numArr[firstNum - 1], numArr[secondNum - 1]);
            output.add(higher);
        }

        // Return list
        for(int max : output){
            System.out.println(max);
        }

        scr.close();
    }
}