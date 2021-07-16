#include <stdio.h> 
#include <limits.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000
#define MAXLINES 5000
//#define swap(t,x,y) (t)=(x); (x)=(y); (y)=(t);

int getLine(char s[], int lim){
	int c, i;
	for(i=0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++) s[i]=c;
	if(c == '\n'){s[i]=c; ++i;}	
	s[i]='\0';
	return i;
}

void copy(char to[], char from[]){
	int i=0; 
	while((to[i]=from[i]) != '\0') ++i;

}

void swap(char *v[], int i, int j){
	char *t;
	
	t=v[i];
	v[i]=v[j];
	v[j]=t;

}

int htoi(char s[]){
	int sum=0;
	int i=0, adjust=0;
	if (s[i]=='0' && s[i+1]=='x'){i+=2; adjust=2;} 
	for(; s[i] != '\0'; ++i){
		if('0' <= s[i] && s[i] <='9') sum+= ((s[i] - '0') << 4*(i-adjust));
		else{
			switch(tolower(s[i])){
				case 'a':
					sum+= (10 << 4*(i-adjust));
					break;
				case 'b':
					sum+=(11 << 4*(i-adjust));
					break;
				case 'c':
					sum+=(12 << 4*(i-adjust));
					break;
				case 'd':
					sum+=(13 << 4*(i-adjust));
					break;
				case 'e':
					sum+=(14 << 4*(i-adjust));
					break;
				case 'f':
					sum+=(15 << 4*(i-adjust));
					break;
				
			}
		}
	}
	return sum;
	

}

void squeeze(char s1[], char s2[]){
	int i, j;
	for(i = j =0; s1[i] != '\0'; i++){
	//if s1[i] in s2
		int ins2= 0;
		for(int p=0; s2[p] != '\0'; p++){
			if(s2[p]==s1[i]){ins2=1; break;}
		}
		if(ins2 == 0){
			s1[j++]=s1[i];
		}
	}
	s1[j]='\0';
}

unsigned setbits(unsigned x, unsigned y, int p, int n){
	y = (y & ~(~0 << n)) << (p-n);
	unsigned bitmask = (~0 << p) | (~(~0 << (p-n)));
	x = x & bitmask;
	return x | y;


}

unsigned invert(unsigned x, int p, int n){
	unsigned bitmask = (~0 << p) | (~(~0 << (p-n)));
	printf("%u\n", bitmask);
	unsigned ix = ~x & ~bitmask;
	x = x & bitmask;
	return x | ix;

}

unsigned bitcount(unsigned x){
	int b=0;
	while(x > 0){
		++b;
		x &= (x-1);
	}
	return b;
}

char * expand(char s1[], char s2[]){
	int i, j; i=j=0;
	int s, e; s=e=0;
	for(i; s1[i] != '\0'; i++){
		if(s1[i-1]=='-') e=s1[i];
		else if(s1[i+1]=='-') s=s1[i];
		if(s!=0 && e!=0){
			printf("ran: %c\n", s);
			for(j; s <= e; j++){
				s2[j]=s;
				s++;
				
			}
			s=e; e=0;
		}
	} j++; s2[j]='\0';
	printf("in: %s, out: %s\n", s1, s2);
	return s2;
}

void reverse(char s[]){
	int j, i; j=i=0;
	for(j; s[j] != '\0'; j++); j--;
	for(i, j; i < j; i++, j--){
		int t=s[i];
		s[i]=s[j]; s[j]=t; /* swap elements */
	}
}

/* Helper for recursive reverse */
void rrv(char s[] ,int right, int left){
	if(right == left) return;
	rrv(s, right-1, left+1);
	int tmp = s[right]; s[right]=s[left]; s[left]=tmp;

}

void rreverse(char s[]){
	int right=0; while(s[right+1] != '\0') right++;
	int left = 0;
	rrv(s, right, left);
}



void itoa(int n, char s[]){
	int i, sign;
	
	if((sign =  (n > 0) ? 1 : -1) < 0); /* if n neg make it pos */
	i=0;
	do{
		s[i++]= (sign*(n%(sign*10))) + '0';
	} while((n/=10) != 0);

	if(sign < 0) s[i++]='-';
	s[i]='\0';
	reverse(s);
}

void ritoa(int n, char s[]){
	int i=0, sign;
	

	if((sign =  (n > 0) ? 1 : -1) < 0) s[i++]='-'; /* if n neg make it pos */

	if(n){
		ritoa(n/10, s);
		while(s[i]!=0) i++;
		s[i++]= (sign*(n%(sign*10))) + '0';
	}

	s[i]='\0';



}

void itob(int n, char s[], int b){
	int i; i=0;
	if(b == 2){
		while(n > 0){
			if(n&1) s[i++]='1';
			n >>= 1;
		}
	} else if(b == 16){
		while(n > 0){
			/* capture first four bits of n then shift n by four and
 			   append bit value */
			unsigned fourb = (n&~(~0 << 4));
			n >>= 4;
			if(fourb < 10) s[i++] = (fourb + '0');
			else s[i++] = 'A' + fourb%10;	
			}
		reverse(s);
		}
	s[i]='\0';
	}

int strrindex(char s[], char t[]){
	int i, mi, j, k; mi=0;

	for(i=0; s[i] != '\0'; i++){
		for(j=i, k=0; t[k] != '\0' && s[j]==t[k]; j++, k++);
		if(k > 0 && t[k]=='\0' && i > mi) mi =i;  
	}
	return mi;
}

void mystrcat(char *s, char *t){
	while(*s++); s--;
	while((*s++ = *t++));
}

int strend(char *s, char *t){
	while(*s++); s--; //move to the send of string s
	for(int i=0; *(t+i); i++, s--); //move s pointer to start position based on length of t

	for(; (*s==*t); s++, t++) if(*t=='\0') return 1;
	return 0;


}

int mystrcmp(char *s, char *t){
	for(; *s == *t; s++, t++) if(*s == '\0') return 0;
	return *s - *t;

}

void qsort(char *v[], int left, int right){
	int i, last;
	
	void swap(char *v[], int i, int j);

	if(left >= right) return; //if arr contains fewer than to elements do nothing

	swap(v, left, (left+right)/2); // move the partition element (middle element) to the begining of the arr
	last = left; 
	
	for(i=left+1; i <= right; i++){
		if(mystrcmp(v[i], v[left]) < 0) swap(v, ++last, i);
		/* begin partitioning by check if element is less than partition element and
   		   moving to the position of last. Last is pre incremented on each call meaning it starts at
		   left +1 */
	}

	swap(v, left, last); /* return partition element to proper place. Since last is pre incremented what it is pointng
	 		       to is guraenteed to be < partition element */

	qsort(v, left, last-1);
	qsort(v, last+1, right); /* continue the sorting process ignoring partition element as it is already sorted */
}




/* int main ()
{	
	char itobtest [100];
	char itoatest [100];
	char reversetest[20]  = "reverse";
	rreverse(reversetest);
	itob(987, itobtest, 16);
	ritoa(-2147483648, itoatest);
	printf("test of setbits:  %u\n", setbits(227, 7, 5, 3));
	printf("test of invert: %u\n", invert(227,5 ,3));
	printf("test of bitcount: %u\n", bitcount(255));
	printf("testing itob: %s\n", itobtest);
	printf("testing strrindex: %d, %s\n", strrindex("orororor","or"), "orororor");
	printf("testing itoa: %s\n", itoatest);
	printf("testing reverse: (reverse) become %s\n", reversetest);

	swap macro test
	int t, x, y; x=2, y=5;
	printf("x:%d, y:%d\n", x, y);
	swap(t,x,y);
	printf("x:%d, y:%d\n", x, y);
	

	//concat test	
	char f[20] = "Hello"; char *l = " World!\n";
	mystrcat(f, l);
	printf("Test concat: %s\n", f);

	//strend test
	char *strendtest = "Hello World!"; char *strendtest2 = "World!";
	printf("strend test: st1(%s) st2(%s) result(%d)\n", strendtest, strendtest2, strend(strendtest, strendtest2));
}
*/
