void reverse(char s[]){
	int j, i; j=i=0;
	for(j; s[j] != '\0'; j++); j--;
	for(i, j; i < j; i++, j--){
		int t=s[i];
		s[i]=s[j]; s[j]=t; /* swap elements */
	}
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

int getLine(int s[], int lim){
	int c, i;
	for(i=0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++) s[i]=c;
	if(c == '\n'){s[i]=c; ++i;}	
	s[i]='\0';
	return i;
}
