#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initBlocks(int (*ptr2Blocks)[24],int *ptr2IndexH,int n);
int twoBlockLegal(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n);
int blockFindIndex(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int n);

void blockAbovePutThemBack(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int n);
void moveABlock2BBlockTop(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n);

void moveAontoB(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n);
void moveAoverB(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n);
void pileAontoB(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n);
void pileAoverB(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n);

void printIndex(int (*ptr2Blocks)[24],int *ptr2IndexH,int noIndex);
//noIndex 0...n-1

int main(){
	int n;
	while(scanf("%d",&n) != EOF){
	
		char moveStr[] = "move";
		char pileStr[] = "pile";
		char ontoStr[] = "onto";
		char overStr[] = "over";

		int no1,no2;
		char tmp1[5]={'\0'};
		char tmp2[5]={'\0'};
		int blocks[24][24]={0};
		int indexHeight[24]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1};
		int (*ptr2Blocks)[24] = blocks;
		int *ptr2IndexH = indexHeight;

		initBlocks(ptr2Blocks,ptr2IndexH,n);
		
		while(scanf("%s ",tmp1)){
			if(tmp1[0]=='q'){break;}
			scanf("%d %s %d",&no1,tmp2,&no2);
			//printf("%s %d %s %d\n",tmp1,no1,tmp2,no2);
			if(strcmp(tmp1,moveStr)==0 && strcmp(tmp2,ontoStr)==0){
				moveAontoB(ptr2Blocks,ptr2IndexH,no1,no2,n);	
			}
			else if(strcmp(tmp1,moveStr)==0 && strcmp(tmp2,overStr)==0){
				moveAoverB(ptr2Blocks,ptr2IndexH,no1,no2,n);
			}
			else if(strcmp(tmp1,pileStr)==0 && strcmp(tmp2,ontoStr)==0){
				pileAontoB(ptr2Blocks,ptr2IndexH,no1,no2,n);
			}
			else if(strcmp(tmp1,pileStr)==0 && strcmp(tmp2,overStr)==0){
				pileAoverB(ptr2Blocks,ptr2IndexH,no1,no2,n);
			}
			else{
				printf("?????\n");
			}
		}
		int index;
		for(index=0;index<n;index++){
			printIndex(ptr2Blocks,ptr2IndexH,index);
		}
	}

	return 0;
}

void initBlocks(int (*ptr2Blocks)[24],int *ptr2IndexH,int n){
	int i,j;	
	for(i=0;i<24;i++){
		for(j=0;j<24;j++){
			ptr2Blocks[i][j] = -1;
		}
	}	
	for(i=0;i<n;i++){
		ptr2Blocks[i][0] = i;
		ptr2IndexH[i] = 1;
	}

	return;
}

int twoBlockLegal(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n){
	// a b are two blocks that shoud be checked
	if(blockFindIndex(ptr2Blocks,ptr2IndexH,a,n)<0 ||
			blockFindIndex(ptr2Blocks,ptr2IndexH,b,n)<0){
		return 0;
	}
	if(blockFindIndex(ptr2Blocks,ptr2IndexH,a,n) == 
			blockFindIndex(ptr2Blocks,ptr2IndexH,b,n)){
		return 0;
	}
	if(a == b){return 0;}
	return 1;
}
int blockFindIndex(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int n){
	//a is a block
	if(a>=n || a<0){return -1;}
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<ptr2IndexH[i];j++){
			if(ptr2Blocks[i][j] == a){return i;}
		}
	}
	return -2;
	// -1 out of index boundary
	//-2 block movement have error make data disappear
}

void blockAbovePutThemBack(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int n){
	int HToMove=-1;
	int HChange=0;
	int i;
	int aIndex = blockFindIndex(ptr2Blocks,ptr2IndexH,a,n);
	for(i=0;i<ptr2IndexH[aIndex];i++){
		if(ptr2Blocks[aIndex][i] == a){
			HToMove=1;
			continue;
		}
		if(HToMove == 1){
			int tmp = ptr2Blocks[aIndex][i];
			int tmpIndex = tmp;
			//		if(tmpIndex < 0){printf("error 1\n")continue;}
			ptr2Blocks[aIndex][i] = -1;
			ptr2Blocks[tmpIndex][ptr2IndexH[tmpIndex]] = tmp;
			ptr2IndexH[tmpIndex]++;
			HChange++;
		}
	}
	ptr2IndexH[aIndex] = ptr2IndexH[aIndex] - HChange;
}

void moveABlock2BBlockTop(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n){
	//if(twoBlockLegal(ptr2Blocks,ptr2IndexH,a,b,n) == 0){printf("not legal");return;}
	int aIndex = blockFindIndex(ptr2Blocks,ptr2IndexH,a,n);
	int bIndex = blockFindIndex(ptr2Blocks,ptr2IndexH,b,n);
	int i,j,l=0;
	int HToMove=-1;
	int HChange=0;
	int tmp[24]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	for(i=0;i<ptr2IndexH[aIndex];i++){
		if(ptr2Blocks[aIndex][i] == a){
			HToMove = 1;
		}
		if(HToMove == 1){
			tmp[l]=ptr2Blocks[aIndex][i];
			l++;
			HChange++;
			ptr2Blocks[aIndex][i]=-1;
		}
	}
	ptr2IndexH[aIndex] = ptr2IndexH[aIndex]-HChange;

	for(i=ptr2IndexH[bIndex];i<ptr2IndexH[bIndex]+HChange;i++){
		ptr2Blocks[bIndex][i] = tmp[i-ptr2IndexH[bIndex]];
	}
	ptr2IndexH[bIndex] = ptr2IndexH[bIndex]+HChange;
}


void moveAontoB(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n){
	if(twoBlockLegal(ptr2Blocks,ptr2IndexH,a,b,n) == 0){
		return;
	}	
	blockAbovePutThemBack(ptr2Blocks,ptr2IndexH,a,n);
	blockAbovePutThemBack(ptr2Blocks,ptr2IndexH,b,n);
	moveABlock2BBlockTop(ptr2Blocks,ptr2IndexH,a,b,n);
	return;
}

void moveAoverB(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n){
	if(twoBlockLegal(ptr2Blocks,ptr2IndexH,a,b,n) == 0){
		return;
	}
	blockAbovePutThemBack(ptr2Blocks,ptr2IndexH,a,n);
  	moveABlock2BBlockTop(ptr2Blocks,ptr2IndexH,a,b,n);
	return;
}

void pileAontoB(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n){
	if(twoBlockLegal(ptr2Blocks,ptr2IndexH,a,b,n) == 0){
		return ;
	}
	blockAbovePutThemBack(ptr2Blocks,ptr2IndexH,b,n);
	moveABlock2BBlockTop(ptr2Blocks,ptr2IndexH,a,b,n);
	return;	
}

void pileAoverB(int (*ptr2Blocks)[24],int *ptr2IndexH,int a,int b,int n){
	if(twoBlockLegal(ptr2Blocks,ptr2IndexH,a,b,n) == 0){
		return;
	}
	moveABlock2BBlockTop(ptr2Blocks,ptr2IndexH,a,b,n);
	return;	

}

void printIndex(int (*ptr2Blocks)[24],int *ptr2IndexH,int noIndex){

	int i=0;
	printf("%d:",noIndex);
	for(;i<ptr2IndexH[noIndex];i++){
		printf(" %d",ptr2Blocks[noIndex][i]);
	}
	printf("\n");
}
