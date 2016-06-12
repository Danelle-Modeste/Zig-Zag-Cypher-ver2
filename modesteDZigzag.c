/*813117885_Comp3000 Assignment 1 ZigZagCipher
				
				Write a program that can decrypt messages written in the zig-zag cipher. 
				Your program must read the number of rows used in the cipher,
 				as well as an encrypted message,and must output the original (decrypted) message
 				
 				Method:
 					Place characters in their correct position in the deciphered aray by extracting them row 
 					by row from the ciphered array, using mathematical formulae.
*/

#include<stdio.h>
#include<string.h>


//Returns the maximum number of columns/characters in a particular row
int  getMax(int numPeaks,int numPits,int row,int numLetters,int numRows){
	
	if(row==1) //First row is the same as peaks which is already calculated
		return numPeaks;
	
	if(row==numRows) //Final row is the same as pits which is already calculated
		return numPits;
		
	if(numPeaks > numPits){//The final character may lie before the final peak or in the column after the final peak
		if(((numPeaks-1)*(2*numRows-2)+row) > numLetters)// The number of characters is not enough to permit a character after the last peak
			return 2*numPeaks-2;
			
		return 2*numPeaks-1; //Number of characters sufficient enough to permit a character after the last peak
	}
	//The final character may lie in the column after the last peak or the column after the last pit
	if(((numPits-1)*(2*numRows-2 )+numRows+(numRows-row) ) > numLetters) // The number of characters is not enough to permit a character after the last pit
		return 2*numPits-1;
	
	return 2*numPits; //Number of characters sufficient enough to permit a character after the last pit
}


int main(){
	
	int numPeaks=0,numPits=0,numRows=0,numLetters=0,row=0,col=0,count=0,loc=-1,maxCols=0,i=0;
	char encrypted[10000],decrypted[10000];
	FILE* in= fopen("input.txt","r");
	FILE* out= fopen("output.txt","w");
	
	if(in==NULL){//Checks to see if the input file exist
		printf("Input File Invalid");
		fprintf(out,"INPUT FILE INVALID");
		return 1;
	}
	
	fscanf(in,"%d",&numRows); //Stores the number of rows
	fscanf(in,"%s",&encrypted); //Stores the encrypted message
	fclose(in);
	
	numLetters= strlen(encrypted); //Gets the length of the encrypted message
	
	if(numLetters<=0 || numRows <=0){//Checks to see if the input in the input file is fairly valid
		printf("This input can not be deciphered or there is no input to be deciphered");
		return 1;	
	}
	
	if(numLetters <= numRows){//All characters fall in first column therefore may be printed directly without deciphering
		fprintf(out,"%s",encrypted);
		fclose(out);
		printf("CHECK OUTPUT.TXT FOR RESULTS");
		return 0;
	}
	
	numPeaks=1+(numLetters/(2*numRows-2)); //Number of peaks in the encrypted message
	numPits=1+((numLetters-numRows)/(2*numRows-2)); //Number of pits in the encrypted message
	
	row=1;
	while(row <= numRows){ //Loops from current row to number of rows
		
		col=1;
		maxCols=getMax(numPeaks,numPits,row,numLetters,numRows); //Retrieves maximum number of columns/characters in row
		
		while(col <= maxCols){
			//loc is the location the character belongs in, in the deciphered array
			//Places characters row by row into their correct position in deciphered array
			
			if(col==1){ //Characters in first column is automatically has correct loc index
				loc=row;
			}
			
			else if(row == 1 || row == numRows){ //Row is first or final row
				loc=(col-1)*(2*numRows -2) +row;
			}
					
			else if(col%2==0){ //Column is even and has 1 more large gaps between characters than small ones
				loc=(col/2)*((2*numRows) - (2*row)) + (col/2 -1)*((2*numRows) - (2*(numRows-row +1))) + row ;
			}
				
			else{//Column is odd and has the same number of large and small gaps before the current character
				loc = (col/2)* (((2*numRows) - (2*row)) + ((2*numRows) - 2*(numRows-row +1))) + row;
			}
			
			loc-=1; //To accommodate for array location starting at 0 
			decrypted[loc]=encrypted[count++];
			col++;		
		}
		row++;
	}
	decrypted[numLetters]='\0'; //Adds end of string character at the end of array to make it a string
	fprintf(out,"%s",decrypted);
	
	printf("CHECK OUTPUT.TXT FOR RESULTS");
	fclose(out);
	return 0;
}
