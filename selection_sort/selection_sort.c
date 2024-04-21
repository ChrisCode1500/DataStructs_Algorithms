void selectionSort(int * arr, int size) 
 {  
    int counter = 0;
    int newArray[size];
    int min = arr[0]; 
    while (counter < size)
    {        
        for (int i = counter; i < size - 1; i++)
        {
            if (min > arr[i + 1])
            {
                int temp = min;
                min = arr[i + 1];
                arr[i + 1] = temp;
            }
        }    
        newArray[counter] = min;
        counter++;
        min = arr[counter];
    }
    
    for (int i = 0; i < size; i++)
    {
        arr[i] = newArray[i];
    }
}