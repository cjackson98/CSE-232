#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;

#include "proj10_mapset.h"

int main (){

  MapSet<string,long> ms1({ {"bill",1},{"alan",2},{"abby",3} });
  cout<<"ms1 good"<<endl;
  MapSet<string,long> ms2({ {"alan",4},{"abby", 5},{"john",7} });
  cout<<"ms2 good"<<endl;
  MapSet<string,long> ms3({ {"abby",5}, {"alan",17} });
  cout<<"ms3 good"<<endl;
  
  /*MapSet<string,long> ms_intersect = ms1.mapset_intersection(ms2);
  ostringstream oss;
  oss << ms_intersect;
  string result1 = oss.str();
  string ans1 = "abby:3, alan:2";
  cout<<result1<<endl;//ASSERT_EQ(result1, ans1);
  cout<<ans1<<endl;
  cout<<endl;
  
  oss.str("");
  ms_intersect = ms2.mapset_intersection(ms1);
  oss << ms_intersect;
  string result2 = oss.str();
  string ans2 = "abby:5, alan:4";
  cout<<result2<<endl;//ASSERT_EQ(result2, ans2); 
  cout<<ans1<<endl;*/

}

