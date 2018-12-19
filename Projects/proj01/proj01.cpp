#include <iostream>
using std::cout; using std::cin; using std::endl; using std::fixed;
#include <iomanip>
using std::setprecision;
#include <cmath>

int main(){
        double car_price,sales_tax_rate,down_payment,title_and_fees,yearly_interest_rate,number_of_months,monthly_payment,total_cost,monthly_interest_rate,n;
        std::cin>>car_price;
        std::cin>>sales_tax_rate;
        std::cin>>down_payment;
        std::cin>>title_and_fees;
        std::cin>>yearly_interest_rate;
        std::cin>>number_of_months;
        
        total_cost = (sales_tax_rate*car_price)+title_and_fees+car_price;
        total_cost = total_cost - down_payment;
        monthly_interest_rate = yearly_interest_rate/12;
        n=pow(1+monthly_interest_rate,number_of_months);
        
        monthly_payment = total_cost * ((monthly_interest_rate)*(n))/((n)-1);

        cout<<fixed<<setprecision(2);
        cout<<monthly_payment<<endl;

return 0;
}