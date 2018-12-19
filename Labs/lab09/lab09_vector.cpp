#include "lab09_vector.h"
#include <iostream>
#include <sstream>
using std::ostringstream;
#include <cmath>

MathVector::MathVector(long x1, long y1){
	x=x1;
	y=y1;
}

/*If V1 is (x,y) and V2 is (a,b), the V+W is a new 
MathVector with  the values (x+a, y+b)*/

MathVector MathVector::add(const MathVector& v){
    MathVector result;
    
    result.x = x + v.x;
    result.y = y + v.y;
    
    return result;
}
  
/*If V1 is (x,y), then V*n is (x*n,y*n), returning a
new MathVector*/
MathVector MathVector::mult(long mult){
    MathVector result;
    
    result.x = x * mult;
    result.y = y * mult;
    
    return result;
}

/*There are two possibilities, dot product or cross product.
We’ll do dot product. If V=(x,y) and W=(a,b), 
then V*W = x*a + y*b, a scalar. Thus the dot product returns 
a scalar type long, not a MathVector*/
long MathVector::mult(const MathVector& v){
    long a=v.x,b=v.y,result;
    
    result = (x*a)+(y*b);
    
    return result;
}
  
/*MathVector magnitude. The magnitude based on the Pythagorean
theorem. For V=(x,y), the magnitude is sqrt(x^2 + y^2).*/
double MathVector::magnitude(){
      double magnitude;
      magnitude = sqrt((x*x)+(y*y));
      return magnitude;
}

string vec_to_str(const MathVector& v){
    ostringstream oss;
    oss<<v.x<<":"<<v.y;
    return oss.str();
}