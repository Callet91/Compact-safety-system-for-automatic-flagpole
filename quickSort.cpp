/* Filename:      quickSort.cpp
 * Project Name:  Compact Safety system for automatic flagpole 
 * Contributors:  Carl Jensen and David Strom
 * Programme:     Design and Product Realisation (CDEPR)
 * Date:          28-05-2019
 * University:    KTH Royal Institute of Technology 
 * Course:        MF133X Degree Project in Mechatronics
 * 
 * Purpose: 
 *    Library for the quicksort algorithm.
 */

//Include libraries. 
#include "Arduino.h"
#include "quickSort.h"

/* Constructor: Sorting()
 * Purpose:     Setup for the class Sorting.
 * 
 * Input:       None
 * 
 * Output:      None
*/
Sorting::Sorting(){
}

/* Function:    switchElements(double* left, double* right) 
 * Purpose:     Switch two elements with each other.
 * 
 * Input:       Pointer to the left element.  double* left               
 *              Pointer to the right element. double* right
 * 
 * Output:      None.
 * 
 * Source:      "QuickSort - GeeksforGeeks", GeeksforGeeks, 2019. [Online]. 
 *              Available: https://www.geeksforgeeks.org/quick-sort/.
 *              [Accessed: 01- May- 2019].
*/
void Sorting::switchElements(double* left, double* right) { 
    double temp = *left;  //Temporary placeholder for the left value.
    *left = *right;         //Overwrite the the left value with the right.
    *right = temp;          //Overwrite the the rigth value with the left.
} 


/* Function:    part(double arr[], int low, int high)
 * Purpose:     Creates a pivot point from the last element in the array.
 *              Arrange all elements that is lesser than the pivot point to
 *              the left of this pivot point and all that is greater to the
 *              right. Then done, moves the pivot point to its proper index
 *              in the array and returns this index. 
 *                
 * Input:       An array with elements        double Array[]               
 *              Lowest index in Array         int farLeftIndex
 *              Highest index in Array        int farRightIndex 
 *                
 * Output:      The index for the pivot points proper position.  
 * 
 * Source:      "QuickSort - GeeksforGeeks", GeeksforGeeks, 2019. [Online]. 
 *              Available: https://www.geeksforgeeks.org/quick-sort/.
 *              [Accessed: 01- May- 2019].
*/
int Sorting::part(double Array[], int farLeftIndex, int farRightIndex) { 
    //Creates a pivot point from the last element in array.
    double piv = Array[farRightIndex]; 
    
    //Keeps track of index lower than the pivot points value.
    int i = (farLeftIndex - 1);          
    
    //Goes through every element in array and places everything smaller than the pivot point to the left. 
    for (int j = farLeftIndex; j <= farRightIndex - 1; j++){    
        if (Array[j] <= piv)                                              
        { 
            i = i + 1;    
            switchElements(&Array[i], &Array[j]); 
        } 
    } 
    
    //When done, move the pivot point to its proper position. Now everything that is greater than the pivot point is to the right.
    switchElements(&Array[i + 1], &Array[farRightIndex]);       
    return (i + 1); 
} 


/* Function:    quickSorting(double Array[], int farLeftIndex, int farRightIndex)
 * Purpose:     Create a partiton from the given inputs and recursively do
 *              so until list is sorted.
 * 
 * Input:       An array with elements.         double Array[]
 *              Lowest index of partion.        int farLeftIndex.
 *              Highest index of partion.       int farRightIndex
 *                
 * Output:      None.  
 * 
 * Source:      "QuickSort - GeeksforGeeks", GeeksforGeeks, 2019. [Online]. 
 *              Available: https://www.geeksforgeeks.org/quick-sort/.
 *              [Accessed: 01- May- 2019].
*/
void Sorting::quickSorting(double Array[], int farLeftIndex, int farRightIndex){ 
    //If the farLeftIndex is the same as the farRightIndex, there is only one element in the array and no need to sort it.
    if (farLeftIndex < farRightIndex){        
     
        //Creates a partion and places the pivot point to its proper position in the array. 
        int partionIndex = part(Array, farLeftIndex, farRightIndex); 

        //Recursively do the same thing but for the left and right part of the array.
        quickSorting(Array, farLeftIndex, partionIndex - 1); 
        quickSorting(Array, partionIndex + 1, farRightIndex); 
    } 
} 
