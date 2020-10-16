/** BOOTH'S ALGORITHM FOR BINARY MULTIPLICATION 8 BIT **/
#include<stdio.h>
#include <math.h>

/* Declaring Functions */
int booth[16]={0},M[8]={0},M_[8]={0},q=0;
void multiplicand(int);
void multiplier(int);
void add(int m[8]);
void arithmeticShiftRight();
void neg();
int dec();

/* Main Function */
int main(){
	int a,b,n=8,i,sum=0;
	printf("Enter the Multiplicand (less than 128 and greater then -129): ");
	scanf("%d",&a);
	printf("Enter the Multiplier: ");
	scanf("%d",&b);
	
	multiplicand(a);
	multiplier(b);
	neg();
	
	while(n>0){
		if(booth[15]==0&&q==1){
			add(M); //AC=AC+M
		}else if(booth[15]==1&&q==0){
			add(M_); //AC=AC-M
		}
		arithmeticShiftRight();
		n--;
	}
	printf("The output in binary is: ");
	for(i=0;i<16;i++){
		printf("%d",booth[i]);
	}
	printf("\nThe output in decimal is: ");
	printf("%d",dec());
	return 0;
	
}
/* MAIN ENDS */


/*FUNCTIONS BEGIN HERE  */

/* Converts multiplier to binary and adds in booth array as Q*/
void multiplier(int a){
	if(a>=0){
		int i=15;
		while(a>0){
			int rem=a%2;
			a=a/2;
			booth[i]=rem;
			i--;
		}
	}else{
		a=a+128;
		int i=15;
		while(a>0){
			int rem=a%2;
			a=a/2;
			booth[i]=rem;
			i--;
		}
		booth[8]=1;
	}
	
}

/*Converts multiplicand to binary*/
void multiplicand(int a){
	if(a>=0){
		int i=7;
		while(a>0){
			int rem=a%2;
			a=a/2;
			M[i]=rem;
			i--;
		}
	}else{
		a=a+128;
		int i=7;
		while(a>0){
			int rem=a%2;
			a=a/2;
			M[i]=rem;
			i--;
		}
		M[0]=1;
	}
	
}

/*ADDS M or -M to AC*/
void add(int m[8]){
	int sum=0,carry=0,i;
	for(i=7;i>=0;i--){
		sum=m[i]+booth[i]+carry;
		if(sum==2){
			sum=0;
			carry=1;
		}else if(sum==3){
			sum=1;
			carry=1;
		}else{
			carry=0;
		}
		booth[i]=sum;
	}	
}

/* neg() creates -M from M */
void neg(){
	int i,carry=0,sum=0;
	for(i=0;i<8;i++){
		if(M[i]==0){
			M_[i]=1;
		}else{
			M_[i]=0;
		}
	}
	sum=1+M_[7];
	if(sum==2){
		carry=1;
		sum=0;
	}
	M_[7]=sum;
	for(i=6;i>=0;i--){
		sum=M_[i]+carry;
		if(sum==2){
			carry=1;
			sum=0;
		}else{
			carry=0;
		}
		M_[i]=sum;
	}
	
}

void arithmeticShiftRight(){
	int i=0;
	q=booth[15];
	for(i=15;i>0;i--){
		booth[i]=booth[i-1];
	}	
}

int dec()
{
	int result=0,i=15,b=0;
	while(i>0&&b<15)
	{
		result+=(booth[i]*pow(2,b));
		b++,i--;
	}
	if(booth[0]==1)
		return (-32768+result);
	else
		return result;
}
/*FUNCTIONS END*/

