int f(int n){
	int fib[1000];//コメントいれます！
	int i;
	for(i=0;i<1000;i=/* じゃま～＾＾ */i+1) fib[i] = 1;//compound-statementでなくてもforが使えるかの検証。
	for(i=2;i<1000;i=i+1){
		int k;
		int l;
		k = fib[i-1];
		l = fib[i-2];
		fib[i] = k+l;
	}
	return fib[n];
}
