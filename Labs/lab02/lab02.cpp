#include <iostream>  
	using std::cout; using std::endl; using std::cin;
 
  int main( ) {
     
     long number;
     long total;
     long ctr=0;
     long ctr2=0;
     long ctr3=0;
     
     
     cin >> number;
	while(1){
		if(number<=0){
			cout<<"Error"<<endl;
			break;
		}
	    if (number<10){
	        ctr=0;
	        break;
	    }
		else{
            ctr++;
			while(number>0){
				total=total+number%10;
				number=number/10;
			}
		number=total;
		total=0;
        ctr2++;
			if(number<10)
				break;
		}
		ctr3++;
	}
if(number>0){
cout<<ctr<<endl;
//cout<<endl;
//cout<<ctr2<<endl;
cout<<number<<endl;
}
}