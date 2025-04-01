#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-----------------------------------------------------------------------------
//       check2
//       ----------
// General      : Checks if the serial index and position in the matrix match certain criteria.
// Parameters   :  
//   serial_index - Serial index of the tenant (In)
//   posmat       - Position value in the matrix (In)
// Return Value : Returns 0 if the position matches invalid criteria, otherwise 1.
//-----------------------------------------------------------------------------
int check2(int serial_index, int posmat)
{
    if ((serial_index == 1 && posmat == 2) ||
        (serial_index == 2 && posmat == 1) ||
        (serial_index == 4 && posmat == 3) ||
        (serial_index == 3 && posmat == 4))
    {
        return 0;
    }
    return 1;
}

//-----------------------------------------------------------------------------
//       check1
//       ----------
// General      : Checks if the specified position in the matrix is valid for placing a tenant.
// Parameters   :  
//   serial_index    - Serial index of the tenant (In)
//   mat             - Matrix representing apartments (In)
//   i               - Row index (In)
//   j               - Column index (In)
//   num_of_tenantes - Maximum allowed neighbors for the tenant (In)
// Return Value : Returns 1 if the position is valid, otherwise 0.
//-----------------------------------------------------------------------------
int check1(int serial_index, int mat[12][9], int i, int j, int num_of_tenantes)
{
    int count = 0;
    for (int k = i - 1; k <= i + 1; k++)
    {
        for (int m = j - 1; m <= j + 1; m++)
        {
            if (mat[k][m] != mat[i][j])
            {
                if (mat[k][m] != 0)
                {
                    count++;
                }
                if (!check2(serial_index, mat[k][m]))
                {
                    return 0;
                }
            }
        }
    }
    if (count > num_of_tenantes)
    {
        return 0;
    }
    return 1;
}

//-----------------------------------------------------------------------------
//       writeMatrixToFile
//       ----------
// General      : Writes the matrix representing the apartments to the specified output file.
// Parameters   :  
//   mat      - Matrix representing the apartments (In)
//   filename - Output file name (In)
//-----------------------------------------------------------------------------
void writeMatrixToFile(int mat[12][9], const char* filename)
{
    FILE* output_File = fopen(filename, "w");

    if (output_File == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 8; j++) {
            fprintf(output_File, "%d ", mat[i][j]);
        }
        fprintf(output_File, "\n");
    }

    fclose(output_File);
    printf("Matrix written to %s successfully.\n", filename);
}

//-----------------------------------------------------------------------------
//       a_flat_for_rent
//       ----------
// General      : Reads the tenant information from the input file, checks availability in the matrix, 
//                and assigns the tenants to available spots.
// Parameters   :  
//   input_file_name - Input file name containing tenant information (In)
//-----------------------------------------------------------------------------
void a_flat_for_rent(const char* input_file_name)
{
    FILE* fp = fopen(input_file_name, "r");
    if (fp == NULL)
    {
        printf("Error opening input file!\n");
        return;
    }

    int mat[12][9] = { 0 };
    char outputFile[256];
    fgets(outputFile, sizeof(outputFile), fp);
    outputFile[strcspn(outputFile, "\n")] = '\0';  // Remove newline character

    int serial_index, num_of_tenantes;

    while (fscanf(fp, "%d %d", &serial_index, &num_of_tenantes) != EOF)
    {
        int flag = 0;
        for (int i = 1; i < 11; i++) {
            for (int j = 1; j < 9; j++) {
                if (mat[i][j] == 0 && check1(serial_index, mat, i, j, num_of_tenantes)) {
                    mat[i][j] = serial_index;
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        if (!flag) {
            printf("Tuite and Sons Ltd. is sorry, but the tenant will have to look for an apartment elsewhere.\n");
        }
    }

    fclose(fp);
    writeMatrixToFile(mat, outputFile);
}

int main()
{
    // Open the input file for writing
    FILE* inputFile = fopen("untitled", "w");

    // Check if the file opened successfully
    if (inputFile == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Write the name of the output file
    fprintf(inputFile, "Apartmant1.txt\n");

    // Write the tenant data
    fprintf(inputFile, "1 3\n"); // Lazy chicken, 3 neighbors
    fprintf(inputFile, "2 4\n"); // Ant, 4 neighbors
    fprintf(inputFile, "5 2\n"); // Dove, 2 neighbors
    fprintf(inputFile, "3 1\n"); // Cat, 1 neighbor
    fprintf(inputFile, "4 3\n"); // Pig, 3 neighbors

    // Close the input file
    fclose(inputFile);

    // Process the tenant data
    a_flat_for_rent("untitled");

    return 0;
}
