int size.
move 5 to size.
loop 5 times[]
add size to sum.
sub 3 from sum.
out newline ,"sum:",sum.
out size , newline.

Keyword int
identifier size
endofline

Keyword move
IntConstant 5
Keyword to
Identifier size
EndOfLine

Keyword
loop
IntConstant
5
Keyword
times
OpenBlock
CloseBlock

Keyword
add
Idenfier
size
Keyword
to
Idenfier
sum
endofline

Keyword
sub
IntConstant
3
Keyword
form
Idenfier
sum
endofline



char degiskenler[100][100];
int degerler[100];

int f=0;
int count=0;
while(f<length){//kayama kontrolünü kaya yapýcak
	if(strcmp(words[f],"Keyword")==0){
		
		if(strcmp(words[f+1],"int")==0){
			if(strcmp(words[f+2],"Identifier")==0){
				if(strcmp(words[f+4],"EndOfLine")==0){
					strcpy(degiskenler[count],words[f+3]);
					strcpy(degerler[count],0);
					count++;
				}
				else{printf("Hata Endofline");
				}
			}	else{printf("Hata Identifier");
				} 
				f = f+5;
		}
		else if((strcmp(words[f+1],"move")==0)){
			int MyInt=0;
			if((strcmp(words[f+2],"IntConstant")==0)){
				MyInt=atoi(words[f+3]);
				if(strcmp(words[f+5],"to")==0){
					if(strcmp(words[f+6],"Identifier")==0){
							if(strcmp(words[f+8],"EndOfLine")==0){
						
							int kaya;
							for(kaya=0; kaya<length ; kaya++){
								if(strcmp(degiskenler[kaya],words[f+7])==0){
									MyInt=degerler[kaya];//dikkat bu hata olabilir
								}
								else{
									printf("Deðiþken daha önce tanýmlanmadý");
								}
							}
						}else{
							printf("Hata Endofline");
						}
					}else{
						printf("Hata Identifier");
					}
				}else{
						printf("Hata to");
					}
			}else{
						printf("Hata IntConstant");
					}
					f = f+9;
		}
		else if((strcmp(words[f+1],"loop")==0)){//çalýþmassa kontorl
			int MyloopInt = 0;
			if((strcmp(words[f+2],"IntConstant")==0)){
				MyloopInt = atoi(words[f+3]);	
				if((strcmp(words[f+5],"times")==0)){
					if((strcmp(words[f+6],"OpenBlock")==0)){
						//burayý doldur hacý f i arttýrmayý unutmayýnn
					}
				}else{
				prinf("HATA times Geerek!")
			}
			}
			else if((strcmp(words[f+2],"Identifier")==0)){
				int kaya;
				for(kaya=0; kaya<length ; kaya++){
					if(strcmp(degiskenler[kaya],words[f+3])==0){
						(strcpy(degerler[kaya],MyloopInt);
						if((strcmp(words[f+5],"times")==0)){
							if((strcmp(words[f+6],"OpenBlock")==0)){
								//burayý doldur hacý f i arttýrmayý unutmayýnn
							}
						}else{
							prinf("HATA times Geerek!")
						}
					}
					else{
						printf("Deðiþken daha önce tanýmlanmadý");
					}
				}
			}else{
				prinf("HATA Int veya Identifier Geerek!")
			}
		}
		else if((strcmp(words[f+1],"add")==0)){
			int MyaddInt1 = 0;
			int MyaddInt2 = 0;
			if((strcmp(words[f+2],"Identifier")==0)){
				int kaya;
				for(kaya=0; kaya<length ; kaya++){
					if(strcmp(degiskenler[kaya],words[f+3])==0){
						MyaddInt1 = degerler[kaya];
						if((strcmp(words[f+5],"to")==0)){
							if((strcmp(words[f+6],"Identifier")==0)){
								int kaya2;
								for(kaya=0; kaya2<length ; kaya2++){
									if(strcmp(degiskenler[kaya2],words[f+7])==0){
										MyaddInt2=degerler[kaya2];//dikkat bu hata olabilir
										MyaddInt2 = MyaddInt2+MyaddInt1;
										degerler[kaya2]=MyaddInt2;
									}
									else{
										printf("Deðiþken daha önce tanýmlanmadý");
									}
								}
							}
						}
					}
					else{
						printf("Deðiþken daha önce tanýmlanmadý");
					}
				}
			}
			else if((strcmp(words[f+2],"IntConstant")==0)){
					MyaddInt1=atoi(words[f+3]);
					if((strcmp(words[f+5],"to")==0)){
						if((strcmp(words[f+6],"Identifier")==0)){
							int kaya2;
							for(kaya=0; kaya2<length ; kaya2++){
								if(strcmp(degiskenler[kaya2],words[f+7])==0){
									MyaddInt2=degerler[kaya2];//dikkat bu hata olabilir
									MyaddInt2 = MyaddInt2+MyaddInt1;
									degerler[kaya2]=MyaddInt2;
								}
								else{
									printf("Deðiþken daha önce tanýmlanmadý");
								}
							}
						}
					}
					
				}
			}
			else if((strcmp(words[f+1],"sub")==0)){
			int MyaddInt1 = 0;
			int MyaddInt2 = 0;
				if((strcmp(words[f+2],"Identifier")==0)){
					int kaya;
					for(kaya=0; kaya<length ; kaya++){
						if(strcmp(degiskenler[kaya],words[f+3])==0){
							MyaddInt1 = degerler[kaya];
							if((strcmp(words[f+5],"from")==0)){
								if((strcmp(words[f+6],"Identifier")==0)){
									int kaya2;
									for(kaya=0; kaya2<length ; kaya2++){
										if(strcmp(degiskenler[kaya2],words[f+7])==0){
											MyaddInt2=degerler[kaya2];//dikkat bu hata olabilir
											MyaddInt2 = MyaddInt2-MyaddInt1;
											degerler[kaya2]=MyaddInt2;
										}
										else{
											printf("Deðiþken daha önce tanýmlanmadý");
										}
									}
								}
							}
						}
						else{
							printf("Deðiþken daha önce tanýmlanmadý");
						}
					}
				}
				else if((strcmp(words[f+2],"IntConstant")==0)){
						MyaddInt1=atoi(words[f+3]);
						if((strcmp(words[f+5],"from")==0)){
							if((strcmp(words[f+6],"Identifier")==0)){
								int kaya2;
								for(kaya=0; kaya2<length ; kaya2++){
									if(strcmp(degiskenler[kaya2],words[f+7])==0){
										MyaddInt2=degerler[kaya2];//dikkat bu hata olabilir
										MyaddInt2 = MyaddInt2-MyaddInt1;
										degerler[kaya2]=MyaddInt2;
									}
									else{
										printf("Deðiþken daha önce tanýmlanmadý");
									}
								}
							}
						}
						
					}
			}
			else if((strcmp(words[f+1],"out")==0)){
				
			}
			
		}
	}
}













