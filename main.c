#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

char keyword[11][30] = {"int", "to", "move", "sub", "add", "loop", "times", "out", "newline", "from"};
char degiskenler[100][100];
int degerler[100];
char sentence[1000];
char id[100] , num[10000], strid[20];


int check_keyword(char s[]){
	int i ;
	for(i = 0; i<10 ; i++)
		if(strcmp(s, keyword[i])==0)
			return 1;
		return 0;
}
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
int count=0;
int errorLine = 0;
int BigAdd(char words[100][1000], int length, char degiskenler[100][100],int degerler[100]){

	int f=0;
	while(f<length){ 
		if(strcmp(words[f],"Keyword")==0){
			
//-------------- VARIABLE DECLARATION -----------------

			if(strcmp(words[f+1],"int")==0){
				if(strcmp(words[f+2],"Identifier")==0){
					if(strcmp(words[f+4],"EndOfLine")==0){
						errorLine++;
						strcpy(degiskenler[count], words[f+3]);
						degerler[count] = 0;
						count++;
					}
					else{
						printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
					}
				}
				else{
					printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
				} 
				f = f+5;
			}
			
//----------------- ASSIGNMENT STATEMENT -------------------
			
			else if((strcmp(words[f+1],"move")==0)){
				int MyInt=0;
				int MyInt2=0;
				if((strcmp(words[f+2],"IntConstant")==0)){
					MyInt=atoi(words[f+3]);
					if(strcmp(words[f+5],"to")==0){
						if(strcmp(words[f+6],"Identifier")==0){
							if(strcmp(words[f+8],"EndOfLine")==0){
								errorLine++;
								int kaya;
								int bulundu = 0;
								for(kaya=0; kaya<count ; kaya++){
									if(strcmp(degiskenler[kaya],words[f+7])==0){
										degerler[kaya] = MyInt;
										bulundu = 1;
									}
								}
								if(bulundu != 1){
									printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
									
								}
							}else{
								printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
							}
						}
						else{
							printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
						}
					}
					else{
						printf("ERROR!\n------\n'TO' MISSING! : Error Line %d\a", errorLine);exit(1);
					}
				}
				else if((strcmp(words[f+2],"Identifier")==0)){
					int kaya;
					int bulundu2 = 0;
					for(kaya = 0; kaya < count ; kaya++){
						if(strcmp(degiskenler[kaya],words[f+3])==0){
							MyInt2 = degerler[kaya];
							bulundu2 = 1;
							if((strcmp(words[f+5],"to")==0)){
								if((strcmp(words[f+6],"Identifier")==0)){
									if(strcmp(words[f+8],"EndOfLine")==0){
										errorLine++;
										int kaya2;
								 		int bulundu = 0;
										for(kaya2=0; kaya2<count ; kaya2++){
											if(strcmp(degiskenler[kaya2],words[f+7])==0){
												degerler[kaya2]=MyInt2;
												bulundu = 1;
											}
										}
										if (bulundu!=1){
											printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
										}
									}
									else{
										printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
									}
								}
								else{
									printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
								}
							}
							else{
								printf("ERROR!\n------\n'TO' MISSING! : Error Line %d\a", errorLine);exit(1);
							}
						}	
					}
					if(bulundu2 != 1){
						printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
					}
				}
				else{
					printf("ERROR!\n------\nNEED INTEGER VALUE FOR ASSIGNMENT! : Error Line %d\a", errorLine);exit(1);
				}
				f = f+9;
			}
			
//-------------- LOOP STATEMENT -----------------
		
						else if((strcmp(words[f+1],"loop")==0)){
				char loopWords[100][1000];
				errorLine++;
				int oldF = f;
				int loopLine = 0;
				int loopCnt = 0;
				if((strcmp(words[f+6],"OpenBlock")==0)){
					while(strcmp(words[f+6],"CloseBlock") != 0){
						f++;
						strcpy(loopWords[loopCnt], words[f+6]);
						loopCnt++;
						if(strcmp(words[f+6],"EndOfLine")==0){
							loopLine++;
						}
					}
				}
				else if((strcmp(words[f+6],"Keyword")==0)){
					while(strcmp(words[f+6],"EndOfLine") != 0){
						strcpy(loopWords[loopCnt], words[f+6]);
						f++;
						loopCnt++;
						
					}
					if(strcmp(words[f+6],"EndOfLine")==0){
							strcpy(loopWords[loopCnt], "EndOfLine");
							loopLine++;
					}
				}
				f = oldF;
				int MyloopInt = 0;
				if((strcmp(words[f+2],"IntConstant")==0)){
					MyloopInt = atoi(words[f+3]);	
					if((strcmp(words[f+5],"times")==0)){
						if((strcmp(words[f+6],"OpenBlock")==0)){
							int l;
							for (l = MyloopInt; l > 0; l--){
								BigAdd(loopWords, loopCnt, degiskenler, degerler); 	
							}
							errorLine = errorLine - (loopLine*(MyloopInt-1))+1;
							strcpy(sentence, "");
						}
						else if((strcmp(words[f+6],"Keyword")==0)){
							int l;
							for (l = MyloopInt; l > 0; l--){
								BigAdd(loopWords, loopCnt, degiskenler, degerler); 	
							}
							errorLine = errorLine - (loopLine*(MyloopInt-1))+1;
							strcpy(sentence, "");
						}
						else{
							printf("ERROR!\n------\n'OPENBLOCK' MISSING! : Error Line %d\a", errorLine);exit(1);
						}	
					}
					else{
						printf("ERROR!\n------\n'TIMES' MISSING! : Error Line %d\a", errorLine);exit(1);
					}
				}
				else if((strcmp(words[f+2],"Identifier")==0)){
					int kaya;
					int bulundu = 0;
					for(kaya=0; kaya<count ; kaya++){// length yerine count yazdýk
						if(strcmp(degiskenler[kaya],words[f+3])==0){
							bulundu = 1;
							MyloopInt = degerler[kaya];
							if((strcmp(words[f+5],"times")==0)){
								if((strcmp(words[f+6],"OpenBlock")==0)){
									for (degerler[kaya]; degerler[kaya] > 0; degerler[kaya]--){
										BigAdd(loopWords, loopCnt, degiskenler, degerler);
										
									}
									errorLine = errorLine - (loopLine*(MyloopInt-1))+1;
									strcpy(sentence, "");
								} 
								else if((strcmp(words[f+6],"Keyword")==0)){
									for (degerler[kaya]; degerler[kaya] > 0; degerler[kaya]--){
										BigAdd(loopWords, loopCnt, degiskenler, degerler);
										
									}
									errorLine = errorLine - (loopLine*(MyloopInt-1))+1;
									strcpy(sentence, "");
								}
								else{
									printf("ERROR!\n------\n'OPENBLOCK' MISSING! : Error Line %d\a", errorLine);exit(1);
								}
							}else{
								printf("ERROR!\n------\n'TIMES' MISSING! : Error Line %d\a", errorLine);exit(1);
							}
						}
					}
					if(bulundu != 1){
						printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);	
					}
				}
				else{
					printf("ERROR!\n------\nNEED INTEGER VALUE OR IDENTIFIER FOR ASSIGNMENT! : Error Line %d\a", errorLine);exit(1);
				}
				f = f + 7 + loopCnt;
				errorLine--;
			}
			
//-------------- ADDITION STATEMENT -----------------
			
			else if((strcmp(words[f+1],"add")==0)){
				int MyaddInt1 = 0;
				int MyaddInt2 = 0;
				if((strcmp(words[f+2],"Identifier")==0)){
					int kaya;
					int bulundu2 = 0;
					for(kaya = 0; kaya < count ; kaya++){
						if(strcmp(degiskenler[kaya],words[f+3])==0){
							MyaddInt1 = degerler[kaya];
							bulundu2 = 1;
							if((strcmp(words[f+5],"to")==0)){
								if((strcmp(words[f+6],"Identifier")==0)){
									if(strcmp(words[f+8],"EndOfLine")==0){
										errorLine++;
										int kaya2;
								 		int bulundu = 0;
										for(kaya2=0; kaya2<count ; kaya2++){
											if(strcmp(degiskenler[kaya2],words[f+7])==0){
												MyaddInt2 = degerler[kaya2];
												MyaddInt2 = MyaddInt2+MyaddInt1;
												degerler[kaya2] = MyaddInt2;
												bulundu = 1;
											}
										}
										if (bulundu!=1){
											printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
										}
									}
									else{
										printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
									}
								}
								else{
									printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
								}
							}
							else{
								printf("ERROR!\n------\n'TO' MISSING! : Error Line %d\a", errorLine);exit(1);
							}
						}	
					}
					if(bulundu2 != 1){
						printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
					}
				}
				else if((strcmp(words[f+2],"IntConstant")==0)){
						MyaddInt1=atoi(words[f+3]);
						if((strcmp(words[f+5],"to")==0)){
							if((strcmp(words[f+6],"Identifier")==0)){
								if(strcmp(words[f+8],"EndOfLine")==0){
									errorLine++;
									int kaya2;
									int bulundu= 0;
									for(kaya2 = 0; kaya2 < count ; kaya2++){
										if(strcmp(degiskenler[kaya2],words[f+7])==0){
											MyaddInt2 = degerler[kaya2];
											MyaddInt2 = MyaddInt2 + MyaddInt1;
											degerler[kaya2] = MyaddInt2;
											bulundu = 1;
										}	
									}
									if(bulundu!=1){
										printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
									}
								}
								else{
									printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
								}
							}
							else{
								printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
							}
						}
						else{
							printf("ERROR!\n------\n'TO' MISSING! : Error Line %d\a", errorLine);exit(1);
						}	
				}
				f = f+9;
			}
			
//-------------- SUBTRACTION STATEMENT ----------------
			
			else if((strcmp(words[f+1],"sub")==0)){
				int MyaddInt1 = 0;
				int MyaddInt2 = 0;
				if((strcmp(words[f+2],"Identifier")==0)){
					int kaya;
					int bulundu2 = 0;
					for(kaya=0; kaya<count ; kaya++){
						if(strcmp(degiskenler[kaya],words[f+3])==0){
							MyaddInt1 = degerler[kaya];
							bulundu2 = 1;
							if((strcmp(words[f+5],"from")==0)){
								if((strcmp(words[f+6],"Identifier")==0)){
									int kaya2;
									int bulundu = 0;
									for(kaya2=0; kaya2<count ; kaya2++){
										if(strcmp(degiskenler[kaya2],words[f+7])==0){
											MyaddInt2 = degerler[kaya2];
											MyaddInt2 = MyaddInt2 - MyaddInt1;
											degerler[kaya2] = MyaddInt2;
											bulundu = 1;
										}
									}
									if (bulundu!=1){
										printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
									}
								}
								else{
									printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
								}
							}
							else{
								printf("ERROR!\n------\n'TO' MISSING! : Error Line %d\a", errorLine);exit(1);
							}
						}	
					}
					if(bulundu2 != 1){
						printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
					}
				}
				else if((strcmp(words[f+2],"IntConstant")==0)){
						MyaddInt1 = atoi(words[f+3]);
						if((strcmp(words[f+5],"from")==0)){
							if((strcmp(words[f+6],"Identifier")==0)){
								int kaya2;
								int bulundu= 0;
								for(kaya2=0; kaya2<count ; kaya2++){
									if(strcmp(degiskenler[kaya2],words[f+7])==0){
										MyaddInt2 = degerler[kaya2];
										MyaddInt2 = MyaddInt2 - MyaddInt1;
										degerler[kaya2] = MyaddInt2;
										bulundu = 1;
									}	
								}
								if(bulundu!=1){
									printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
								}
							}
							else{
								printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
							}
						}
						else{
							printf("ERROR!\n------\n'TO' MISSING! : Error Line %d\a", errorLine);exit(1);
						}	
				}
				f = f+9;
			}
			
//-------------- OUTPUT STATEMENT -----------------

			else if((strcmp(words[f+1],"out")==0)){
				
				//out newline.
				if (strcmp(words[f+3], "newline") == 0){
					strcat(sentence, "\n");
					if(strcmp(words[f+4],"Seperator")==0){
						if (strcmp(words[f+5], "StringConstant") == 0){
							strcat(sentence, words[f+6]);
							strcat(sentence, " ");
							if(strcmp(words[f+7],"Seperator")==0) {
								if(strcmp(words[f+8], "Identifier") == 0) {
									int kaya3;
									int bulundu = 0;
									for(kaya3=0; kaya3<count ; kaya3++){

										if(strcmp(degiskenler[kaya3],words[f+9])==0){
											char text[101];
											sprintf(text, "%d", degerler[kaya3]);
											strcat(sentence, text);
											strcat(sentence, " ");
											bulundu = 1;
											if(strcmp(words[f+10],"EndOfLine")==0) {
												errorLine++;
												printf("%s",sentence);
												strcpy(sentence,"");
												f = f+11;
											}
											else{
												printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
											}			
										}
									}
									
									if (bulundu != 1){
										printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
									}
								}
								else{
									printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
								}
									
							}
							else if(strcmp(words[f+7],"EndOfLine")==0){
								errorLine++;
								printf("%s",sentence);
								strcpy(sentence,"");
								f = f+8;	
							}
							else{
								printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
							}	
						}
						else{
							printf("ERROR!\n------\nSTRINGCONSTANT MISSING! : Error Line %d\a", errorLine);exit(1);
						}							

					}
					else if(strcmp(words[f+4],"EndOfLine")==0){
						errorLine++;
						printf("%s",sentence);
						strcpy(sentence,"");
						f = f+5;
					}
					else{
						printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
					}
				}
				else if (strcmp(words[f+2], "StringConstant") == 0){
					strcat(sentence, words[f+3]);
					strcat(sentence, " ");
					if(strcmp(words[f+4],"Seperator")==0) {
						if(strcmp(words[f+5], "Identifier") == 0){
							int kaya4;
							int bulundu=0;
							for(kaya4=0; kaya4<count ; kaya4++){
								if(strcmp(degiskenler[kaya4],words[f+6])==0){
									
									char text[101];
									sprintf(text, "%d", degerler[kaya4]);
									strcat(sentence, text); 
									strcat(sentence, " ");
									bulundu = 1;
									if(strcmp(words[f+7],"EndOfLine")==0) {
										errorLine++;
										printf("%s",sentence);
										strcpy(sentence,"");
								    	f = f+8;
									}
									else{
										printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
									}							
								}
							}
							if(bulundu!=1){
								printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
							}
						}
						else{
							printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
						}
							
					}
					else if(strcmp(words[f+4],"EndOfLine")==0){
						errorLine++;
						printf("%s",sentence);
						strcpy(sentence,"");
						f = f+5;
					}
					else{
						printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
					}
				
				}			
				else if((strcmp(words[f+2],"Identifier")==0)) {
					int kaya5;
					int bulundu = 0;
			    	for(kaya5=0; kaya5<count ; kaya5++){
				   	    if(strcmp(degiskenler[kaya5],words[f+3])==0){
				       		char text[101];
							sprintf(text, "%d", degerler[kaya5]);
							strcat(sentence, text);
							strcat(sentence, " ");
							bulundu = 1;
							if(strcmp(words[f+4],"Seperator")==0){
								if(strcmp(words[f+6], "newline") == 0){
									strcat(sentence, "\n");
									if(strcmp(words[f+7],"EndOfLine")==0) {
										errorLine++;
										printf("%s",sentence);
										strcpy(sentence,"");
										f = f+8;
									}
									else{
										printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
									}										
								}else{
									printf("ERROR!\n------\n'NEWLINE' MISSING! : Error Line %d\a", errorLine);exit(1);
								}	
							}
							else if (strcmp(words[f+4],"EndOfLine")==0){
								errorLine++;
								printf("%s",sentence);
								strcpy(sentence,"");
								f = f+5;
							}
							else{
								printf("ERROR!\n------\nLINE OF CODE IS UNFINISHED! : Error Line %d\a", errorLine);exit(1);
							}	
				    	}
				   }
				   if(bulundu!=1){
				   		printf("ERROR!\n------\nVARIABLE NOT DEFINED BEFORE! : Error Line %d\a", errorLine);exit(1);
				   }
				}
				else {
					printf("ERROR!\n------\nIDENTIFIER MISSING! : Error Line %d\a", errorLine);exit(1);
				}			
			}
		}
		else{
			break;
		}
	}
}







int main() {
	FILE *fp1, *fp2 , *fp3 ,*fp4;
	char c;
	int state = 0;
	int i=0, j=0;
	int a = 1;
	
	
	char scanname[100];
	printf("\n----------------- WELCOME -----------------\n\nPlease, enter file name: ");
	gets(scanname);
	printf("___________________________________________\n\n");
	char names[2][30];
	char *token = strtok(scanname, " ");
    
	int h;
    for (h = 0; h<2; h++){
	  strcpy(names[h], token);
      token = strtok(NULL, " ");
	}
	
	char* temp = concat(names[1], ".");
	char* filename = concat(temp, names[0]);	
	char* filenamelx = concat(temp, "lx");
	char* filenamec = concat(temp, "c");
	
	if ((fp1 = fopen(filename, "r")) == NULL){
       printf("ERROR! FILE NOT FOUND!\a");
	
       exit(1);
   }
   else
   		fp2 = fopen(filenamelx, "w");
	
	
	
	
	while (!feof(fp1) && a){
        c = fgetc(fp1);
		
		switch (state){
			case 0:
				if(isalpha(c) || c=='_'){
					state = 1;
					id[i++] = c;
				}
				else if (isdigit(c) ){
					state = 2;
					num[j++] = c;
				}
				else if (c==' ' || c=='\t' || c=='\n' )
					state =0;
				else if (c=='.')
					state =3;
				else if (c==',')
					state =4;
				else if (c=='[')
					state =5;
				else if (c==']')
					state =6;
				else if (c == '"')
					state = 7;					
				else if (c == '{')
					state = 8;
			    else if (c=='-'){
					state =9;
					num[j++] = c;
				}
					
				else if(c == '\377'){ // End of file
					a = 0;
				}
				
				else
					printf("ERROR! '%c' UNRECOGNIZED CHARACTER!\a\n", c);
				break;
			
		
			case 1:
				if(isalnum(c) || c == '_'){
					state = 1;	
					id [i++] = c;
				}
				else{
					
					id[i] = '\0';
					int len1 = strlen(id);
					if(check_keyword(id))
						fprintf(fp2, "Keyword %s\n", id);
					else if(len1>20){
						printf("\nERROR!, VARIABLE MORE THAN 20 LETTERS!\n\a");
						a = 0;
					}
					else {
						fprintf(fp2, "Identifier %s\n", id);
					}
					state = 0;
					i=0;
					ungetc(c, fp1);	
				}
				break;
				
				
			case 2:
				if (isdigit(c)){
					num[j++] = c;
					state = 2;
				}
				else {
					num[j] = '\0';
					int len = strlen(num);
					if (len > 100){
						printf("\nERROR!, INTEGER MORE THAN 100 DECIMAL DIGITS!\n\a");
						a =0;
					}
					fprintf(fp2, "IntConstant %s\n", num);
					state = 0;
					j = 0;	
				}
				break;
				
			
			case 3:
				fprintf(fp2, "EndOfLine\n");
				state = 0;
				ungetc(c, fp1);	
				break;
				
				
			case 4:
				fprintf(fp2, "Seperator\n");
				state = 0;
				ungetc(c, fp1);
				break;
				
			
			case 5:
				fprintf(fp2, "OpenBlock\n");
				state = 0;
				ungetc(c, fp1);	
				break;
				
			
			case 6:
				fprintf(fp2, "CloseBlock\n");
				state = 0;
				ungetc(c, fp1);	
				break;
				
			case 7:
				if(c != '"'){
					state = 7;	
					strid [i++] = c;
					if(c==EOF){
						printf("\nERROR!, STRING START BUT DOES NOT TERMINATE BEFORE THE END OF FILE!\n\a");
					}
				}
				else{
					strid[i] = '"';
					
					fprintf(fp2, "StringConstant %c%s\n", '"', strid);
					
						
					
					state = 0;
					i=0;
				}
				break;
				
				
			case 8:
				if(c=='}'||c==EOF){				
					if(c==EOF){
						printf("\nERROR!, COMMENT START BUT DOES NOT TERMINATE BEFORE THE END OF FILE!\n\a");
					}
					state = 0;
					i=0;
				}
				else{
					state = 8;
				}
				break;
				
				
			case 9:
				if (isdigit(c)){
					num[j++] = c;
					state = 2;
				}
				else if (c == '-'){
					printf("\nERROR!, UNVALID INTEGER ASSIGNMENT!\n\a");	
					a = 0;	
				}
			
				break;	
		}	
	}
	fclose(fp1);
	fclose(fp2);
	
		
	
	
	
	
	
	fp3 = fopen(filenamelx, "r");





	char words[100][1000];
	int k = 0 ;
	int length = 0;
	
	while (!feof(fp3)) {
		
		char satir[200];
		fgets(satir, 200,fp3);
				

		
		

		
		if (strcmp(satir,"EndOfLine\n")!=0 && strcmp(satir,"OpenBlock\n")!=0 && strcmp(satir,"CloseBlock\n")!=0 && strcmp(satir,"Seperator\n")!=0) {
			char names2[2][100];
			char *token2 = strtok(satir, " ");
			
			int v;
	    	for (v = 0; v<2; v++){
		 		strcpy(names2[v], token2);
	      		token2 = strtok(NULL, " ");
			}
			
			strcpy(words[k], names2[0]);
			char *str = names2[1];
			str[strlen(str)-1] = '\0';
			strcpy(words[k+1], str);
			k=k+2;
			length = length+2;
		}
		
		else if(strcmp(satir,"EndOfLine\n")==0) {
			strcpy(words[k], "EndOfLine");
			k++;
			length++;
			
		}
		
		else if(strcmp(satir,"OpenBlock\n")==0) {
			strcpy(words[k], "OpenBlock");
			k++;
			length++;
		}
		
		else if(strcmp(satir,"CloseBlock\n")==0) {
			strcpy(words[k], "CloseBlock");
			k++;
			length++;
		}
		
		else if(strcmp(satir,"Seperator\n")==0) {
			strcpy(words[k], "Seperator");
			k++;
			length++;
		}

	}

	strcpy(words[length-1], "bitti" );
	
	Sleep(500);

	printf("\n///////////////////////////////////////////\n");
	printf(  "///////////////// OUTPUT //////////////////\n");
	printf(  "///////////////////////////////////////////\n\n");
	
	Sleep(500);
	
	BigAdd(words,length, degiskenler, degerler);
	
	Sleep(1200);
	
	printf("\n\n___________________________________________\n\nDESIGNED BY;\n____________\n\n-> Cemil CESUR\n-> Ersin ELMAS\n-> Emre ERGENC\n-> Emre KAYA\n");
	
	
	return 0;
}
