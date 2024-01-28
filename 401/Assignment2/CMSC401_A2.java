// Krish Patel

import java.util.Scanner;

public class CMSC401_A2 {
    // Selection algorithm to find the k-th smallest element in an unordered list
    public static int quickSelect(int[] array, int start, int end, int k){
        int pivotIndex = start + (int)(Math.random() * (end - start + 1));
        swap(array, pivotIndex, end);
        pivotIndex = partition(array, start, end);

        if(k - 1 == pivotIndex){
            return array[k - 1];
        } else if (k - 1 > pivotIndex){
            return quickSelect(array, pivotIndex + 1, end, k); 
        } else {
            return quickSelect(array, start, pivotIndex - 1, k);
        }        
    }

    // Partition similar to quicksort - considers last element as pivot and adds 
    // elements with less value to the left and higher to the right, changing pivot 
    // positions
    public static int partition(int[] array, int start, int end){
        int pivot = array[end];
        int pivotIndex = start;
        
        for(int i = start; i <= end; i++){
            if(array[i] < pivot){
                swap(array, i, pivotIndex);
                pivotIndex++; 
            }
        }

        swap(array, end, pivotIndex);
        return pivotIndex;
    }

    // Supporting swap function for partition
    public static void swap(int[] array, int i, int j){
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp; 
    }

    // Find total sum of size array elements
    public static int totalSum(int[] array){
        int sum = 0;
        for(int size : array){
            sum += size;
        }
        return sum;
    }

    // Find median of powerline expenses array
    public static int findMedian(int[] array){
        int x = (int) Math.floor(array.length/2);
        return quickSelect(array, 0, array.length - 1, x); 
    }

    // Driver code
    public static void main(String[] args){
        Scanner scr = new Scanner(System.in);
        int numHouses = scr.nextInt(); 
        
        int[] positions = new int[numHouses];
        int[] sizes = new int[numHouses];

        for(int i = 0; i < numHouses; i++){
            positions[i] = scr.nextInt();
            sizes[i] = scr.nextInt();
        }

        int varTotalSum = totalSum(sizes);
        int[] plArray = new int[varTotalSum]; 
        
        int pointer = 0;

        for(int i = 0; i < sizes.length; i++){
            int current = sizes[i];
            for(int j = 0; j < current; j++){
                plArray[pointer] = positions[i];
                pointer++;
            }
        }

        System.out.println(findMedian(plArray));
        scr.close();
    }
}