
int** generate(int numRows, int* returnSize, int** returnColumnSizes) 
{   
    int count = 1;
    int k = numRows;
    for(int i = 0; i < numRows; i++)
    {
        for(int j = numRows-k+1; i < 0; j++)
        {
        if(i == 0)
        {
        *returnColumnSizes = (int*) malloc(1 * sizeof(int*));
        returnColumnSizes[i][j] == 1;
        j++;
        count++;
        }
        returnColumnSizes[i][j] = returnColumnSizes[i-1][j-1] + returnColumnSizes[i][j-1];
        count++;

        *returnColumnSizes = realloc(*returnColumnSizes, count+1 * sizeof(int));
        }
        returnSize = (int*) malloc(count+1 * sizeof(int*));
        *returnSize = returnColumnSizes[0][0];
    
}
      return *returnSize;
}
