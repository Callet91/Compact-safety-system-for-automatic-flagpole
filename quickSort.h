/* Filename:      quickSort.h
 * Project Name:  Compact Safety system for automatic flagpole 
 * Contributors:  Carl Jensen and David Strom
 * Programme:     Design and Product Realisation (CDEPR)
 * Date:          28-05-2019
 * University:    KTH Royal Institute of Technology 
 * Course:        MF133X Degree Project in Mechatronics
 * 
 * Purpose : 
 *    Header for the quickSort library.
 */

//Include libraries. 
#ifndef quickSort_h   //Include guard.
#define quickSort_h
#include "Arduino.h"

//Class for quicksort algorithm. 
class Sorting{
  public:
    /* Constructor:  Sorting()
     * Purpose:      Setup for the class Sorting.
     * 
     * Input:        None
     * 
     * Output:       None
    */
    Sorting();

    /* Function:    part(double arr[], int low, int high)
     * Purpose:     Creates a pivot point from the last element in the
     *              array. Arrange all elements that is lesser than the
     *              pivot point to the left of this pivot point and all that
     *              is greater to the right. Then done, moves the pivot
     *              point to its proper index in the array and returns this
     *              index. 
     *                
     * Input:       An array with elements        double Array[]  
     *              Lowest index in Array         int farLeftIndex
     *              Highest index in Array        int farRightIndex 
     *                
     * Output:      The index for the pivot points proper position.  
     * 
     * Source:  "QuickSort - GeeksforGeeks", GeeksforGeeks, 2019. [Online]. 
     *          Available: https://www.geeksforgeeks.org/quick-sort/.
     *          [Accessed: 01- May- 2019].
    */
    int part(double Array[], int farLeftIndex, int farRightIndex);

    /* Function:    quickSorting(double Array[], int farLeftIndex, int farRightIndex)
     * Purpose:     Create a partiton from the given inputs and
     *              recursively do so until list is sorted.
     * 
     * Input:       An array with elements.         double Array[]
     *              Lowest index of partion.        int farLeftIndex.
     *              Highest index of partion.       int farRightIndex
     *                
     * Output:      None.  
     * 
     * Source:  "QuickSort - GeeksforGeeks", GeeksforGeeks, 2019. [Online]. 
     *          Available: https://www.geeksforgeeks.org/quick-sort/.
     *          [Accessed: 01- May- 2019].
    */
    void quickSorting(double Array[], int farLeftIndex, int farRightIndex); 
    
    /*Function:     switchElements(double* left, double* right) 
     * Purpose:     Switch two elements with each other.
     * 
     * Input:       Pointer to the left element.  double* left          
     *              Pointer to the right element. double* right
     * 
     * Output:       None.
     * 
     * Source:  "QuickSort - GeeksforGeeks", GeeksforGeeks, 2019. [Online]. 
     *          Available: https://www.geeksforgeeks.org/quick-sort/.
     *          [Accessed: 01- May- 2019].
    */
    void switchElements(double* left, double* right);
};

#endif
