// Krish Patel

import java.util.Scanner;

public class CMSC401_A1 {
    public static String findMajorityElement(int[] nums){
        // Initialize counters for possibly 2 M.E. candidates
        int candidate1 = 0, candidate2 = 0;
        int counter1 = 0, counter2 = 0;

        // Find possible candidates
        for (int num : nums) {
            if (num == candidate1) {
                counter1++;
            } else if (num == candidate2) {
                counter2++;
            } else if (counter1 == 0) {
                candidate1 = num;
                counter1 = 1;
            } else if (counter2 == 0) {
                candidate2 = num;
                counter2 = 1;
            } else {
                counter1--;
                counter2--;
            }
        }

        // Counter number of M.E. candidates
        counter1 = 0; counter2 = 0;

        for(int num : nums){
            if(num == candidate1){
                counter1++;
            } else if(num == candidate2){
                counter2++;
            }
        }

        // Put M.E. into string to be returned if they exist
        String result = "";

        if(counter1 > nums.length/3 && counter2 > nums.length/3){
            if(candidate1 < candidate2){
                result += candidate1 + " " + candidate2;
            } else {
                result += candidate2 + " " + candidate1;
            }
        } else if (counter1 > nums.length/3){
            result += candidate1;
        } else if (counter2 > nums.length/3){
            result += candidate2;
        } else {
            result += "-1";
        }

        return result;
    }
    
    public static void main(String[] args){
        // Initializing and populating array
        Scanner scr = new Scanner(System.in);
        int numElements = scr.nextInt(); 
        int[] elementArray = new int[numElements];

        for(int i = 0; i < numElements; i++){
            elementArray[i] = scr.nextInt(); 
        }

        // Display M.E. values
        System.out.println(findMajorityElement(elementArray));
    }
}